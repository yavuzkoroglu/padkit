/**
 * @file stack.h
 * @brief Declares stack macros that establishes a practical stack paradigm for C arrays on heap memory.
 *
 * A stack is a LIFO (Last-In-First-Out) array. In contrast, a queue is a FIFO (First-In-First-Out) array.
 *
 * @author Yavuz Koroglu
 */
#ifndef STACK_H
    #define STACK_H
    #include <stdint.h>
    #include <string.h>
    #include "padkit/reallocate.h"

    /**
     * @def ALLOCATE_STACK(type, stack, initial_cap)
     *   Allocates a stack on heap memory.
     */
    #define ALLOCATE_STACK(type, stack, initial_cap)                                            \
        DEBUG_ASSERT(stack == NULL)                                                             \
        DEBUG_ASSERT(initial_cap > 0)                                                           \
        DEBUG_ASSERT(initial_cap < UINT32_MAX / sizeof(type))                                   \
        stack##_cap = initial_cap;                                                              \
        stack       = malloc(initial_cap * sizeof(type));                                       \
        DEBUG_ERROR_IF(stack == NULL)

    /**
     * @def CONSTRUCT_EMPTY_STACK(type, stack, initial_cap)
     *   Allocates an empty stack.
     */
    #define CONSTRUCT_EMPTY_STACK(type, stack, initial_cap)                                     \
        ALLOCATE_STACK(type, stack, initial_cap)                                                \
        stack##_size = 0;

    /**
     * @def CREATE_EMPTY_STACK(type, stack, initial_cap)
     *   Declares and constructs an empty stack.
     */
    #define CREATE_EMPTY_STACK(type, stack, initial_cap)                                        \
        DEBUG_ASSERT(initial_cap > 0)                                                           \
        DEBUG_ASSERT(initial_cap < UINT32_MAX / sizeof(type))                                   \
        uint32_t stack##_size   = 0;                                                            \
        uint32_t stack##_cap    = initial_cap;                                                  \
        type* const stack       = malloc(initial_cap * sizeof(type));                           \
        DEBUG_ERROR_IF(stack == NULL)

    /**
     * @def DECLARE_STACK(type, stack)
     *   Declares all the variables related to a stack.
     */
    #define DECLARE_STACK(type, stack)                                                          \
        uint32_t stack##_size;                                                                  \
        uint32_t stack##_cap;                                                                   \
        type* stack;

    /**
     * @def FLUSH_STACK(stack)
     *   Empties a stack.
     */
    #define FLUSH_STACK(stack)                                                                  \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        stack##_size = 0;

    /**
     * @def FREE_STACK(stack)
     *   Deallocates and invalidates a stack.
     */
    #define FREE_STACK(stack)                                                                   \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        free(stack);                                                                            \
        INVALIDATE_STACK(stack)

    /**
     * @def INVALIDATE_STACK(stack)
     *   Makes a stack unable to pass the IS_VALID_STACK(stack) test.
     */
    #define INVALIDATE_STACK(stack)                                                             \
        stack##_size    = 0;                                                                    \
        stack##_cap     = 0;                                                                    \
        stack           = NULL;

    /**
     * @def IS_VALID_STACK(stack)
     *   A Boolean expression that checks if a stack is valid.
     */
    #define IS_VALID_STACK(stack) (                                                             \
        (stack != NULL)                 &&                                                      \
        (stack##_size <= stack##_cap)   &&                                                      \
        (stack##_cap > 0)               &&                                                      \
        (stack##_cap < UINT32_MAX)                                                              \
    )

    /**
     * @def PEEK_BOTTOM_STACK(ptr, stack)
     *   Peeks the bottom element of a stack.
     */
    #define PEEK_BOTTOM_STACK(ptr, stack)                                                       \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        DEBUG_ASSERT(stack##_size > 0)                                                          \
        ptr = stack;

    /**
     * @def PEEK_STACK(ptr, stack)
     *   A synonym for PEEK_TOP_STACK(ptr, stack).
     */
    #define PEEK_STACK(ptr, stack) PEEK_TOP_STACK(ptr, stack)

    /**
     * @def PEEK_TOP_STACK(ptr, stack)
     *   Peeks the top element of a stack.
     */
    #define PEEK_TOP_STACK(ptr, stack)                                                          \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        DEBUG_ASSERT(stack##_size > 0)                                                          \
        ptr = stack + stack##_size - 1;

    /**
     * @def POP_STACK(stack)
     *   A synonym for POP_TOP_STACK(stack).
     */
    #define POP_STACK(stack) POP_TOP_STACK(stack)

    /**
     * @def POP_STACK_V(ptr, stack)
     *   A synonym for POP_TOP_STACK_V(ptr, stack).
     */
    #define POP_STACK_V(ptr, stack) POP_TOP_STACK_V(ptr, stack)

    /**
     * @def POP_TOP_STACK(stack)
     *   Pops the top element of a stack.
     */
    #define POP_TOP_STACK(stack)                                                                \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        DEBUG_ASSERT(stack##_size > 0)                                                          \
        stack##_size--;

    /**
     * @def POP_TOP_STACK_V(ptr, stack)
     *   Gets the top element of a stack and pops it.
     */
    #define POP_TOP_STACK_V(ptr, stack)                                                         \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        DEBUG_ASSERT(stack##_size > 0)                                                          \
        ptr = stack + --stack##_size;

    /**
     * @def PUSH_STACK(type, stack, ptr)
     *   A synonym for PUSH_TOP_STACK(type, stack, ptr).
     */
    #define PUSH_STACK(type, stack, ptr) PUSH_TOP_STACK(type, stack, ptr)

    /**
     * @def PUSH_STACK_N(type, ptr, stack)
     *   A synonym for PUSH_TOP_STACK_N(type, ptr, stack).
     */
    #define PUSH_STACK_N(type, ptr, stack) PUSH_TOP_STACK_N(type, ptr, stack)

    /**
     * @def PUSH_TOP_STACK(type, stack, ptr)
     *   Pushes an element to the top of a stack.
     */
    #define PUSH_TOP_STACK(type, stack, ptr)                                                    \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        REALLOC_IF_NECESSARY(type, stack, uint32_t, stack##_cap, stack##_size, REALLOC_ERROR)   \
        if (ptr == NULL) {                                                                      \
            memset(stack + stack##_size, 0, sizeof(type));                                      \
        } else {                                                                                \
            memcpy(stack + stack##_size, ptr, sizeof(type));                                    \
        }                                                                                       \
        stack##_size++;

    /**
     * @def PUSH_TOP_STACK_N(type, ptr, stack)
     *   Pushes a zero (or NULL) element to the top of a stack and then peeks it.
     */
    #define PUSH_TOP_STACK_N(type, ptr, stack)                                                  \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        REALLOC_IF_NECESSARY(type, stack, uint32_t, stack##_cap, stack##_size, REALLOC_ERROR)   \
        memset(stack + stack##_size, 0, sizeof(type));                                          \
        ptr = stack + stack##_size++;

    /**
     * @def REVERSE_STACK(type, stack)
     *   Reverses the order of elements in a stack, essentially turning it into a FIFO queue.
     */
    #define REVERSE_STACK(type, stack)                                                          \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        if (stack##_size > 0) {                                                                 \
            for (uint32_t i = 0, j = stack##_size - 1; i < j; i++, j--) {                       \
                type const tmp[1];                                                              \
                memcpy(tmp, stack + i, sizeof(type));                                           \
                memcpy(stack + i, stack + j, sizeof(type));                                     \
                memcpy(stack + j, tmp, sizeof(type));                                           \
            }                                                                                   \
        }

    /**
     * @def SWAP_STACKS(type, stack_A, stack_B)
     *   Swaps two stacks, which is a good way to implement a Breadth-First Search (BFS) in C.
     */
    #define SWAP_STACKS(type, stack_A, stack_B) {                                               \
        type* const _tmp = stack_A; stack_A = stack_B; stack_B = _tmp;                          \
    } {                                                                                         \
        uint32_t _tmp;                                                                          \
        _tmp = stack##_cap_A;   stack##_cap_A   = stack##_cap_B;    stack##_cap_B   = _tmp;     \
        _tmp = stack##_size_A;  stack##_size_A  = stack##_size_B;   stack##_size_B  = _tmp;     \
    }
#endif
