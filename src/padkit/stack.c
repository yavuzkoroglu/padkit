/**
 * @file stack.c
 * @brief Implements the functions defined stack.h
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/memalloc.h"
#ifndef NDEBUG
    #include "padkit/overlap.h"
#endif
#include "padkit/reallocate.h"
#include "padkit/stack.h"

static uint32_t calculateNewCap_stack(Stack const* const stack);

static uint32_t calculateNewCap_stack(Stack const* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack)) return UINT32_MAX;
    #endif

    uint32_t newCap = stack->cap;
    while (newCap <= stack->size) {
        newCap <<= 1;
        if (newCap <= stack->cap) return UINT32_MAX;
    }

    return newCap;
}

#ifndef NDEBUG
bool
#else
void
#endif
constructEmpty_stack(
    Stack* const stack,
    size_t const element_size_in_bytes,
    uint32_t const initial_cap
) {
    #ifndef NDEBUG
        if (stack == NULL)                      return 0;
        if (element_size_in_bytes == 0)         return 0;
        if (element_size_in_bytes == SIZE_MAX)  return 0;
        if (initial_cap == 0)                   return 0;
        if (initial_cap == UINT32_MAX)          return 0;
    #endif

    stack->element_size_in_bytes    = element_size_in_bytes;
    stack->cap                      = initial_cap;
    stack->size                     = 0;
    stack->array                    = mem_alloc((size_t)initial_cap * element_size_in_bytes);

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
flush_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack)) return 0;
    #endif

    stack->size = 0;

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
free_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack)) return 0;
    #endif

    free(stack->array);
    *stack = NOT_A_STACK;

    #ifndef NDEBUG
        return 1;
    #endif
}

void* get_stack(Stack const* const stack, uint32_t const elementId) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))      return NULL;
        if (elementId >= stack->size)   return NULL;
    #endif

    return stack->array + (size_t)elementId * stack->element_size_in_bytes;
}

bool isValid_stack(Stack const* const stack) {
    if (stack == NULL)                              return 0;
    if (stack->element_size_in_bytes == 0)          return 0;
    if (stack->element_size_in_bytes == UINT64_MAX) return 0;
    if (stack->cap == 0)                            return 0;
    if (stack->cap == UINT32_MAX)                   return 0;
    if (stack->size > stack->cap)                   return 0;
    if (stack->array == NULL)                       return 0;

    return 1;
}

void* peek_stack(Stack const* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return NULL;
        if (stack->size == 0)       return NULL;
    #endif

    return peekTop_stack(stack);
}

void* peekBottom_stack(Stack const* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return NULL;
        if (stack->size == 0)       return NULL;
    #endif

    return get_stack(stack, 0);
}

void* peekTop_stack(Stack const* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return NULL;
        if (stack->size == 0)       return NULL;
    #endif

    return get_stack(stack, stack->size - 1);
}

void* pop_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return NULL;
        if (stack->size == 0)       return NULL;
    #endif

    return popTop_stack(stack);
}

void* popBottom_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))      return NULL;
        if (stack->size == 0)           return NULL;
        if (!rotateDown_stack(stack,1)) return NULL;
    #else
        rotateDown_stack(stack,1);
    #endif

    return popTop_stack(stack);
}

void* popTop_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))      return NULL;
        if (stack->size == 0)           return NULL;
    #endif

    void* const ptr = get_stack(stack, stack->size - 1);
    stack->size--;
    return ptr;
}

void* push_stack(Stack* const stack, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))      return NULL;
    #endif

    return pushTop_stack(stack, ptr);
}

void* pushBottom_stack(Stack* const stack, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))              return NULL;
        if (pushTop_stack(stack, ptr) == NULL)  return NULL;
        if (!rotateUp_stack(stack, 1))          return NULL;
    #else
        pushTop_stack(stack, ptr);
        rotateUp_stack(stack, 1);
    #endif

    return stack->array;
}

void* pushTop_stack(Stack* const stack, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))              return NULL;
        if (overlaps_ptr(
            stack->array, (size_t)(stack->cap - 1) * stack->element_size_in_bytes,
            ptr, stack->element_size_in_bytes
        )) return NULL;
        if (!reallocIfNecessary_stack(stack))   return NULL;
    #else
        reallocIfNecessary_stack(stack);
    #endif

    stack->size++;
    #ifndef NDEBUG
        if (!set_stack(stack, stack->size - 1, ptr)) return NULL;
    #else
        set_stack(stack, stack->size - 1, ptr);
    #endif

    return peekTop_stack(stack);
}

void* pushZeros_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack)) return NULL;
    #endif

    return pushTop_stack(stack, NULL);
}

void* pushZerosBottom_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack)) return NULL;
    #endif

    return pushBottom_stack(stack, NULL);
}

void* pushZerosTop_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack)) return NULL;
    #endif

    return pushTop_stack(stack, NULL);
}

#ifndef NDEBUG
bool
#else
void
#endif
reallocIfNecessary_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack)) return 0;
    #endif

    uint32_t const newCap = calculateNewCap_stack(stack);
    if (newCap == UINT32_MAX) REALLOC_ERROR

    #ifndef NDEBUG
        if (newCap == stack->cap) return 1;
    #else
        if (newCap == stack->cap) return;
    #endif

    void* const newArray = realloc(
        stack->array,
        (size_t)newCap * stack->element_size_in_bytes
    );
    #ifndef NDEBUG
        if (newArray == NULL) REALLOC_ERROR
    #endif

    stack->cap      = newCap;
    stack->array    = newArray;

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
rotate_stack(Stack* const stack, uint32_t n) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return 0;
        if (stack->size == 0)       return 0;
    #endif

    n %= stack->size;
    #ifndef NDEBUG
        if (n == 0) return 1;
        return rotateDown_stack(stack, n);
    #else
        if (n == 0) return;
        rotateDown_stack(stack, n);
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
rotateDown_stack(Stack* const stack, uint32_t n) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return 0;
        if (stack->size == 0)       return 0;
    #endif

    n %= stack->size;
    #ifndef NDEBUG
        if (n == 0) return 1;
    #else
        if (n == 0) return;
    #endif

    /* Divide stack->size into sz[0] and sz[1]. */
    uint64_t const sz[2] = {
        (uint64_t)n * (uint64_t)stack->element_size_in_bytes,
        (uint64_t)(stack->size - n) * (uint64_t)stack->element_size_in_bytes
    };
    #ifndef NDEBUG
        if (sz[0] < (uint64_t)n)                            return 0;
        if (sz[0] < (uint64_t)stack->element_size_in_bytes) return 0;
        if (sz[1] < (uint64_t)(stack->size - n))            return 0;
        if (sz[1] < (uint64_t)stack->element_size_in_bytes) return 0;
    #endif

    char* const buffer = mem_alloc((size_t)sz[0]);
    memcpy(buffer, stack->array, (size_t)sz[0]);                /* Remember the sz[0] (bottom) part.*/
    memmove(stack->array, stack->array + sz[0], (size_t)sz[1]); /* Shift down the sz[1] part.       */
    memcpy(stack->array + sz[1], buffer, (size_t)sz[0]);        /* Put the sz[0] part at the top.   */
    free(buffer);

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
rotateUp_stack(Stack* const stack, uint32_t n) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return 0;
        if (stack->size == 0)       return 0;
    #endif

    n %= stack->size;
    #ifndef NDEBUG
        if (n == 0) return 1;
    #else
        if (n == 0) return;
    #endif

    /* Divide stack->size into sz[0] and sz[1]. */
    uint64_t const sz[2] = {
        (uint64_t)n * (uint64_t)stack->element_size_in_bytes,
        (uint64_t)(stack->size - n) * (uint64_t)stack->element_size_in_bytes
    };
    #ifndef NDEBUG
        if (sz[0] < (uint64_t)n)                            return 0;
        if (sz[0] < (uint64_t)stack->element_size_in_bytes) return 0;
        if (sz[1] < (uint64_t)(stack->size - n))            return 0;
        if (sz[1] < (uint64_t)stack->element_size_in_bytes) return 0;
    #endif

    char* const buffer = mem_alloc((size_t)sz[0]);
    memcpy(buffer, stack->array + sz[1], (size_t)sz[0]);        /* Remember the sz[0] (top) part.   */
    memmove(stack->array + sz[0], stack->array, (size_t)sz[1]); /* Shift up the sz[1] part.         */
    memcpy(stack->array, buffer, (size_t)sz[0]);                /* Put the sz[0] part at the bottom.*/
    free(buffer);

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
reverse_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return 0;
        if (stack->size == 0)       return 0;
    #endif

    char* const buffer  = mem_alloc(stack->element_size_in_bytes);
    char* bottom        = peekBottom_stack(stack);
    char* top           = peekTop_stack(stack);
    #ifndef NDEBUG
        if (bottom == NULL)         return 0;
        if (top == NULL)            return 0;
    #endif

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

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
set_stack(Stack* const stack, uint32_t const elementId, void const* const restrict ptr) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))      return 0;
        if (elementId >= stack->size)   return 0;
    #endif

    void* const dest = get_stack(stack, elementId);
    #ifndef NDEBUG
        if (dest == NULL)   return 0;
        if (dest == ptr)    return 1;
        if (overlaps_ptr(
            dest, stack->element_size_in_bytes,
            ptr, stack->element_size_in_bytes
        )) return 0;
    #else
        if (dest == ptr) return;
    #endif

    if (ptr == NULL)
        memset(dest, 0, stack->element_size_in_bytes);
    else
        memcpy(dest, ptr, stack->element_size_in_bytes); /* UB if dest and ptr overlaps. */

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
setZeros_stack(Stack* const stack, uint32_t const elementId) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))      return 0;
        if (elementId >= stack->size)   return 0;

        return set_stack(stack, elementId, NULL);
    #else
        set_stack(stack, elementId, NULL);
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
swap_stacks(Stack* const restrict stack_A, Stack* const restrict stack_B) {
    #ifndef NDEBUG
        if (!isValid_stack(stack_A))                                        return 0;
        if (!isValid_stack(stack_B))                                        return 0;
        if (overlaps_ptr(stack_A, sizeof(Stack), stack_B, sizeof(Stack)))   return 0;
    #endif

    Stack sbuffer[1];
    memcpy(sbuffer, stack_A, sizeof(Stack));
    memcpy(stack_A, stack_B, sizeof(Stack)); /* UB if stack_A overlaps with stack_B */
    memcpy(stack_B, sbuffer, sizeof(Stack));

    #ifndef NDEBUG
        return 1;
    #endif
}
