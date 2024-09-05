/**
 * @file chunk.c
 * @brief Implements the functions defined in chunk.h
 * @see Chunk
 * @author Yavuz Koroglu
 */
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include "padkit/chunk.h"
#include "padkit/debug.h"
#include "padkit/memalloc.h"
#include "padkit/reallocate.h"

#ifndef NDEBUG
    #include "padkit/overlap.h"
#endif

static char const defaultDelimeters[] = " \t\n\v\f\r";

uint32_t add_chunk(
    Chunk chunk[static const 1],
    char const str[static const restrict 1],
    uint64_t const n
) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ASSERT(n < INT64_MAX)
    {
        uint32_t const id     = chunk->nStrings++;
        uint64_t const offset = (chunk->len += !!(chunk->len));

        append_chunk(chunk, str, n);

        chunk->stringOffsets[id] = offset;
        return id;
    }
}

uint32_t addIndex_chunk(Chunk chunk[static const 1], uint32_t const str_id) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ASSERT(str_id < chunk->nStrings)
    {
        uint32_t const id = add_chunk(chunk, "", 0);
        appendIndex_chunk(chunk, str_id);
        return id;
    }
}

char const* append_chunk(
    Chunk chunk[static const 1],
    char const str[static const restrict 1],
    uint64_t const n
) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    #if UINT64_MAX < SIZE_MAX
        DEBUG_ASSERT(n < INT64_MAX)
    #else
        DEBUG_ASSERT(n < SIZE_MAX >> 1)
        DEBUG_ASSERT(chunk->len < SIZE_MAX >> 1)
    #endif
    {
        DEBUG_EXECUTE(size_t const sz_chunk = (size_t)chunk->len)
        DEBUG_EXECUTE(size_t const sz_str   = (size_t)n)
        DEBUG_ERROR_IF(overlaps_ptr(chunk->start, str, sz_chunk, sz_str))
    }
    {
        char* const append_start = appendSpace_chunk(chunk, n);
        DEBUG_ERROR_IF(append_start < chunk->start)

        memcpy(append_start, str, n);
        chunk->start[(chunk->len += n)] = '\0';

        REALLOC_IF_NECESSARY(
            uint64_t, chunk->stringOffsets,
            uint32_t, chunk->stringsCap, chunk->nStrings
        )

        /* May try to append when there are no strings. Then, just add a new string. */
        if (chunk->nStrings == 0) {
            DEBUG_ASSERT(append_start == chunk->start)
            chunk->stringOffsets[chunk->nStrings++] = 0;
            return chunk->start;
        }
    }

    return chunk->start + chunk->stringOffsets[chunk->nStrings - 1];
}

char const* appendIndex_chunk(Chunk chunk[static const 1], uint32_t const str_id) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ASSERT(str_id < chunk->nStrings)
    {
        uint64_t const start_offset = chunk->stringOffsets[str_id];
        uint64_t const end_offset   = str_id == chunk->nStrings - 1
            ? chunk->len
            : chunk->stringOffsets[str_id + 1] - 1;
        uint64_t const n            = (uint64_t)(end_offset - start_offset);
        char* const append_start    = appendSpace_chunk(chunk, n);
        DEBUG_ERROR_IF(append_start < chunk->start + start_offset + n)

        memcpy(append_start, chunk->start + start_offset, n);
        chunk->start[(chunk->len += n)] = '\0';
    }

    REALLOC_IF_NECESSARY(
        uint64_t, chunk->stringOffsets,
        uint32_t, chunk->stringsCap, chunk->nStrings
    )

    return chunk->start + chunk->stringOffsets[chunk->nStrings - 1];
}

char* appendSpace_chunk(Chunk chunk[static const 1], uint64_t const size) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ASSERT(size < INT64_MAX)

    if (size > 0) {
        uint64_t const pseudo_len = chunk->len + size;
        DEBUG_ASSERT(pseudo_len < INT64_MAX)

        REALLOC_IF_NECESSARY(
            char, chunk->start,
            uint64_t, chunk->cap, pseudo_len
        )
    }

    return chunk->start + chunk->len;
}

