/**
 * @file circbuff.h
 * @brief Defines CircularBuffer and related functions.
 * @author Yavuz Koroglu
 */
#ifndef CIRCBUFF_H
    #define CIRCBUFF_H
    #include "padkit/stack.h"

    /**
     * @def NOT_A_CIRCBUFF
     *   A special CircularBuffer that cannot pass the isValid_cbuff() test.
     */
    #define NOT_A_CIRCBUFF \
        ((CircularBuffer){ {NOT_A_STACK}, 0, 0 })

    /**
     * @def CIRCBUFF_RECOMMENDED_INITIAL_CAP
     *   This initial capacity should work nicely in most situations.
     */
    #define CIRCBUFF_RECOMMENDED_INITIAL_CAP    STACK_RECOMMENDED_INITIAL_CAP

    /**
     * @struct CircularBuffer
     * @brief A circular stack of elements located in heap memory.
     *
     * @var CircularBuffer::stack
     *   The Stack of the CircularBuffer.
     * @var CircularBuffer::bottomElementId
     *   The bottom element index.
     * @var CircularBuffer::topElementId
     *   The top element index.
     */
    typedef struct CircularBufferBody {
        Stack       stack[1];
        uint32_t    bottomElementId;
        uint32_t    topElementId;
    } CircularBuffer;

    /**
     * @brief Constructs an empty CircularBuffer.
     * @param buffer A pointer to the CircularBuffer.
     * @param element_size_in_bytes Size of one element in bytes.
     * @param initial_cap The initial capacity of the CircularBuffer.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    constructEmpty_cbuff(
        CircularBuffer* const buffer,
        size_t const element_size_in_bytes,
        uint32_t const initial_cap
    );

    /**
     * @brief Flushes the contents of a CircularBuffer.
     * @param buffer A pointer to the CircularBuffer.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    flush_cbuff(CircularBuffer* const buffer);

    /**
     * @brief Frees the contents of a CircularBuffer.
     * @param buffer A pointer to the CircularBuffer.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    free_cbuff(CircularBuffer* const buffer);

    /**
     * @brief Gets an element from a CircularBuffer.
     * @param buffer A pointer to the constant CircularBuffer.
     * @param elementId The element index.
     */
    void* get_cbuff(CircularBuffer const* const buffer, uint32_t const elementId);

    /**
     * @brief Checks if a CircularBuffer is valid.
     * @param buffer A pointer to the constant CircularBuffer.
     */
    bool isValid_cbuff(CircularBuffer const* const buffer);

    /**
     * @brief Sets one element of a CircularBuffer to a value.
     * @param buffer A pointer to the CircularBuffer.
     * @param elementId The element index.
     * @param ptr A pointer to the constant value.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    set_cbuff(CircularBuffer const* const buffer, uint32_t const elementId, void const* const ptr);
#endif
