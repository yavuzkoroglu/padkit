#ifndef PADKIT_HASHTABLE_H
    #define PADKIT_HASHTABLE_H
    #include "padkit/arraylist.h"

    #define NOT_AN_HTBL                             ((HashTable){ { NOT_AN_ALIST }, 0, 0, 0, 0, NULL })

    #ifndef HTBL_RECOMMENDED_MAX_PERCENT_LOAD
        #define HTBL_RECOMMENDED_MAX_PERCENT_LOAD   (75)
    #endif

    #ifndef HTBL_RECOMMENDED_MIN_HEIGHT
        #define HTBL_RECOMMENDED_MIN_HEIGHT         (131071)
    #endif

    #define HTBL_RECOMMENDED_PARAMETERS         \
        HTBL_RECOMMENDED_MIN_HEIGHT,            \
        HTBL_RECOMMENDED_MAX_PERCENT_LOAD,      \
        ALIST_RECOMMENDED_INITIAL_CAP

    typedef struct HashTableBody {
        ArrayList   mappings[1];
        uint32_t    height;
        uint32_t    load;
        uint32_t    max_percent_load;
        uint32_t    max_load;
        uint32_t*   rows;
    } HashTable;

    void constructEmpty_htbl(
        HashTable table[static const 1],
        uint32_t const min_height,
        uint32_t const max_percent_load,
        uint32_t const initial_cap
    );

    void flush_htbl(HashTable table[static const 1]);

    void free_htbl(HashTable table[static const 1]);

    bool isValid_htbl(HashTable const table[static const 1]);
#endif
