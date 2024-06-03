/**
 * @file stack.h
 * @brief Declares stack macros to define a practical stack paradigm for C arrays on heap.
 *
 * A stack is a LIFO (Last-In-First-Out) array. In contrast, a queue is a FIFO (First-In-First-Out) array.
 *
 * @author Yavuz Koroglu
 */
#ifndef STACK_H
    #define STACK_H
    #include <stdint.h>
    #include "padkit/reallocate.h"

    /**
     * @def ALLOCATE_STACK(type, stack, initial_cap)
     *   Allocates a stack of zeros (or NULLs, if it is a pointer stack).
     */
    #define ALLOCATE_STACK(type, stack, initial_cap)                                            \
        DEBUG_ASSERT(stack == NULL)                                                             \
        DEBUG_ASSERT(initial_cap > 0)                                                           \
        DEBUG_ASSERT(initial_cap < 0xFFFFFFFF)                                                  \
        cap_##stack = initial_cap;                                                              \
        stack       = calloc(initial_cap, sizeof(type));                                        \
        DEBUG_ERROR_IF(stack == NULL)

    /**
     * @def CONSTRUCT_EMPTY_STACK(type, stack, initial_cap)
     *   Allocates an empty stack.
     */
    #define CONSTRUCT_EMPTY_STACK(type, stack, initial_cap)                                     \
        ALLOCATE_STACK(type, stack, initial_cap)                                                \
        size_##stack = 0;

    /**
     * @def CREATE_EMPTY_STACK(type, stack, initial_cap)
     *   Declares and constructs an empty stack.
     */
    #define CREATE_EMPTY_STACK(type, stack, initial_cap)                                        \
        DEBUG_ASSERT(initial_cap > 0)                                                           \
        DEBUG_ASSERT(initial_cap < 0xFFFFFFFF)                                                  \
        uint32_t size_##stack   = 0;                                                            \
        uint32_t cap_##stack    = initial_cap;                                                  \
        type* stack             = calloc(initial_cap, sizeof(type));                            \
        DEBUG_ERROR_IF(stack == NULL)

    /**
     * @def DECLARE_STACK(type, stack)
     *   Declares all the variables related to a stack.
     */
    #define DECLARE_STACK(type, stack)                                                          \
        uint32_t size_##stack;                                                                  \
        uint32_t cap_##stack;                                                                   \
        type* stack;

    /**
     * @def INVALIDATE_STACK(stack)
     *   Makes a stack unable to pass the IS_VALID_STACK(stack) test.
     */
    #define INVALIDATE_STACK(stack)                                                             \
        size_##stack    = 0;                                                                    \
        cap_##stack     = 0;                                                                    \
        stack           = NULL;

    /**
     * @def FLUSH_STACK(stack)
     *   Empties a stack.
     */
    #define FLUSH_STACK(stack)                                                                  \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        size_##stack = 0;

    /**
     * @def FREE_STACK(stack)
     *   Deallocates and invalidates a stack.
     */
    #define FREE_STACK(stack)                                                                   \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        free(stack);                                                                            \
        INVALIDATE_STACK(stack)

    /**
     * @def IS_VALID_STACK(stack)
     *   A Boolean expression that checks if a stack is valid.
     */
    #define IS_VALID_STACK(stack) (                                                             \
        (stack != NULL)                 &&                                                      \
        (size_##stack <= cap_##stack)   &&                                                      \
        (cap_##stack > 0)               &&                                                      \
        (cap_##stack < 0xFFFFFFFF)                                                              \
    )

    /**
     * @def PEEK_STACK_D(type, variable, stack)
     *   Declares a constant variable and sets its value to the last element of the stack.
     */
    #define PEEK_STACK_D(type, variable, stack)                                                 \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        DEBUG_ASSERT(size_##stack > 0)                                                          \
        type const variable = stack[size_##stack - 1];

    /**
     * @def PEEK_STACK_V(variable, stack)
     *   Assigns the last element of the stack to a variable.
     */
    #define PEEK_STACK_V(variable, stack)                                                       \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        DEBUG_ASSERT(size_##stack > 0)                                                          \
        variable = stack[size_##stack - 1];

    /**
     * @def POP_STACK_D(type, variable, stack)
     *   Declares a constant variable and pops the last element of the stack to that variable.
     */
    #define POP_STACK_D(type, variable, stack)                                                  \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        DEBUG_ASSERT(size_##stack > 0)                                                          \
        type const variable = stack[--size_##stack];

    /**
     * @def POP_STACK_N(type, variable, stack)
     *   Pops the last element of the stack and forgets that element.
     */
    #define POP_STACK_N(stack)                                                                  \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        DEBUG_ASSERT(size_##stack > 0)                                                          \
        size_##stack--;

    /**
     * @def POP_STACK_V(variable, stack)
     *   Pops the last element of the stack to a variable.
     */
    #define POP_STACK_V(variable, stack)                                                        \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        DEBUG_ASSERT(size_##stack > 0)                                                          \
        variable = stack[--size_##stack];

    /**
     * @def PUSH_STACK(type, stack, element)
     *   Pushes a new element to a stack (reallocates the stack if necessary).
     */
    #define PUSH_STACK(type, stack, element)                                                    \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        RECALLOC_IF_NECESSARY(type, stack, uint32_t, cap_##stack, size_##stack, RECALLOC_ERROR) \
        stack[size_##stack++] = element;

    /**
     * @def REVERSE_STACK(type, stack)
     *   Reverses the order of elements in a stack, essentially turning it into a FIFO queue.
     */
    #define REVERSE_STACK(type, stack)                                                          \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                     \
        if (size_##stack > 0) {                                                                 \
            for (uint32_t i = 0, j = size_##stack - 1; i < j; i++, j--) {                       \
                type const tmp = stack[i];                                                      \
                stack[i] = stack[j];                                                            \
                stack[j] = tmp;                                                                 \
            }                                                                                   \
        }

    /**
     * @def SWAP_STACKS(type, stack_A, stack_B)
     *   Swaps two stacks, which is a good way to implement a Breadth-First Search (BFS) in C.
     */
    #define SWAP_STACKS(type, stack_A, stack_B) {                                               \
        type* tmp_stack     = stack_A;                                                          \
        uint32_t tmp_cap    = cap_##stack_A;                                                    \
        uint32_t tmp_size   = size_##stack_A;                                                   \
        stack_A             = stack_B;                                                          \
        cap_##stack_A       = cap_##stack_B;                                                    \
        size_##stack_A      = size_##stack_B;                                                   \
        stack_B             = tmp_stack;                                                        \
        cap_##stack_B       = tmp_cap;                                                          \
        size_##stack_B      = tmp_size;                                                         \
    }
#endif
