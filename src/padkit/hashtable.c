#include <assert.h>
#include <string.h>
#include "padkit/hashmapping.h"
#include "padkit/hashtable.h"
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
