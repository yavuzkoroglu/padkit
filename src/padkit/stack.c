/**
 * @file stack.c
 * @brief Implements the functions defined stack.h
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/debug.h"
#include "padkit/memalloc.h"
#include "padkit/reallocate.h"
#include "padkit/stack.h"

#ifndef NDEBUG
    #include "padkit/overlap.h"
#endif

static uint32_t calculateNewCap_stack(Stack const stack[static const 1]);

static uint32_t calculateNewCap_stack(Stack const stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    {
        uint32_t newCap = stack->cap;
        while (newCap <= stack->size) {
            newCap <<= 1;
            if (newCap >= INT32_MAX) return UINT32_MAX;
        }
        return newCap;
    }
}

void constructEmpty_stack(
    Stack stack[static const 1],
    size_t const element_size_in_bytes,
    uint32_t const initial_cap
) {
    size_t const sz = (size_t)initial_cap * element_size_in_bytes;

    DEBUG_ASSERT(element_size_in_bytes > 0)
    DEBUG_ASSERT(element_size_in_bytes < SIZE_MAX >> 1)
    DEBUG_ASSERT(initial_cap > 0)
    DEBUG_ASSERT(initial_cap < INT32_MAX)
    DEBUG_ASSERT(sz / (size_t)initial_cap == element_size_in_bytes)

    stack->element_size_in_bytes    = element_size_in_bytes;
    stack->cap                      = initial_cap;
    stack->size                     = 0;
    stack->array                    = mem_alloc(sz);
}

void flush_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    stack->size = 0;
}

void free_stack(Stack stack[static const 1]) {
    DEBUG_ABORT_UNLESS(isValid_stack(stack))

    free(stack->array);
    stack[0] = NOT_A_STACK;
}

void* get_stack(Stack const stack[static const 1], uint32_t const elementId) {
    size_t const offset = (size_t)elementId * stack->element_size_in_bytes;
    DEBUG_ASSERT(elementId == 0 || offset / (size_t)elementId == stack->element_size_in_bytes)

    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ASSERT(elementId < stack->size)

    return stack->array + offset;
}

bool isValid_stack(Stack const stack[static const 1]) {
    if (stack->element_size_in_bytes == 0)          return 0;
    if (stack->element_size_in_bytes >= INT64_MAX)  return 0;
    if (stack->cap == 0)                            return 0;
    if (stack->cap >= INT32_MAX)                    return 0;
    if (stack->size > stack->cap)                   return 0;
    if (stack->array == NULL)                       return 0;

    return 1;
}

void* peek_stack(Stack const stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ERROR_IF(stack->size == 0)

    return peekTop_stack(stack);
}

void* peekBottom_stack(Stack const stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ERROR_IF(stack->size == 0)

    return get_stack(stack, 0);
}

void* peekTop_stack(Stack const stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ERROR_IF(stack->size == 0)

    return get_stack(stack, stack->size - 1);
}

void* pop_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ERROR_IF(stack->size == 0)

    return popTop_stack(stack);
}

void* popBottom_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ERROR_IF(stack->size == 0)

    rotateDown_stack(stack, 1);

    return popTop_stack(stack);
}

void* popTop_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ERROR_IF(stack->size == 0)
    {
        void* const ptr = get_stack(stack, stack->size - 1);
        stack->size--;
        return ptr;
    }
}

void* push_stack(Stack stack[static const 1], void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_stack(stack))

    return pushTop_stack(stack, ptr);
}

void* pushBottom_stack(Stack stack[static const 1], void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_stack(stack))

    DEBUG_ERROR_IF(pushTop_stack(stack, ptr) == NULL)
    NDEBUG_EXECUTE(pushTop_stack(stack, ptr))

    rotateUp_stack(stack, 1);

    return stack->array;
}

void* pushTop_stack(Stack stack[static const 1], void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_stack(stack))

    {
        DEBUG_EXECUTE(size_t const sz_element   = stack->element_size_in_bytes)
        DEBUG_EXECUTE(size_t const sz_stack     = (size_t)stack->cap * sz_element)
        DEBUG_ASSERT(sz_stack / (size_t)stack->cap == sz_element)
        DEBUG_ERROR_IF(overlaps_ptr(stack->array, ptr, sz_stack, sz_element))
    }

    reallocIfNecessary_stack(stack); /* May invalidate ptr if stack->array and ptr overlap. */

    set_stack(stack, ++stack->size - 1, ptr);

    return peekTop_stack(stack);
}

void* pushZeros_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))

    return pushTop_stack(stack, NULL);
}

void* pushZerosBottom_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))

    return pushBottom_stack(stack, NULL);
}

