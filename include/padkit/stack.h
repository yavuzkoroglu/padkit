/**
 * @file stack.h
 * @brief Defines Stack and related functions.
 * @author Yavuz Koroglu
 */
#ifndef STACK_H
    #define STACK_H
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdio.h>

    /**
     * @def STACK_RECOMMENDED_INITIAL_CAP
     *   This initial capacity should work nicely in most situations.
     */
    #define STACK_RECOMMENDED_INITIAL_CAP   BUFSIZ

    /**
     * @struct Stack
     * @brief A stack of elements located in heap memory.
     *
     * @var Stack::element_size_in_bytes
     *   The size of one element in the Stack, in bytes.
     * @var Stack::cap
     *   The maximum number of elements the Stack can hold.
     * @var Stack::size
     *   The number of elements in the Stack.
     * @var Stack::array
     *   A pointer to the first element in the Stack.
     */
    typedef struct StackBody {
        size_t      element_size_in_bytes;
        uint32_t    cap;
        uint32_t    size;
        char*       array;
    } Stack;

    /**
     * @brief Constructs an empty Stack.
     * @param stack A pointer to the Stack.
     * @param element_size_in_bytes Size of one element in bytes.
     * @param initial_cap The initial capacity of the stack.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    constructEmpty_stack(
        Stack* const stack,
        size_t const element_size_in_bytes,
        uint32_t const initial_cap
    );

    /**
     * @brief Flushes the contents of a Stack.
     * @param stack A pointer to the Stack.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    flush_stack(Stack* const stack);

    /**
     * @brief Frees the contents of a Stack.
     * @param stack A pointer to the Stack.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    free_stack(Stack* const stack);

    /**
     * @brief Gets one element from a Stack.
     * @param stack A pointer to the constant Stack.
     * @param elementId The element index.
     */
    void* get_stack(Stack const* const stack, uint32_t const elementId);

    /**
     * @brief Checks if a Stack is valid.
     * @param stack A pointer to the constant Stack.
     */
    bool isValid_stack(Stack const* const stack);

    /**
     * @brief Peeks the top element in a Stack.
     * @param stack A pointer to the constant Stack.
     */
    void* peek_stack(Stack const* const stack);

    /**
     * @brief Peeks the bottom element in a Stack.
     * @param stack A pointer to the constant Stack.
     */
    void* peekBottom_stack(Stack const* const stack);

    /**
     * @brief Peeks the top element in a Stack.
     * @param stack A pointer to the constant Stack.
     */
    void* peekTop_stack(Stack const* const stack);

    /**
     * @brief Pops the top element in a Stack.
     * @param stack A pointer to the Stack.
     */
    void* pop_stack(Stack* const stack);

    /**
     * @brief Pops the bottom element in a Stack.
     * @param stack A pointer to the Stack.
     */
    void* popBottom_stack(Stack* const stack);

    /**
     * @brief Pops the top element in a Stack.
     * @param stack A pointer to the Stack.
     */
    void* popTop_stack(Stack* const stack);

    /**
     * @brief Pushes an element to the top of a Stack.
     * @param stack A pointer to the Stack.
     * @param ptr A pointer to the element.
     */
    void* push_stack(Stack* const stack, void* const ptr);

    /**
     * @brief Pushes an element to the bottom of a Stack.
     * @param stack A pointer to the Stack.
     * @param ptr A pointer to the element.
     */
    void* pushBottom_stack(Stack* const stack, void* const ptr);

    /**
     * @brief Pushes an element to the top of a Stack.
     * @param stack A pointer to the Stack.
     * @param ptr A pointer to the element.
     */
    void* pushTop_stack(Stack* const stack, void* const ptr);

    /**
     * @brief Pushes one element of zeros to the top of a Stack.
     * @param stack A pointer to the Stack.
     */
    void* pushZeros_stack(Stack* const stack);

    /**
     * @brief Pushes one element of zeros to the bottom of a Stack.
     * @param stack A pointer to the Stack.
     */
    void* pushZerosBottom_stack(Stack* const stack);

    /**
     * @brief Pushes one element of zeros to the top of a Stack.
     * @param stack A pointer to the Stack.
     */
    void* pushZerosTop_stack(Stack* const stack);

    /**
     * @brief Reallocates a Stack if necessary.
     * @param stack A pointer to the Stack.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    reallocIfNecessary_stack(Stack* const stack);

    /**
     * @brief Rotates down a Stack.
     * @param stack A pointer to the Stack.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    rotate_stack(Stack* const stack);

    /**
     * @brief Rotates down a Stack.
     * @param stack A pointer to the Stack.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    rotateDown_stack(Stack* const stack);

    /**
     * @brief Rotates up a Stack.
     * @param stack A pointer to the Stack.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    rotateUp_stack(Stack* const stack);

    /**
     * @brief Reverses the elements of a Stack.
     * @param stack A pointer to the Stack.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    reverse_stack(Stack* const stack);

    /**
     * @brief Swaps two Stack objects.
     * @param stack_A A pointer to the first Stack.
     * @param stack_B A pointer to the second Stack.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    swap_stacks(Stack* const stack_A, Stack* const stack_B);
#endif