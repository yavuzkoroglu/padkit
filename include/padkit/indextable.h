#ifndef INDEXTABLE_H
    #define INDEXTABLE_H
    #include <stdbool.h>
    #include <stdint.h>

    #define NOT_AN_INDEX_TABLE  ((IndexTable){ 0, 0, NULL })

    typedef struct IndexTableBody {
        uint32_t height;
        uint32_t width;
        uint32_t** matrix;
    } IndexTable;

    void constructEmpty_itbl(IndexTable table[static const 1], uint32_t const min_height, uint32_t const width);

    uint32_t const* findRow_itbl(
        IndexTable table[static const 1],
        char const key[static const 1],
        uint32_t const key_len
    );

    void flush_itbl(IndexTable table[static const 1]);

    void free_itbl(IndexTable table[static const 1]);

    uint32_t const* getRow_itbl(IndexTable table[static const 1], uint_fast64_t const hashValue);

    bool isValid_itbl(IndexTable const table[static const 1]);
#endif
