#include <assert.h>
#include <string.h>
#include "padkit/chunktable.h"
#include "padkit/invalid.h"
#include "padkit/memalloc.h"
#include "padkit/prime.h"
#include "padkit/size.h"

bool areEqual_iditm(
    IndexedItem const item[static const 1],
    uint32_t const sz_item, void const* const restrict ptr_item
) {
    assert(isValid_iditm(item));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX);
    assert(ptr_item != NULL);

    if (sz_item != item->sz)                        return 0;
    if (memcmp(item->data, ptr_item, sz_item) != 0) return 0;

    return 1;
}

void constructEmpty_ctbl(
    ChunkTable table[static const 1],
    uint32_t const min_height,
    uint32_t const max_percent_load,
    uint32_t const initial_cap_area,
    uint32_t const initial_cap_len
) {
    assert(min_height < SZ32_MAX);
    assert(max_percent_load > 0);
    assert(max_percent_load <= 100);
    assert(initial_cap_area > 0);
    assert(initial_cap_area < SZ32_MAX);
    assert(initial_cap_len > 0);
    assert(initial_cap_len < SZ32_MAX);

    constructEmpty_chunk(table->indexedItems, initial_cap_area, initial_cap_len);

    if (min_height > 100)
        if (min_height % 2 == 1 && isPrime(min_height))
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

void flush_ctbl(ChunkTable table[static const 1]) {
    size_t const sz_rows = sizeof(uint32_t) * (size_t)table->height;

    assert(isValid_ctbl(table));
    assert(sz_rows < SZSZ_MAX);
    assert(sz_rows / sizeof(uint32_t) == (size_t)table->height);

    flush_chunk(table->indexedItems);
    table->load = 0;
    memset(table->rows, 0xFF, sz_rows);
}

bool contains_ctbl(
    ChunkTable const table[static const 1], uint_fast64_t const index,
    uint32_t const sz_item, void const* const ptr_item
) {
    assert(isValid_ctbl(table));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX);
    assert(ptr_item != NULL);

    for (
        IndexedItem* item = getFirst_ctbl(table, index);
        item != NULL;
        item = nextItem_ctbl(table, item);
    ) {
        assert(isValid_iditm(item));
        if (areEqual_iditm(item, sz_item, ptr_item))
            return 1;
    }

    return 0;
}

void free_ctbl(ChunkTable table[static const 1]) {
    assert(isValid_ctbl(table));
    free_chunk(table->indexedItems);
    free(table->rows);
    table[0] = NOT_A_CTBL;
}

IndexedItem* getFirst_ctbl(ChunkTable const table[static const 1], uint_fast64_t const index) {
    assert(isValid_ctbl(table));
    {
        uint32_t const row_id   = index % table->height;
        uint32_t const item_id  = table->rows[row_id];
        if (item_id >= LEN_CHUNK(table->indexedItems)) {
            return NULL;
        } else {
            IndexedItem* item = get_chunk(table->indexedItems, item_id);
            while (item->index != index) {
                if (item->next_id >= LEN_CHUNK(table->indexedItems))
                    return NULL;

                item = get_chunk(table->indexedItems, item->next_id);
            }
            return item;
        }
    }
}

void grow_itbl(ChunkTable table[static const 1]) {
    ChunkTable grownTable[1] = { NOT_A_CTBL };
    assert(isValid_ctbl(table));
    {
        uint32_t const grownHeight = table->height << 1;
        assert(grownHeight < SZ32_MAX);
        assert(grownHeight >> 1 == table->height);
        constructEmpty_ctbl(
            grownTable, grownHeight, table->max_percent_load,
            AREA_CHUNK(table->indexedItems), LEN_CHUNK(table->indexedItems)
        );
    }

    for (uint32_t item_id = 0; item_id < LEN_CHUNK(table->indexedItems); item_id++) {
        IndexedItem const* const item = get_chunk(table->indexedItems, item_id);
        #ifndef NDEBUG
            int const insert_result =
        #endif
        insert_ctbl(
            grownTable,
            item->index,
            item->sz,
            item->ptr,
            CTBL_RELATION_ONE_TO_MANY,
            CTBL_BEHAVIOR_RESPECT
        );
        assert(insert_result == CTBL_INSERT_UNIQUE);
    }

    free_ctbl(table);
    table[0] = grownTable[0];
}

