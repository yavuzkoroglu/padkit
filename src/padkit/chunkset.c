/**
 * @file chunkset.c
 * @brief Implements the functions defined in chunkset.h.
 * @see ChunkSet
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/chunkset.h"
#include "padkit/debug.h"
#include "padkit/hash.h"
#include "padkit/memalloc.h"
#include "padkit/prime.h"
#include "padkit/reallocate.h"
#include "padkit/streq.h"

static uint32_t determineNRows(uint32_t const str_count, uint32_t const loadPercent) {
    DEBUG_ASSERT(str_count < UINT32_MAX / 100)
    DEBUG_ERROR_IF(loadPercent == 0)

    uint32_t nRows = (str_count > loadPercent)
        ? (str_count / loadPercent) * 100
        : (str_count * 100) / loadPercent;

    if (nRows < str_count) nRows = str_count;
    if (nRows < 11)        nRows = 11;

    return nextPrime(nRows);
}

static void adjust(ChunkSet set[static const 1]) {
    DEBUG_ASSERT(isValid_cset(set))

    Chunk* const chunk = (Chunk*)set;

    uint32_t const newNRows = determineNRows(chunk->nStrings, set->loadPercent);
    if (newNRows <= set->nRows) return;

    free(set->rowSize);
    free(set->rowCap);
    for (uint32_t** row = set->table + set->nRows; --row >= set->table; free(*row));
    free(set->table);
    set->nRows = newNRows;

    set->rowSize    = mem_calloc((size_t)newNRows, sizeof(uint32_t));
    set->rowCap     = mem_calloc((size_t)newNRows, sizeof(uint32_t));
    set->table      = mem_calloc((size_t)newNRows, sizeof(uint32_t*));

    for (uint32_t key_id = 0; key_id < chunk->nStrings; key_id++) {
        char const* const key   = get_chunk(chunk, key_id);
        uint64_t const key_len  = strlen_chunk(chunk, key_id);
        uint32_t const row_id   = hash_str(key, key_len) % newNRows;

        /* Initialize the row if necessary. */
        if (set->rowSize[row_id] == 0) {
            uint32_t* const row_ptr = mem_alloc(
                (size_t)CHUNK_SET_INITIAL_ROW_CAP * sizeof(uint32_t)
            );
            set->rowCap[row_id] = CHUNK_SET_INITIAL_ROW_CAP;
            set->table[row_id]  = row_ptr;
        }

        /* Adjust Cap */
        REALLOC_IF_NECESSARY(
            uint32_t, set->table[row_id],
            uint32_t, set->rowCap[row_id], set->rowSize[row_id]
        )

        /* Adjust Size and Insert Index to Table */
        set->table[row_id][set->rowSize[row_id]++] = key_id;
    }
}

uint32_t addKey_cset(ChunkSet set[static const 1], char const key[static const 1], uint64_t const n) {
    DEBUG_ASSERT(isValid_cset(set))
    DEBUG_ERROR_IF(key == NULL)
    DEBUG_ASSERT((size_t)n <= strlen(key))

    Chunk* const chunk = (Chunk*)set;
    uint32_t const row_id = hash_str(key, n) % set->nRows;

    /* Initialize the row if necessary. */
    if (set->table[row_id] == NULL) {
        uint32_t* const row_ptr = mem_alloc(
            (size_t)CHUNK_SET_INITIAL_ROW_CAP * sizeof(uint32_t)
        );
        set->rowCap[row_id] = CHUNK_SET_INITIAL_ROW_CAP;
        set->table[row_id] = row_ptr;
    }

    for (
        uint32_t* key_id = set->table[row_id] + set->rowSize[row_id];
        --key_id >= set->table[row_id];
    ) {
        char const* const candidate = get_chunk(chunk, *key_id);
        if (!str_eq_n(key, candidate, n)) continue;
        /* This exact key exists in the ChunkSet. Do nothing more. */
        return *key_id;
    }

    /* Adjust Cap */
    REALLOC_IF_NECESSARY(
        uint32_t, set->table[row_id],
        uint32_t, set->rowCap[row_id], set->rowSize[row_id]
    )

    uint32_t const key_id = add_chunk(chunk, key, n);
    set->table[row_id][set->rowSize[row_id]++] = key_id;

    adjust(set);

    return key_id;
}

void constructEmpty_cset(
    ChunkSet set[static const 1], uint64_t const initial_cap,
    uint32_t const initial_stringsCap, uint32_t const loadPercent
) {
    DEBUG_ERROR_IF(set == NULL)
    DEBUG_ERROR_IF(loadPercent == 0)

    constructEmpty_chunk((Chunk*)set, initial_cap, initial_stringsCap);

    set->loadPercent    = loadPercent;
    set->nRows          = determineNRows(initial_stringsCap, loadPercent);
    set->rowSize        = mem_calloc((size_t)set->nRows, sizeof(uint32_t));
    set->rowCap         = mem_calloc((size_t)set->nRows, sizeof(uint32_t));
    set->table          = mem_calloc((size_t)set->nRows, sizeof(uint32_t*));
}

void flush_cset(ChunkSet set[static const 1]) {
    DEBUG_ASSERT(isValid_cset(set))

    flush_chunk((Chunk*)set);
    memset(set->rowSize, 0, set->nRows * sizeof(uint32_t));
}

void free_cset(ChunkSet set[static const 1]) {
    DEBUG_ASSERT(isValid_cset(set))

    free(set->rowSize);
    free(set->rowCap);
    for (uint32_t** row = set->table + set->nRows; --row >= set->table; free(*row)) {}
    free(set->table);
    free_chunk((Chunk*)set);
    set[0] = NOT_A_CHUNK_SET;
}

char const* getKey_cset(ChunkSet const set[static const 1], uint32_t const key_id) {
    DEBUG_ASSERT(isValid_cset(set))
    DEBUG_ERROR_IF(set->nStrings == 0)
    return get_chunk((Chunk const*)set, key_id);
}

uint32_t getKeyCount_cset(ChunkSet const set[static const 1]) {
    DEBUG_ASSERT(isValid_cset(set))
    return set->nStrings;
}

uint32_t getKeyId_cset(ChunkSet const set[static const 1], char const key[static const 1], uint64_t const n) {
    DEBUG_ASSERT(isValid_cset(set))
    DEBUG_ERROR_IF(key == NULL)
    DEBUG_ASSERT((size_t)n <= strlen(key))

    Chunk const* const chunk = (Chunk const*)set;
    uint32_t const row_id    = hash_str(key, n) % set->nRows;

    if (set->table[row_id] == NULL) return UINT32_MAX;

    for (
        uint32_t* key_id = set->table[row_id] + set->rowSize[row_id];
        --key_id >= set->table[row_id];
    ) {
        char const* const candidate  = get_chunk(chunk, *key_id);
        uint64_t const candidate_len = strlen_chunk(chunk, *key_id);
        if (!str_eq_n(key, candidate, candidate_len)) continue;
        return *key_id;
    }

    /* Could NOT find the key. */
    return UINT32_MAX;
}

bool isValid_cset(ChunkSet const set[static const 1]) {
    return isValid_chunk((Chunk const*)set) &&
           set->loadPercent != 0            &&
           set->nRows != 0                  &&
           set->rowSize != NULL             &&
           set->rowCap != NULL              &&
           set->table != NULL;
}

uint64_t strlen_cset(ChunkSet const set[static const 1], uint32_t const key_id) {
    DEBUG_ASSERT(isValid_cset(set))
    return strlen_chunk((Chunk const*)set, key_id);
}
