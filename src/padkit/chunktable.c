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
    constructEmpty_alist(ctbl->list, sizeof(ChunkMapping), chnk_init_cap_len);
}

void destruct_ctbl(void* const p_tbl) {
    ChunkTable* const ctbl = p_tbl;
    assert(isValid_ctbl(ctbl));
    destruct_itbl(ctbl->itbl);
    destruct_chunk(ctbl->chnk);
    destruct_alist(ctbl->list);
}

void flush_ctbl(ChunkTable* const ctbl) {
    assert(isValid_ctbl(ctbl));
    flush_itbl(ctbl->itbl);
    flush_chunk(ctbl->chnk);
    flush_alist(ctbl->list);
}

bool isAllocated_ctbl(void const* const p_tbl) {
    ChunkTable const* const ctbl = p_tbl;
    if (!isAllocated_itbl(ctbl->itbl)) return 0;
    assert(isAllocated_chunk(ctbl->chnk));
    assert(isAllocated_alist(ctbl->list));
    return 1;
}

bool isValid_ctbl(void const* const p_tbl) {
    ChunkTable const* const ctbl = p_tbl;

    if (ctbl == NULL)               return 0;
    if (!isValid_itbl(ctbl->itbl))  return 0;
    if (!isValid_chunk(ctbl->chnk)) return 0;
    if (!isValid_alist(ctbl->list)) return 0;

    return 1;
}

ChunkMapping* searchInsert_ctbl(
    bool* const p_result,
    ChunkTable* const ctbl,
    Item const key_item,
    uint32_t const value,
    uint32_t const mode
) {
    IndexMapping* i_mapping;
    ChunkMapping* c_mapping;
    Item dup_item;
    uint_fast64_t key_index;

    assert(isValid_ctbl(ctbl));
    assert(isValid_item(key_item));
    assert(mode <= CTBL_MODE_FINAL);

    key_index = hash64_item(key_item);
    i_mapping = findFirstMapping_itbl(ctbl->itbl, key_index);
    while (i_mapping != NULL) {
        c_mapping   = get_alist(ctbl->list, i_mapping->value);
        dup_item    = get_chunk(ctbl->chnk, c_mapping->chunk_id);
        if (areEquiv_item(key_item, dup_item)) {
            switch (mode) {
                case CTBL_MODE_INSERT_REPLACE:
                    if (c_mapping->value == value) {
                        if (p_result != NULL) *p_result = CTBL_REPLACE_NO_CHANGES;
                    } else {
                        if (p_result != NULL) *p_result = CTBL_REPLACE_CHANGED;
                        c_mapping->value = value;
                    }
                    return c_mapping;
                case CTBL_MODE_INSERT_RESPECT:
                    if (c_mapping->value == value) {
                        if (p_result != NULL) *p_result = CTBL_RESPECT_NOT_UNIQUE;
                    } else {
                        if (p_result != NULL) *p_result = CTBL_RESPECT_UNIQUE;
                    }
                    return c_mapping;
                case CTBL_MODE_SEARCH:
                default:
                    if (c_mapping->value == value || value == INVALID_UINT32) {
                        if (p_result != NULL) *p_result = CTBL_SEARCH_FOUND;
                    } else {
                        if (p_result != NULL) *p_result = CTBL_SEARCH_NOT_FOUND;
                    }
                    return NULL;
            }
        }
        i_mapping = nextMapping_itbl(ctbl->itbl, i_mapping);
    }

    switch (mode) {
        case CTBL_MODE_INSERT_REPLACE:
        case CTBL_MODE_INSERT_RESPECT:
            i_mapping = insert_itbl(
                NULL, ctbl->itbl, key_index, ctbl->list->len,
                ITBL_RELATION_ONE_TO_ONE, ITBL_BEHAVIOR_RESPECT
            );
            c_mapping           = addIndeterminate_alist(ctbl->list);
            c_mapping->chunk_id = LEN_CHUNK(ctbl->chnk);
            c_mapping->value    = value;
            add_chunk(ctbl->chnk, key_item.p, key_item.sz);
            if (p_result != NULL) *p_result = CTBL_REPLACE_CHANGED || CTBL_RESPECT_UNIQUE;
            return c_mapping;
        case CTBL_MODE_SEARCH:
        default:
            if (p_result != NULL) *p_result = CTBL_SEARCH_NOT_FOUND;
            return NULL;
    }
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
