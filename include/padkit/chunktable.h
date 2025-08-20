#ifndef PADKIT_CHUNKTABLE_H
    #define PADKIT_CHUNKTABLE_H
    #include "padkit/chunk.h"
    #include "padkit/indextable.h"
    #include "padkit/invalid.h"

    #define CTBL_RECOMMENDED_PARAMETERS     ITBL_RECOMMENDED_PARAMETERS, CHUNK_RECOMMENDED_PARAMETERS

    #define LEN_CTBL(ctbl)                  ((ctbl)->list->len)

    #define NOT_A_CTBL                      ((ChunkTable){ { NOT_AN_ITBL }, { NOT_A_CHUNK }, { NOT_AN_ALIST } })

    typedef struct ChunkMappingBody {
        uint32_t    chunk_id;
        uint32_t    value;
    } ChunkMapping;

    typedef struct ChunkTableBody {
        IndexTable  itbl[1];
        Chunk       chnk[1];
        ArrayList   list[1];
    } ChunkTable;

    void construct_ctbl(void* const p_tbl, ...);

    void constructEmpty_ctbl(
        ChunkTable* const ctbl,
        uint32_t const tbl_min_height,
        uint32_t const tbl_max_percent_load,
        uint32_t const tbl_initial_cap,
        uint32_t const chnk_init_cap_len,
        uint32_t const chnk_init_cap_area
    );

    void destruct_ctbl(void* const p_tbl);

    void flush_ctbl(ChunkTable* const ctbl);

    bool isAllocated_ctbl(void const* const p_tbl);

    bool isValid_ctbl(void const* const p_tbl);

    #define CTBL_MODE_SEARCH                (0)
    #define CTBL_MODE_INSERT_REPLACE        (1)
    #define CTBL_MODE_INSERT_RESPECT        (2)
    #define CTBL_MODE_FINAL                 CTBL_MODE_INSERT_RESPECT
    #define CTBL_SEARCH_NOT_FOUND           (0)
    #define CTBL_SEARCH_FOUND               (1)
    #define CTBL_REPLACE_NO_CHANGES         (0)
    #define CTBL_REPLACE_CHANGED            (1)
    #define CTBL_RESPECT_NOT_UNIQUE         (0)
    #define CTBL_RESPECT_UNIQUE             (1)
    ChunkMapping* searchInsert_ctbl(
        bool* const p_result,
        ChunkTable* const ctbl,
        Item const key_item,
        uint32_t const value,
        uint32_t const mode
    );

    void vconstruct_ctbl(
        void* const p_tbl,
        va_list args
    );
#endif
