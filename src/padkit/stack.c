#include <assert.h>
#include <string.h>
#include "padkit/memalloc.h"
#include "padkit/size.h"
#include "padkit/stack.h"
#include "padkit/unused.h"

void constructEmpty_stack(
    Stack stack[static const 1],
    size_t const sz_element,
    uint32_t const initial_cap
) {
    #ifndef NDEBUG
        size_t const sz = (size_t)initial_cap * sz_element;
    #endif
    assert(sz_element > 0);
    assert(sz_element < SZSZ_MAX);
    assert(initial_cap > 0);
    assert(initial_cap < SZ32_MAX);
    assert(sz / sz_element == (size_t)initial_cap);

    constructEmpty_alist(stack, sz_element, initial_cap);
}

void flush_stack(Stack stack[static const 1]) {
    assert(isValid_stack(stack));
    flush_alist(stack);
}

void free_stack(Stack stack[static const 1]) {
    assert(isValid_stack(stack));
    free(stack->array);
    stack[0] = NOT_A_STACK;
}

bool isValid_stack(Stack const stack[static const 1]) {
    return isValid_alist(stack);
}

void* peek_stack(Stack const stack[static const 1], uint32_t const n) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n <= stack->size);

    return peekTop_stack(stack, n);
}

void* peekBottom_stack(Stack const stack[static const 1], uint32_t const n) {
    MAYBE_UNUSED(n)
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n <= stack->size);

    return get_alist(stack, 0);
}

void* peekTop_stack(Stack const stack[static const 1], uint32_t const n) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n <= stack->size);

    return get_alist(stack, stack->size - n);
}

void* pop_stack(Stack stack[static const 1], uint32_t const n) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n <= stack->size);

    return popTop_stack(stack, n);
}

void* popBottom_stack(Stack stack[static const 1], uint32_t const n) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n <= stack->size);

    rotateDown_stack(stack, n);

    return popTop_stack(stack, n);
}

void* popTop_stack(Stack stack[static const 1], uint32_t const n) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n <= stack->size);

    return removeLast_alist(stack, n);
}

void* push_stack(Stack stack[static const 1], uint32_t const n, void const* const restrict ptr) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return pushTop_stack(stack, n, ptr);
}

void* pushBottom_stack(Stack stack[static const 1], uint32_t const n, void const* const restrict ptr) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    pushTop_stack(stack, n, ptr);
    rotateUp_stack(stack, n);

    return get_alist(stack, n - 1);
}

void* pushIndeterminate_stack(Stack stack[static const 1], uint32_t const n) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return pushIndeterminateTop_stack(stack, n);
}

void* pushIndeterminateBottom_stack(Stack stack[static const 1], uint32_t const n) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return pushBottom_stack(stack, n, NULL);
}

void* pushIndeterminateTop_stack(Stack stack[static const 1], uint32_t const n) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return pushTop_stack(stack, n, NULL);
}

void* pushTop_stack(Stack stack[static const 1], uint32_t const n, void const* const restrict ptr) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    /* UB if stack->array and ptr overlap, and stack->size + n >= stack->cap. */
    return add_alist(stack, n, ptr);
}

void* pushZeros_stack(Stack stack[static const 1], uint32_t const n) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return pushZerosTop_stack(stack, n);
}

void* pushZerosBottom_stack(Stack stack[static const 1], uint32_t const n) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    pushBottom_stack(stack, n, NULL);
    return setZeros_alist(stack, 0, n);
}

void* pushZerosTop_stack(Stack stack[static const 1], uint32_t const n) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return addZeros_alist(stack, n);
}

void rotate_stack(Stack stack[static const 1], uint32_t n) {
    assert(isValid_stack(stack));

    if (stack->size <= 1)           return;
    if ((n %= stack->size) == 0)    return;

    rotateDown_stack(stack, n);
}

void rotateDown_stack(Stack stack[static const 1], uint32_t n) {
    assert(isValid_stack(stack));

    if (stack->size <= 1)           return;
    if ((n %= stack->size) == 0)    return;

    /* Divide stack->size into sz[0] and sz[1]. */
    {
        size_t const sz[2] = {
            (size_t)n * stack->sz_element,
            (size_t)(stack->size - n) * stack->sz_element
        };
        assert(sz[0] < SZSZ_MAX);
        assert(sz[0] / (size_t)n == stack->sz_element);
        assert(sz[1] < SZSZ_MAX);
        assert(sz[1] / (size_t)(stack->size - n) == stack->sz_element);

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
    assert(isValid_stack(stack));

    if (stack->size <= 1)           return;
    if ((n %= stack->size) == 0)    return;

    rotateDown_stack(stack, stack->size - n);
}
