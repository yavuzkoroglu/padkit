#ifndef PADKIT_CHUNKTABLE_H
    #define PADKIT_CHUNKTABLE_H
    #include "padkit/chunk.h"

    #define NOT_AN_INDEXED_ITEM                     ((IndexedItem){ 0, 0, 0, NULL })
    #define NOT_A_CTBL                              ((ChunkTable){ NOT_A_CHUNK, 0, 0, 0, 0, NULL })

    #ifndef CTBL_RECOMMENDED_MAX_PERCENT_LOAD
        #define CTBL_RECOMMENDED_MAX_PERCENT_LOAD   (75)
    #endif

    #ifndef CTBL_RECOMMENDED_MIN_HEIGHT
        #define CTBL_RECOMMENDED_MIN_HEIGHT         (131071)
    #endif

    #define CTBL_RECOMMENDED_PARAMETERS             \
        CTBL_RECOMMENDED_MIN_HEIGHT,                \
        CTBL_RECOMMENDED_MAX_PERCENT_LOAD,          \
        CHUNK_RECOMMENDED_PARAMETERS

    typedef struct IndexedItemBody {
        uint_fast64_t   index;
        uint32_t        next_id;
        uint32_t        sz;
        char            data[];
    } IndexedItem;

    typedef struct ChunkTableBody {
        Chunk       indexedItems;
        uint32_t    height;
        uint32_t    load;
        uint32_t    max_percent_load;
        uint32_t    max_load;
        uint32_t*   rows;
    } ChunkTable;

    bool areEqual_iditm(
        IndexedItem const item[static const 1],
        uint32_t const sz_item, void const* const restrict ptr_item
    );

    void constructEmpty_ctbl(
        ChunkTable table[static const 1],
        uint32_t const min_height,
        uint32_t const max_percent_load,
        uint32_t const initial_cap_area,
        uint32_t const initial_cap_len
    );

    bool contains_ctbl(
        ChunkTable const table[static const 1], uint_fast64_t const index,
        uint32_t const sz_item, void const* const ptr_item
    );

    void flush_ctbl(ChunkTable table[static const 1]);

    void free_ctbl(ChunkTable table[static const 1]);

    IndexedItem* getFirst_ctbl(ChunkTable const table[static const 1], uint_fast64_t const index);

    void grow_ctbl(ChunkTable table[static const 1]);

    #define CTBL_BEHAVIOR_REPLACE       0
    #define CTBL_BEHAVIOR_RESPECT       1
    #define CTBL_RELATION_ONE_TO_ONE    0
    #define CTBL_RELATION_ONE_TO_MANY   1
    #define CTBL_INSERT_UNIQUE          0
    #define CTBL_INSERT_NOT_UNIQUE      1
    bool insert_ctbl(
        ChunkTable table[static const 1],
        uint_fast64_t const index,
        uint32_t const sz_item,
        void const* const restrict ptr_item,
        bool const relationType,
        bool const behavior
    );

    bool isValid_ctbl(ChunkTable const table[static const 1]);

    bool isValid_iditm(IndexedItem const item[static const 1]);

    IndexedItem* nextItem_ctbl(
        ChunkTable const table[static const 1],
        IndexedItem const item[static const 1]
    );
#endif
