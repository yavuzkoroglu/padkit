/**
 * @file chunktable.c
 * @brief Implements the functions defined in chunktable.h.
 * @see ChunkTable
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/chunktable.h"
#include "padkit/hash.h"
#include "padkit/prime.h"
#include "padkit/reallocate.h"
#include "padkit/streq.h"

static uint32_t determineNRows(uint32_t const key_count, uint32_t const loadPercent) {
    #ifndef NDEBUG
        if (key_count >= 0xFFFFFFFF / 100) return 0xFFFFFFFF;
        if (loadPercent == 0)              return 0xFFFFFFFF;
    #endif
    uint32_t nRows = (key_count > loadPercent)
        ? (key_count / loadPercent) * 100
        : (key_count * 100) / loadPercent;

    if (nRows < key_count) nRows = key_count;
    if (nRows < 11)        nRows = 11;

    return nextPrime(nRows);
}

static
#ifndef NDEBUG
bool
#else
void
#endif
adjust(ChunkTable* const tbl, Chunk const* const chunk) {
    #ifndef NDEBUG
        if (!isValid_ctbl(tbl))    return 0;
        if (!isValid_chunk(chunk)) return 0;
    #endif

    uint32_t const newNRows = determineNRows(tbl->nKeys, tbl->loadPercent);
    #ifndef NDEBUG
        if (newNRows == 0xFFFFFFFF) return 0;
    #endif

    if (newNRows <= tbl->nRows)
    #ifndef NDEBUG
        return 1;
    #else
        return;
    #endif

    ChunkTable newTbl;
    #ifndef NDEBUG
        if (!constructEmpty_ctbl(&newTbl, tbl->capKeys, tbl->loadPercent)) return 0;
    #else
        constructEmpty_ctbl(&newTbl, tbl->capKeys, tbl->loadPercent);
    #endif

    for (uint32_t row_id = 0; row_id < tbl->nRows; row_id++) {
        if (tbl->rows[row_id] == NULL) continue;
        ChunkTableEntry const* entry = tbl->rows[row_id] + 1;
        for (uint32_t n = tbl->rowSizes[row_id]; n > 0; n--) {
            #ifndef NDEBUG
                switch (
                    insert_ctbl(
                        &newTbl, chunk, entry->key_id, entry->value, CTBL_BEHAVIOR_MULTIPLE
                    )
                ) {
                    case CTBL_INSERT_ERROR:
                    case CTBL_INSERT_DUPLICATE_ENTRY:
                        return 0;
                }
            #else
                insert_ctbl(
                    &newTbl, chunk, entry->key_id, entry->value, CTBL_BEHAVIOR_MULTIPLE
                );
            #endif
        }
    }

    #ifndef NDEBUG
        if (!free_ctbl(tbl)) return 0;
    #else
        free_ctbl(tbl);
    #endif
    *tbl = newTbl;

    #ifndef NDEBUG
        return 1;
    #endif
}

bool isValid_cte(ChunkTableEntry const* const entry) {
    return entry && entry->key_id != 0xFFFFFFFF;
}

#ifndef NDEBUG
bool
#else
void
#endif
constructEmpty_ctbl(ChunkTable* tbl, uint32_t const initial_cap, uint32_t const loadPercent) {
    #ifndef NDEBUG
        if (tbl == NULL)                     return 0;
        if (initial_cap == 0)                return 0;
        if (initial_cap >= 0xFFFFFFFF / 100) return 0;
        if (loadPercent == 0)                return 0;
    #endif

    tbl->nKeys   = 0;
    tbl->capKeys = initial_cap;

    tbl->keys = malloc(initial_cap * sizeof(int));
    #ifndef NDEBUG
        if (tbl->keys == NULL) return 0;
    #endif

    tbl->loadPercent = loadPercent;
    tbl->nRows       = determineNRows(initial_cap, loadPercent);

    tbl->rowSizes = calloc(tbl->nRows, sizeof(uint32_t));
    #ifndef NDEBUG
        if (tbl->rowSizes == NULL) return 0;
    #endif

    tbl->rowCaps = calloc(tbl->nRows, sizeof(uint32_t));
    #ifndef NDEBUG
        if (tbl->rowCaps == NULL) return 0;
    #endif

    tbl->rows = calloc(tbl->nRows, sizeof(uint32_t*));
    #ifndef NDEBUG
        if (tbl->rows == NULL) return 0;
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
flush_ctbl(ChunkTable* const tbl) {
    #ifndef NDEBUG
        if (!isValid_ctbl(tbl)) return 0;
    #endif
    tbl->nKeys = 0;
    memset(tbl->rowSizes, 0, tbl->nRows * sizeof(unsigned));
    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
free_ctbl(ChunkTable* const tbl) {
    #ifndef NDEBUG
        if (!isValid_ctbl(tbl)) return 0;
    #endif
    free(tbl->keys);
    free(tbl->rowSizes);
    free(tbl->rowCaps);

    for (uint32_t row_id = tbl->nRows - 1; row_id != 0xFFFFFFFF; row_id--)
        free(tbl->rows[row_id]);

    free(tbl->rows);
    #ifndef NDEBUG
        return 1;
    #endif
}

ChunkTableEntry* get_ctbl(
    ChunkTable const* const tbl, Chunk const* const chunk,
    char const* const key, uint64_t const key_len
) {
    #ifndef NDEBUG
        if (!isValid_ctbl(tbl)) return 0;
        if (!isValid_chunk(chunk)) return 0;
        if (key == NULL) return NULL;
    #endif

    unsigned const row_id = hash_str(key, key_len) % tbl->nRows;
    if (tbl->rows[row_id] == NULL) return NULL;

    for (
        ChunkTableEntry* candidate = tbl->rows[row_id] + tbl->rowSizes[row_id];
        isValid_cte(candidate);
        candidate--
    ) {
        char const* const candidate_key = get_chunk(chunk, candidate->key_id);
        if (candidate_key == NULL) continue;

        if (str_eq_n(key, candidate_key, key_len)) return candidate;
    }

    return NULL;
}

uint32_t getEntryCount_ctbl(ChunkTable const* const tbl) {
    #ifndef NDEBUG
        if (!isValid_ctbl(tbl)) return 0xFFFFFFFF;
    #endif
    uint32_t count = 0;
    for (
        uint32_t row_id = 0;
        row_id < tbl->nRows;
        row_id++
    ) count += tbl->rowSizes[row_id];
    return count;
}

ChunkTableEntry* getExact_ctbl(
    ChunkTable const* const tbl, Chunk const* const chunk,
    char const* const key, uint64_t const key_len, uint32_t const value
) {
    #ifndef NDEBUG
        if (!isValid_ctbl(tbl)) return 0;
        if (!isValid_chunk(chunk)) return 0;
        if (key == NULL) return NULL;
    #endif

    unsigned const row_id = hash_str(key, key_len) % tbl->nRows;
    if (tbl->rows[row_id] == NULL) return NULL;

    for (
        ChunkTableEntry* candidate = tbl->rows[row_id] + tbl->rowSizes[row_id];
        isValid_cte(candidate);
        candidate--
    ) {
        char const* const candidate_key = get_chunk(chunk, candidate->key_id);
        if (candidate_key == NULL) continue;

        if (str_eq_n(key, candidate_key, key_len) && value == candidate->value)
            return candidate;
    }

    return NULL;
}

uint32_t getKeyCount_ctbl(ChunkTable const* const tbl) {
    #ifndef NDEBUG
        if (!isValid_ctbl(tbl)) return 0xFFFFFFFF;
    #endif
    return tbl->nKeys;
}

int insert_ctbl(
    ChunkTable* const tbl, Chunk const* const chunk,
    uint32_t const key_id, uint32_t const value,
    int const ctbl_insert_behavior
) {
    #ifndef NDEBUG
        if (!isValid_ctbl(tbl))    return CTBL_INSERT_ERROR;
        if (!isValid_chunk(chunk)) return CTBL_INSERT_ERROR;
    #endif

    char const* const key = get_chunk(chunk, key_id);
    #ifndef NDEBUG
        if (key == NULL) return CTBL_INSERT_ERROR;
    #endif

    uint64_t const key_len = strlen_chunk(chunk, key_id);
    unsigned const row_id  = hash_str(key, key_len) % tbl->nRows;

    /* Initialize a new row if necessary. */
    if (tbl->rows[row_id] == NULL) {
        tbl->rowCaps[row_id] = CHUNK_TABLE_INITIAL_ROW_CAP;
        tbl->rows[row_id] = malloc(
            tbl->rowCaps[row_id] * sizeof(ChunkTableEntry)
        );
        #ifndef NDEBUG
            if (tbl->rows[row_id] == NULL) return CTBL_INSERT_ERROR;
        #endif
        tbl->rows[row_id][0] = NOT_A_CHUNK_TABLE_ENTRY;
    }

    bool keyExists = 0;
    for (
        ChunkTableEntry* entry = tbl->rows[row_id] + tbl->rowSizes[row_id];
        isValid_cte(entry);
        entry--
    ) {
        char const* entry_key = get_chunk(chunk, entry->key_id);
        if (str_eq_n(key, entry_key, key_len)) {
            keyExists = 1;
            switch (ctbl_insert_behavior) {
                case CTBL_BEHAVIOR_MULTIPLE:
                    if (value == entry->value) return CTBL_INSERT_DUPLICATE_ENTRY;
                    break;
                case CTBL_BEHAVIOR_REPLACE:
                    entry->value = value;
                    return CTBL_INSERT_DUPLICATE_KEY;
                default:
                    return CTBL_INSERT_DUPLICATE_KEY;
            }
        }
    }

    if (!keyExists) {
        /* Adjust the key cap if necessary. */
        REALLOC_IF_NECESSARY(
            uint32_t, tbl->keys,
            uint32_t, tbl->capKeys, tbl->nKeys,
            return CTBL_INSERT_ERROR;
        )

        /* Insert the key index. */
        tbl->keys[tbl->nKeys++] = key_id;
    }

    /* Adjust the cap if necessary. */
    tbl->rowSizes[row_id]++;
    REALLOC_IF_NECESSARY(
        ChunkTableEntry, tbl->rows[row_id],
        uint32_t, tbl->rowCaps[row_id], tbl->rowSizes[row_id],
        return CTBL_INSERT_ERROR;
    )

    /* Insert to the chunktable. */
    tbl->rows[row_id][tbl->rowSizes[row_id]] = (ChunkTableEntry){ key_id, value };

    /* Adjust the # of rows. */
    #ifndef NDEBUG
        if (!adjust(tbl, chunk)) return CTBL_INSERT_ERROR;
    #else
        adjust(tbl, chunk);
    #endif
    return CTBL_INSERT_OK;
}

