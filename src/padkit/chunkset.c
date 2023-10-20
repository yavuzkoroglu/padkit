/**
 * @file chunkset.c
 * @brief Implements the functions defined in chunkset.h.
 * @see ChunkSet
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/chunkset.h"
#include "padkit/hash.h"
#include "padkit/prime.h"
#include "padkit/reallocate.h"
#include "padkit/streq.h"

static uint32_t determineNRows(uint32_t const str_count, uint32_t const loadPercent) {
    #ifndef NDEBUG
        if (str_count >= 0xFFFFFFFF / 100) return 0xFFFFFFFF;
        if (loadPercent == 0)              return 0xFFFFFFFF;
    #endif
    uint32_t nRows = (str_count > loadPercent)
        ? (str_count / loadPercent) * 100
        : (str_count * 100) / loadPercent;

    if (nRows < str_count) nRows = str_count;
    if (nRows < 11)        nRows = 11;

    return nextPrime(nRows);
}

static
#ifndef NDEBUG
bool
#else
void
#endif
adjust(ChunkSet* const set) {
    #ifndef NDEBUG
        if (!isValid_cset(set)) return 0;
    #endif

    Chunk* const chunk = (Chunk*)set;

    unsigned const newNRows = determineNRows(chunk->nStrings, set->loadPercent);
    #ifndef NDEBUG
        if (newNRows == 0xFFFFFFFF) return 0;
    #endif

    if (newNRows <= set->nRows)
        #ifndef NDEBUG
            return 1;
        #else
            return;
        #endif

    free(set->rowSize);
    free(set->rowCap);
    for (uint32_t** row = set->table + set->nRows; --row >= set->table; free(*row));
    free(set->table);
    set->nRows = newNRows;

    set->rowSize = calloc(newNRows, sizeof(uint32_t));
    #ifndef NDEBUG
        if (set->rowSize == NULL) return 0;
    #endif

    set->rowCap = calloc(newNRows, sizeof(uint32_t));
    #ifndef NDEBUG
        if (set->rowCap == NULL) return 0;
    #endif

    set->table = calloc(newNRows, sizeof(uint32_t*));
    #ifndef NDEBUG
        if (set->table == NULL) return 0;
    #endif

    for (uint32_t key_id = 0; key_id < chunk->nStrings; key_id++) {
        char const* const key  = get_chunk(chunk, key_id);
        uint64_t const key_len = strlen_chunk(chunk, key_id);
        unsigned const row_id  = hash_str(key, key_len) % newNRows;

        /* Initialize the row if necessary. */
        if (set->rowSize[row_id] == 0) {
            uint32_t* const row_ptr = malloc(
                CHUNK_SET_INITIAL_ROW_CAP * sizeof(uint32_t)
            );
            #ifndef NDEBUG
                if (row_ptr == NULL) return 0;
            #endif
            set->rowCap[row_id] = CHUNK_SET_INITIAL_ROW_CAP;
            set->table[row_id] = row_ptr;
        }

        /* Adjust Cap */
        REALLOC_IF_NECESSARY(
            uint32_t, set->table[row_id],
            uint32_t, set->rowCap[row_id], set->rowSize[row_id],
            return 0;
        )

        /* Adjust Size and Insert Index to Table */
        set->table[row_id][set->rowSize[row_id]++] = key_id;
    }

    #ifndef NDEBUG
        return 1;
    #endif
}

uint32_t addKey_cset(ChunkSet* const set, char const* const key, uint64_t const n) {
    #ifndef NDEBUG
        if (!isValid_cset(set)) return 0xFFFFFFFF;
        if (key == NULL)        return 0xFFFFFFFF;
    #endif

    Chunk* const chunk = (Chunk*)set;
    unsigned const row_id = hash_str(key, n) % set->nRows;

    /* Initialize the row if necessary. */
    if (set->table[row_id] == NULL) {
        uint32_t* const row_ptr = malloc(
            CHUNK_SET_INITIAL_ROW_CAP * sizeof(uint32_t)
        );
        #ifndef NDEBUG
            if (row_ptr == NULL) return 0xFFFFFFFF;
        #endif
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
        uint32_t, set->rowCap[row_id], set->rowSize[row_id],
        return 0xFFFFFFFF;
    )

    uint32_t const key_id = add_chunk(chunk, key, n);
    #ifndef NDEBUG
        if (key_id == 0xFFFFFFFF) return 0xFFFFFFFF;
    #endif
    set->table[row_id][set->rowSize[row_id]++] = key_id;

    #ifndef NDEBUG
        if (!adjust(set)) return 0xFFFFFFFF;
        if (set->start[0] == '\0') return 0xFFFFFFFF;
    #else
        adjust(set);
    #endif

    return key_id;
}

