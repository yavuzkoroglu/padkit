#include <assert.h>
#include <string.h>
#include "padkit/hash.h"
#include "padkit/indextable.h"
#include "padkit/memalloc.h"
#include "padkit/prime.h"
#include "padkit/size.h"

void constructEmpty_itbl(IndexTable table[static const 1], uint32_t const min_height, uint32_t const width) {
    assert(min_height > 2);
    assert(min_height < SZ32_MAX);
    assert(width > 0);
    assert(width < SZ32_MAX);

    table->height   = nextPrime(min_height);
    table->width    = width;
    {
        size_t const sz     = sizeof(uint32_t*) * (size_t)table->height;
        size_t const sz_row = sizeof(uint32_t) * (size_t)table->width;
        assert(sz < SZSZ_MAX);
        assert(sz_row < SZSZ_MAX);
        assert(sz / sizeof(uint32_t*) == (size_t)table->height);
        assert(sz_row / sizeof(uint32_t) == (size_t)table->width);

        table->matrix = mem_alloc(sz);
        for (uint32_t row_id = 0; row_id < table->height; row_id++) {
            table->matrix[row_id] = mem_alloc(sz_row);
            memset(table->matrix[row_id], 0xFF, sz_row);
        }
    }
}

uint32_t const* findRow_itbl(
    IndexTable table[static const 1],
    char const key[static const 1],
    uint32_t const key_len
) {
    assert(isValid_itbl(table));
    assert(key_len < SZ32_MAX);
    {
        uint_fast64_t const hashValue = hash_str(key, (size_t)key_len);
        return getRow_itbl(table, hashValue);
    }
}

void flush_itbl(IndexTable table[static const 1]) {
    size_t const sz_row = sizeof(uint32_t) * (size_t)table->width;

    assert(isValid_itbl(table));
    assert(sz_row < SZSZ_MAX);
    assert(sz_row / sizeof(uint32_t) == (size_t)table->width);

    for (uint32_t row_id = 0; row_id < table->height; row_id++)
        memset(table->matrix[row_id], 0xFF, sz_row);
}

void free_itbl(IndexTable table[static const 1]) {
    assert(isValid_itbl(table));

    for (uint32_t row_id = 0; row_id < table->height; row_id++)
        free(table->matrix[row_id]);

    free(table->matrix);
    table[0] = NOT_AN_INDEX_TABLE;
}

uint32_t const* getRow_itbl(IndexTable table[static const 1], uint_fast64_t const hashValue) {
    uint32_t const row_id = hashValue % table->height;

    assert(isValid_itbl(table));

    return table->matrix[row_id];
}

bool isValid_itbl(IndexTable const table[static const 1]) {
    if (table->height <= 2)         return 0;
    if (table->height >= SZ32_MAX)  return 0;
    if (!isPrime(table->height))    return 0;
    if (table->width == 0)          return 0;
    if (table->width >= SZ32_MAX)   return 0;
    if (table->matrix == NULL)      return 0;

    return 1;
}
