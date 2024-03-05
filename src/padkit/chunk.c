/**
 * @file chunk.c
 * @brief Implements the functions defined in chunk.h
 * @see Chunk
 * @author Yavuz Koroglu
 */
#include <ctype.h>
#include <string.h>
#include "padkit/chunk.h"
#include "padkit/reallocate.h"

uint32_t add_chunk(Chunk* const chunk, char const* const str, uint64_t const n) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return 0xFFFFFFFF;
        if (str == NULL)           return 0xFFFFFFFF;
    #endif

    uint32_t const id     = chunk->nStrings++;
    uint64_t const offset = (chunk->len += !!(chunk->len));

    #ifndef NDEBUG
        if (append_chunk(chunk, str, n) == NULL) return 0xFFFFFFFF;
    #else
        append_chunk(chunk, str, n);
    #endif

    chunk->stringOffsets[id] = offset;
    return id;
}

uint32_t addIndex_chunk(Chunk* const chunk, uint32_t const str_id) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return 0xFFFFFFFF;
        if (str_id == 0xFFFFFFFF)  return 0xFFFFFFFF;
    #endif

    uint32_t const id = add_chunk(chunk, "", 0);

    #ifndef NDEBUG
        if (id == 0xFFFFFFFF)                         return 0xFFFFFFFF;
        if (appendIndex_chunk(chunk, str_id) == NULL) return 0xFFFFFFFF;
    #else
        appendIndex_chunk(chunk, str_id);
    #endif

    return id;
}

char const* append_chunk(Chunk* const chunk, char const* const str, uint64_t const n) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return NULL;
        if (str == NULL)           return NULL;
    #endif

    char* const append_start = appendSpace_chunk(chunk, n);
    #ifndef NDEBUG
        if (append_start < chunk->start) return NULL;
    #endif

    memcpy(append_start, str, n);
    chunk->start[(chunk->len += n)] = '\0';

    REALLOC_IF_NECESSARY(
        uint64_t, chunk->stringOffsets,
        uint32_t, chunk->stringsCap, chunk->nStrings,
        return NULL;
    )

    /* May try to append when there are no strings. Then, just add a new string. */
    if (chunk->nStrings == 0) {
        #ifndef NDEBUG
            if (append_start != chunk->start) return NULL;
        #endif
        chunk->stringOffsets[chunk->nStrings++] = 0;
        return chunk->start;
    }

    return chunk->start + chunk->stringOffsets[chunk->nStrings - 1];
}

char const* appendIndex_chunk(Chunk* const chunk, uint32_t const str_id) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return NULL;
    #endif

    uint64_t const start_offset = chunk->stringOffsets[str_id];
    uint64_t const end_offset   = str_id == chunk->nStrings - 1
        ? chunk->len
        : chunk->stringOffsets[str_id + 1] - 1;
    uint64_t const n            = (uint64_t)(end_offset - start_offset);
    char* const append_start    = appendSpace_chunk(chunk, n);
    #ifndef NDEBUG
        if (append_start == NULL) return NULL;
    #endif

    memcpy(append_start, chunk->start + start_offset, n);
    chunk->start[(chunk->len += n)] = '\0';

    REALLOC_IF_NECESSARY(
        uint64_t, chunk->stringOffsets,
        uint32_t, chunk->stringsCap, chunk->nStrings,
        return NULL;
    )

    return chunk->start + chunk->stringOffsets[chunk->nStrings - 1];
}

char* appendSpace_chunk(Chunk* const chunk, uint64_t const size) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return NULL;
    #endif

    if (size == 0) return chunk->start + chunk->len;

    uint64_t const pseudo_len = chunk->len + size;
    #ifndef NDEBUG
        if (pseudo_len < chunk->len) return NULL;
    #endif

    REALLOC_IF_NECESSARY(
        char, chunk->start,
        uint64_t, chunk->cap, pseudo_len,
        return NULL;
    )

    return chunk->start + chunk->len;
}

