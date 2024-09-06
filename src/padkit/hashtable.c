#include <assert.h>
#include <string.h>
#include "padkit/hashmapping.h"
#include "padkit/hashtable.h"
#include "padkit/invalid.h"
#include "padkit/memalloc.h"
#include "padkit/prime.h"
#include "padkit/size.h"

void constructEmpty_htbl(
    HashTable table[static const 1],
    uint32_t const min_height,
    uint32_t const max_percent_load,
    uint32_t const initial_cap
) {
    assert(min_height < SZ32_MAX);
    assert(max_percent_load > 0);
    assert(max_percent_load <= 100);
    assert(initial_cap > 0);
    assert(initial_cap < SZ32_MAX);

    constructEmpty_alist(table->mappings, sizeof(HashMapping), initial_cap);

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

void flush_htbl(HashTable table[static const 1]) {
    size_t const sz_rows = sizeof(uint32_t) * (size_t)table->height;

    assert(isValid_htbl(table));
    assert(sz_rows < SZSZ_MAX);
    assert(sz_rows / sizeof(uint32_t) == (size_t)table->height);

    flush_alist(table->mappings);
    table->load = 0;
    memset(table->rows, 0xFF, sz_rows);
}

void free_htbl(HashTable table[static const 1]) {
    assert(isValid_htbl(table));
    free_alist(table->mappings);
    free(table->rows);
    table[0] = NOT_AN_HTBL;
}

HashMapping* getFirstMapping_htbl(HashTable const table[static const 1], uint_fast64_t const hashValue) {
    assert(isValid_htbl(table));
    {
        uint32_t const row_id       = hashValue % table->height;
        uint32_t const mapping_id   = table->rows[row_id];
        if (mapping_id >= table->mappings->size) {
            return NULL;
        } else {
            HashMapping* mapping = get_alist(table->mappings, mapping_id);
            while (mapping->hashValue != hashValue) {
                if (mapping->next_id >= table->mappings->size)
                    return NULL;

                mapping = get_alist(table->mappings, mapping->next_id);
            }
            return mapping;
        }
    }
}

bool isValid_htbl(HashTable const table[static const 1]) {
    if (!isValid_alist(table->mappings))                    return 0;
    if (table->mappings->sz_element != sizeof(HashMapping)) return 0;
    if (table->height <= 100)                               return 0;
    if (table->height >= SZ32_MAX)                          return 0;
    if (table->load >= table->max_load)                     return 0;
    if (table->max_percent_load == 0)                       return 0;
    if (table->max_percent_load > 100)                      return 0;
    if (table->max_load == 0)                               return 0;
    if (table->max_load > table->height)                    return 0;
    if (table->rows == NULL)                                return 0;

    return 1;
}

HashMapping* nextMapping_htbl(
    HashTable const table[static const 1],
    HashMapping const mapping[static const 1]
) {
    assert(isValid_htbl(table));
    assert(isValid_hmpng(mapping));

    if (mapping->next_id >= table->mappings->size) {
        return NULL;
    } else {
        HashMapping* next = get_alist(table->mappings, mapping->next_id);
        while (next->hashValue != mapping->hashValue) {
            if (next->next_id >= table->mappings->size)
                return NULL;

            next = get_alist(table->mappings, next->next_id);
        }
        return next;
    }
}

void grow_htbl(HashTable table[static const 1]) {
    HashTable grownTable[1] = { NOT_AN_HTBL };
    assert(isValid_htbl(table));
    {
        uint32_t const grownHeight = table->height << 1;
        assert(grownHeight < SZ32_MAX);
        assert(grownHeight >> 1 == table->height);
        constructEmpty_htbl(grownTable, grownHeight, table->max_percent_load, table->mappings->cap);
    }

    for (uint32_t mapping_id = 0; mapping_id < table->mappings->size; mapping_id++) {
        HashMapping const* const mapping = get_alist(table->mappings, mapping_id);
        #ifndef NDEBUG
            int const insert_result =
        #endif
        insert_htbl(
            grownTable,
            mapping->hashValue,
            mapping->mappedValue,
            HTBL_RELATION_ONE_TO_MANY,
            HTBL_BEHAVIOR_RESPECT
        );
        assert(insert_result == HTBL_INSERT_UNIQUE);
    }

    free_htbl(table);
    table[0] = grownTable[0];
}

bool insert_htbl(
    HashTable table[static const 1],
    uint_fast64_t const hashValue,
    uint32_t const mappedValue,
    bool const relationType,
    bool const behavior
) {
    assert(isValid_htbl(table));
    {
        uint32_t const row_id           = hashValue % table->height;
        uint32_t const first_mapping_id = table->rows[row_id];

        if (first_mapping_id >= table->mappings->size) {
            HashMapping* const mapping  = addIndeterminate_alist(table->mappings, 1);
            table->rows[row_id]         = table->mappings->size - 1;
            mapping->hashValue          = hashValue;
            mapping->mappedValue        = mappedValue;
            mapping->next_id            = INVALID_UINT32;

            if (table->load >= table->max_load) {
                grow_htbl(table);
                table->load++;
            }

            return HTBL_INSERT_UNIQUE;
        } else {
            HashMapping* mapping = get_alist(table->mappings, first_mapping_id);
            while (
                mapping->hashValue != hashValue || (
                    relationType == HTBL_RELATION_ONE_TO_MANY && mapping->mappedValue != mappedValue
                )
            ) {
                if (mapping->next_id >= table->mappings->size) {
                    mapping->next_id        = table->mappings->size;
                    mapping                 = addIndeterminate_alist(table->mappings, 1);
                    mapping->hashValue      = hashValue;
                    mapping->mappedValue    = mappedValue;
                    mapping->next_id        = INVALID_UINT32;
                    return HTBL_INSERT_UNIQUE;
                }

                mapping = get_alist(table->mappings, mapping->next_id);
            }

            if (behavior == HTBL_BEHAVIOR_REPLACE)
                mapping->mappedValue = mappedValue;

            return HTBL_INSERT_NOT_UNIQUE;
        }
    }
}
