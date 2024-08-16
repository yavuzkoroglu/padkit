/**
 * @file stack.c
 * @brief Implements the functions defined stack.h
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/memalloc.h"
#include "padkit/reallocate.h"
#include "padkit/stack.h"

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

    return stack->array;
}

void* peekTop_stack(Stack const* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return NULL;
        if (stack->size == 0)       return NULL;
    #endif

    return stack->array + (size_t)(stack->size - 1) * stack->element_size_in_bytes;
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
        if (!rotateDown_stack(stack))   return NULL;
    #else
        rotateDown_stack(stack);
    #endif

    return popTop_stack(stack);
}

void* popTop_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))      return NULL;
        if (stack->size == 0)           return NULL;
    #endif

    return stack->array + (size_t)(--stack->size) * stack->element_size_in_bytes;
}

void* push_stack(Stack* const stack, void const* const ptr) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))      return NULL;
    #endif

    return pushTop_stack(stack, ptr);
}

void* pushBottom_stack(Stack* const stack, void const* const ptr) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))              return NULL;
        if (pushTop_stack(stack, ptr) == NULL)  return NULL;
        if (!rotateUp_stack(stack))             return NULL;
    #else
        pushTop_stack(stack, ptr);
        rotateUp_stack(stack);
    #endif

    return stack->array;
}

void* pushTop_stack(Stack* const stack, void const* const ptr) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return NULL;
    #endif

    bool const isPtrInStack
        = (stack->array <= (char const*)ptr && (char const*)ptr < stack->array + stack->size);

    size_t const offset = (size_t)((char const*)ptr - stack->array);

    #ifndef NDEBUG
        if (isPtrInStack && offset % stack->element_size_in_bytes != 0) return NULL;
        if (!reallocIfNecessary_stack(stack))                           return NULL;
    #else
        reallocIfNecessary_stack(stack);
    #endif

    if (ptr == NULL)
        memset(
            stack->array + (size_t)stack->size * stack->element_size_in_bytes,
            0,
            stack->element_size_in_bytes
        );
    else if (isPtrInStack)
        memcpy(
            stack->array + (size_t)stack->size * stack->element_size_in_bytes,
            stack->array + offset,
            stack->element_size_in_bytes
        );
    else
        memcpy(
            stack->array + (size_t)stack->size * stack->element_size_in_bytes,
            ptr,
            stack->element_size_in_bytes
        );

    return stack->array + (size_t)stack->size++ * stack->element_size_in_bytes;
}

void* pushZeros_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return NULL;
    #endif

    return push_stack(stack, NULL);
}

void* pushZerosBottom_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return NULL;
    #endif

    return pushBottom_stack(stack, NULL);
}

void* pushZerosTop_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return NULL;
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

    uint32_t new_cap = stack->cap;
    while (new_cap <= stack->size) {
        new_cap <<= 1;
        #ifndef NDEBUG
            if (new_cap <= stack->cap) REALLOC_ERROR
        #endif
    }

    if (new_cap == stack->cap)
        #ifndef NDEBUG
            return 1;
        #else
            return;
        #endif

    void* const new_array = realloc(
        stack->array,
        (size_t)(stack->cap = new_cap) * stack->element_size_in_bytes
    );
    #ifndef NDEBUG
        if (new_array == NULL) REALLOC_ERROR
    #endif

    stack->cap      = new_cap;
    stack->array    = new_array;

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
rotate_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))
            return 0;

        return rotateDown_stack(stack);
    #else
        rotateDown_stack(stack);
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
rotateDown_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return 0;
        if (stack->size == 0)       return 0;
    #endif

    char* const buffer = mem_alloc(stack->element_size_in_bytes);
    memcpy(buffer, stack->array, stack->element_size_in_bytes);
    memmove(
        stack->array,
        stack->array + stack->element_size_in_bytes,
        (size_t)(stack->size - 1) * stack->element_size_in_bytes
    );
    memcpy(
        stack->array + (size_t)(stack->size - 1) * stack->element_size_in_bytes,
        buffer,
        stack->element_size_in_bytes
    );
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
rotateUp_stack(Stack* const stack) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))  return 0;
        if (stack->size == 0)       return 0;
    #endif

    char* const buffer = mem_alloc(stack->element_size_in_bytes);
    memcpy(
        buffer,
        stack->array + (size_t)(stack->size - 1) * stack->element_size_in_bytes,
        stack->element_size_in_bytes
    );
    memmove(
        stack->array + stack->element_size_in_bytes,
        stack->array,
        (size_t)(stack->size - 1) * stack->element_size_in_bytes
    );
    memcpy(stack->array, buffer, stack->element_size_in_bytes);
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
    char* first         = stack->array;
    char* second        = stack->array + (size_t)(stack->size - 1) * stack->element_size_in_bytes;
    while (first < second) {
        memcpy(buffer, first, stack->element_size_in_bytes);
        memcpy(first, second, stack->element_size_in_bytes);
        memcpy(second, buffer, stack->element_size_in_bytes);

        first += stack->element_size_in_bytes;
        second -= stack->element_size_in_bytes;
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
set_stack(Stack* const stack, uint32_t const elementId, void const* const ptr) {
    #ifndef NDEBUG
        if (!isValid_stack(stack))      return 0;
        if (elementId >= stack->size)   return 0;
        if (ptr == NULL)                return 0;
        if (stack->array <= (char const*)ptr && (char const*)ptr < stack->array + stack->size) {
            size_t const offset = (size_t)((char const*)ptr - stack->array);

            if (offset % stack->element_size_in_bytes != 0)                 return 0;
            if (offset / stack->element_size_in_bytes == (size_t)elementId) return 0;
        }
    #endif

    memcpy(
        stack->array + (size_t)elementId * stack->element_size_in_bytes,
        ptr,
        stack->element_size_in_bytes
    );

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
swap_stacks(Stack* const stack_A, Stack* const stack_B) {
    #ifndef NDEBUG
        if (!isValid_stack(stack_A))    return 0;
        if (!isValid_stack(stack_B))    return 0;
    #endif

    Stack tmp[1];
    memcpy(tmp, stack_A, sizeof(Stack));
    memcpy(stack_A, stack_B, sizeof(Stack));
    memcpy(stack_B, tmp, sizeof(Stack));

    #ifndef NDEBUG
        return 1;
    #endif
}
