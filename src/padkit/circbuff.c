/**
 * @file circbuff.c
 * @brief Implements the functions defined in circbuff.h
 * @author Yavuz Koroglu
 */
#include "padkit/circbuff.h"

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
        if (!constructEmpty_stack(
            buffer->stack, element_size_in_bytes, initial_cap
        )) return 0;
    #else
        constructEmpty_stack(buffer->stack, element_size_in_bytes, initial_cap);
    #endif

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
flush_cbuff(CircularBuffer* const buffer) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer)) return 0;
    #endif

    buffer->stack->size     = 0;
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

    free_stack(buffer->stack);
    *buffer = NOT_A_CIRCBUFF;

    #ifndef NDEBUG
        return 1;
    #endif
}

void* get_cbuff(CircularBuffer const* const buffer, uint32_t const elementId) {
    #ifndef NDEBUG
        if (!isValid_cbuff(buffer))             return 0;
        if (elementId >= buffer->stack->size)   return 0;
    #endif

    return get_stack(
        buffer->stack,
        (buffer->bottomElementId + elementId) % buffer->stack->cap
    );
}

bool isValid_cbuff(CircularBuffer const* const buffer) {
    if (buffer == NULL)                 return 0;
    if (!isValid_stack(buffer->stack))  return 0;

    if (buffer->stack->size == 0) {
        if (buffer->bottomElementId != UINT32_MAX)  return 0;
        if (buffer->topElementId != UINT32_MAX)     return 0;

        return 1;
    }

    if (buffer->bottomElementId >= buffer->stack->cap)  return 0;
    if (buffer->topElementId >= buffer->stack->cap)     return 0;

    if (buffer->topElementId < buffer->bottomElementId) {
        uint32_t const n[2] = {
            buffer->topElementId + 1,
            buffer->stack->cap - buffer->bottomElementId
        };

        if (buffer->stack->size != n[0] + n[1]) return 0;

        return 1;
    } else if (buffer->stack->size != buffer->topElementId - buffer->bottomElementId + 1) {
        return 0;
    }

    return 1;
}