#ifndef NDEBUG
bool
#else
void
#endif
concat_chunk(Chunk* const to, Chunk const* const from) {
    #ifndef NDEBUG
        if (!isValid_chunk(to))   return 0;
        if (!isValid_chunk(from)) return 0;
    #endif

    if (from->nStrings == 0)
        #ifndef NDEBUG
            return 1;
        #else
            return;
        #endif

    uint64_t const hasStrings = (to->nStrings > 0);
    char* const append_start = appendSpace_chunk(to, from->len + hasStrings) + hasStrings;
    #ifndef NDEBUG
        if (append_start < to->start) return 0;
    #endif
    memcpy(append_start, from->start, from->len + 1);

    uint32_t const old_str_count = to->nStrings;
    to->nStrings += from->nStrings;
    REALLOC_IF_NECESSARY(
        uint64_t, to->stringOffsets,
        uint32_t, to->stringsCap, to->nStrings,
        return 0;
    )

    uint64_t const diff = (uint64_t)(append_start - to->start);
    for (uint32_t from_str_id = 0; from_str_id < from->nStrings; from_str_id++) {
        uint32_t const to_str_id = from_str_id + old_str_count;
        to->stringOffsets[to_str_id] = diff + from->stringOffsets[from_str_id];
    }

    to->len += from->len + hasStrings;

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
constructEmpty_chunk(Chunk* chunk, uint64_t const initial_cap, uint32_t const initial_stringsCap) {
    #ifndef NDEBUG
        if (chunk == NULL)                     return 0;
        if (initial_cap == 0)                  return 0;
        if (initial_cap == 0xFFFFFFFFFFFFFFFF) return 0;
        if (initial_stringsCap == 0)           return 0;
        if (initial_stringsCap == 0xFFFFFFFF)  return 0;
    #endif

    chunk->cap        = initial_cap;
    chunk->stringsCap = initial_stringsCap;
    chunk->nStrings   = 0;
    chunk->len        = 0;

    chunk->stringOffsets = malloc(initial_stringsCap * sizeof(uint64_t));
    #ifndef NDEBUG
        if (chunk->stringOffsets == NULL) return 0;
    #endif

    chunk->start = malloc(initial_cap);
    #ifndef NDEBUG
        if (chunk->start == NULL) return 0;
    #endif

    chunk->start[0] = '\0';

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
delete_chunk(Chunk* const chunk, uint32_t const str_id) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return 0;
        if (str_id >= chunk->nStrings) return 0;
    #endif

    if (str_id == chunk->nStrings - 1) {
        #ifndef NDEBUG
            return deleteLast_chunk(chunk);
        #else
            deleteLast_chunk(chunk);
            return;
        #endif
    }

    char* const str  = chunk->start + chunk->stringOffsets[str_id];
    char* const next = chunk->start + chunk->stringOffsets[str_id + 1];
    uint64_t const n = chunk->len - chunk->stringOffsets[str_id + 1] + 1;
    memmove(str, next, n);

    uint64_t const diff = (uint64_t)(next - str);
    chunk->nStrings--;
    for (uint32_t i = str_id; i < chunk->nStrings; i++)
        chunk->stringOffsets[i] = chunk->stringOffsets[i + 1] - diff;

    chunk->len -= diff;

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
deleteLast_chunk(Chunk* const chunk) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return 0;
        if (chunk->nStrings == 0)  return 0;
    #endif

    uint32_t const lastStr_id = --chunk->nStrings;
    if (lastStr_id == 0) {
        #ifndef NDEBUG
            return flush_chunk(chunk);
        #else
            flush_chunk(chunk);
            return;
        #endif
    }

    uint64_t const max_len = chunk->stringOffsets[lastStr_id] - 1;
    uint64_t const min_len = chunk->stringOffsets[lastStr_id - 1];

    for (
        chunk->start[chunk->len = max_len] = '\0';
        chunk->len > min_len && chunk->start[chunk->len - 1] == '\0';
        chunk->len--
    ) {}

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
flush_chunk(Chunk* const chunk) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return 0;
    #endif
    chunk->nStrings = 0;
    chunk->len      = 0;
    chunk->start[0] = '\0';
    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
free_chunk(Chunk* const chunk) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return 0;
    #endif
    free(chunk->start);
    free(chunk->stringOffsets);
    *chunk = NOT_A_CHUNK;
    #ifndef NDEBUG
        return 1;
    #endif
}

uint32_t fromStream_chunk(
    Chunk* const chunk, FILE* const stream, char const* delimeters
) {
    static char const defaultDelimeters[] = " \t\n\v\f\r";
    if (delimeters == NULL) delimeters    = defaultDelimeters;

    uint32_t const str_id = fromStreamAsWhole_chunk(chunk, stream);
    #ifndef NDEBUG
        if (str_id == 0xFFFFFFFF) return 0xFFFFFFFF;
        if (splitLast_chunk(chunk, delimeters) == 0) return 0xFFFFFFFF;
    #else
        splitLast_chunk(chunk, delimeters);
    #endif

    return str_id;
}

uint32_t fromStreamAsWhole_chunk(Chunk* const chunk, FILE* const stream) {
    #ifndef NDEBUG
        if (stream == NULL) return 0xFFFFFFFF;
    #endif

    uint32_t str_id = add_chunk(chunk, "", 0);
    #ifndef NDEBUG
        if (str_id == 0xFFFFFFFF)             return 0xFFFFFFFF;
        if (fseek(stream, 0L, SEEK_END) != 0) return 0xFFFFFFFF;
    #else
        fseek(stream, 0L, SEEK_END);
    #endif

    long size = ftell(stream);
    #ifndef NDEBUG
        if (size < 0L)                        return 0xFFFFFFFF;
        if (fseek(stream, 0L, SEEK_SET) != 0) return 0xFFFFFFFF;
    #else
        fseek(stream, 0L, SEEK_SET);
    #endif

    char* append_start = appendSpace_chunk(chunk, (uint64_t)size);
    #ifndef NDEBUG
        if (append_start == NULL)                              return 0xFFFFFFFF;
        if (fread(append_start, (size_t)size, 1, stream) != 1) return 0xFFFFFFFF;
    #else
        fread(append_start, (size_t)size, 1, stream);
    #endif

    chunk->len += (uint64_t)size;
    return str_id;
}

char const* get_chunk(Chunk const* const chunk, uint32_t const str_id) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk))     return NULL;
        if (str_id >= chunk->nStrings) return NULL;
    #endif
    return chunk->start + chunk->stringOffsets[str_id];
}