void concat_chunk(Chunk to[static const 1], Chunk const from[static const 1]) {
    DEBUG_ASSERT(isValid_chunk(to))
    DEBUG_ASSERT(isValid_chunk(from))

    if (from->nStrings > 0) {
        uint64_t const hasStrings = (to->nStrings > 0);
        char* const append_start = appendSpace_chunk(to, from->len + hasStrings) + hasStrings;
        memcpy(append_start, from->start, from->len + 1);
        {
            uint32_t const old_str_count = to->nStrings;
            to->nStrings += from->nStrings;
            REALLOC_IF_NECESSARY(uint64_t, to->stringOffsets, uint32_t, to->stringsCap, to->nStrings)
            {
                uint64_t const diff = (uint64_t)(append_start - to->start);
                for (uint32_t from_str_id = 0; from_str_id < from->nStrings; from_str_id++) {
                    uint32_t const to_str_id = from_str_id + old_str_count;
                    to->stringOffsets[to_str_id] = diff + from->stringOffsets[from_str_id];
                }
            }
        }
        to->len += from->len + hasStrings;
    }
}

void constructEmpty_chunk(
    Chunk chunk[static const 1],
    uint64_t const initial_cap,
    uint32_t const initial_stringsCap
) {
    size_t const sz = (size_t)initial_stringsCap * sizeof(uint64_t);

    DEBUG_ASSERT(initial_cap > 0)
    #if UINT64_MAX < SIZE_MAX
        DEBUG_ASSERT(initial_cap < INT64_MAX)
    #else
        DEBUG_ASSERT(initial_cap < SIZE_MAX >> 1)
    #endif
    DEBUG_ASSERT(initial_stringsCap > 0)
    DEBUG_ASSERT(initial_stringsCap < INT32_MAX)
    DEBUG_ASSERT(sz / sizeof(uint64_t) == (size_t)initial_stringsCap)

    chunk->cap              = initial_cap;
    chunk->stringsCap       = initial_stringsCap;
    chunk->nStrings         = 0;
    chunk->len              = 0;
    chunk->stringOffsets    = mem_alloc(sz);
    chunk->start            = mem_alloc((size_t)initial_cap);
    chunk->start[0]         = '\0';
}

void delete_chunk(Chunk chunk[static const 1], uint32_t const str_id) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ASSERT(str_id < chunk->nStrings)

    if (str_id == chunk->nStrings - 1) {
        deleteLast_chunk(chunk);
    } else {
        char* const str     = chunk->start + chunk->stringOffsets[str_id];
        char* const next    = chunk->start + chunk->stringOffsets[str_id + 1];
        uint64_t const diff = (uint64_t)(next - str);
        uint64_t const n    = chunk->len - chunk->stringOffsets[str_id + 1] + 1;
        DEBUG_ASSERT(next > str)
        memmove(str, next, n);

        chunk->nStrings--;
        for (uint32_t i = str_id; i < chunk->nStrings; i++)
            chunk->stringOffsets[i] = chunk->stringOffsets[i + 1] - diff;

        chunk->len -= diff;
    }
}

void deleteLast_chunk(Chunk chunk[static const 1]) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ERROR_IF(chunk->nStrings == 0)
    {
        uint32_t const lastStr_id = --chunk->nStrings;
        if (lastStr_id == 0) {
            flush_chunk(chunk);
        } else {
            uint64_t const max_len = chunk->stringOffsets[lastStr_id] - 1;
            uint64_t const min_len = chunk->stringOffsets[lastStr_id - 1];

            for (
                chunk->start[chunk->len = max_len] = '\0';
                chunk->len > min_len && chunk->start[chunk->len - 1] == '\0';
                chunk->len--
            ) {}
        }
    }
}

void flush_chunk(Chunk chunk[static const 1]) {
    DEBUG_ASSERT(isValid_chunk(chunk))

    chunk->nStrings = 0;
    chunk->len      = 0;
    chunk->start[0] = '\0';
}

void free_chunk(Chunk chunk[static const 1]) {
    DEBUG_ABORT_UNLESS(isValid_chunk(chunk))

    free(chunk->start);
    free(chunk->stringOffsets);
    chunk[0] = NOT_A_CHUNK;
}

uint32_t fromStream_chunk(
    Chunk chunk[static const 1],
    FILE stream[static const 1],
    char const delimeters[]
) {
    DEBUG_ASSERT(isValid_chunk(chunk))

    if (delimeters == NULL) delimeters = defaultDelimeters;

    {
        uint32_t const str_id = fromStreamAsWhole_chunk(chunk, stream);
        if (str_id == UINT32_MAX)
            return UINT32_MAX;

        splitLast_chunk(chunk, delimeters);

        return str_id;
    }
}

