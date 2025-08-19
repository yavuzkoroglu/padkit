#ifndef PADKIT_CHUNKTABLE_H
    #define PADKIT_CHUNKTABLE_H
    #include "padkit/chunk.h"
    #include "padkit/indextable.h"
    #include "padkit/invalid.h"

    #define CTBL_RECOMMENDED_PARAMETERS     ITBL_RECOMMENDED_PARAMETERS, CHUNK_RECOMMENDED_PARAMETERS

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

    bool isAllocated_ctbl(void const* const p_tbl);

    bool isValid_ctbl(void const* const p_tbl);

    void vconstruct_ctbl(
        void* const p_tbl,
        va_list args
    );
#endif
