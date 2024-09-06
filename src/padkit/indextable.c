#include <assert.h>
#include <string.h>
#include "padkit/indextable.h"
#include "padkit/invalid.h"
#include "padkit/memalloc.h"
#include "padkit/prime.h"
#include "padkit/size.h"

void constructEmpty_itbl(
    IndexTable table[static const 1],
    uint32_t const min_height,
    uint32_t const max_percent_load,
    uint32_t const initial_cap
) {
    assert(min_height < SZ32_MAX);
    assert(max_percent_load > 0);
    assert(max_percent_load <= 100);
    assert(initial_cap > 0);
    assert(initial_cap < SZ32_MAX);

    constructEmpty_alist(table->mappings, sizeof(Mapping), initial_cap);

    if (min_height > 100)
        if (isPrime(min_height))
            table->height = min_height;
        else
            table->height = nextPrime(min_height);
    else
        table->height = nextPrime(100);

    assert(table->height < SZ32_MAX);

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

void flush_itbl(IndexTable table[static const 1]) {
    size_t const sz_rows = sizeof(uint32_t) * (size_t)table->height;

    assert(isValid_itbl(table));
    assert(sz_rows < SZSZ_MAX);
    assert(sz_rows / sizeof(uint32_t) == (size_t)table->height);

    flush_alist(table->mappings);
    table->load = 0;
    memset(table->rows, 0xFF, sz_rows);
}

void free_itbl(IndexTable table[static const 1]) {
    assert(isValid_itbl(table));
    free_alist(table->mappings);
    free(table->rows);
    table[0] = NOT_AN_ITBL;
}

Mapping* getFirstMapping_itbl(IndexTable const table[static const 1], uint_fast64_t const index) {
    assert(isValid_itbl(table));
    {
        uint32_t const row_id       = index % table->height;
        uint32_t const mapping_id   = table->rows[row_id];
        if (mapping_id >= table->mappings->size) {
            return NULL;
        } else {
            Mapping* mapping = get_alist(table->mappings, mapping_id);
            while (mapping->index != index) {
                if (mapping->next_id >= table->mappings->size)
                    return NULL;

                mapping = get_alist(table->mappings, mapping->next_id);
            }
            return mapping;
        }
    }
}

void grow_itbl(IndexTable table[static const 1]) {
    IndexTable grownTable[1] = { NOT_AN_ITBL };
    assert(isValid_itbl(table));
    {
        uint32_t const grownHeight = table->height << 1;
        assert(grownHeight < SZ32_MAX);
        assert(grownHeight >> 1 == table->height);
        constructEmpty_itbl(grownTable, grownHeight, table->max_percent_load, table->mappings->cap);
    }

    for (uint32_t mapping_id = 0; mapping_id < table->mappings->size; mapping_id++) {
        Mapping const* const mapping = get_alist(table->mappings, mapping_id);
        #ifndef NDEBUG
            int const insert_result =
        #endif
        insert_itbl(
            grownTable,
            mapping->index,
            mapping->value,
            ITBL_RELATION_ONE_TO_MANY,
            ITBL_BEHAVIOR_RESPECT
        );
        assert(insert_result == ITBL_INSERT_UNIQUE);
    }

    free_itbl(table);
    table[0] = grownTable[0];
}

bool insert_itbl(
    IndexTable table[static const 1],
    uint_fast64_t const index,
    uint32_t const value,
    bool const relationType,
    bool const behavior
) {
    assert(isValid_itbl(table));
    {
        uint32_t const row_id           = index % table->height;
        uint32_t const first_mapping_id = table->rows[row_id];

        if (first_mapping_id >= table->mappings->size) {
            Mapping* const mapping  = addIndeterminate_alist(table->mappings, 1);
            table->rows[row_id]     = table->mappings->size - 1;
            mapping->index          = index;
            mapping->value          = value;
            mapping->next_id        = INVALID_UINT32;

            if (table->load >= table->max_load)
                grow_itbl(table);

            table->load++;

            return ITBL_INSERT_UNIQUE;
        } else {
            Mapping* mapping = get_alist(table->mappings, first_mapping_id);
            while (
                mapping->index != index || (
                    relationType == ITBL_RELATION_ONE_TO_MANY && mapping->value != value
                )
            ) {
                if (mapping->next_id >= table->mappings->size) {
                    mapping->next_id    = table->mappings->size;
                    mapping             = addIndeterminate_alist(table->mappings, 1);
                    mapping->index      = index;
                    mapping->value      = value;
                    mapping->next_id    = INVALID_UINT32;
                    return ITBL_INSERT_UNIQUE;
                }

                mapping = get_alist(table->mappings, mapping->next_id);
            }

            if (behavior == ITBL_BEHAVIOR_REPLACE)
                mapping->value = value;

            return ITBL_INSERT_NOT_UNIQUE;
        }
    }
}

bool isValid_itbl(IndexTable const table[static const 1]) {
    if (!isValid_alist(table->mappings))                return 0;
    if (table->mappings->sz_element != sizeof(Mapping)) return 0;
    if (table->height <= 100)                           return 0;
    if (table->height >= SZ32_MAX)                      return 0;
    if (!isPrime(table->height))                        return 0;
    if (table->load >= table->max_load)                 return 0;
    if (table->max_percent_load == 0)                   return 0;
    if (table->max_percent_load > 100)                  return 0;
    if (table->max_load == 0)                           return 0;
    if (table->max_load > table->height)                return 0;
    if (table->rows == NULL)                            return 0;

    return 1;
}

Mapping* nextMapping_itbl(
    IndexTable const table[static const 1],
    Mapping const mapping[static const 1]
) {
    assert(isValid_itbl(table));
    assert(isValid_mppng(mapping));

    if (mapping->next_id >= table->mappings->size) {
        return NULL;
    } else {
        Mapping* next = get_alist(table->mappings, mapping->next_id);
        while (next->index != mapping->index) {
            if (next->next_id >= table->mappings->size)
                return NULL;

            next = get_alist(table->mappings, next->next_id);
        }
        return next;
    }
}

