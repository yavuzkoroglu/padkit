/**
 * @file stack.c
 * @brief Implements the functions defined stack.h
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/debug.h"
#include "padkit/memalloc.h"
#include "padkit/size.h"
#include "padkit/stack.h"

void constructEmpty_stack(
    Stack stack[static const 1],
    size_t const sz_element,
    uint32_t const initial_cap
) {
    size_t const sz = (size_t)initial_cap * sz_element;

    DEBUG_ASSERT(sz_element > 0)
    DEBUG_ASSERT(sz_element < SZSZ_MAX)
    DEBUG_ASSERT(initial_cap > 0)
    DEBUG_ASSERT(initial_cap < SZ32_MAX)
    DEBUG_ASSERT(sz / sz_element == (size_t)initial_cap)

    constructEmpty_alist(stack, sz_element, initial_cap);
}

void flush_stack(Stack stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    flush_alist(stack);
}

void free_stack(Stack stack[static const 1]) {
    DEBUG_ABORT_UNLESS(isValid_stack(stack))
    free(stack->array);
    stack[0] = NOT_A_STACK;
}

bool isValid_stack(Stack const stack[static const 1]) {
    return isValid_alist(stack);
}

void* peek_stack(Stack const stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ERROR_IF(stack->size == 0)

    return peekTop_stack(stack);
}

void* peekBottom_stack(Stack const stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ERROR_IF(stack->size == 0)

    return get_alist(stack, 0);
}

void* peekTop_stack(Stack const stack[static const 1]) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ERROR_IF(stack->size == 0)

    return get_alist(stack, stack->size - 1);
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
        void* const ptr = get_alist(stack, stack->size - 1);
        stack->size--;
        return ptr;
    }
}

void* push_stack(Stack stack[static const 1], uint32_t const n, void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ASSERT(n > 0)
    DEBUG_ASSERT(n < SZ32_MAX)

    return pushTop_stack(stack, n, ptr);
}

void* pushBottom_stack(Stack stack[static const 1], uint32_t const n, void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ASSERT(n > 0)
    DEBUG_ASSERT(n < SZ32_MAX)

    DEBUG_ERROR_IF(pushTop_stack(stack, n, ptr) == NULL)
    NDEBUG_EXECUTE(pushTop_stack(stack, n, ptr))

    rotateUp_stack(stack, n);

    return get_alist(stack, n - 1);
}

void* pushTop_stack(Stack stack[static const 1], uint32_t const n, void const* const restrict ptr) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ASSERT(n > 0)
    DEBUG_ASSERT(n < SZ32_MAX)

    /* UB if stack->array and ptr overlap, and stack->size + n >= stack->cap. */
    return add_alist(stack, n, ptr);
}

void* pushZeros_stack(Stack stack[static const 1], uint32_t const n) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ASSERT(n > 0)
    DEBUG_ASSERT(n < SZ32_MAX)

    return pushTop_stack(stack, n, NULL);
}

void* pushZerosBottom_stack(Stack stack[static const 1], uint32_t const n) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ASSERT(n > 0)
    DEBUG_ASSERT(n < SZ32_MAX)

    return pushBottom_stack(stack, n, NULL);
}

void* pushZerosTop_stack(Stack stack[static const 1], uint32_t const n) {
    DEBUG_ASSERT(isValid_stack(stack))
    DEBUG_ASSERT(n > 0)
    DEBUG_ASSERT(n < SZ32_MAX)

    return pushTop_stack(stack, n, NULL);
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
            (size_t)n * stack->sz_element,
            (size_t)(stack->size - n) * stack->sz_element
        };
        DEBUG_ASSERT(sz[0] < SZSZ_MAX)
        DEBUG_ASSERT(sz[0] / (size_t)n == stack->sz_element)
        DEBUG_ASSERT(sz[1] < SZSZ_MAX)
        DEBUG_ASSERT(sz[1] / (size_t)(stack->size - n) == stack->sz_element)

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

    rotateDown_stack(stack, stack->size - n);
}
