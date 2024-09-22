#include <assert.h>
#include <string.h>
#include "padkit/memalloc.h"
#include "padkit/size.h"
#include "padkit/stack.h"
#include "padkit/unused.h"

void construct_stack(void* const p_stack, ...) {
    va_list args;
    assert(p_stack != NULL);
    va_start(args, p_stack);
    vconstruct_stack(p_stack, args);
}

void constructEmpty_stack(
    Stack stack[static const 1],
    size_t const sz_elem,
    uint32_t const init_cap
) {
    #ifndef NDEBUG
        size_t const sz = (size_t)init_cap * sz_elem;
    #endif
    assert(sz_elem > 0);
    assert(sz_elem < SZSZ_MAX);
    assert(init_cap > 0);
    assert(init_cap < SZ32_MAX);
    assert(sz / sz_elem == (size_t)init_cap);

    constructEmpty_alist(stack, sz_elem, init_cap);
}

void destruct_stack(void* const p_stack) {
    Stack* const stack = (Stack*)p_stack;
    assert(isValid_stack(stack));
    free(stack->arr);
    stack[0] = NOT_A_STACK;
}

void flush_stack(Stack stack[static const 1]) {
    assert(isValid_stack(stack));
    flush_alist(stack);
}

bool isAllocated_stack(void const* const p_stack) {
    return isAllocated_alist(p_stack);
}

bool isValid_stack(void const* const p_stack) {
    return isValid_alist(p_stack);
}

void* peek_stack(
    Stack const stack[static const 1],
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n <= stack->len);

    return peekTop_stack(stack, n);
}

void* peekBottom_stack(
    Stack const stack[static const 1],
    uint32_t const n
) {
    MAYBE_UNUSED(n)
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n <= stack->len);

    return getFirst_alist(stack);
}

void* peekTop_stack(
    Stack const stack[static const 1],
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n <= stack->len);

    return get_alist(stack, stack->len - n);
}

void* pop_stack(
    Stack stack[static const 1],
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n <= stack->len);

    return popTop_stack(stack, n);
}

void* popBottom_stack(
    Stack stack[static const 1],
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n <= stack->len);

    rotateDown_stack(stack, n);

    return popTop_stack(stack, n);
}

void* popTop_stack(
    Stack stack[static const 1],
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n <= stack->len);

    return removeLast_alist(stack, n);
}

void* push_stack(
    Stack stack[static const 1],
    void const* const p,
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return pushTop_stack(stack, p, n);
}

void* pushBottom_stack(
    Stack stack[static const 1],
    void const* const p,
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    pushTop_stack(stack, p, n);
    rotateUp_stack(stack, n);

    return get_alist(stack, n - 1);
}

void* pushIndeterminates_stack(
    Stack stack[static const 1],
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return pushIndeterminatesTop_stack(stack, n);
}

void* pushIndeterminatesBottom_stack(
    Stack stack[static const 1],
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return pushBottom_stack(stack, NULL, n);
}

void* pushIndeterminatesTop_stack(
    Stack stack[static const 1],
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return pushTop_stack(stack, NULL, n);
}

void* pushTop_stack(
    Stack stack[static const 1],
    void const* const p,
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    /* UB if stack->arr has to reallocated and stack->arr overlaps with p. */
    return addElements_alist(stack, p, n);
}

void* pushZeros_stack(
    Stack stack[static const 1],
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return pushZerosTop_stack(stack, n);
}

void* pushZerosBottom_stack(
    Stack stack[static const 1],
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    pushBottom_stack(stack, NULL, n);
    return setZeros_alist(stack, 0, n);
}

void* pushZerosTop_stack(
    Stack stack[static const 1],
    uint32_t const n
) {
    assert(isValid_stack(stack));
    assert(n > 0);
    assert(n < SZ32_MAX);

    return addZeros_alist(stack, n);
}

void rotate_stack(
    Stack stack[static const 1],
    uint32_t n
) {
    assert(isValid_stack(stack));

    if (stack->len <= 1)        return;
    if ((n %= stack->len) == 0) return;

    rotateDown_stack(stack, n);
}

void rotateDown_stack(
    Stack stack[static const 1],
    uint32_t n
) {
    assert(isValid_stack(stack));

    if (stack->len <= 1)        return;
    if ((n %= stack->len) == 0) return;

    /* Divide stack->size into sz[0] and sz[1]. */
    {
        size_t const sz[2] = {
            (size_t)n * stack->sz_elem,
            (size_t)(stack->len - n) * stack->sz_elem
        };
        assert(sz[0] < SZSZ_MAX);
        assert(sz[0] / (size_t)n == stack->sz_elem);
        assert(sz[1] < SZSZ_MAX);
        assert(sz[1] / (size_t)(stack->len - n) == stack->sz_elem);

        {
            char* const buf = mem_alloc(sz[0]);
            memcpy(buf, stack->arr, sz[0]);                 /* Remember the sz[0] (bottom) part.*/
            memmove(stack->arr, stack->arr + sz[0], sz[1]); /* Shift down the sz[1] part.       */
            memcpy(stack->arr + sz[1], buf, sz[0]);         /* Put the sz[0] part at the top.   */
            free(buf);
        }
    }
}

void rotateUp_stack(Stack stack[static const 1], uint32_t n) {
    assert(isValid_stack(stack));

    if (stack->len <= 1)        return;
    if ((n %= stack->len) == 0) return;

    rotateDown_stack(stack, stack->len - n);
}

void vconstruct_stack(void* const p_stack, va_list args) {
    Stack* const stack      = (Stack*)p_stack;
    size_t const sz_elem    = va_arg(args, size_t);
    uint32_t const init_cap = va_arg(args, uint32_t);

    assert(stack != NULL);
    assert(sz_elem > 0);
    assert(sz_elem < SZSZ_MAX);
    assert(init_cap > 0);
    assert(init_cap < SZ32_MAX);

    constructEmpty_stack(stack, sz_elem, init_cap);
}