void* pushZerosTop_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))

    return pushTop_stack(stack, NULL);
}

void reallocIfNecessary_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    {
        uint32_t const newCap = calculateNewCap_stack(stack);
        if (newCap >= INT32_MAX) REALLOC_ERROR

        if (newCap > stack->cap) {
            size_t const sz = (size_t)newCap * stack->element_size_in_bytes;
            DEBUG_ASSERT(sz / (size_t)newCap == stack->element_size_in_bytes)

            {
                void* const newArray = realloc(stack->array, sz);
                if (newArray == NULL) REALLOC_ERROR

                stack->cap      = newCap;
                stack->array    = newArray;
            }
        }
    }
}

void rotate_stack(Stack stack[static const 1], uint32_t n) {
    DEBUG_ASSERT(isValid_stack(stack))

    if (stack->size <= 1)           return;
    if ((n %= stack->size) == 0)    return;

    rotateDown_stack(stack, n);
}

void rotateDown_stack(Stack stack[static const 1], uint32_t n) {
    DEBUG_ASSERT(isValid_stack(stack))

    if (stack->size <= 1)           return;
    if ((n %= stack->size) == 0)    return;

    /* Divide stack->size into sz[0] and sz[1]. */
    {
        size_t const sz[2] = {
            (size_t)n * stack->element_size_in_bytes,
            (size_t)(stack->size - n) * stack->element_size_in_bytes
        };
        DEBUG_ASSERT(n == 0 || sz[0] / (size_t)n == stack->element_size_in_bytes)
        DEBUG_ASSERT(sz[1] / (size_t)(stack->size - n) == stack->element_size_in_bytes)

        {
            char* const buffer = mem_alloc(sz[0]);
            memcpy(buffer, stack->array, sz[0]);                /* Remember the sz[0] (bottom) part.*/
            memmove(stack->array, stack->array + sz[0], sz[1]); /* Shift down the sz[1] part.       */
            memcpy(stack->array + sz[1], buffer, sz[0]);        /* Put the sz[0] part at the top.   */
            free(buffer);
        }
    }
}

void rotateUp_stack(Stack stack[static const 1], uint32_t n) {
    DEBUG_ASSERT(isValid_stack(stack))

    if (stack->size <= 1)           return;
    if ((n %= stack->size) == 0)    return;

    /* Divide stack->size into sz[0] and sz[1]. */
    {
        size_t const sz[2] = {
            (size_t)n * stack->element_size_in_bytes,
            (size_t)(stack->size - n) * stack->element_size_in_bytes
        };
        DEBUG_ASSERT(n == 0 || sz[0] / (size_t)n == stack->element_size_in_bytes)
        DEBUG_ASSERT(sz[1] / (size_t)(stack->size - n) == stack->element_size_in_bytes)

        {
            char* const buffer = mem_alloc(sz[0]);
            memcpy(buffer, stack->array + sz[1], sz[0]);        /* Remember the sz[0] (top) part.   */
            memmove(stack->array + sz[0], stack->array, sz[1]); /* Shift up the sz[1] part.         */
            memcpy(stack->array, buffer, sz[0]);                /* Put the sz[0] part at the bottom.*/
            free(buffer);
        }
    }
}

void reverse_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))

    if (stack->size > 1) {
        char* const buffer  = mem_alloc(stack->element_size_in_bytes);
        char* bottom        = peekBottom_stack(stack);
        char* top           = peekTop_stack(stack);

        /* (bottom < top) is NOT UB because
         * both belong to stack->array. */
        while (bottom < top) {
            memcpy(buffer, bottom, stack->element_size_in_bytes);
            memcpy(bottom, top, stack->element_size_in_bytes);
            memcpy(top, buffer, stack->element_size_in_bytes);

            bottom += stack->element_size_in_bytes;
            top -= stack->element_size_in_bytes;
        }
        free(buffer);
    }
}

void set_stack(Stack stack[static const 1], uint32_t const elementId, void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ASSERT(elementId < stack->size)

    {
        void* const dest = get_stack(stack, elementId);
        if (dest == ptr) return;

        {
            DEBUG_EXECUTE(size_t const sz_element = stack->element_size_in_bytes)
            DEBUG_ERROR_IF(overlaps_ptr(dest, ptr, sz_element, sz_element))
        }

        if (ptr == NULL)
            memset(dest, 0, stack->element_size_in_bytes);
        else
            memcpy(dest, ptr, stack->element_size_in_bytes); /* UB if dest and ptr overlap. */
    }
}

void setZeros_stack(Stack stack[static const 1], uint32_t const elementId) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ASSERT(elementId < stack->size)

    set_stack(stack, elementId, NULL);
}
