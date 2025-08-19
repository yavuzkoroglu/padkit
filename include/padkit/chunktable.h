#ifndef PADKIT_CHUNKTABLE_H
    #define PADKIT_CHUNKTABLE_H
    #include "padkit/chunk.h"
    #include "padkit/indextable.h"
    #include "padkit/invalid.h"

    #define CTBL_RECOMMENDED_PARAMETERS     ITBL_RECOMMENDED_PARAMETERS, CHUNK_RECOMMENDED_PARAMETERS

    #define NOT_A_CTBL                      ((ChunkTable){ { NOT_AN_ITBL }, { NOT_A_CHUNK } })

    typedef struct ChunkTableBody {
        IndexTable  itbl[1];
        Chunk       chnk[1];
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

    #define CTBL_IBEHAVIOR_INSERT       (0)
    #define CTBL_IBEHAVIOR_SEARCH       (1)
    #define CTBL_RBEHAVIOR_REPLACE      (0)
    #define CTBL_RBEHAVIOR_RESPECT      (1)
    #define CTBL_RELATION_ONE_TO_ONE    (0)
    #define CTBL_RELATION_ONE_TO_MANY   (1)
    #define CTBL_INSERT_NOT_UNIQUE      (0)
    #define CTBL_INSERT_UNIQUE          (1)
    #define CTBL_SEARCH_NOT_FOUND       (0)
    #define CTBL_SEARCH_FOUND           (1)
    uint32_t searchInsert_ctbl(
        bool* const p_insert_result,
        bool* const p_search_result,
        ChunkTable* const ctbl,
        char const* const key,
        uint32_t const key_len,
        bool const relationType,
        bool const r_behavior,
        bool const i_behavior
    );

    void vconstruct_ctbl(
        void* const p_tbl,
        va_list args
    );
#endif
