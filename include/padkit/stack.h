/**
 * @file stack.h
 * @brief Defines Stack and related functions.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_STACK_H
    #define PADKIT_STACK_H
    #include "padkit/arraylist.h"

    /**
     * @def NOT_A_STACK
     *   A special Stack denoting a NOT-Stack. It cannot pass the isValid_stack() test.
     */
    #define NOT_A_STACK                     NOT_AN_ALIST

    /**
     * @def STACK_RECOMMENDED_INITIAL_CAP
     *   This initial capacity should work nicely in most situations.
     */
    #define STACK_RECOMMENDED_INITIAL_CAP   ALIST_RECOMMENDED_INITIAL_CAP

    typedef ArrayList Stack;

    /**
     * @brief Constructs an empty Stack.
     *
     * @param[in,out]       stack A constant non-null pointer to at least one Stack.
     * @param[in]      sz_element A constant size.
     * @param[in]     initial_cap A constant 32-bit unsigned integer.
     */
    void constructEmpty_stack(
        Stack stack[static const 1],
        size_t const sz_element,
        uint32_t const initial_cap
    );

    /**
     * @brief Empties a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     */
    void flush_stack(Stack stack[static const 1]);

    /**
     * @brief Deallocates the contents of a Stack.
     *
     * Assigns NOT_A_STACK to the Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     */
    void free_stack(Stack stack[static const 1]);

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
    void* peekTop_stack(Stack const stack[static const 1]);

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
     * @brief Pushes n copies of an element to the top of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     * @param[in]         n A constant 32-bit unsigned integer.
     * @param[in]       ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* push_stack(Stack stack[static const 1], uint32_t const n, void const* const restrict ptr);

    /**
     * @brief Pushes n copies of an element to the bottom of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     * @param[in]         n A constant 32-bit unsigned integer.
     * @param[in]       ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* pushBottom_stack(Stack stack[static const 1], uint32_t const n, void const* const restrict ptr);

    /**
     * @brief Pushes the copy of an element to the top of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     * @param[in]         n A constant 32-bit unsigned integer.
     * @param[in]       ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* pushTop_stack(Stack stack[static const 1], uint32_t const n, void const* const restrict ptr);

    /**
     * @brief Pushes n elements of zeros to the top of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     * @param[in]         n A constant 32-bit unsigned integer.
     *
     * @return A pointer to an object.
     */
    void* pushZeros_stack(Stack stack[static const 1], uint32_t const n);

    /**
     * @brief Pushes n elements of zeros to the bottom of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     * @param[in]         n A constant 32-bit unsigned integer.
     *
     * @return A pointer to an object.
     */
    void* pushZerosBottom_stack(Stack stack[static const 1], uint32_t const n);

    /**
     * @brief Pushes n elements of zeros to the top of a Stack.
     *
     * @param[in,out] stack A constant non-null pointer to at least one Stack.
     * @param[in]         n A constant 32-bit unsigned integer.
     *
     * @return A pointer to an object.
     */
    void* pushZerosTop_stack(Stack stack[static const 1], uint32_t const n);

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
#endif
