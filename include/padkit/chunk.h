#ifndef PADKIT_CHUNK_H
    #define PADKIT_CHUNK_H
    #include "padkit/arraylist.h"
    #include "padkit/item.h"

    #define CHUNK_RECOMMENDED_PARAMETERS    ALIST_RECOMMENDED_INITIAL_CAP, ALIST_RECOMMENDED_INITIAL_CAP

    #define AREA_CHUNK(chunk)               (chunk[0].len)
    #define LEN_CHUNK(chunk)                (chunk[1].len)

    #define ITR_NEXT_CHUNK(chunk)           chunk += sizeof(Chunk) / sizeof(ArrayList))
    #define ITR_PREV_CHUNK(chunk)           chunk -= sizeof(Chunk) / sizeof(ArrayList))

    #define NOT_A_CHUNK                     { NOT_AN_ALIST, NOT_AN_ALIST }

    typedef ArrayList           Chunk[2];
    typedef ArrayList*          ChunkItr;
    typedef ArrayList const*    ChunkConstItr;

    Item addIndeterminate_chunk(
        Chunk chunk,
        uint32_t const sz_item
    );

    Item addItem_chunk(
        Chunk chunk,
        void const* const p_item,
        uint32_t const sz_item
    );

    Item append_chunk(
        Chunk chunk,
        void const* const p_item,
        uint32_t const sz_item

    );

    Item appendDuplicate_chunk(
        Chunk chunk,
        uint32_t const id
    );

    void concat_chunk(
        Chunk head,
        Chunk const tail
    );

    void construct_chunk(void* const p_chunk, ...);

    void constructEmpty_chunk(
        Chunk chunk,
        uint32_t const initial_cap_area,
        uint32_t const initial_cap_len
    );

    #define deleteFirst_chunk(chunk, n)     deleteItem_chunk(chunk, 0, n)

    void deleteItem_chunk(
        Chunk chunk,
        uint32_t const id,
        uint32_t const n
    );

    void deleteLast_chunk(
        Chunk chunk,
        uint32_t const n
    );

    void destruct_chunk(void* const p_chunk);

    void* duplicateItem_chunk(
        Chunk chunk,
        uint32_t const id
    );

    void* duplicateItemLast_chunk(Chunk chunk);

    void* enlargeItem_chunk(
        Chunk chunk,
        uint32_t const id,
        uint32_t const by
    );

    void* enlargeItemLast_chunk(
        Chunk chunk,
        uint32_t const by
    );

    void flush_chunk(Chunk chunk);

    uint32_t fromStream_chunk(
        Chunk chunk,
        FILE* const stream,
        char const delimeters[],
        size_t nDelimeters
    );

    void* fromStreamAsWhole_chunk(
        Chunk chunk,
        FILE* const stream
    );

    void* get_chunk(
        Chunk const chunk,
        uint32_t const id
    );

    void* getLast_chunk(Chunk const chunk);

    bool isValid_chunk(Chunk const chunk);

    void* resizeItem_chunk(
        Chunk chunk,
        uint32_t const id,
        uint32_t const sz_new
    );

    void* resizeItemLast_chunk(
        Chunk chunk,
        uint32_t const sz_new
    );

    void* setItem_chunk(
        Chunk chunk,
        uint32_t const id,
        uint32_t const sz,
        void const* const ptr
    );

    void* setItemLast_chunk(
        Chunk chunk,
        uint32_t const sz,
        void const* const ptr
    );

    void* shrinkItem_chunk(
        Chunk chunk,
        uint32_t const id,
        uint32_t const by
    );

    void* shrinkItemLast_chunk(
        Chunk chunk,
        uint32_t const by
    );

    uint32_t splitLast_chunk(
        Chunk chunk,
        char const delimeters[],
        size_t nDelimeters
    );

    uint32_t sz_item_chunk(
        Chunk const chunk,
        uint32_t const id
    );

    uint32_t sz_itemLast_chunk(Chunk const chunk);

    void vconstruct_chunk(
        void* const p_chunk,
        va_list args
    );
#endif
