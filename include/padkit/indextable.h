#ifndef PADKIT_INDEXTABLE_H
    #define PADKIT_INDEXTABLE_H
    #include "padkit/arraylist.h"
    #include "padkit/invalid.h"

    #define NOT_AN_IMAPPING                         ((IndexMapping){ 0, 0, INVALID_UINT32 })
    #define NOT_AN_ITBL                             ((IndexTable){ { NOT_AN_ALIST }, 0, 0, 0, 0, NULL })

    #ifndef ITBL_RECOMMENDED_MAX_PERCENT_LOAD
        #define ITBL_RECOMMENDED_MAX_PERCENT_LOAD   (75)
    #endif

    #ifndef ITBL_RECOMMENDED_MIN_HEIGHT
        #define ITBL_RECOMMENDED_MIN_HEIGHT         (131071)
    #endif

    #define ITBL_RECOMMENDED_PARAMETERS         \
        ITBL_RECOMMENDED_MIN_HEIGHT,            \
        ITBL_RECOMMENDED_MAX_PERCENT_LOAD,      \
        ALIST_RECOMMENDED_INITIAL_CAP

    typedef struct IndexMappingBody {
        uint_fast64_t   index;
        uint32_t        value;
        uint32_t        next_id;
    } IndexMapping;

    typedef struct IndexTableBody {
        ArrayList   mappings[1];
        uint32_t    height;
        uint32_t    load;
        uint32_t    max_percent_load;
        uint32_t    max_load;
        uint32_t*   rows;
    } IndexTable;

    void constructEmpty_itbl(
        IndexTable table[static const 1],
        uint32_t const min_height,
        uint32_t const max_percent_load,
        uint32_t const initial_cap
    );

    void flush_itbl(IndexTable table[static const 1]);

    void free_itbl(IndexTable table[static const 1]);

    IndexMapping* getFirstMapping_itbl(IndexTable const table[static const 1], uint_fast64_t const index);

    void grow_itbl(IndexTable table[static const 1]);

    #define ITBL_BEHAVIOR_REPLACE       0
    #define ITBL_BEHAVIOR_RESPECT       1
    #define ITBL_RELATION_ONE_TO_ONE    0
    #define ITBL_RELATION_ONE_TO_MANY   1
    #define ITBL_INSERT_UNIQUE          0
    #define ITBL_INSERT_NOT_UNIQUE      1
    bool insert_itbl(
        IndexTable table[static const 1],
        uint_fast64_t const index,
        uint32_t const value,
        bool const relationType,
        bool const behavior
    );

    bool isValid_itbl(IndexTable const table[static const 1]);

    IndexMapping* nextMapping_itbl(
        IndexTable const table[static const 1],
        IndexMapping const mapping[static const 1]
    );
#endif
