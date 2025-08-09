#include <assert.h>
#include <string.h>
#include "padkit/indextable.h"
#include "padkit/intfn.h"
#include "padkit/invalid.h"
#include "padkit/implication.h"
#include "padkit/memalloc.h"
#include "padkit/size.h"

void construct_itbl(void* const p_tbl, ...) {
    va_list args;
    va_start(args, p_tbl);
    vconstruct_itbl(p_tbl, args);
    va_end(args);
}

void constructEmpty_itbl(
    IndexTable* const table,
    uint32_t const min_height,
    uint32_t const max_percent_load,
    uint32_t const initial_cap
) {
    assert(table != NULL);
    assert(min_height < SZ32_MAX);
    assert(max_percent_load > 0);
    assert(max_percent_load <= 100);
    assert(initial_cap > 0);
    assert(initial_cap < SZ32_MAX);

    constructEmpty_alist(table->mappings, sizeof(IndexMapping), initial_cap);

    if (min_height > 100)
        if (min_height % 2 == 1 && isPrime(min_height))
            table->height = min_height;
        else
            table->height = nextPrime(min_height);
    else
        table->height = nextPrime(100);

    assert(table->height < SZ32_MAX);
    assert(table->height >= min_height);

    table->load             = 0;
    table->max_percent_load = max_percent_load;
    table->max_load         = max_percent_load * (table->height / 100);

    {
        size_t const sz_rows = sizeof(uint32_t) * (size_t)table->height;
        assert(sz_rows < SZSZ_MAX);
        assert(sz_rows / sizeof(uint32_t) == (size_t)table->height);

        table->rows = mem_alloc(sz_rows);
        memset(table->rows, 0xFF, sz_rows);
    }
}

void destruct_itbl(IndexTable* const table) {
    assert(isValid_itbl(table));
    destruct_alist(table->mappings);
    free(table->rows);
    table[0] = NOT_AN_ITBL;
}

IndexMapping* findFirstMapping_itbl(
    IndexTable const* const table,
    uint_fast64_t const index
) {
    assert(isValid_itbl(table));
    {
        uint32_t const row_id       = index % table->height;
        uint32_t const mapping_id   = table->rows[row_id];
        if (mapping_id >= table->mappings->len) {
            return NULL;
        } else {
            IndexMapping* mapping = get_alist(table->mappings, mapping_id);
            while (mapping->index != index) {
                if (mapping->next_id >= table->mappings->len)
                    return NULL;

                mapping = get_alist(table->mappings, mapping->next_id);
            }
            return mapping;
        }
    }
}

void flush_itbl(IndexTable* const table) {
    size_t const sz_rows = sizeof(uint32_t) * (size_t)table->height;

    assert(isValid_itbl(table));
    assert(sz_rows < SZSZ_MAX);
    assert(sz_rows / sizeof(uint32_t) == (size_t)table->height);

    flush_alist(table->mappings);
    table->load = 0;
    memset(table->rows, 0xFF, sz_rows);
}

void grow_itbl(IndexTable* const table) {
    IndexTable grownTable[1] = { NOT_AN_ITBL };
    assert(isValid_itbl(table));
    {
        uint32_t const grownHeight = table->height << 1;
        assert(grownHeight < SZ32_MAX);
        assert(grownHeight >> 1 == table->height);
        constructEmpty_itbl(grownTable, grownHeight, table->max_percent_load, table->mappings->cap);
    }

    for (uint32_t mapping_id = 0; mapping_id < table->mappings->len; mapping_id++) {
        IndexMapping const* const mapping = get_alist(table->mappings, mapping_id);
        #ifndef NDEBUG
            bool const insert_result =
        #endif
        insert_itbl(
            NULL,
            grownTable,
            mapping->index,
            mapping->value,
            ITBL_RELATION_ONE_TO_MANY,
            ITBL_BEHAVIOR_RESPECT
        );
        assert(insert_result == ITBL_INSERT_UNIQUE);
    }

    destruct_itbl(table);
    table[0] = grownTable[0];
}

bool insert_itbl(
    IndexMapping* mapping,
    IndexTable* const table,
    uint_fast64_t const index,
    uint32_t const value,
    bool const relationType,
    bool const behavior
) {
    (void)relationType;
    assert(isValid_itbl(table));
    {
        uint32_t const row_id           = index % table->height;
        uint32_t const first_mapping_id = table->rows[row_id];

        if (first_mapping_id >= table->mappings->len) {
            table->rows[row_id] = table->mappings->len;
            mapping             = addIndeterminate_alist(table->mappings);
            mapping->index      = index;
            mapping->value      = value;
            mapping->next_id    = INVALID_UINT32;

            if (table->load >= table->max_load)
                grow_itbl(table);

            table->load++;

            return ITBL_INSERT_UNIQUE;
        } else {
            bool unique = ITBL_INSERT_UNIQUE;
            mapping     = get_alist(table->mappings, first_mapping_id);
            while (1) {
                if (mapping->index == index) {
                    if (relationType == ITBL_RELATION_ONE_TO_ONE) {
                        if (behavior == ITBL_BEHAVIOR_REPLACE) mapping->value = value;
                        return ITBL_INSERT_NOT_UNIQUE;
                    } else if (mapping->value == value) { /* relationType == ITBL_RELATION_ONE_TO_MANY */
                        if (behavior == ITBL_BEHAVIOR_REPLACE) return ITBL_INSERT_NOT_UNIQUE;
                        unique = ITBL_INSERT_NOT_UNIQUE;
                    }
                }
                if (mapping->next_id >= table->mappings->len) {
                    mapping->next_id    = table->mappings->len;
                    mapping             = addIndeterminate_alist(table->mappings);
                    mapping->index      = index;
                    mapping->value      = value;
                    mapping->next_id    = INVALID_UINT32;
                    return unique;
                }
                mapping = get_alist(table->mappings, mapping->next_id);
            }
        }
    }
}

bool isValid_itbl(IndexTable const* const table) {
    if (table == NULL)                                      return 0;
    if (!isValid_alist(table->mappings))                    return 0;
    if (table->mappings->sz_elem != sizeof(IndexMapping))   return 0;
    if (table->height <= 100)                               return 0;
    if (table->height >= SZ32_MAX)                          return 0;
    if (!isPrime(table->height))                            return 0;
    if (table->load >= table->max_load)                     return 0;
    if (table->max_percent_load == 0)                       return 0;
    if (table->max_percent_load > 100)                      return 0;
    if (table->max_load == 0)                               return 0;
    if (table->max_load > table->height)                    return 0;
    if (table->rows == NULL)                                return 0;

    return 1;
}

IndexMapping* nextMapping_itbl(
    IndexTable const* const table,
    IndexMapping const* const mapping
) {
    assert(isValid_itbl(table));

    if (mapping->next_id >= table->mappings->len) {
        return NULL;
    } else {
        IndexMapping* next = get_alist(table->mappings, mapping->next_id);
        while (next->index != mapping->index) {
            if (next->next_id >= table->mappings->len)
                return NULL;

            next = get_alist(table->mappings, next->next_id);
        }
        return next;
    }
}

void vconstruct_itbl(
    void* const p_tbl,
    va_list args
) {
    IndexTable* const table         = (IndexTable*)p_tbl;
    uint32_t const min_height       = va_arg(args, uint32_t);
    uint32_t const max_percent_load = va_arg(args, uint32_t);
    uint32_t const initial_cap      = va_arg(args, uint32_t);
    constructEmpty_itbl(table, min_height, max_percent_load, initial_cap);
}