char const* getFirst_chunk(Chunk const* const chunk) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return NULL;
        if (chunk->nStrings == 0)  return NULL;
    #endif
    return get_chunk(chunk, 0);
}

char const* getLast_chunk(Chunk const* const chunk) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return NULL;
        if (chunk->nStrings == 0)  return NULL;
    #endif
    return get_chunk(chunk, chunk->nStrings - 1);
}

bool isValid_chunk(Chunk const* const chunk) {
    return chunk != NULL                         &&
           chunk->cap != 0                       &&
           chunk->cap != 0xFFFFFFFFFFFFFFFF      &&
           chunk->stringsCap != 0                &&
           chunk->stringsCap != 0xFFFFFFFF       &&
           chunk->stringOffsets != NULL          &&
           chunk->start != NULL                  &&
           chunk->len <= chunk->cap              &&
           chunk->nStrings <= chunk->stringsCap;
}

size_t splitLast_chunk(Chunk* const chunk, char const* delimeters) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return 0xFFFFFFFFFFFFFFFF;
        if (chunk->nStrings == 0) return 0;
    #endif

    static char const defaultDelimeters[] = " \t\n\v\f\r";
    if (delimeters == NULL) delimeters = defaultDelimeters;

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
    );

    /* Trim from the start */
    for (;
        isspace((unsigned char)str_start[0]) || str_start[0] == '\0' || strchr(delimeters, str_start[0]);
        chunk->stringOffsets[str_id]++, *(str_start++) = '\0'
    );

    /* In-Place Split */
    size_t nSplitted = 1;
    for (char* chr = str_start; chr < str_end; chr++) {
        if (strchr(delimeters, *chr) == NULL) continue;

        /* Realloc stringOffsets if necessary */
        REALLOC_IF_NECESSARY(
            uint64_t, chunk->stringOffsets,
            uint32_t, chunk->stringsCap, chunk->nStrings,
            return 0;
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

uint64_t strlen_chunk(Chunk const* const chunk, uint32_t const str_id) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return 0xFFFFFFFFFFFFFFFF;
        if (chunk->nStrings == 0) return 0xFFFFFFFFFFFFFFFF;
    #endif

    uint32_t const last_str_id = chunk->nStrings - 1;
    #ifndef NDEBUG
        if (str_id > last_str_id) return 0xFFFFFFFFFFFFFFFF;
    #endif

    if (str_id == last_str_id) {
        return chunk->len - chunk->stringOffsets[last_str_id];
    } else {
        return chunk->stringOffsets[str_id + 1] - chunk->stringOffsets[str_id] - 1;
    }
}

uint64_t strlenLast_chunk(Chunk const* const chunk) {
    #ifndef NDEBUG
        if (!isValid_chunk(chunk)) return 0xFFFFFFFFFFFFFFFF;
        if (chunk->nStrings == 0)  return 0xFFFFFFFFFFFFFFFF;
    #endif
    return chunk->len - chunk->stringOffsets[chunk->nStrings - 1];
}
