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

    #define addAll_chunk(head, tail)                        addAllN_chunk(head, tail, 1)

    extern void (* const addAllN_chunk)(
        Chunk* const head,
        Chunk const* const tail,
        uint32_t const n
    );

    #define addDup_chunk(chunk, id)                         addDupN_chunk(chunk, id, 1)

    #define addDupFirst_chunk(chunk)                        addDup_chunk(chunk, 0)

    #define addDupFirstN_chunk(chunk, n)                    addDupN_chunk(chunk, 0, n)

    #define addDupFirstSameN_chunk(chunk, n)                addDupSameN_chunk(chunk, 0, n)

    #define addDupLast_chunk(chunk)                         addDupLastN_chunk(chunk, 1)

    Item addDupLastN_chunk(
        Chunk* const chunk,
        uint32_t const n
    );

    Item addDupLastSameN_chunk(
        Chunk* const chunk,
        uint32_t const n
    );

    Item addDupN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        uint32_t const n
    );

    Item addDupSameN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        uint32_t const n
    );

    #define addF_chunk(chunk, fp, max_sz_item, max_sz_buf)  addFN_chunk(chunk, fp, max_sz_item, max_sz_buf, 1)

    Item addFN_chunk(
        Chunk* const chunk,
        FILE* const fp,
        uint32_t const max_sz_item,
        uint32_t const max_sz_buf,
        uint32_t const n
    );

    #define addIndeterminate_chunk(chunk, sz_item)          add_chunk(chunk, NULL, sz_item)

    #define addIndeterminateN_chunk(chunk, sz_item, n)      addN_chunk(chunk, NULL, sz_item, n)

    Item addN_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item,
        uint32_t const n
    );

    #define addZeros_chunk(chunk, sz_item)                  addZerosN_chunk(chunk, sz_item, 1)

    Item addZerosN_chunk(
        Chunk* const chunk,
        uint32_t const sz_item,
        uint32_t const n
    );

    #define append_chunk(chunk, id, p_item, sz_item)        appendN_chunk(chunk, id, p_item, sz_item, 1)

    Item appendAll_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item
    );

    Item appendDup_chunk(
        Chunk* const chunk,
        uint32_t const dup_id,
        uint32_t const orig_id
    );

    Item appendDupAll2One_chunk(
        Chunk* const chunk,
        uint32_t const dup_id
    );

    Item appendDupNMany2Many_chunk(
        Chunk* const chunk,
        uint32_t const dup_id,
        uint32_t const orig_id,
        uint32_t const n
    );

    Item appendDupNMany2One_chunk(
        Chunk* const chunk,
        uint32_t const dup_id,
        uint32_t const orig_id,
        uint32_t const n
    );

    Item appendDupNOne2Many_chunk(
        Chunk* const chunk,
        uint32_t const dup_id,
        uint32_t const orig_id,
        uint32_t const n
    );

    Item appendDupOne2All_chunk(
        Chunk* const chunk,
        uint32_t const orig_id
    );

    #define appendFirst_chunk(chunk, p_item, sz_item)       append_chunk(chunk, 0, p_item, sz_item)

    #define appendFirstN_chunk(chunk, p_item, sz_item, n)   appendN_chunk(chunk, 0, p_item, sz_item, n)

    #define appendFirstSameN_chunk(chunk, p_item, sz_item, n)       \
        appendSameN_chunk(chunk, 0, p_item, sz_item, n)

    #define appendFLast_chunk(chunk, fp, max_sz_item, max_sz_buf)   \
        appendFLastSameN_chunk(chunk, fp, max_sz_item, max_sz_buf, 1)

    Item appendFLastSameN_chunk(
        Chunk* const chunk,
        FILE* const fp,
        uint32_t const max_sz_item,
        uint32_t const max_sz_buf,
        uint32_t const n
    );

    #define appendIndeterminate_chunk(chunk, id, sz_item)   appendN_chunk(chunk, id, NULL, sz_item, 1)

    #define appendIndeterminateAll_chunk(chunk, sz_item)    appendAll_chunk(chunk, NULL, sz_item)

    #define appendIndeterminateFirst_chunk(chunk, sz_item)  appendFirst_chunk(chunk, NULL, sz_item)

    #define appendIndeterminateFirstN_chunk(chunk, sz_item, n)      \
        appendFirstN_chunk(chunk, NULL, sz_item, n)

    #define appendIndeterminateLast_chunk(chunk, sz_item)   appendLast_chunk(chunk, NULL, sz_item)

    #define appendIndeterminateLastN_chunk(chunk, sz_item, n)       \
        appendLastN_chunk(chunk, NULL, sz_item, n)

    #define appendIndeterminateN_chunk(chunk, id, sz_item, n)       \
        appendN_chunk(chunk, id, NULL, sz_item, n)

    #define appendLast_chunk(chunk, p_item, sz_item)        appendLastSameN_chunk(chunk, p_item, sz_item, 1)

    Item appendLastN_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item,
        uint32_t const n
    );

    Item appendLastSameN_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item,
        uint32_t const n
    );

    Item appendN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        void const* const p_item,
        uint32_t const sz_item,
        uint32_t const n
    );

    Item appendSameN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        void const* const p_item,
        uint32_t const sz_item,
        uint32_t const n
    );

    #define appendZeros_chunk(chunk, id, sz_item)           appendZerosN_chunk(chunk, id, sz_item, 1)

    Item appendZerosAll_chunk(
        Chunk* const chunk,
        uint32_t const sz_item
    );

    #define appendZerosFirst_chunk(chunk, sz_item)          appendZerosN_chunk(chunk, 0, sz_item, 1)

    #define appendZerosFirstN_chunk(chunk, sz_item, n)      appendZerosN_chunk(chunk, 0, sz_item, n)

	#define appendZerosLast_chunk(chunk, sz_item)			appendZerosLastN_chunk(chunk, sz_item, 1)

    Item appendZerosLastN_chunk(
        Chunk* const chunk,
        uint32_t const sz_item,
        uint32_t const n
    );

    Item appendZerosN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        uint32_t const sz_item,
        uint32_t const n
    );

    #define area_chunk(chunk, id)                           areaBtw_chunk(chunk, id, id + 1)

    uint32_t areaBtw_chunk(
        Chunk const* const chunk,
        uint32_t const id0,
        uint32_t const id1
    );

    #define areaFirst_chunk(chunk)                          areaFirstN_chunk(chunk, 1)

    #define areaFirstN_chunk(chunk, n)                      areaBtw_chunk(chunk, 0, n - 1)

    #define areaLast_chunk(chunk)                           areaLastN_chunk(chunk, 1)

    uint32_t areaLastN_chunk(
        Chunk const* const chunk,
        uint32_t const n
    );

    #define concat_chunk(head, tail)                        concatN_chunk(head, tail, 1)

    void concatN_chunk(
        Chunk* const head,
        Chunk const* const tail,
        uint32_t const n
    );

    void construct_chunk(void* const p_chunk, ...);

    void constructEmpty_chunk(
        Chunk* const chunk,
        uint32_t const init_cap_len,
        uint32_t const init_cap_area
    );

    #define cut2BySize_chunk(chunk, id, sz_first)           cut2BySizeN_chunk(chunk, id, sz_first, 1)

    #define cut2BySizeFirst_chunk(chunk, sz_first)          cut2BySizeN_chunk(chunk, 0, sz_first, 1)

    #define cut2BySizeFirstN_chunk(chunk, sz_first, n)      cut2BySizeFirstN_chunk(chunk, 0, sz_first, n)

    #define cut2BySizeLast_chunk(chunk, sz_first)           cut2BySizeLastN_chunk(chunk, sz_first, 1)

    Item cut2BySizeLastN_chunk(
        Chunk* const chunk,
        uint32_t const sz_first,
        uint32_t const n
    );

    Item cut2BySizeN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        uint32_t const sz_first,
        uint32_t const n
    );

    #define cutByDelim_chunk(chunk, delim, id)              cutByDelimetersN_chunk(chunk, delim, id, 1)

    #define cutByDelimFirst_chunk(chunk, delim)             cutByDelimetersN_chunk(chunk, delim, 0, 1)

    #define cutByDelimFirstN_chunk(chunk, delim, n)         cutByDelimetersN_chunk(chunk, delim, 0, n)

    #define cutByDelimLast_chunk(chunk, delim)              cutByDelimetersLastN_chunk(chunk, delim, 1)

    Item cutByDelimLastN_chunk(
        Chunk* const chunk,
        char const delim[],
        uint32_t const n
    );

    Item cutByDelimN_chunk(
        Chunk* const chunk,
        char const delim[],
        uint32_t const id,
        uint32_t const n
    );

    #define cutNEqually_chunk(chunk, n_pieces, id)          cutNEquallyN_chunk(chunk, n_pieces, id, 1)

    #define cutNEquallyFirst_chunk(chunk, n_pieces)         cutNEquallyN_chunk(chunk, n_pieces, 0, 1)

    #define cutNEquallyFirstN_chunk(chunk, n_pieces, n)     cutNEquallyN_chunk(chunk, n_pieces, 0, n)

    #define cutNEquallyLast_chunk(chunk, n_pieces)          cutNEquallyLastN_chunk(chunk, n_pieces, 1)

    Item cutNEquallyLastN_chunk(
        Chunk* const chunk,
        uint32_t const n_pieces,
        uint32_t const n
    );

    Item cutNEquallyN_chunk(
        Chunk* const chunk,
        uint32_t const n_pieces,
        uint32_t const id,
        uint32_t const n
    );

    #define delete_chunk(chunk, id)                         deleteN_chunk(chunk, id, 1)

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
    );

    void destruct_chunk(void* const p_chunk);

    #define enlarge_chunk(chunk, id, by)                    appendIndeterminate_chunk(chunk, id, by)

    #define enlargeAll_chunk(chunk, by)                     appendIndeterminateAll_chunk(chunk, by)

    #define enlargeFirst_chunk(chunk, by)                   appendIndeterminateFirst_chunk(chunk, by)

    #define enlargeFirstN_chunk(chunk, by, n)               appendIndeterminateFirstN_chunk(chunk, by, n)

    #define enlargeLast_chunk(chunk, by)                    appendIndeterminateLast_chunk(chunk, by)

    #define enlargeLastN_chunk(chunk, by, n)                appendIndeterminateLastN_chunk(chunk, by, n)

    #define enlargeN_chunk(chunk, id, by, n)                appendIndeterminateN_chunk(chunk, id, by, n)

    void flush_chunk(Chunk* const chunk);

    #define get_chunk(chunk, id)                            getN_chunk(chunk, id, 1)

    #define getFirst_chunk(chunk)                           getN_chunk(chunk, 0, 1)

    #define getFirstN_chunk(chunk, n)                       getN_chunk(chunk, 0, n)

    #define getLast_chunk(chunk)                            getLastN_chunk(chunk, 1)

    Item getLastN_chunk(
        Chunk const* const chunk,
        uint32_t const n
    );

    Item getN_chunk(
        Chunk const* const chunk,
        uint32_t const id,
        uint32_t const n
    );

    bool isAllocated_chunk(void const* const p_chunk);

    bool isValid_chunk(void const* const p_chunk);

    Item mergeAll_chunk(Chunk* const chunk);

    Item mergeLastN_chunk(
        Chunk* const chunk,
        uint32_t const n
    );

    #define mergeLastPair_chunk(chunk)                      mergeLastN_chunk(chunk, 2)

    Item mergeN_chunk(
        Chunk* const chunk,
        uint32_t const first_id,
        uint32_t const n
    );

    #define mergePair_chunk(chunk, first_id)                mergeN_chunk(chunk, first_id, 2)

    uint32_t offsetOf_chunk(
        Chunk const* const chunk,
        uint32_t const id
    );

    #define set_chunk(chunk, id, p_item, sz_item)           setN_chunk(chunk, id, p_item, sz_item, 1)

    Item setAll_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item
    );

    #define setAllZeros_chunk(chunk, sz_item)               setAll_chunk(chunk, NULL, sz_item)

    #define setDup_chunk(chunk, dup_id, orig_id)            setDupN_chunk(chunk, dup_id, orig_id, 1)

    Item setDupN_chunk(
        Chunk* const chunk,
        uint32_t const dup_id,
        uint32_t const orig_id,
        uint32_t const n
    );

    Item setDupSameN_chunk(
        Chunk* const chunk,
        uint32_t const dup_id,
        uint32_t const orig_id,
        uint32_t const n
    );

    #define setFirst_chunk(chunk, p_item, sz_item)          setFirstN_chunk(chunk, p_item, sz_item, 1)

    #define setFirstN_chunk(chunk, p_item, sz_item, n)      setN_chunk(chunk, 0, p_item, sz_item, n)

    #define setLast_chunk(chunk, p_item, sz_item)           setLastN_chunk(chunk, p_item, sz_item, 1)

    Item setLastN_chunk(
        Chunk* const chunk,
        void const* const p_item,
        uint32_t const sz_item,
        uint32_t const n
    );

    Item setN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        void const* const p_item,
        uint32_t const sz_item,
        uint32_t const n
    );

    #define setZeros_chunk(chunk, id)                       setZerosN_chunk(chunk, id, 1)

    Item setZerosN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        uint32_t const n
    );

    #define shrink_chunk(chunk, id, by)                     shrinkN_chunk(chunk, id, by, 1)

    Item shrinkAll_chunk(
        Chunk* const chunk,
        uint32_t const by
    );

    #define shrinkFirst_chunk(chunk, by)                    shrink_chunk(chunk, 0, by)

    #define shrinkFirstN_chunk(chunk, by, n)                shrinkN_chunk(chunk, 0, by, n)

    Item shrinkLast_chunk(
        Chunk* const chunk,
        uint32_t const by
    );

    Item shrinkLastN_chunk(
        Chunk* const chunk,
        uint32_t const by,
        uint32_t const n
    );

    Item shrinkN_chunk(
        Chunk* const chunk,
        uint32_t const id,
        uint32_t const by,
        uint32_t const n
    );

    #define swap_chunk(chunk, id1, id0)                     swapN_chunk(chunk, id1, id0, 1)

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
