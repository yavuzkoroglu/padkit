/**
 * @file circbuff.h
 * @brief Defines CircularBuffer and related functions.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_CIRCBUFF_H
    #define PADKIT_CIRCBUFF_H
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdio.h>

    /**
     * @def NOT_A_CIRCBUFF
     *   A special CircularBuffer that cannot pass the isValid_cbuff() test.
     */
    #define NOT_A_CIRCBUFF                      ((CircularBuffer){ 0, 0, 0, NULL, 0, 0 })

    /**
     * @def CIRCBUFF_RECOMMENDED_INITIAL_CAP
     *   This initial capacity should work nicely in most situations.
     */
    #define CIRCBUFF_RECOMMENDED_INITIAL_CAP    (BUFSIZ)

    /**
     * @struct CircularBuffer
     * @brief A circular stack of elements located in heap memory.
     *
     * @var CircularBuffer::element_size_in_bytes
     *   The size of one element in the CircularBuffer, in bytes.
     * @var CircularBuffer::cap
     *   The maximum number of elements the CircularBuffer can hold.
     * @var CircularBuffer::size
     *   The number of elements in the CircularBUffer.
     * @var CircularBuffer::array
     *   A pointer to the first element in the CircularBuffer.
     * @var CircularBuffer::bottomElementId
     *   The bottom element index.
     * @var CircularBuffer::topElementId
     *   The top element index.
     */
    typedef struct CircularBufferBody {
        /* Stack Definitions */
        size_t      element_size_in_bytes;
        uint32_t    cap;
        uint32_t    size;
        char*       array;
        /* CircularBuffer Definitions */
        uint32_t    bottomElementId;
        uint32_t    topElementId;
    } CircularBuffer;

    /**
     * @brief Constructs an empty CircularBuffer.
     *
     * @param[in,out]                buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]     element_size_in_bytes A constant size.
     * @param[in]               initial_cap A constant 32-bit unsigned integer.
     */
    void constructEmpty_cbuff(
        CircularBuffer buffer[static const 1],
        size_t const element_size_in_bytes,
        uint32_t const initial_cap
    );

    /**
     * @brief Pops one element from the bottom of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* dequeue_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Pushes one element to the top of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]        ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* enqueue_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes one element to the top of a CircularBuffer (overwrites, does NOT grow).
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]        ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* enqueue_o_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes one element of zeros to the top of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* enqueueZeros_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Pushes one element of zeros to the top of a CircularBuffer (overwrites, does NOT grow).
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* enqueueZeros_o_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Flushes the contents of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     */
    void flush_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Frees the contents of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     */
    void free_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Gets an element from a CircularBuffer.
     *
     * @param[in] buffer A constant non-null pointer to at least one constant CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* get_cbuff(CircularBuffer const buffer[static const 1], uint32_t const elementId);

    /**
     * @brief Checks if a CircularBuffer is valid.
     *
     * @param[in] buffer A constant non-null pointer to at least one constant CircularBuffer.
     *
     * @return A Boolean value.
     */
    bool isValid_cbuff(CircularBuffer const buffer[static const 1]);

    /**
     * @brief Peeks one element from the top of a CircularBuffer.
     *
     * @param[in] buffer A constant non-null pointer to at least one constant CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* peek_cbuff(CircularBuffer const buffer[static const 1]);

    /**
     * @brief Peeks one element from the bottom of a CircularBuffer.
     *
     * @param[in] buffer A constant non-null pointer to at least one constant CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* peekBottom_cbuff(CircularBuffer const buffer[static const 1]);

    /**
     * @brief Peeks one element from the top of a CircularBuffer.
     *
     * @param[in] buffer A constant non-null pointer to at least one constant CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* peekTop_cbuff(CircularBuffer const buffer[static const 1]);

    /**
     * @brief Pops one element from the top of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* pop_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Pops one element from the bottom of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* popBottom_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Pops one element from the top of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* popTop_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Pushes one element to the top of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]        ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* push_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes one element to the top of a CircularBuffer (overwrites, does NOT grow).
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]        ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* push_o_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes one element to the top of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]        ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* pushBottom_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes one element to the top of a CircularBuffer (overwrites, does NOT grow).
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]        ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* pushBottom_o_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes one element to the top of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]        ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* pushTop_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes one element to the top of a CircularBuffer (overwrites, does NOT grow).
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]        ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* pushTop_o_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes one element of zeros to the top of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* pushZeros_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Pushes one element of zeros to the top of a CircularBuffer (overwrites, does NOT grow).
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* pushZeros_o_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Pushes one element of zeros to the bottom of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* pushZerosBottom_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Pushes one element of zeros to the bottom of a CircularBuffer (overwrites, does NOT grow).
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* pushZerosBottom_o_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Pushes one element of zeros to the top of a CircularBuffer.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* pushZerosTop_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Pushes one element of zeros to the top of a CircularBuffer (overwrites, does NOT grow).
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     *
     * @return A pointer to an object.
     */
    void* pushZerosTop_o_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Reallocates a CircularBuffer if necessary.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     */
    void reallocIfNecessary_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Rotates down a CircularBuffer by n.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]          n A 32-bit unsigned integer.
     */
    void rotate_cbuff(CircularBuffer buffer[static const 1], uint32_t n);

    /**
     * @brief Rotates down a CircularBuffer by n.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]          n A 32-bit unsigned integer.
     */
    void rotateDown_cbuff(CircularBuffer buffer[static const 1], uint32_t n);

    /**
     * @brief Rotates up a CircularBuffer by n.
     *
     * @param[in,out] buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]          n A 32-bit unsigned integer.
     */
    void rotateUp_cbuff(CircularBuffer buffer[static const 1], uint32_t n);

    /**
     * @brief Sets one element of a CircularBuffer to a value.
     *
     * @param[in,out]    buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]     elementId A constant 32-bit unsigned integer.
     * @param[in]           ptr A constant restricted pointer to a constant object.
     */
    void set_cbuff(CircularBuffer buffer[static const 1], uint32_t const elementId, void const* const restrict ptr);

    /**
     * @brief Sets one element of a CircularBuffer to zeros.
     *
     * @param[in,out]    buffer A constant non-null pointer to at least one CircularBuffer.
     * @param[in]     elementId A constant 32-bit unsigned integer.
     */
    void setZeros_cbuff(CircularBuffer buffer[static const 1], uint32_t const elementId);
#endif
