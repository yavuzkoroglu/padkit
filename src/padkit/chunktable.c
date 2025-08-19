#include <assert.h>
#include "padkit/chunktable.h"
#include "padkit/size.h"

void construct_ctbl(void* const p_tbl, ...) {
    va_list args;
    va_start(args, p_tbl);
    vconstruct_ctbl(p_tbl, args);
    va_end(args);
}

void constructEmpty_ctbl(
    ChunkTable* const ctbl,
    uint32_t const itbl_min_height,
    uint32_t const itbl_max_percent_load,
    uint32_t const itbl_initial_cap,
    uint32_t const chnk_init_cap_len,
    uint32_t const chnk_init_cap_area
) {
    assert(ctbl != NULL);
    assert(itbl_min_height < SZ32_MAX);
    assert(itbl_max_percent_load > 0);
    assert(itbl_max_percent_load <= 100);
    assert(itbl_initial_cap > 0);
    assert(itbl_initial_cap < SZ32_MAX);
    assert(chnk_init_cap_len > 0);
    assert(chnk_init_cap_len < SZ32_MAX);
    assert(chnk_init_cap_area > 0);
    assert(chnk_init_cap_area < SZ32_MAX);

    constructEmpty_itbl(ctbl->itbl, itbl_min_height, itbl_max_percent_load, itbl_initial_cap);
    constructEmpty_chunk(ctbl->chnk, chnk_init_cap_len, chnk_init_cap_area);
}

void destruct_ctbl(void* const p_tbl) {
    ChunkTable* const ctbl = p_tbl;
    assert(isValid_ctbl(ctbl));
    destruct_itbl(ctbl->itbl);
    destruct_chunk(ctbl->chnk);
    *ctbl = NOT_A_CTBL;
}

bool isAllocated_ctbl(void const* const p_tbl) {
    ChunkTable const* const ctbl = p_tbl;
    if (!isAllocated_itbl(ctbl->itbl)) return 0;
    assert(isAllocated_chunk(ctbl->chnk));
    return 1;
}

bool isValid_ctbl(void const* const p_tbl) {
    ChunkTable const* const ctbl = p_tbl;

    if (ctbl == NULL)               return 0;
    if (!isValid_itbl(ctbl->itbl))  return 0;
    if (!isValid_chunk(ctbl->chnk)) return 0;

    return 1;
}

void vconstruct_ctbl(
    void* const p_tbl,
    va_list args
) {
    ChunkTable* const ctbl                  = p_tbl;
    uint32_t const itbl_min_height          = va_arg(args, uint32_t);
    uint32_t const itbl_max_percent_load    = va_arg(args, uint32_t);
    uint32_t const itbl_initial_cap         = va_arg(args, uint32_t);
    uint32_t const chnk_init_cap_len        = va_arg(args, uint32_t);
    uint32_t const chnk_init_cap_area       = va_arg(args, uint32_t);
    constructEmpty_ctbl(
        ctbl,
        itbl_min_height, itbl_max_percent_load, itbl_initial_cap,
        chnk_init_cap_len, chnk_init_cap_area
    );
}
