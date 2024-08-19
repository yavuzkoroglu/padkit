/**
 * @file circbuff.h
 * @brief Defines CircularBuffer and related functions.
 * @author Yavuz Koroglu
 */
#ifndef CIRCBUFF_H
    #define CIRCBUFF_H
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdio.h>

    /**
     * @def NOT_A_CIRCBUFF
     *   A special CircularBuffer that cannot pass the isValid_cbuff() test.
     */
    #define NOT_A_CIRCBUFF \
        ((CircularBuffer){ 0, 0, 0, NULL, 0, 0 })

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
     * @param                buffer A constant non-null pointer to at least one CircularBuffer.
     * @param element_size_in_bytes A constant size.
     * @param           initial_cap A constant 32-bit unsigned integer.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    constructEmpty_cbuff(
        CircularBuffer buffer[static const 1],
        size_t const element_size_in_bytes,
        uint32_t const initial_cap
    );

    /**
     * @brief Pops one element from the bottom of a CircularBuffer.
     * @param buffer A constant non-null pointer to at least one CircularBuffer.
     */
    void* dequeue_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Pushes one element to the top of a CircularBuffer.
     * @param buffer A constant non-null pointer to at least one CircularBuffer.
     * @param    ptr A constant restricted pointer to a constant object.
     */
    void* enqueue_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes one element to the top of a CircularBuffer (overwrites, does NOT grow).
     * @param buffer A constant non-null pointer to at least one CircularBuffer.
     * @param    ptr A constant restricted pointer to a constant object.
     */
    void* enqueue_o_cbuff(CircularBuffer buffer[static const 1], void const* const restrict ptr);

    /**
     * @brief Pushes one element of zeros to the top of a CircularBuffer.
     * @param buffer A constant non-null pointer to at least one CircularBuffer.
     */
    void* enqueueZeros_cbuff(CircularBuffer buffer[static const 1]);

    /**
     * @brief Pushes one element of zeros to the top of a CircularBuffer (overwrites, does NOT grow).
     * @param buffer A pointer to the CircularBuffer.
     */
    void* enqueueZeros_o_cbuff(CircularBuffer* const buffer);

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
     * @brief Peeks one element from the top of a CircularBuffer.
     * @param buffer A pointer to the const CircularBuffer.
     */
    void* peek_cbuff(CircularBuffer const* const buffer);

    /**
     * @brief Peeks one element from the bottom of a CircularBuffer.
     * @param buffer A pointer to the constant CircularBuffer.
     */
    void* peekBottom_cbuff(CircularBuffer const* const buffer);

    /**
     * @brief Peeks one element from the top of a CircularBuffer.
     * @param buffer A pointer to the constant CircularBuffer.
     */
    void* peekTop_cbuff(CircularBuffer const* const buffer);

    /**
     * @brief Pops one element from the top of a CircularBuffer.
     * @param buffer A pointer to the CircularBuffer.
     */
    void* pop_cbuff(CircularBuffer* const buffer);

    /**
     * @brief Pops one element from the bottom of a CircularBuffer.
     * @param buffer A pointer to the CircularBuffer.
     */
    void* popBottom_cbuff(CircularBuffer* const buffer);

    /**
     * @brief Pops one element from the top of a CircularBuffer.
     * @param buffer A pointer to the CircularBuffer.
     */
    void* popTop_cbuff(CircularBuffer* const buffer);

    /**
     * @brief Pushes one element to the top of a CircularBuffer.
     * @param buffer A pointer to the CircularBuffer.
     * @param ptr A pointer to the constant element.
     */
    void* push_cbuff(CircularBuffer* const buffer, void const* const restrict ptr);

    /**
     * @brief Pushes one element to the top of a CircularBuffer (overwrites, does NOT grow).
     * @param buffer A pointer to the CircularBuffer.
     * @param ptr A pointer to the constant element.
     */
    void* push_o_cbuff(CircularBuffer* const buffer, void const* const restrict ptr);

    /**
     * @brief Pushes one element to the top of a CircularBuffer.
     * @param buffer A pointer to the CircularBuffer.
     * @param ptr A pointer to the constant element.
     */
    void* pushBottom_cbuff(CircularBuffer* const buffer, void const* const restrict ptr);

    /**
     * @brief Pushes one element to the top of a CircularBuffer (overwrites, does NOT grow).
     * @param buffer A pointer to the CircularBuffer.
     * @param ptr A pointer to the constant element.
     */
    void* pushBottom_o_cbuff(CircularBuffer* const buffer, void const* const restrict ptr);

    /**
     * @brief Pushes one element to the top of a CircularBuffer.
     * @param buffer A pointer to the CircularBuffer.
     * @param ptr A pointer to the constant element.
     */
    void* pushTop_cbuff(CircularBuffer* const buffer, void const* const restrict ptr);

    /**
     * @brief Pushes one element to the top of a CircularBuffer (overwrites, does NOT grow).
     * @param buffer A pointer to the CircularBuffer.
     * @param ptr A pointer to the constant element.
     */
    void* pushTop_o_cbuff(CircularBuffer* const buffer, void const* const restrict ptr);

    /**
     * @brief Pushes one element of zeros to the top of a CircularBuffer.
     * @param buffer A pointer to the CircularBuffer.
     */
    void* pushZeros_cbuff(CircularBuffer* const buffer);

    /**
     * @brief Pushes one element of zeros to the top of a CircularBuffer (overwrites, does NOT grow).
     * @param buffer A pointer to the CircularBuffer.
     */
    void* pushZeros_o_cbuff(CircularBuffer* const buffer);

    /**
     * @brief Pushes one element of zeros to the bottom of a CircularBuffer.
     * @param buffer A pointer to the CircularBuffer.
     */
    void* pushZerosBottom_cbuff(CircularBuffer* const buffer);

    /**
     * @brief Pushes one element of zeros to the bottom of a CircularBuffer (overwrites, does NOT grow).
     * @param buffer A pointer to the CircularBuffer.
     */
    void* pushZerosBottom_o_cbuff(CircularBuffer* const buffer);

    /**
     * @brief Pushes one element of zeros to the top of a CircularBuffer.
     * @param buffer A pointer to the CircularBuffer.
     */
    void* pushZerosTop_cbuff(CircularBuffer* const buffer);

    /**
     * @brief Pushes one element of zeros to the top of a CircularBuffer (overwrites, does NOT grow).
     * @param buffer A pointer to the CircularBuffer.
     */
    void* pushZerosTop_o_cbuff(CircularBuffer* const buffer);

    /**
     * @brief Reallocates a CircularBuffer if necessary.
     * @param buffer A pointer to the CircularBuffer.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    reallocIfNecessary_cbuff(CircularBuffer* const buffer);

    /**
     * @brief Rotates down a CircularBuffer by n.
     * @param buffer A pointer to the CircularBuffer.
     * @param n The number of rotations.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    rotate_cbuff(CircularBuffer* const buffer, uint32_t n);

    /**
     * @brief Rotates down a CircularBuffer by n.
     * @param buffer A pointer to the CircularBuffer.
     * @param n The number of rotations.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    rotateDown_cbuff(CircularBuffer* const buffer, uint32_t n);

    /**
     * @brief Rotates up a CircularBuffer by n.
     * @param buffer A pointer to the CircularBuffer.
     * @param n The number of rotations.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    rotateUp_cbuff(CircularBuffer* const buffer, uint32_t n);

    /**
     * @brief Sets one element of a CircularBuffer to a value.
     * @param    buffer A constant non-null pointer to at least one CircularBuffer.
     * @param elementId A constant 32-bit unsigned integer.
     * @param       ptr A constant restricted pointer to a constant object.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    set_cbuff(CircularBuffer buffer[static const 1], uint32_t const elementId, void const* const restrict ptr);

    /**
     * @brief Sets one element of a CircularBuffer to zeros.
     * @param buffer A pointer to the CircularBuffer.
     * @param elementId The element index.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    setZeros_cbuff(CircularBuffer* const buffer, uint32_t const elementId);
#endif
