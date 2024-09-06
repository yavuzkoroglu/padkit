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

    HashMapping* getFirstMapping_htbl(HashTable const table[static const 1], uint_fast64_t const hashValue);

    void grow_htbl(HashTable table[static const 1]);

    #define HTBL_BEHAVIOR_REPLACE       0
    #define HTBL_BEHAVIOR_RESPECT       1
    #define HTBL_RELATION_ONE_TO_ONE    0
    #define HTBL_RELATION_ONE_TO_MANY   1
    #define HTBL_INSERT_UNIQUE          0
    #define HTBL_INSERT_NOT_UNIQUE      1
    bool insert_htbl(
        HashTable table[static const 1],
        uint_fast64_t const hashValue,
        uint32_t const mappedValue,
        bool const relationType,
        bool const behavior
    );

    bool isValid_htbl(HashTable const table[static const 1]);

    HashMapping* nextMapping_htbl(
        HashTable const table[static const 1],
        HashMapping const mapping[static const 1]
    );
#endif
