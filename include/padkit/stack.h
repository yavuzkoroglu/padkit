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
     * @def NOT_A_STACK
     *   A special Stack denoting a NOT-Stack. It cannot pass the isValid_stack() test.
     */
    #define NOT_A_STACK                     ((Stack){ 0, 0, 0, NULL })

    /**
     * @def STACK_RECOMMENDED_INITIAL_CAP
     *   This initial capacity should work nicely in most situations.
     */
    #define STACK_RECOMMENDED_INITIAL_CAP   (BUFSIZ)

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
     *
     * @param[in,out]                 stack A constant non-null pointer to at least one Stack.
     * @param[in]      element_size_in_bytes A constant size.
     * @param[in]                initial_cap A constant 32-bit unsigned integer.
     */
    void constructEmpty_stack(
        Stack stack[static const 1],
        size_t const element_size_in_bytes,
        uint32_t const initial_cap
    );

    /**
     * @brief Flushes the contents of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     */
    void flush_stack(Stack stack[static const 1]);

    /**
     * @brief Frees the contents of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     */
    void free_stack(Stack stack[static const 1]);

    /**
     * @brief Gets one element from a Stack.
     *
     * @param[in]     stack A constant non-null pointer to at least one constant Stack.
     * @param[in] elementId A constant 32-bit unsigned integer.
     *
     * @return A pointer to an object.
     */
    void* get_stack(Stack const stack[static const 1], uint32_t const elementId);

    /**
     * @brief Checks if a Stack is valid.
     *
     * @param[in] stack A constant non-null pointer to at least one constant Stack.
     *
     * @return A Boolean value.
     */
    bool isValid_stack(Stack const stack[static const 1]);

    /**
     * @brief Peeks the top element in a Stack.
     *
     * @param[in] stack A constant non-null pointer to at least one constant Stack.
     *
     * @return A pointer to an object.
     */
    void* peek_stack(Stack const stack[static const 1]);

    /**
     * @brief Peeks the bottom element in a Stack.
     *
     * @param[in] stack A constant non-null pointer to at least one constant Stack.
     *
     * @return A pointer to an object.
     */
    void* peekBottom_stack(Stack const stack[static const 1]);

    /**
     * @brief Peeks the top element in a Stack.
     *
     * @param[in] stack A constant non-null pointer to at least one constant Stack.
     *
     * @return A pointer to an object.
     */
    void* peekTop_stack(Stack const* const stack);

    /**
     * @brief Pops the top element in a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     *
     * @return A pointer to an object.
     */
    void* pop_stack(Stack stack[static const 1]);

    /**
     * @brief Pops the bottom element in a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     *
     * @return A pointer to an object.
     */
    void* popBottom_stack(Stack stack[static const 1]);

    /**
     * @brief Pops the top element in a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     *
     * @return A pointer to an object.
     */
    void* popTop_stack(Stack stack[static const 1]);

    /**
     * @brief Pushes the copy of an element to the top of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     * @param[in]        ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* push_stack(Stack stack[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes the copy of an element to the bottom of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     * @param[in]        ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* pushBottom_stack(Stack stack[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes the copy of an element to the top of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     * @param[in]        ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* pushTop_stack(Stack stack[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes one element of zeros to the top of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     *
     * @return A pointer to an object.
     */
    void* pushZeros_stack(Stack stack[static const 1]);

    /**
     * @brief Pushes one element of zeros to the bottom of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     *
     * @return A pointer to an object.
     */
    void* pushZerosBottom_stack(Stack stack[static const 1]);

    /**
     * @brief Pushes one element of zeros to the top of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     *
     * @return A pointer to an object.
     */
    void* pushZerosTop_stack(Stack stack[static const 1]);

    /**
     * @brief Reallocates a Stack if necessary.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     */
    void reallocIfNecessary_stack(Stack stack[static const 1]);

    /**
     * @brief Rotates down a Stack by n.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     * @param[in]          n A 32-bit unsigned integer.
     */
    void rotate_stack(Stack stack[static const 1], uint32_t n);

    /**
     * @brief Rotates down a Stack by n.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     * @param[in]          n A 32-bit unsigned integer.
     */
    void rotateDown_stack(Stack stack[static const 1], uint32_t n);

    /**
     * @brief Rotates up a Stack by n.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     * @param[in]          n A 32-bit unsigned integer.
     */
    void rotateUp_stack(Stack stack[static const 1], uint32_t n);

    /**
     * @brief Reverses the elements of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     */
    void reverse_stack(Stack stack[static const 1]);

    /**
     * @brief Sets one element of a Stack to a value.
     *
     * @param[in,out]      stack A constant non-null pointer to at least one Stack.
     * @param[in]       elementId A constant 32-bit unsigned integer.
     * @param[in]             ptr A constant restricted pointer to a constant object.
     */
    void set_stack(Stack stack[static const 1], uint32_t const elementId, void const* const restrict ptr);

    /**
     * @brief Sets one element of a Stack to zeros.
     *
     * @param[in,out]      stack A constant non-null pointer to at least one Stack.
     * @param[in]       elementId A constant 32-bit unsigned integer.
     */
    void setZeros_stack(Stack stack[static const 1], uint32_t const elementId);

    /**
     * @brief Swaps two Stack objects.
     *
     * @param[in,out] stack_A A constant restricted non-null pointer to at least one Stack.
     * @param[in,out] stack_B A constant restricted non-null pointer to at least one Stack.
     */
    void swap_stacks(Stack stack_A[static const restrict 1], Stack stack_B[static const restrict 1]);
#endif
