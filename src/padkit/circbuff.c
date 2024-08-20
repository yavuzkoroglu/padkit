/**
 * @file circbuff.c
 * @brief Implements the functions defined in circbuff.h
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/circbuff.h"
#include "padkit/debug.h"
#include "padkit/memalloc.h"
#include "padkit/reallocate.h"
#include "padkit/repeat.h"

#ifndef NDEBUG
    #include "padkit/overlap.h"
#endif

static uint32_t calculateNewCap_cbuff(CircularBuffer const buffer[static const 1]);

static uint32_t calculateNewCap_cbuff(CircularBuffer const buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))

    uint32_t newCap = buffer->cap;
    while (newCap <= buffer->size) {
        newCap <<= 1;
        if (newCap <= buffer->cap) return UINT32_MAX;
    }

    return newCap;
}

void constructEmpty_cbuff(
    CircularBuffer buffer[static const 1],
    size_t const element_size_in_bytes,
    uint32_t const initial_cap
) {
    DEBUG_ERROR_IF(buffer == NULL)
    DEBUG_ERROR_IF(element_size_in_bytes == 0)
    DEBUG_ERROR_IF(element_size_in_bytes == SIZE_MAX)
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(initial_cap == UINT32_MAX)

    buffer->element_size_in_bytes   = element_size_in_bytes;
    buffer->cap                     = initial_cap;
    buffer->size                    = 0;
    buffer->array                   = mem_alloc((size_t)initial_cap * element_size_in_bytes);
    buffer->bottomElementId         = UINT32_MAX;
    buffer->topElementId            = UINT32_MAX;
}

void* dequeue_cbuff(CircularBuffer buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    DEBUG_ERROR_IF(buffer->size == 0)

    return popBottom_cbuff(buffer);
}

void* enqueue_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    return pushTop_cbuff(buffer, ptr);
}

void* enqueue_o_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    return pushTop_o_cbuff(buffer, ptr);
}

void* enqueueZeros_cbuff(CircularBuffer buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    return enqueue_cbuff(buffer, NULL);
}

void* enqueueZeros_o_cbuff(CircularBuffer buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    return enqueue_o_cbuff(buffer, NULL);
}

void flush_cbuff(CircularBuffer buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))

    buffer->size            = 0;
    buffer->bottomElementId = UINT32_MAX;
    buffer->topElementId    = UINT32_MAX;
}

void free_cbuff(CircularBuffer buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))

    free(buffer->array);
    buffer[0] = NOT_A_CIRCBUFF;
}

void* get_cbuff(CircularBuffer const buffer[static const 1], uint32_t const elementId) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    DEBUG_ERROR_IF(buffer->size == 0)

    return
        buffer->array +
            (uint64_t)((buffer->bottomElementId + (elementId % buffer->size)) % buffer->cap) *
            (uint64_t)buffer->element_size_in_bytes;
}

bool isValid_cbuff(CircularBuffer const buffer[static const 1]) {
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

void* peek_cbuff(CircularBuffer const buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    DEBUG_ERROR_IF(buffer->size == 0)

    return peekTop_cbuff(buffer);
}

void* peekBottom_cbuff(CircularBuffer const buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    DEBUG_ERROR_IF(buffer->size == 0)

    return get_cbuff(buffer, 0);
}

void* peekTop_cbuff(CircularBuffer const buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    DEBUG_ERROR_IF(buffer->size == 0)

    return get_cbuff(buffer, buffer->size - 1);
}

void* pop_cbuff(CircularBuffer buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    DEBUG_ERROR_IF(buffer->size == 0)

    return popTop_cbuff(buffer);
}

void* popBottom_cbuff(CircularBuffer buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    DEBUG_ERROR_IF(buffer->size == 0)

    void* const ptr = get_cbuff(buffer, 0);

    buffer->bottomElementId++;
    buffer->bottomElementId %= buffer->cap;

    buffer->size--;
    if (buffer->size == 0) {
        buffer->bottomElementId = UINT32_MAX;
        buffer->topElementId    = UINT32_MAX;
    }

    return ptr;
}

void* popTop_cbuff(CircularBuffer buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    DEBUG_ERROR_IF(buffer->size == 0)

    void* const ptr = get_cbuff(buffer, buffer->size - 1);

    buffer->topElementId--;
    if (buffer->topElementId == UINT32_MAX)
        buffer->topElementId = buffer->cap - 1;

    if (--buffer->size == 0) {
        buffer->bottomElementId = UINT32_MAX;
        buffer->topElementId    = UINT32_MAX;
    }

    return ptr;
}

void* push_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    return pushTop_cbuff(buffer, ptr);
}

void* push_o_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    return pushTop_o_cbuff(buffer, ptr);
}

void* pushBottom_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_cbuff(buffer))

    DEBUG_EXECUTE(size_t const sz_buff    = (size_t)buffer->cap * buffer->element_size_in_bytes)
    DEBUG_EXECUTE(size_t const sz_element = buffer->element_size_in_bytes)
    DEBUG_ERROR_IF(overlaps_ptr(buffer->array, ptr, sz_buff, sz_element))

    reallocIfNecessary_cbuff(buffer); /* May invalidate ptr if buffer->array and ptr overlap. */

    return pushBottom_o_cbuff(buffer, ptr);
}

