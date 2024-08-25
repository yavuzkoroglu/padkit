/**
 * @file chunktable.c
 * @brief Implements the functions defined in chunktable.h.
 * @see ChunkTable
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/chunktable.h"
#include "padkit/debug.h"
#include "padkit/hash.h"
#include "padkit/memalloc.h"
#include "padkit/prime.h"
#include "padkit/reallocate.h"
#include "padkit/streq.h"

static uint32_t determineNRows(uint32_t const key_count, uint32_t const loadPercent) {
    DEBUG_ASSERT(key_count < UINT32_MAX / 100)
    DEBUG_ASSERT(loadPercent > 0)
    DEBUG_ASSERT(loadPercent < INT32_MAX)
    {
        uint32_t nRows = (key_count > loadPercent)
            ? (key_count / loadPercent) * 100
            : (key_count * 100) / loadPercent;

        if (nRows < key_count) nRows = key_count;
        if (nRows < 11)        nRows = 11;

        return nextPrime(nRows);
    }
}

static void adjust(ChunkTable tbl[static const 1], Chunk const chunk[static const 1]) {
    DEBUG_ASSERT(isValid_ctbl(tbl))
    DEBUG_ASSERT(isValid_chunk(chunk))
    {
        uint32_t const newNRows = determineNRows(tbl->nKeys, tbl->loadPercent);
        if (newNRows <= tbl->nRows) return;
    }

    {
        ChunkTable newTbl[1] = { NOT_A_CHUNK_TABLE };
        constructEmpty_ctbl(newTbl, tbl->capKeys, tbl->loadPercent);

        for (uint32_t row_id = 0; row_id < tbl->nRows; row_id++) {
            if (tbl->rows[row_id] != NULL) {
                ChunkTableEntry const* const entry = tbl->rows[row_id] + 1;
                for (uint32_t n = tbl->rowSizes[row_id]; n > 0; n--) {
                    #ifndef NDEBUG
                        switch (insert_ctbl(newTbl, chunk, entry->key_id, entry->value, CTBL_BEHAVIOR_MULTIPLE)) {
                            case CTBL_INSERT_DUPLICATE_ENTRY:
                                TERMINATE_ERROR_MSG("CTBL_INSERT_DUPLICATE_ENTRY")
                            case CTBL_INSERT_OK:
                            default:
                                break;
                        }
                    #else
                        insert_ctbl(newTbl, chunk, entry->key_id, entry->value, CTBL_BEHAVIOR_MULTIPLE);
                    #endif
                }
            }
        }

        free_ctbl(tbl);
        tbl[0] = newTbl[0];
    }
}

bool isValid_cte(ChunkTableEntry const entry[static const 1]) {
    if (entry->key_id >= INT32_MAX) return 0;

    return 1;
}

void constructEmpty_ctbl(ChunkTable tbl[static const 1], uint32_t const initial_cap, uint32_t const loadPercent) {
    size_t const sz = (size_t)initial_cap * sizeof(int);

    DEBUG_ASSERT(initial_cap > 0)
    DEBUG_ASSERT(initial_cap < UINT32_MAX / 100)
    DEBUG_ASSERT(loadPercent > 0)
    DEBUG_ASSERT(loadPercent < INT32_MAX)
    DEBUG_ASSERT(sz / sizeof(int) == (size_t)initial_cap)

    tbl->nKeys          = 0;
    tbl->capKeys        = initial_cap;
    tbl->keys           = mem_alloc(sz);
    tbl->loadPercent    = loadPercent;
    tbl->nRows          = determineNRows(initial_cap, loadPercent);
    tbl->rowSizes       = mem_calloc((size_t)tbl->nRows, sizeof(uint32_t));
    tbl->rowCaps        = mem_calloc((size_t)tbl->nRows, sizeof(uint32_t));
    tbl->rows           = mem_calloc((size_t)tbl->nRows, sizeof(uint32_t*));
}

void flush_ctbl(ChunkTable tbl[static const 1]) {
    DEBUG_ASSERT(isValid_ctbl(tbl))

    tbl->nKeys = 0;
    memset(tbl->rowSizes, 0, tbl->nRows * sizeof(uint32_t));
}

void free_ctbl(ChunkTable tbl[static const 1]) {
    DEBUG_ASSERT(isValid_ctbl(tbl))

    free(tbl->keys);
    free(tbl->rowSizes);
    free(tbl->rowCaps);

    for (uint32_t row_id = tbl->nRows - 1; row_id != UINT32_MAX; row_id--)
        free(tbl->rows[row_id]);

    free(tbl->rows);
    tbl[0] = NOT_A_CHUNK_TABLE;
}

ChunkTableEntry* get_ctbl(
    ChunkTable const tbl[static const 1], Chunk const chunk[static const 1],
    char const key[static const 1], uint64_t const key_len
) {
    DEBUG_ASSERT(isValid_ctbl(tbl))
    DEBUG_ASSERT(isValid_chunk(chunk))
    #if UINT64_MAX < SIZE_MAX
        DEBUG_ASSERT(key_len < INT64_MAX)
    #else
        DEBUG_ASSERT(key_len < SIZE_MAX >> 1)
    #endif
    {
        uint32_t const row_id = hash_str(key, key_len) % tbl->nRows;
        if (tbl->rows[row_id] == NULL) return NULL;

        for (
            ChunkTableEntry* candidate = tbl->rows[row_id] + tbl->rowSizes[row_id];
            isValid_cte(candidate);
            candidate--
        ) {
            char const* const candidate_key = get_chunk(chunk, candidate->key_id);
            if (candidate_key == NULL) continue;

            if (str_eq_n(key, candidate_key, (size_t)key_len)) return candidate;
        }

        return NULL;
    }
}

uint32_t getEntryCount_ctbl(ChunkTable const tbl[static const 1]) {
    DEBUG_ASSERT(isValid_ctbl(tbl))
    {
        uint32_t count = 0;
        for (uint32_t row_id = 0; row_id < tbl->nRows; row_id++)
            count += tbl->rowSizes[row_id];
        return count;
    }
}

ChunkTableEntry* getExact_ctbl(
    ChunkTable const tbl[static const 1], Chunk const chunk[static const 1],
    char const key[static const 1], uint64_t const key_len, uint32_t const value
) {
    DEBUG_ASSERT(isValid_ctbl(tbl))
    DEBUG_ASSERT(isValid_chunk(chunk))
    #if UINT64_MAX < SIZE_MAX
        DEBUG_ASSERT(key_len < INT64_MAX)
    #else
        DEBUG_ASSERT(key_len < SIZE_MAX >> 1)
    #endif
    {
        uint32_t const row_id = hash_str(key, key_len) % tbl->nRows;
        if (tbl->rows[row_id] == NULL) return NULL;

        for (
            ChunkTableEntry* candidate = tbl->rows[row_id] + tbl->rowSizes[row_id];
            isValid_cte(candidate);
            candidate--
        ) {
            char const* const candidate_key = get_chunk(chunk, candidate->key_id);
            if (candidate_key == NULL) continue;

            if (str_eq_n(key, candidate_key, (size_t)key_len) && value == candidate->value)
                return candidate;
        }
    }

    return NULL;
}

uint32_t getKeyCount_ctbl(ChunkTable const tbl[static const 1]) {
    DEBUG_ASSERT(isValid_ctbl(tbl))
    return tbl->nKeys;
}

int insert_ctbl(
    ChunkTable tbl[static const 1], Chunk const chunk[static const 1],
    uint32_t const key_id, uint32_t const value,
    int const ctbl_insert_behavior
) {
    DEBUG_ASSERT(isValid_ctbl(tbl))
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ASSERT(key_id < chunk->nStrings)
    DEBUG_ASSERT(IS_VALID_CTBL_INSERT_BEHAVIOR(ctbl_insert_behavior))
    {
        char const* const key   = get_chunk(chunk, key_id);
        uint64_t const key_len  = strlen_chunk(chunk, key_id);
        uint32_t const row_id   = hash_str(key, key_len) % tbl->nRows;

        /* Initialize a new row if necessary. */
        if (tbl->rows[row_id] == NULL) {
            DEBUG_ASSERT(CHUNK_TABLE_INITIAL_ROW_CAP < SIZE_MAX / sizeof(ChunkTableEntry))
            tbl->rowCaps[row_id] = CHUNK_TABLE_INITIAL_ROW_CAP;
            tbl->rows[row_id] = mem_alloc(
                (size_t)tbl->rowCaps[row_id] * sizeof(ChunkTableEntry)
            );
            tbl->rows[row_id][0] = NOT_A_CHUNK_TABLE_ENTRY;
        }

        {
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
                        case CTBL_BEHAVIOR_UNIQUE:
                        default:
                            return CTBL_INSERT_DUPLICATE_KEY;
                    }
                }
            }

            if (!keyExists) {
                /* Adjust the key cap if necessary. */
                REALLOC_IF_NECESSARY(
                    uint32_t, tbl->keys,
                    uint32_t, tbl->capKeys, tbl->nKeys
                )

                /* Insert the key index. */
                tbl->keys[tbl->nKeys++] = key_id;
            }
        }

        /* Adjust the cap if necessary. */
        tbl->rowSizes[row_id]++;
        REALLOC_IF_NECESSARY(
            ChunkTableEntry, tbl->rows[row_id],
            uint32_t, tbl->rowCaps[row_id], tbl->rowSizes[row_id]
        )

        /* Insert to the chunktable. */
        tbl->rows[row_id][tbl->rowSizes[row_id]] = (ChunkTableEntry){ key_id, value };
    }

    /* Adjust the # of rows. */
    adjust(tbl, chunk);

    return CTBL_INSERT_OK;
}

