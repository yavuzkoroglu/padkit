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

    uint32_t newCap = stack->cap;
    while (newCap <= stack->size) {
        newCap <<= 1;
        if (newCap <= stack->cap) return UINT32_MAX;
    }

    return newCap;
}

void constructEmpty_stack(
    Stack stack[static const 1],
    size_t const element_size_in_bytes,
    uint32_t const initial_cap
) {
    DEBUG_ERROR_IF(stack == NULL)
    DEBUG_ERROR_IF(element_size_in_bytes == 0)
    DEBUG_ERROR_IF(element_size_in_bytes == SIZE_MAX)
    DEBUG_ERROR_IF(initial_cap == 0)
    DEBUG_ERROR_IF(initial_cap == UINT32_MAX)

    stack->element_size_in_bytes    = element_size_in_bytes;
    stack->cap                      = initial_cap;
    stack->size                     = 0;
    stack->array                    = mem_alloc((size_t)initial_cap * element_size_in_bytes);
}

void flush_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    stack->size = 0;
}

void free_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))

    free(stack->array);
    *stack = NOT_A_STACK;
}

void* get_stack(Stack const stack[static const 1], uint32_t const elementId) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ASSERT(elementId < stack->size)

    return stack->array + (size_t)elementId * stack->element_size_in_bytes;
}

bool isValid_stack(Stack const stack[static const 1]) {
    if (stack == NULL)                              return 0;
    if (stack->element_size_in_bytes == 0)          return 0;
    if (stack->element_size_in_bytes == UINT64_MAX) return 0;
    if (stack->cap == 0)                            return 0;
    if (stack->cap == UINT32_MAX)                   return 0;
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

    void* const ptr = get_stack(stack, stack->size - 1);
    stack->size--;
    return ptr;
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
    DEBUG_ERROR_IF(overlaps_ptr(
        stack->array, (size_t)stack->cap * stack->element_size_in_bytes,
        ptr, stack->element_size_in_bytes
    ))

    reallocIfNecessary_stack(stack);

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

    uint32_t const newCap = calculateNewCap_stack(stack);
    if (newCap == UINT32_MAX) REALLOC_ERROR

    if (newCap == stack->cap) return;

    void* const newArray = realloc(
        stack->array,
        (size_t)newCap * stack->element_size_in_bytes
    );
    if (newArray == NULL) REALLOC_ERROR

    stack->cap      = newCap;
    stack->array    = newArray;
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
    uint64_t const sz[2] = {
        (uint64_t)n * (uint64_t)stack->element_size_in_bytes,
        (uint64_t)(stack->size - n) * (uint64_t)stack->element_size_in_bytes
    };
    DEBUG_ERROR_IF(sz[0] < (uint64_t)n)
    DEBUG_ERROR_IF(sz[0] < (uint64_t)stack->element_size_in_bytes)
    DEBUG_ERROR_IF(sz[1] < (uint64_t)(stack->size - n))
    DEBUG_ERROR_IF(sz[1] < (uint64_t)stack->element_size_in_bytes)

    char* const buffer = mem_alloc((size_t)sz[0]);
    memcpy(buffer, stack->array, (size_t)sz[0]);                /* Remember the sz[0] (bottom) part.*/
    memmove(stack->array, stack->array + sz[0], (size_t)sz[1]); /* Shift down the sz[1] part.       */
    memcpy(stack->array + sz[1], buffer, (size_t)sz[0]);        /* Put the sz[0] part at the top.   */
    free(buffer);
}

void rotateUp_stack(Stack stack[static const 1], uint32_t n) {
    DEBUG_ASSERT(isValid_stack(stack))

    if (stack->size <= 1)           return;
    if ((n %= stack->size) == 0)    return;

    /* Divide stack->size into sz[0] and sz[1]. */
    uint64_t const sz[2] = {
        (uint64_t)n * (uint64_t)stack->element_size_in_bytes,
        (uint64_t)(stack->size - n) * (uint64_t)stack->element_size_in_bytes
    };
    DEBUG_ERROR_IF(sz[0] < (uint64_t)n)
    DEBUG_ERROR_IF(sz[0] < (uint64_t)stack->element_size_in_bytes)
    DEBUG_ERROR_IF(sz[1] < (uint64_t)(stack->size - n))
    DEBUG_ERROR_IF(sz[1] < (uint64_t)stack->element_size_in_bytes)

    char* const buffer = mem_alloc((size_t)sz[0]);
    memcpy(buffer, stack->array + sz[1], (size_t)sz[0]);        /* Remember the sz[0] (top) part.   */
    memmove(stack->array + sz[0], stack->array, (size_t)sz[1]); /* Shift up the sz[1] part.         */
    memcpy(stack->array, buffer, (size_t)sz[0]);                /* Put the sz[0] part at the bottom.*/
    free(buffer);
}

void reverse_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))

    if (stack->size <= 1) return;

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

void set_stack(Stack stack[static const 1], uint32_t const elementId, void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ASSERT(elementId < stack->size)

    void* const dest = get_stack(stack, elementId);
    if (dest == ptr) return;

    DEBUG_ERROR_IF(overlaps_ptr(
        dest, stack->element_size_in_bytes,
        ptr, stack->element_size_in_bytes
    ))

    if (ptr == NULL)
        memset(dest, 0, stack->element_size_in_bytes);
    else
        memcpy(dest, ptr, stack->element_size_in_bytes); /* UB if dest and ptr overlaps. */
}

void setZeros_stack(Stack stack[static const 1], uint32_t const elementId) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ASSERT(elementId < stack->size)

    set_stack(stack, elementId, NULL);
}

void swap_stacks(Stack stack_A[static const restrict 1], Stack stack_B[static const restrict 1]) {
    DEBUG_ASSERT(isValid_stack(stack_A))
    DEBUG_ASSERT(isValid_stack(stack_B))
    DEBUG_ERROR_IF(overlaps_ptr(stack_A, sizeof(Stack), stack_B, sizeof(Stack)))

    Stack sbuffer[1];
    memcpy(sbuffer, stack_A, sizeof(Stack));
    memcpy(stack_A, stack_B, sizeof(Stack)); /* UB if stack_A and stack_B overlaps. */
    memcpy(stack_B, sbuffer, sizeof(Stack));
}