bool insert_ctbl(
    IndexTable table[static const 1],
    uint_fast64_t const index,
    uint32_t const sz_item,
    void const* const restrict ptr_item,
    bool const relationType,
    bool const behavior
) {
    assert(isValid_ctbl(table));
    assert(sz_item > 0);
    assert(sz_item < SZ32_MAX);
    {
        uint32_t const row_id           = index % table->height;
        uint32_t const first_item_id    = table->rows[row_id];

        if (first_item_id >= LEN_CHUNK(table->indexedItems)) {
            uint32_t const sz_total = sz_item + sizeof(IndexedItem);
            IndexedItem* const item = addIndeterminateItem_chunk(table->indexedItems, sz_total);
            table->rows[row_id]     = LEN_CHUNK(table->indexedItems) - 1;
            item->index             = index;
            item->next_id           = INVALID_UINT32;
            item->sz                = sz_item;
            if (ptr_item != NULL)
                memcpy(item->data, ptr_item, sz_item);

            if (table->load >= table->max_load)
                grow_ctbl(table);

            table->load++;

            return CTBL_INSERT_UNIQUE;
        } else {
            IndexedItem* item = get_chunk(table->indexedItems, first_item_id);
            while (
                item->index != index || (
                    relationType == CTBL_RELATION_ONE_TO_MANY &&
                    !areEqual_iditm(item, sz_item, ptr_item)
                )
            ) {
                if (item->next_id >= LEN_CHUNK(table->indexedItems) - 1) {
                    uint32_t const sz_total = sz_item + sizeof(IndexedItem);
                    item->next_id           = LEN_CHUNK(table->indexedItems);
                    item                    = addIndeterminateItem_chunk(table->indexedItems, sz_total);
                    item->index             = index;
                    item->next_id           = INVALID_UINT32;
                    memcpy
                    return CTBL_INSERT_UNIQUE;
                }

                mapping = get_alist(table->mappings, mapping->next_id);
            }

            if (behavior == CTBL_BEHAVIOR_REPLACE) {
                assert(!overlaps_ptr(item->data, ptr_item, item->sz, sz_item));
                
            } else if (relationType == ITBL_RELATION_ONE_TO_MANY) { /* Also ITBL_BEHAVIOR_RESPECT */
                while (mapping->next_id < table->mappings->size)
                    mapping = get_alist(table->mappings, mapping->next_id);

                mapping->next_id    = table->mappings->size;
                mapping             = addIndeterminate_alist(table->mappings, 1);
                mapping->index      = index;
                mapping->value      = value;
                mapping->next_id    = INVALID_UINT32;
                return ITBL_INSERT_NOT_UNIQUE;
            }

            return ITBL_INSERT_NOT_UNIQUE;
        }
    }
}

bool isValid_itbl(IndexTable const table[static const 1]) {
    if (!isValid_alist(table->mappings))                        return 0;
    if (table->mappings->sz_element != sizeof(IndexMapping))    return 0;
    if (table->height <= 100)                                   return 0;
    if (table->height >= SZ32_MAX)                              return 0;
    if (!isPrime(table->height))                                return 0;
    if (table->load >= table->max_load)                         return 0;
    if (table->max_percent_load == 0)                           return 0;
    if (table->max_percent_load > 100)                          return 0;
    if (table->max_load == 0)                                   return 0;
    if (table->max_load > table->height)                        return 0;
    if (table->rows == NULL)                                    return 0;

    return 1;
}

bool isValid_iditm(IndexedItem const item[static const 1]) {
    if (item->sz == 0)          return 0;
    if (item->sz >= SZ32_MAX)   return 0;
    if (item->data == NULL)     return 0;

    return 1;
}

IndexMapping* nextMapping_itbl(
    IndexTable const table[static const 1],
    IndexMapping const mapping[static const 1]
) {
    assert(isValid_itbl(table));

    if (mapping->next_id >= table->mappings->size) {
        return NULL;
    } else {
        IndexMapping* next = get_alist(table->mappings, mapping->next_id);
        while (next->index != mapping->index) {
            if (next->next_id >= table->mappings->size)
                return NULL;

            next = get_alist(table->mappings, next->next_id);
        }
        return next;
    }
}