bool isValid_ctbl(ChunkTable const tbl[static const 1]) {
    if (tbl->capKeys == 0)                  return 0;
    if (tbl->capKeys >= UINT32_MAX / 100)   return 0;
    if (tbl->nKeys > tbl->capKeys)          return 0;
    if (tbl->keys == NULL)                  return 0;
    if (tbl->loadPercent == 0)              return 0;
    if (tbl->loadPercent >= INT32_MAX)      return 0;
    if (tbl->nRows == 0)                    return 0;
    if (tbl->nRows >= INT32_MAX)            return 0;
    if (tbl->rowSizes == NULL)              return 0;
    if (tbl->rowCaps == NULL)               return 0;
    if (tbl->rows == NULL)                  return 0;

    return 1;
}

void construct_ctblitr(
    CTblConstIterator itr[static const 1],
    ChunkTable const tbl[static const 1], Chunk const chunk[static const 1],
    char const key[static const 1], uint64_t const key_len
) {
    DEBUG_ASSERT(isValid_ctbl(tbl))
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ASSERT(key_len < INT64_MAX)

    itr->tbl        = tbl;
    itr->chunk      = chunk;
    itr->key        = key;
    itr->key_len    = key_len;
    itr->entry      = get_ctbl(tbl, chunk, key, key_len);
}

bool isValid_ctblitr(CTblConstIterator const itr[static const 1]) {
    if (itr->tbl == NULL)           return 0;
    if (!isValid_ctbl(itr->tbl))    return 0;
    if (itr->chunk == NULL)         return 0;
    if (!isValid_chunk(itr->chunk)) return 0;
    if (itr->key == NULL)           return 0;
    if (itr->key_len >= INT64_MAX)  return 0;

    return 1;
}

ChunkTableEntry const* next_ctblitr(CTblConstIterator itr[static const 1]) {
    DEBUG_ASSERT(isValid_ctblitr(itr))
    #if SIZE_MAX < UINT64_MAX
        DEBUG_ASSERT(itr->key_len < SIZE_MAX >> 1)
    #endif

    if (!isValid_cte(itr->entry)) {
        return NULL;
    } else {
        ChunkTableEntry const* const entry_to_be_returned = itr->entry;
        while (isValid_cte(--itr->entry)) {
            char const* const candidate_key = get_chunk(itr->chunk, itr->entry->key_id);
            if (candidate_key != NULL && str_eq_n(itr->key, candidate_key, (size_t)itr->key_len))
                break;
        }

        return entry_to_be_returned;
    }
}