#ifndef NDEBUG
bool
#else
void
#endif
constructEmpty_cset(
    ChunkSet* set, uint64_t const initial_cap,
    uint32_t const initial_stringsCap, uint32_t const loadPercent
) {
    #ifndef NDEBUG
        if (set == NULL)                                                         return 0;
        if (loadPercent == 0)                                                    return 0;
        if (!constructEmpty_chunk((Chunk*)set, initial_cap, initial_stringsCap)) return 0;
    #else
        constructEmpty_chunk((Chunk*)set, initial_cap, initial_stringsCap);
    #endif

    set->loadPercent = loadPercent;

    set->nRows = determineNRows(initial_stringsCap, loadPercent);
    #ifndef NDEBUG
        if (set->nRows == 0xFFFFFFFF) return 0;
    #endif

    set->rowSize = calloc(set->nRows, sizeof(uint32_t));
    #ifndef NDEBUG
        if (set->rowSize == NULL) return 0;
    #endif

    set->rowCap = calloc(set->nRows, sizeof(uint32_t));
    #ifndef NDEBUG
        if (set->rowCap == NULL) return 0;
    #endif

    set->table = calloc(set->nRows, sizeof(uint32_t*));
    #ifndef NDEBUG
        if (set->table == NULL) return 0;
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
flush_cset(ChunkSet* const set) {
    #ifndef NDEBUG
        if (!isValid_cset(set))        return 0;
        if (!flush_chunk((Chunk*)set)) return 0;
    #else
        flush_chunk((Chunk*)set);
    #endif
    memset(set->rowSize, 0, set->nRows * sizeof(uint32_t));
    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
free_cset(ChunkSet* const set) {
    #ifndef NDEBUG
        if (!isValid_cset(set)) return 0;
    #endif
    free_chunk((Chunk*)set);
    free(set->rowSize);
    free(set->rowCap);
    for (uint32_t** row = set->table + set->nRows; --row >= set->table; free(*row));
    free(set->table);
    #ifndef NDEBUG
        return 1;
    #endif
}

char const* getKey_cset(ChunkSet const* const set, uint32_t const key_id) {
    #ifndef NDEBUG
        if (!isValid_cset(set)) return NULL;
    #endif
    return get_chunk((Chunk const*)set, key_id);
}

uint32_t getKeyCount_cset(ChunkSet const* const set) {
    #ifndef NDEBUG
        if (!isValid_cset(set)) return 0xFFFFFFFF;
    #endif
    return set->nStrings;
}

uint32_t getKeyId_cset(ChunkSet const* const set, char const* const key, uint64_t const n) {
    #ifndef NDEBUG
        if (!isValid_cset(set)) return 0xFFFFFFFF;
        if (key == NULL)        return 0xFFFFFFFF;
    #endif
    Chunk const* const chunk = (Chunk const*)set;
    unsigned const row_id    = hash_str(key, n) % set->nRows;

    if (set->table[row_id] == NULL) return 0xFFFFFFFF;

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
    return 0xFFFFFFFF;
}

bool isValid_cset(ChunkSet const* const set) {
    return isValid_chunk((Chunk const*)set) &&
           set->loadPercent != 0            &&
           set->nRows != 0                  &&
           set->rowSize != NULL             &&
           set->rowCap != NULL              &&
           set->table != NULL;
}

uint64_t strlen_cset(ChunkSet const* const set, uint32_t const key_id) {
    #ifndef NDEBUG
        if (!isValid_cset(set)) return 0xFFFFFFFFFFFFFFFF;
    #endif
    return strlen_chunk((Chunk const*)set, key_id);
}