uint32_t fromStreamAsWhole_chunk(Chunk chunk[static const 1], FILE stream[static const 1]) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    {
        uint32_t const str_id = add_chunk(chunk, "", 0);
        if (fseek(stream, 0L, SEEK_END) != 0) {
            return UINT32_MAX;
        } else {
            long const size = ftell(stream);
            if (size < 0L) {
                return UINT32_MAX;
            #if ULONG_MAX > SIZE_MAX
                } else if ((unsigned long)size >= SIZE_MAX >> 1) {
                    return UINT32_MAX;
            #endif
            } else if (fseek(stream, 0L, SEEK_SET) != 0) {
                return UINT32_MAX;
            } else {
                char* const append_start = appendSpace_chunk(chunk, (uint64_t)size);
                if (fread(append_start, (size_t)size, 1, stream) != 1)
                    return UINT32_MAX;
            }

            chunk->len += (uint64_t)size;
        }

        return str_id;
    }
}

char const* get_chunk(Chunk const chunk[static const 1], uint32_t const str_id) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ASSERT(str_id < chunk->nStrings)

    return chunk->start + chunk->stringOffsets[str_id];
}

char const* getFirst_chunk(Chunk const chunk[static const 1]) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ERROR_IF(chunk->nStrings == 0)

    return get_chunk(chunk, 0);
}

char const* getLast_chunk(Chunk const chunk[static const 1]) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ERROR_IF(chunk->nStrings == 0)

    return get_chunk(chunk, chunk->nStrings - 1);
}

bool isValid_chunk(Chunk const chunk[static const 1]) {
    if (chunk->cap == 0)                        return 0;
    if (chunk->cap >= INT64_MAX)                return 0;
    if (chunk->cap >= SIZE_MAX >> 1)            return 0;
    if (chunk->stringsCap == 0)                 return 0;
    if (chunk->stringsCap >= INT32_MAX)         return 0;
    if (chunk->stringOffsets == NULL)           return 0;
    if (chunk->start == NULL)                   return 0;
    if (chunk->len > chunk->cap)                return 0;
    if (chunk->nStrings > chunk->stringsCap)    return 0;

    return 1;
}

uint32_t splitLast_chunk(Chunk chunk[static const 1], char const delimeters[]) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ERROR_IF(chunk->nStrings == 0)

    if (delimeters == NULL) delimeters = defaultDelimeters;

    {
        uint32_t const str_id = chunk->nStrings - 1;
        char* str_start       = chunk->start + chunk->stringOffsets[str_id];
        char* str_end         = chunk->start + chunk->len;

        /* Trim from the end */
        for (
            str_end[0] = '\0';
            str_end > str_start && (
                isspace((unsigned char)str_end[-1]) || str_end[-1] == '\0' || strchr(delimeters, str_end[-1])
            );
            chunk->start[--chunk->len] = '\0', str_end--
        ) {}

        /* Trim from the start */
        for (;
            isspace((unsigned char)str_start[0]) || str_start[0] == '\0' || strchr(delimeters, str_start[0]);
            chunk->stringOffsets[str_id]++, *(str_start++) = '\0'
        ) {}

        {
            /* In-Place Split */
            uint32_t nSplitted = 1;
            for (char* chr = str_start; chr < str_end; chr++) {
                if (strchr(delimeters, *chr) == NULL) continue;

                /* Realloc stringOffsets if necessary */
                REALLOC_IF_NECESSARY(
                    uint64_t, chunk->stringOffsets,
                    uint32_t, chunk->stringsCap, chunk->nStrings
                )

                for (
                    *(chr++) = '\0';
                    (chr[0] == '\0' || strchr(delimeters, chr[0]));
                    *(chr++) = '\0'
                ) if (chr >= str_end) return nSplitted;

                chunk->stringOffsets[chunk->nStrings++] = (uint64_t)(chr - chunk->start);
                nSplitted++;
            }

            return nSplitted;
        }
    }
}

uint64_t strlen_chunk(Chunk const chunk[static const 1], uint32_t const str_id) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ERROR_IF(chunk->nStrings == 0)
    {
        uint32_t const last_str_id = chunk->nStrings - 1;
        DEBUG_ERROR_IF(str_id > last_str_id)

        if (str_id == last_str_id)
            return chunk->len - chunk->stringOffsets[last_str_id];
    }

    return chunk->stringOffsets[str_id + 1] - chunk->stringOffsets[str_id] - 1;
}

uint64_t strlenLast_chunk(Chunk const chunk[static const 1]) {
    DEBUG_ASSERT(isValid_chunk(chunk))
    DEBUG_ERROR_IF(chunk->nStrings == 0)

    return chunk->len - chunk->stringOffsets[chunk->nStrings - 1];
}