bool isValid_ctbl(ChunkTable const* const tbl) {
    return tbl != NULL                     &&
           tbl->capKeys > 0                &&
           tbl->capKeys < 0xFFFFFFFF / 100 &&
           tbl->nKeys <= tbl->capKeys      &&
           tbl->keys != NULL               &&
           tbl->loadPercent != 0           &&
           tbl->nRows != 0                 &&
           tbl->rowSizes != NULL           &&
           tbl->rowCaps != NULL            &&
           tbl->rows != NULL;
}

#ifndef NDEBUG
bool
#else
void
#endif
construct_ctblitr(
    CTblConstIterator* const itr,
    ChunkTable const* const tbl, Chunk const* const chunk,
    char const* const key, uint64_t const key_len
) {
    #ifndef NDEBUG
        if (itr == NULL)                    return 0;
        if (!isValid_ctbl(tbl))             return 0;
        if (!isValid_chunk(chunk))          return 0;
        if (key == NULL)                    return 0;
        if (key_len == 0xFFFFFFFFFFFFFFFF)  return 0;
    #endif

    itr->tbl        = tbl;
    itr->chunk      = chunk;
    itr->key        = key;
    itr->key_len    = key_len;
    itr->entry      = get_ctbl(tbl, chunk, key, key_len);

    #ifndef NDEBUG
        return 1;
    #endif
}

bool isValid_ctblitr(CTblConstIterator const* const itr) {
    return  itr != NULL                 &&
            isValid_ctbl(itr->tbl)      &&
            isValid_chunk(itr->chunk)   &&
            itr->key != NULL            &&
            itr->key_len != 0xFFFFFFFFFFFFFFFF;
}

ChunkTableEntry const* next_ctblitr(CTblConstIterator* const itr) {
    #ifndef NDEBUG
        if (!isValid_ctblitr(itr)) return NULL;
    #endif

    if (!isValid_cte(itr->entry)) return NULL;

    ChunkTableEntry const* const entry_to_be_returned = itr->entry;
    while (isValid_cte(--itr->entry)) {
        char const* const candidate_key = get_chunk(itr->chunk, itr->entry->key_id);
        if (candidate_key != NULL && str_eq_n(itr->key, candidate_key, itr->key_len))
            break;
    }

    return entry_to_be_returned;
}
