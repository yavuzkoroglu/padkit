/**
 * @file circbuff.c
 * @brief Implements the functions defined in circbuff.h
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/circbuff.h"
#include "padkit/memalloc.h"
#include "padkit/reallocate.h"
#include "padkit/repeat.h"

static uint32_t calculateNewCap_cbuff(CircularBuffer const* const buffer);

static uint32_t calculateNewCap_cbuff(CircularBuffer const* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return UINT32_MAX;
    #endif

    uint32_t newCap = buffer->cap;
    while (newCap <= buffer->size) {
        newCap <<= 1;
        if (newCap <= buffer->cap) return UINT32_MAX;
    }

    return newCap;
}

#ifndef NDEBUG
bool
#else
void
#endif
constructEmpty_cbuff(
    CircularBuffer* const buffer,
    size_t const element_size_in_bytes,
    uint32_t const initial_cap
) {
    #ifndef NDEBUG
        if (buffer == NULL)                     return 0;
        if (element_size_in_bytes == 0)         return 0;
        if (element_size_in_bytes == SIZE_MAX)  return 0;
        if (initial_cap == 0)                   return 0;
        if (initial_cap == UINT32_MAX)          return 0;
    #endif

    buffer->element_size_in_bytes   = element_size_in_bytes;
    buffer->cap                     = initial_cap;
    buffer->size                    = 0;
    buffer->array                   = mem_alloc((size_t)initial_cap * element_size_in_bytes);
    buffer->bottomElementId         = UINT32_MAX;
    buffer->topElementId            = UINT32_MAX;

    #ifndef NDEBUG
        return 1;
    #endif
}

void* dequeue_cbuff(CircularBuffer* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
        if (buffer->size == 0)      return NULL;
    #endif

    return popBottom_cbuff(buffer);
}

void* enqueue_cbuff(CircularBuffer* const buffer, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
    #endif

    return pushTop_cbuff(buffer, ptr);
}

void* enqueue_o_cbuff(CircularBuffer* const buffer, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
    #endif

    return pushTop_o_cbuff(buffer, ptr);
}

void* enqueueZeros_cbuff(CircularBuffer* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
    #endif

    return enqueue_cbuff(buffer, NULL);
}

void* enqueueZeros_o_cbuff(CircularBuffer* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
    #endif

    return enqueue_o_cbuff(buffer, NULL);
}

#ifndef NDEBUG
bool
#else
void
#endif
flush_cbuff(CircularBuffer* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return 0;
    #endif

    buffer->size            = 0;
    buffer->bottomElementId = UINT32_MAX;
    buffer->topElementId    = UINT32_MAX;

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
free_cbuff(CircularBuffer* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return 0;
    #endif

    free(buffer->array);
    *buffer = NOT_A_CIRCBUFF;

    #ifndef NDEBUG
        return 1;
    #endif
}

void* get_cbuff(CircularBuffer const* const buffer, uint32_t const elementId) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
        if (buffer->size == 0)      return NULL;
    #endif

    return
        buffer->array +
            (uint64_t)((buffer->bottomElementId + (elementId % buffer->size)) % buffer->cap) *
            (uint64_t)buffer->element_size_in_bytes;
}

bool isValid_cbuff(CircularBuffer const* const buffer) {
    if (buffer == NULL)                                 return 0;
    if (buffer->element_size_in_bytes == 0)             return 0;
    if (buffer->element_size_in_bytes == UINT64_MAX)    return 0;
    if (buffer->cap == 0)                               return 0;
    if (buffer->cap == UINT32_MAX)                      return 0;
    if (buffer->size > buffer->cap)                     return 0;
    if (buffer->array == NULL)                          return 0;

    if (buffer->size == 0) {
        if (buffer->bottomElementId != UINT32_MAX)      return 0;
        if (buffer->topElementId != UINT32_MAX)         return 0;

        return 1;
    }

    if (buffer->bottomElementId >= buffer->cap)         return 0;
    if (buffer->topElementId >= buffer->cap)            return 0;

    if (buffer->topElementId < buffer->bottomElementId) {
        if (buffer->size !=
                buffer->topElementId + 1 +
                buffer->cap - buffer->bottomElementId
        ) return 0;

        return 1;
    } else if (buffer->size != buffer->topElementId - buffer->bottomElementId + 1) {
        return 0;
    }

    return 1;
}

void* peek_cbuff(CircularBuffer const* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
        if (buffer->size == 0)      return NULL;
    #endif

    return peekTop_cbuff(buffer);
}

void* peekBottom_cbuff(CircularBuffer const* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
        if (buffer->size == 0)      return NULL;
    #endif

    return get_cbuff(buffer, 0);
}

void* peekTop_cbuff(CircularBuffer const* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
        if (buffer->size == 0)      return NULL;
    #endif

    return get_cbuff(buffer, buffer->size - 1);
}

void* pop_cbuff(CircularBuffer* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
        if (buffer->size == 0)      return NULL;
    #endif

    return popTop_cbuff(buffer);
}

void* popBottom_cbuff(CircularBuffer* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
        if (buffer->size == 0)      return NULL;
    #endif

    void* const ptr = get_cbuff(buffer, 0);
    #ifndef NDEBUG
        if (ptr == NULL)            return NULL;
    #endif

    buffer->bottomElementId++;
    buffer->bottomElementId %= buffer->cap;

    buffer->size--;
    if (buffer->size == 0) {
        buffer->bottomElementId = UINT32_MAX;
        buffer->topElementId    = UINT32_MAX;
    }

    return ptr;
}

void* popTop_cbuff(CircularBuffer* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
        if (buffer->size == 0)      return NULL;
    #endif

    void* const ptr = get_cbuff(buffer, buffer->size - 1);
    #ifndef NDEBUG
        if (ptr == NULL)            return NULL;
    #endif

    buffer->topElementId--;
    if (buffer->topElementId == UINT32_MAX)
        buffer->topElementId = buffer->cap - 1;

    if (--buffer->size == 0) {
        buffer->bottomElementId = UINT32_MAX;
        buffer->topElementId    = UINT32_MAX;
    }

    return ptr;
}

void* push_cbuff(CircularBuffer* const buffer, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
    #endif

    return pushTop_cbuff(buffer, ptr);
}

void* push_o_cbuff(CircularBuffer* const buffer, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
    #endif

    return pushTop_o_cbuff(buffer, ptr);
}

void* pushBottom_cbuff(CircularBuffer* const buffer, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer))             return NULL;
        if (!reallocIfNecessary_cbuff(buffer))  return NULL;
    #else
        reallocIfNecessary_cbuff(buffer);
    #endif

    return pushBottom_o_cbuff(buffer, ptr);
}

void* pushBottom_o_cbuff(CircularBuffer* const buffer, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
    #endif

    if (buffer->size == 0) {
        buffer->bottomElementId = 0;
        buffer->topElementId    = 0;
        buffer->size++;
    } else {
        buffer->bottomElementId--;
        if (buffer->bottomElementId >= buffer->cap)
            buffer->bottomElementId = buffer->cap - 1;

        if (buffer->size == buffer->cap) {
            buffer->topElementId--;
            if (buffer->topElementId >= buffer->cap)
                buffer->topElementId = buffer->cap - 1;
        } else {
            buffer->size++;
        }
    }

    #ifndef NDEBUG
        if (!set_cbuff(buffer, 0, ptr)) return NULL;
    #else
        set_cbuff(buffer, 0, ptr);
    #endif

    return peekBottom_cbuff(buffer);
}

void* pushTop_cbuff(CircularBuffer* const buffer, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer))             return NULL;
        if (!reallocIfNecessary_cbuff(buffer))  return NULL;
    #else
        reallocIfNecessary_cbuff(buffer);
    #endif

    return pushTop_o_cbuff(buffer, ptr);
}

void* pushTop_o_cbuff(CircularBuffer* const buffer, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return NULL;
    #endif

    if (buffer->size == 0) {
        buffer->topElementId    = 0;
        buffer->bottomElementId = 0;
        buffer->size++;
    } else {
        buffer->topElementId++;
        buffer->topElementId %= buffer->cap;

        if (buffer->size == buffer->cap) {
            buffer->bottomElementId++;
            buffer->bottomElementId %= buffer->cap;
        } else {
            buffer->size++;
        }
    }

    #ifndef NDEBUG
        if (!set_cbuff(buffer, buffer->size - 1, ptr)) return NULL;
    #else
        set_cbuff(buffer, buffer->size - 1, ptr);
    #endif

    return peekTop_cbuff(buffer);
}

#ifndef NDEBUG
bool
#else
void
#endif
reallocIfNecessary_cbuff(CircularBuffer* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return 0;
    #endif

    uint32_t const newCap = calculateNewCap_cbuff(buffer);
    if (newCap == UINT32_MAX) REALLOC_ERROR

    #ifndef NDEBUG
        if (newCap == buffer->cap) return 1;
    #else
        if (newCap == buffer->cap) return;
    #endif

    char* const newArray = realloc(
        buffer->array,
        (size_t)newCap * buffer->element_size_in_bytes
    );
    #ifndef NDEBUG
        if (newArray == NULL) REALLOC_ERROR
    #endif

    if (buffer->bottomElementId > buffer->topElementId) {
        uint32_t const nShift = buffer->cap - buffer->bottomElementId;

        char* const newBottom = newArray +
            (uint64_t)(newCap - nShift) * (uint64_t)buffer->element_size_in_bytes;

        char* const oldBottom = newArray +
            (uint64_t)buffer->bottomElementId * (uint64_t)buffer->element_size_in_bytes;

        memmove(newBottom, oldBottom, (size_t)nShift);
    }

    buffer->cap     = newCap;
    buffer->array   = newArray;

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
rotate_cbuff(CircularBuffer* const buffer, uint32_t n) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return 0;
        if (buffer->size == 0)      return 0;
    #endif

    n %= buffer->size;
    #ifndef NDEBUG
        if (n == 0) return 1;
        return rotateDown_cbuff(buffer, n);
    #else
        if (n == 0) return;
        return rotateDown_cbuff(buffer, n);
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
rotateDown_cbuff(CircularBuffer* const buffer, uint32_t n) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return 0;
        if (buffer->size == 0)      return 0;
    #endif

    n %= buffer->size;
    #ifndef NDEBUG
        if (n == 0) return 1;
    #else
        if (n == 0) return;
    #endif

    void* const copy = mem_alloc(buffer->element_size_in_bytes);
    REPEAT(n) {
        void* const element = popBottom_cbuff(buffer);
        memcpy(copy, element, buffer->element_size_in_bytes);
        #ifndef NDEBUG
            if (element == NULL)                        return 0;
            if (pushTop_cbuff(buffer, copy) == NULL)    return 0;
        #else
            pushTop_cbuff(buffer, copy);
        #endif
    }
    free(copy);

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
rotateUp_cbuff(CircularBuffer* const buffer, uint32_t n) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return 0;
        if (buffer->size == 0)      return 0;
    #endif

    n %= buffer->size;
    #ifndef NDEBUG
        if (n == 0) return 1;
    #else
        if (n == 0) return;
    #endif

    void* const copy = mem_alloc(buffer->element_size_in_bytes);
    REPEAT(n) {
        void* const element = popTop_cbuff(buffer);
        memcpy(copy, element, buffer->element_size_in_bytes);
        #ifndef NDEBUG
            if (element == NULL)                        return 0;
            if (pushBottom_cbuff(buffer, copy) == NULL) return 0;
        #else
            pushBottom_cbuff(buffer, copy);
        #endif
    }
    free(copy);

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
set_cbuff(CircularBuffer* const buffer, uint32_t const elementId, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return 0;
        if (buffer->size == 0)      return 0;
    #endif

    void* const dest = get_cbuff(buffer, elementId);
    #ifndef NDEBUG
        if (dest == NULL)           return 0;
        if (dest == ptr)            return 0;
    #endif

    if (ptr == NULL)
        memset(dest, 0, buffer->element_size_in_bytes);
    else
        memcpy(dest, ptr, buffer->element_size_in_bytes); /* UB if dest == ptr */

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
setZeros_cbuff(CircularBuffer* const buffer, uint32_t const elementId) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return 0;
        if (buffer->size == 0)      return 0;

        return set_cbuff(buffer, elementId, NULL);
    #else
        set_cbuff(buffer, elementId, NULL);
    #endif
}
