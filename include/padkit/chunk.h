#ifndef PADKIT_CHUNK_H
    #define PADKIT_CHUNK_H
    #include "padkit/arraylist.h"
    #include "padkit/item.h"

    #define CHUNK_RECOMMENDED_PARAMETERS                    \
        ALIST_RECOMMENDED_INITIAL_CAP,                      \
        ALIST_RECOMMENDED_INITIAL_CAP

    #define LEN_CHUNK(chunk)                                (chunk->offsets->len)
    #define AREA_CHUNK(chunk)                               (chunk->items->len)

    #define NOT_A_CHUNK                                     (Chunk){ {NOT_AN_ALIST}, {NOT_AN_ALIST} }

    typedef struct ChunkBody {
        ArrayList offsets[1];
        ArrayList items[1];
    } Chunk;

    #define add_chunk(chunk, p_item, sz_item)               addN_chunk(chunk, p_item, sz_item, 1)

    /* TBI */
    extern void (* const addAll_chunk)(
        Chunk* const head,
        Chunk const* const tail
    )

    #define addDup_chunk(chunk, id)                         addDupN_chunk(chunk, id, 1)

    #define addDupFirst_chunk(chunk)                        addDupN_chunk(chunk, 0, 1)

    #define addDupFirstN_chunk(chunk, n)                    addDupN_chunk(chunk, 0, n)

    #define addDupLast_chunk(chunk)                         addDupLastN_chunk(chunk, 1)

    /* TBI */
    Item addDupLastN_chunk(
        Chunk* const chunk,
        uint32_t const n
    );

    /* TBI */
    Item addDupN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        uint32_t const n
    );

    #define addF_chunk(chunk, fp, max_sz_item, max_sz_buf)  addFN_chunk(chunk, fp, max_sz_item, max_sz_buf, 1)

    /* TBI */
    Item addFN_chunk(
        Chunk* const chunk,
        FILE* const fp,
        uint32_t const max_sz_item,
        uint32_t const max_sz_buf,
        uint32_t const n
    );

    #define addIndeterminate_chunk(chunk, sz_item)          addN_chunk(chunk, NULL, sz_item, 1)

    #define addIndeterminateN_chunk(chunk, sz_item, n)      addN_chunk(chunk, NULL, sz_item, n)

    /* TBI */
    Item addN_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item,
        uint32_t const n
    );

    #define addZeros_chunk(chunk, sz_item)                  addZerosN_chunk(chunk, sz_item, 1)

    /* TBI */
    Item addZerosN_chunk(
        Chunk* const chunk,
        uint32_t const sz_item,
        uint32_t const n
    );

    #define append_chunk(chunk, id, p_item, sz_item)        appendN_chunk(chunk, id, p_item, sz_item, 1)

    /* TBI */
    Item appendAll_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item
    );

    #define appendDup_chunk(chunk, orig_id, dup_id)         appendDupN_chunk(chunk, orig_id, dup_id, 1)

    #define appendDupFirst_chunk(chunk, dup_id)             appendDupN_chunk(chunk, 0, dup_id, 1)

    #define appendDupFirstN_chunk(chunk, dup_id, n)         appendDupN_chunk(chunk, 0, dup_id, n)

    #define appendDupLast_chunk(chunk, orig_id)             appendDupLastN_chunk(chunk, orig_id, 1)

    /* TBI */
    Item appendDupLastN_chunk(
        Chunk* const chunk,
        uint32_t const orig_id,
        uint32_t const n
    );

    /* TBI */
    Item appendDupN_chunk(
        Chunk* const chunk,
        uint32_t const orig_id,
        uint32_t const dup_id,
        uint32_t const n
    );

    #define appendFirst_chunk(chunk, p_item, sz_item)       appendN_chunk(chunk, 0, p_item, sz_item, 1)

    #define appendFirstN_chunk(chunk, p_item, sz_item, n)   appendN_chunk(chunk, 0, p_item, sz_item, n)

    #define appendFLast_chunk(chunk, fp, max_sz_item, max_sz_buf)   \
        appendFLastN_chunk(chunk, fp, max_sz_item, max_sz_buf, 1)

    /* TBI */
    Item appendFLastN_chunk(
        Chunk* const chunk,
        FILE* const fp,
        uint32_t const max_sz_item,
        uint32_t const max_sz_buf,
        uint32_t const n
    );

    #define appendIndeterminate_chunk(chunk, id, sz_item)   appendN_chunk(chunk, id, NULL, sz_item, 1)

    #define appendIndeterminateAll_chunk(chunk, sz_item)    appendAll(chunk, NULL, sz_item)

    #define appendIndeterminateFirst_chunk(chunk, sz_item)  appendN_chunk(chunk, 0, NULL, sz_item, 1)

    #define appendIndeterminateFirstN_chunk(chunk, sz_item, n)      \
        appendN_chunk(chunk, 0, NULL, sz_item, n)

    #define appendIndeterminateLast_chunk(chunk, sz_item)   appendLastN_chunk(chunk, NULL, sz_item, 1)

    #define appendIndeterminateLastN_chunk(chunk, sz_item, n)       \
        appendLastN_chunk(chunk, NULL, sz_item, n)

    #define appendIndeterminateN_chunk(chunk, id, sz_item, n)       \
        appendN_chunk(chunk, id, NULL, sz_item, n)

    /* TBI */
    Item appendLast_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item
    );

    /* TBI */
    Item appendLastN_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item,
        uint32_t const n
    );

    /* TBI */
    Item appendN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        void const* const p_item,
        uint32_t const sz_item,
        uint32_t const n
    );

    #define appendZeros_chunk(chunk, id, sz_item)           appendZerosN_chunk(chunk, id, sz_item, 1)

    /* TBI */
    Item appendZerosAll_chunk(
        Chunk* const chunk,
        uint32_t const sz_item
    );

    #define appendZerosFirst_chunk(chunk, sz_item)          appendZerosN_chunk(chunk, 0, sz_item, 1)

    #define appendZerosFirstN_chunk(chunk, sz_item, n)      appendZerosN_chunk(chunk, 0, sz_item, n)

    #define appendZerosLast_chunk(chunk, sz_item)           appendZerosLastN_chunk(chunk, sz_item, 1)

    /* TBI */
    Item appendZerosLastN_chunk(
        Chunk* const chunk,
        uint32_t const sz_item,
        uint32_t const n
    );

    /* TBI */
    Item appendZerosN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        uint32_t const sz_item,
        uint32_t const n
    );

    /* TBI */
    uint32_t bsearch_alist(
        void** const p_key,
        Chunk const* const chunk,
        void const* const p_item,
        int (*cmp)(void const*, void const*)
    );

    /* TBI */
    void concat_chunk(
        Chunk* const head,
        Chunk const* const tail
    );

    /* TBI */
    void construct_chunk(void* const p_chunk, ...);

    /* TBI */
    void constructEmpty_chunk(
        Chunk* const chunk,
        uint32_t const init_cap_len,
        uint32_t const init_cap_area
    );

    #define cut2BySize_chunk(chunk, id, sz_first)           cut2BySizeN_chunk(chunk, id, sz_first, 1)

    #define cut2BySizeFirst_chunk(chunk, sz_first)          cut2BySizeN_chunk(chunk, 0, sz_first, 1)

    #define cut2BySizeFirstN_chunk(chunk, sz_first, n)      cut2BySizeFirstN_chunk(chunk, 0, sz_first, n)

    #define cut2BySizeLast_chunk(chunk, sz_first)           cut2BySizeLastN_chunk(chunk, sz_first, 1)

    /* TBI */
    Item cut2BySizeLastN_chunk(
        Chunk* const chunk,
        uint32_t const sz_first,
        uint32_t const n
    );

    /* TBI */
    Item cut2BySizeN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        uint32_t const sz_first,
        uint32_t const n
    );

    #define cutNEqually_chunk(chunk, n_pieces, id)          cutNEquallyN_chunk(chunk, n_pieces, id, 1)

    #define cutNEquallyFirst_chunk(chunk, n_pieces)         cutNEquallyN_chunk(chunk, n_pieces, 0, 1)

    #define cutNEquallyFirstN_chunk(chunk, n_pieces, n)     cutNEquallyN_chunk(chunk, n_pieces, 0, n)

    #define cutNEquallyLast_chunk(chunk, n_pieces)          cutNEquallyLastN_chunk(chunk, n_pieces, 1)

    /* TBI */
    Item cutNEquallyLastN_chunk(
        Chunk* const chunk,
        uint32_t const n_pieces,
        uint32_t const n
    );

    #defien cutNEqually_chunk(chunk, n_pieces, id)          cutNEquallyN_chunk(chunk, n_pieces, id, n)

    /* TBI */
    Item cutNEquallyN_chunk(
        Chunk* const chunk,
        uint32_t const n_pieces,
        uint32_t const id,
        uint32_t const n
    );

    #define cutByDelimeters_chunk(chunk, delim, id)         cutByDelimetersN_chunk(chunk, delim, id, 1)

    #define cutByDelimetersFirst_chunk(chunk, delim)        cutByDelimetersN_chunk(chunk, delim, 0, 1)

    #define cutByDelimetersFirstN_chunk(chunk, delim, n)    cutByDelimetersN_chunk(chunk, delim, 0, n)

    #define cutByDelimetersLast_chunk(chunk, delim)         cutByDelimetersLastN_chunk(chunk, delim, 1)

    /* TBI */
    Item cutByDelimetersLastN_chunk(
        Chunk* const chunk,
        char const delim[],
        uint32_t const n
    );

    /* TBI */
    Item cutByDelimetersN_chunk(
        Chunk* const chunk,
        char const delim[],
        uint32_t const id,
        uint32_t const n
    );

    #define delete_chunk(chunk, id)                         deleteN_chunk(chunk, id, 1)

    /* TBI */
    extern void (* const deleteAll_chunk)(Chunk* const chunk);

    #define deleteFirst_chunk(chunk)                        deleteN_chunk(chunk, 0, 1)

    #define deleteFirstN_chunk(chunk, n)                    deleteN_chunk(chunk, 0, n)

    #define deleteLast_chunk(chunk)                         deleteLastN_chunk(chunk, 1)

    void deleteLastN_chunk(
        Chunk* const chunk,
        uint32_t const n
    );

    void deleteN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        uint32_t const n
    )

    void destruct_chunk(void* const p_chunk);

    #define enlarge_chunk(chunk, id, by)                    appendN_chunk(chunk, id, NULL, by, 1)

    #define enlargeAll_chunk(chunk, by)                     appendAll_chunk(chunk, NULL, by)

    #define enlargeFirst_chunk(chunk, by)                   appendN_chunk(chunk, 0, NULL, by, 1)

    #define enlargeFirstN_chunk(chunk, by)                  appendN_chunk(chunk, 0, NULL, by, 1)

    #define enlargeLast_chunk(chunk, by)                    appendLastN_chunk(chunk, NULL, by, 1)

    #define enlargeLastN_chunk(chunk, by, n)                appendLastN_chunk(chunk, NULL, by, n)

    #define enlargeN_chunk(chunk, id, by, n)                appendN_chunk(chunk, id, NULL, by, n)

    void flush_chunk(Chunk* const chunk);

    #define get_chunk(chunk, id)                            getN_chunk(chunk, id, 1)

    #define getFirst_chunk(chunk)                           getN_chunk(chunk, 0, 1)

    #define getFirstN_chunk(chunk, n)                       getN_chunk(chunk, 0, n)

    #define getLast_chunk(chunk)                            getLastN_chunk(chunk, 1)

    /* TBI */
    Item getLastN_chunk(
        Chunk const* const chunk,
        uint32_t const n
    );

    /* TBI */
    Item getN_chunk(
        Chunk const* const chunk,
        uint32_t const id,
        uint32_t const n
    );

    /* TBI */
    Item getNext_chunk(
        Chunk const* const chunk,
        Item const prev
    );

    #define insert_chunk(chunk, id, p_item, sz_item)        insertN_chunk(chunk, id, p_item, sz_item, 1)

    /* TBI */
    Item insertAll_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item
    );

    #define insertDup_chunk(chunk, dup_id, orig_id)         insertDupN_chunk(chunk, dup_id, orig_id, 1)

    /* TBI */
    Item insertDupN_chunk(
        Chunk* const chunk,
        uint32_t const dup_id,
        uint32_t const orig_id,
        uint32_t const n
    );

    #define insertIndeterminate_chunk(chunk, id, sz_item)   insertN_chunk(chunk, id, NULL, sz_item, 1)

    #define insertIndeterminateN_chunk(chunk, id, sz_item, n)       \
        insertN_chunk(chunk, id, NULL, sz_item, 1)

    /* TBI */
    Item insertN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        void const* const p_item,
        uint32_t const sz_item,
        uint32_t const n
    );

    /* TBI */
    bool isAllocated_chunk(void const* const p_chunk);

    /* TBI */
    bool isSorted_chunk(
        Chunk const* const chunk,
        int (*cmp)(void const*, void const*)
    );

    /* TBI */
    bool isValid_chunk(void const* const p_chunk);

    /* TBI */
    Item mergeAll_chunk(Chunk* const chunk);

    /* TBI */
    Item mergeN_chunk(
        Chunk* const chunk,
        uint32_t const first_id,
        uint32_t const n
    );

    /* TBI */
    Item mergeLastPair_chunk(Chunk* const chunk);

    /* TBI */
    Item mergePair_chunk(
        Chunk* const chunk,
        uint32_t const first_id
    );

    extern Item (* const peek_chunk)(Chunk const* const chunk);

    extern Item (* const pop_chunk)(Chunk* const chunk);

    extern Item (* const push_chunk)(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item
    );

    #define pushIndeterminate_chunk(chunk, sz_item)     addIndeterminate_chunk(chunk, sz_item)

    Item remove_chunk(
        Chunk* const chunk,
        uint32_t const id
    );

    Item removeLast_chunk(Chunk* const chunk);

    void* setN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        void const* const p,
        uint32_t const n
    );

    #define setZeros_chunk(chunk, id)                   setN_chunk(chunk, id, NULL, 1)

    #define setZerosN_chunk(chunk, id, n)               setN_chunk(chunk, id, NULL, n)

    #define shrink_chunk(

    Item shrinkN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        uint32_t const by,
        uint32_t const n
    );

    #define shringFirst_chunk(chunk, by)                shrink_chunk(chunk, 0, by)

    Item shrinkLast_chunk(
        Chunk* const chunk,
        uint32_t const by
    );

    #define swap_chunk(chunk, id1, id0)                 swapN_chunk(chunk, id1, id0, 1)

    void swapN_chunk(
        Chunk* const chunk,
        uint32_t const id1,
        uint32_t const id0,
        uint32_t const n
    );

    void vconstruct_chunk(
        void* const p_chunk,
        va_list args
    );
#endif
