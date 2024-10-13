#ifndef PADKIT_CHUNK_H
    #define PADKIT_CHUNK_H
    #include "padkit/arraylist.h"
    #include "padkit/item.h"

    #define CHUNK_RECOMMENDED_PARAMETERS                        \
        ALIST_RECOMMENDED_INITIAL_CAP,                          \
        ALIST_RECOMMENDED_INITIAL_CAP

    #define LEN_CHUNK(chunk)                                    (chunk[0].len)
    #define AREA_CHUNK(chunk)                                   (chunk[1].len)

    #define ITR_NEXT_CHUNK(chunk)                               (chunk += sizeof(Chunk) / sizeof(ArrayList)))
    #define ITR_PREV_CHUNK(chunk)                               (chunk -= sizeof(Chunk) / sizeof(ArrayList)))

    #define NOT_A_CHUNK                                         { NOT_AN_ALIST, NOT_AN_ALIST }

    typedef ArrayList           Chunk[2];
    typedef ArrayList*          ChunkItr;
    typedef ArrayList const*    ChunkConstItr;

    Item add_chunk(
        Chunk chunk,
        void const* const p_item,
        uint32_t const sz_item
    );

    Item addDup_chunk(
        Chunk chunk,
        uint32_t const id
    );

    #define addDupFirst_chunk(chunk)                addDup_chunk(chunk, 0)

    #define addDupFirstN_chunk(chunk, n)            addDupN_chunk(chunk, 0, n)

    Item addDupLast_chunk(Chunk chunk);

    void* addDupLastN_chunk(
        Chunk chunk,
        uint32_t const n
    );

    void* addDupN_chunk(
        Chunk chunk,
        uint32_t const id,
        uint32_t const n
    );

    Item addFromStream_chunk(
        Chunk chunk,
        FILE* const stream,
        uint32_t const max_sz_buf,
        uint32_t const max_sz_item,
        bool const null_terminated
    );

    #define addIndeterminate_chunk(chunk, sz_item)  addIndeterminateN_chunk(chunk, 1, sz_item)

    void* addIndeterminateN_chunk(
        Chunk chunk,
        uint32_t const n,
        ...
    );

    void* addIndeterminateNSameSz_chunk(
        Chunk chunk,
        uint32_t const n,
        uint32_t const sz_item
    );

    Item addZeros_chunk(
        Chunk chunk,
        uint32_t const sz_item
    );

    void* addZerosN_chunk(
        Chunk chunk,
        uint32_t const n,
        ...
    );

    void* addZerosNSameSz_chunk(
        Chunk chunk,
        uint32_t const n,
        uint32_t const sz_item
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

    void destruct_chunk(void* const p_chunk);

    void* enlarge_chunk(
        Chunk chunk,
        uint32_t const id,
        uint32_t const by
    );

    void* enlargeAll_chunk(
        Chunk chunk,
        uint32_t const by
    );

    #define enlargeFirst_chunk(chunk, by)           enlarge_chunk(chunk, 0, by)

    void* enlargeLast_chunk(
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

    #define removeFirstItem_chunk(chunk, n)     removeItemN_chunk(chunk, 0, 1)

    #define removeFirstItemN_chunk(chunk, n)    removeItemN_chunk(chunk, 0, n)

    #define removeItem_chunk(chunk, id)         removeItemN_chunk(chunk, id, 1)

    Item removeItemN_chunk(
        Chunk chunk,
        uint32_t const id,
        uint32_t const n
    );

    #define removeLastItem_chunk(chunk)         removeLastItemN_chunk(chunk, 1)

    Item removeLastItemN_chunk(
        Chunk chunk,
        uint32_t const n
    );

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

    void* vaddIndeterminateItemN_chunk(
        Chunk chunk,
        uint32_t const n,
        va_list args
    );

    void vconstruct_chunk(
        void* const p_chunk,
        va_list args
    );
#endif