void* pushBottom_o_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_cbuff(buffer))

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

    set_cbuff(buffer, 0, ptr);
    return peekBottom_cbuff(buffer);
}

void* pushTop_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_cbuff(buffer))

    DEBUG_EXECUTE(size_t const sz_buff    = (size_t)buffer->cap * buffer->element_size_in_bytes)
    DEBUG_EXECUTE(size_t const sz_element = buffer->element_size_in_bytes)
    DEBUG_ERROR_IF(overlaps_ptr(buffer->array, ptr, sz_buff, sz_element))

    reallocIfNecessary_cbuff(buffer); /* May invalidate ptr if buffer->array and ptr overlap. */

    return pushTop_o_cbuff(buffer, ptr);
}

void* pushTop_o_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_cbuff(buffer))

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

    set_cbuff(buffer, buffer->size - 1, ptr);
    return peekBottom_cbuff(buffer);
}

void reallocIfNecessary_cbuff(CircularBuffer buffer[static const 1]) {
    DEBUG_ASSERT(isValid_cbuff(buffer))

    uint32_t const newCap = calculateNewCap_cbuff(buffer);
    if (newCap == UINT32_MAX) REALLOC_ERROR

    if (newCap == buffer->cap) return;

    char* const newArray = realloc(
        buffer->array,
        (size_t)newCap * buffer->element_size_in_bytes
    );
    if (newArray == NULL) REALLOC_ERROR

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
}

void rotate_cbuff(CircularBuffer buffer[static const 1], uint32_t n) {
    DEBUG_ASSERT(isValid_cbuff(buffer))

    if (buffer->size <= 1) return;

    if ((n %= buffer->size) == 0) return;
    rotateDown_cbuff(buffer, n);
}

void rotateDown_cbuff(CircularBuffer buffer[static const 1], uint32_t n) {
    DEBUG_ASSERT(isValid_cbuff(buffer))

    if (buffer->size <= 1) return;

    if ((n %= buffer->size) == 0) return;

    void* const copy = mem_alloc(buffer->element_size_in_bytes);
    REPEAT(n) {
        void* const element = popBottom_cbuff(buffer);
        memcpy(copy, element, buffer->element_size_in_bytes);
        pushTop_o_cbuff(buffer, copy);
    }
    free(copy);
}

void rotateUp_cbuff(CircularBuffer buffer[static const 1], uint32_t n) {
    DEBUG_ASSERT(isValid_cbuff(buffer))

    if (buffer->size <= 1) return;

    if ((n %= buffer->size) == 0) return;

    void* const copy = mem_alloc(buffer->element_size_in_bytes);
    REPEAT(n) {
        void* const element = popTop_cbuff(buffer);
        memcpy(copy, element, buffer->element_size_in_bytes);
        pushBottom_o_cbuff(buffer, copy);
    }
    free(copy);
}

void set_cbuff(
    CircularBuffer buffer[static const 1],
    uint32_t const elementId,
    void const* const restrict ptr
) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    DEBUG_ERROR_IF(buffer->size == 0)

    void* const dest = get_cbuff(buffer, elementId);
    if (dest == ptr) return;

    DEBUG_EXECUTE(size_t const sz_element = buffer->element_size_in_bytes)
    DEBUG_ERROR_IF(overlaps_ptr(dest, ptr, sz_element, sz_element))

    if (ptr == NULL)
        memset(dest, 0, buffer->element_size_in_bytes);
    else
        memcpy(dest, ptr, buffer->element_size_in_bytes); /* UB if dest and ptr overlap. */
}

void setZeros_cbuff(CircularBuffer buffer[static const 1], uint32_t const elementId) {
    DEBUG_ASSERT(isValid_cbuff(buffer))
    DEBUG_ERROR_IF(buffer->size == 0)

    set_cbuff(buffer, elementId, NULL);
}
