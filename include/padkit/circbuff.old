/**
 * @file circbuff.h
 * @brief Declares circular buffer macros that establishes a practical double-ended queue paradigm for C arrays on heap memory.
 *
 * A circular buffer may both act as a LIFO (Last-In-First-Out) and a FIFO (First-In-First-Out) array.
 *
 * @author Yavuz Koroglu
 */
#ifndef CIRCBUFF_H
    #define CIRCBUFF_H
    #include <stdint.h>
    #include <string.h>
    #include "padkit/reallocate.h"
    #include "padkit/repeat.h"

    /**
     * @def ALLOCATE_CIRCBUFF(type, buffer, initial_cap)
     *   Allocates a circular buffer on heap memory.
     */
    #define ALLOCATE_CIRCBUFF(type, buffer, initial_cap) {                                                                      \
        DEBUG_ASSERT(buffer == NULL)                                                                                            \
        DEBUG_ASSERT(initial_cap > 0)                                                                                           \
        DEBUG_ASSERT(initial_cap < UINT32_MAX / sizeof(type))                                                                   \
        buffer##_cap    = (uint32_t)initial_cap;                                                                                \
        buffer          = malloc(initial_cap * sizeof(type));                                                                   \
        DEBUG_ERROR_IF(buffer == NULL)                                                                                          \
    }

    /**
     * @def CONSTRUCT_EMPTY_CIRCBUFF(type, buffer, initial_cap)
     *   Allocates an empty circular buffer.
     */
    #define CONSTRUCT_EMPTY_CIRCBUFF(type, buffer, initial_cap) {                                                               \
        ALLOCATE_CIRCBUFF(type, buffer, initial_cap)                                                                            \
        buffer##_size   = 0;                                                                                                    \
        buffer##_top    = NULL;                                                                                                 \
        buffer##_bottom = NULL;                                                                                                 \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
    }

    /**
     * @def CREATE_EMPTY_CIRCBUFF(type, buffer, initial_cap)
     *   Declares and constructs an empty circular buffer.
     */
    #define CREATE_EMPTY_CIRCBUFF(type, buffer, initial_cap)                                                                    \
        DEBUG_ASSERT(initial_cap > 0)                                                                                           \
        DEBUG_ASSERT(initial_cap < UINT32_MAX / sizeof(type))                                                                   \
        uint32_t buffer##_size  = 0;                                                                                            \
        uint32_t buffer##_cap   = (uint32_t)initial_cap;                                                                        \
        type* buffer            = malloc((size_t)initial_cap * sizeof(type));                                                   \
        DEBUG_ERROR_IF(buffer == NULL)                                                                                          \
        type* buffer##_top      = NULL;                                                                                         \
        type* buffer##_bottom   = NULL;                                                                                         \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))

    /**
     * @def CREATE_EMPTY_STATIC_CIRCBUFF(type, buffer, initial_cap)
     *   Declares and constructs an empty static circular buffer.
     */
    #define CREATE_EMPTY_STATIC_CIRCBUFF(type, buffer, initial_cap)                                                             \
        DEBUG_ASSERT(initial_cap > 0)                                                                                           \
        DEBUG_ASSERT(initial_cap < UINT32_MAX / sizeof(type))                                                                   \
        uint32_t buffer##_size  = 0;                                                                                            \
        uint32_t buffer##_cap   = (uint32_t)initial_cap;                                                                        \
        type* buffer            = NULL;                                                                                         \
        type* buffer##_top      = NULL;                                                                                         \
        type* buffer##_bottom   = NULL;                                                                                         \
        if (!IS_VALID_CIRCBUFF(buffer))                                                                                         \
            buffer = malloc((size_t)initial_cap * sizeof(type));                                                                \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))

    /**
     * @def DECLARE_CIRCBUFF(type, buffer)
     *   Delares all the variables related to a circular buffer.
     */
    #define DECLARE_CIRCBUFF(type, buffer)                                                                                      \
        uint32_t buffer##_size;                                                                                                 \
        uint32_t buffer##_cap;                                                                                                  \
        type* buffer;                                                                                                           \
        type* buffer##_top;                                                                                                     \
        type* buffer##_bottom;

    /**
     * @def DECLARE_STATIC_CIRCBUFF(type, buffer)
     *   Delares all the static variables related to a circular buffer.
     */
    #define DECLARE_STATIC_CIRCBUFF(type, buffer)                                                                               \
        static uint32_t buffer##_size   = 0;                                                                                    \
        static uint32_t buffer##_cap    = 0;                                                                                    \
        static type* buffer             = NULL;                                                                                 \
        static type* buffer##_top       = NULL;                                                                                 \
        static type* buffer##_bottom    = NULL;

    /**
     * @def DEQUEUE_CIRCBUFF(buffer)
     *   A synonym for POP_BOTTOM_CIRCBUFF(buffer).
     */
    #define DEQUEUE_CIRCBUFF(buffer) POP_BOTTOM_CIRCBUFF(buffer)

    /**
     * @def DEQUEUE_CIRCBUFF_V(ptr, buffer)
     *   A synonym for POP_BOTTOM_CIRCBUFF_V(ptr, buffer).
     */
    #define DEQUEUE_CIRCBUFF_V(ptr, buffer) POP_BOTTOM_CIRCBUFF_V(ptr, buffer)

    /**
     * @def DOWNGRADE_CIRCBUFF_TO_STACK(type, buffer)
     *   Converts a circular buffer to a stack.
     */
    #define DOWNGRADE_CIRCBUFF_TO_STACK(type, buffer) {                                                                         \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        if (buffer##_bottom > buffer) {                                                                                         \
            size_t const _size_in_bytes = (size_t)buffer##_size * sizeof(buffer[0]);                                            \
            DEBUG_ASSERT(_size_in_bytes >= (size_t)buffer##_size)                                                               \
            if (buffer##_bottom <= buffer##_top) {                                                                              \
                memmove(buffer, buffer##_bottom, _size_in_bytes);                                                               \
            } else {                                                                                                            \
                type* const _tmp = malloc(_size_in_bytes);                                                                      \
                DEBUG_ERROR_IF(_tmp == NULL)                                                                                    \
                memcpy(_tmp, buffer##_bottom, (size_t)(buffer + buffer##_cap - buffer##_bottom) * sizeof(buffer[0]));           \
                memcpy(_tmp, (type*)(_tmp+buffer##_cap-buffer##_bottom), (size_t)(buffer##_top-buffer+1) * sizeof(buffer[0]));  \
                memcpy(buffer, _tmp, _size_in_bytes);                                                                           \
                free(_tmp);                                                                                                     \
            }                                                                                                                   \
        }                                                                                                                       \
        buffer##_bottom = NULL;                                                                                                 \
        buffer##_top    = NULL;                                                                                                 \
        DEBUG_ASSERT(IS_VALID_STACK(buffer))                                                                                    \
    }

    /**
     * @def ENQUEUE_CIRCBUFF(type, buffer, ptr)
     *   A synonym for PUSH_TOP_CIRCBUFF(type, buffer, ptr).
     */
    #define ENQUEUE_CIRCBUFF(type, buffer, ptr) PUSH_TOP_CIRCBUFF(type, buffer, ptr)

    /**
     * @def ENQUEUE_CIRCBUFF_C(type, buffer, ptr)
     *   A synonym for PUSH_TOP_CIRCBUFF_C(type, buffer, ptr).
     */
    #define ENQUEUE_CIRCBUFF_C(type, buffer, ptr) PUSH_TOP_CIRCBUFF_C(type, buffer, ptr)

    /**
     * @def ENQUEUE_CIRCBUFF_N(type, ptr, buffer)
     *   A synonym for PUSH_TOP_CIRCBUFF_N(type, ptr, buffer).
     */
    #define ENQUEUE_CIRCBUFF_N(type, ptr, buffer) PUSH_TOP_CIRCBUFF_N(type, ptr, buffer)

    /**
     * @def ENQUEUE_CIRCBUFF_NC(type, ptr, buffer)
     *   A synonym for PUSH_TOP_CIRCBUFF_NC(type, ptr, buffer).
     */
    #define ENQUEUE_CIRCBUFF_NC(type, ptr, buffer) PUSH_TOP_CIRCBUFF_NC(type, ptr, buffer)

    /**
     * @def FLUSH_CIRCBUFF(buffer)
     *   Empties a circular buffer.
     */
    #define FLUSH_CIRCBUFF(buffer) {                                                                                            \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        buffer##_size   = 0;                                                                                                    \
        buffer##_top    = NULL;                                                                                                 \
        buffer##_bottom = NULL;                                                                                                 \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
    }

    /**
     * @def FREE_CIRCBUFF(buffer)
     *   Deallocates and invalidates a circular buffer.
     */
    #define FREE_CIRCBUFF(buffer) {                                                                                             \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        free(buffer);                                                                                                           \
        INVALIDATE_CIRCBUFF(buffer)                                                                                             \
    }

    /**
     * @def GET_CIRCBUFF(ptr, buffer, i)
     *   Gets the ith element from the bottom of a circular buffer.
     */
    #define GET_CIRCBUFF(ptr, buffer, i)                                                                                        \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        DEBUG_ASSERT(i < buffer##_size)                                                                                         \
        ptr = ((buffer##_bottom + i < buffer + buffer##_cap) ? buffer##_bottom + i : buffer##_top - (buffer##_size - i - 1));   \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))

    /**
     * @def INVALIDATE_CIRCBUFF(buffer)
     *   Invalidates a circular buffer so it cannot pass the IS_VALID_CIRCBUFF(buffer) test.
     */
    #define INVALIDATE_CIRCBUFF(buffer) {                                                                                       \
        buffer##_size   = 0;                                                                                                    \
        buffer##_cap    = 0;                                                                                                    \
        buffer          = NULL;                                                                                                 \
        buffer##_top    = NULL;                                                                                                 \
        buffer##_bottom = NULL;                                                                                                 \
    }

    /**
     * @def IS_VALID_CIRCBUFF(buffer)
     *   A Boolean expression that checks if a buffer is valid.
     */
    #define IS_VALID_CIRCBUFF(buffer) (                                                                                         \
        (buffer != NULL)                                &&                                                                      \
        (buffer##_size <= buffer##_cap)                 &&                                                                      \
        (buffer##_cap > 0)                              &&                                                                      \
        (buffer##_cap < UINT32_MAX / sizeof(buffer[0])) &&                                                                      \
        (                                                                                                                       \
            (                                                                                                                   \
                (buffer##_bottom == buffer##_top)                                                                       &&      \
                (buffer##_size <= 1)                                                                                            \
            ) || (                                                                                                              \
                (buffer##_top < buffer##_bottom)                                                                        &&      \
                (buffer##_top >= buffer)                                                                                &&      \
                (buffer##_bottom < buffer + buffer##_cap)                                                               &&      \
                ((uint32_t)((buffer##_top - buffer + 1) + (buffer + buffer##_cap - buffer##_bottom)) == buffer##_size)          \
            ) || (                                                                                                              \
                (buffer##_bottom < buffer##_top)                                                                        &&      \
                (buffer##_bottom >= buffer)                                                                             &&      \
                (buffer##_top < buffer + buffer##_cap)                                                                  &&      \
                ((uint32_t)(buffer##_top - buffer##_bottom + 1) == buffer##_size)                                               \
            )                                                                                                                   \
        )                                                                                                                       \
    )

    /**
     * @def PEEK_BOTTOM_CIRCBUFF(ptr, buffer)
     *   Peeks the bottom element of a circular buffer.
     */
    #define PEEK_BOTTOM_CIRCBUFF(ptr, buffer)                                                                                   \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        DEBUG_ERROR_IF(buffer##_bottom == NULL)                                                                                 \
        ptr = buffer##_bottom;

    /**
     * @def PEEK_CIRCBUFF(ptr, buffer)
     *   A synonym for PEEK_TOP_CIRCBUFF(ptr, buffer).
     */
    #define PEEK_CIRCBUFF(ptr, buffer) PEEK_TOP_CIRCBUFF(ptr, buffer)

    /**
     * @def PEEK_TOP_CIRCBUFF(ptr, buffer)
     *   Peeks the top element of a circular buffer.
     */
    #define PEEK_TOP_CIRCBUFF(ptr, buffer)                                                                                      \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        DEBUG_ERROR_IF(buffer##_top == NULL)                                                                                    \
        ptr = buffer##_top;

    /**
     * @def POP_BOTTOM_CIRCBUFF(buffer)
     *   Pops the bottom element in a circular buffer.
     */
    #define POP_BOTTOM_CIRCBUFF(buffer) {                                                                                       \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        DEBUG_ASSERT(buffer##_size > 0)                                                                                         \
        if (buffer##_size == 1) {                                                                                               \
            buffer##_bottom = NULL;                                                                                             \
            buffer##_top    = NULL;                                                                                             \
        } else {                                                                                                                \
            buffer##_bottom = (buffer##_bottom == buffer + buffer##_cap - 1) ? buffer: buffer##_bottom + 1;                     \
        }                                                                                                                       \
        buffer##_size--;                                                                                                        \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
    }

    /**
     * @def POP_BOTTOM_CIRCBUFF_V(ptr, buffer)
     *   Gets the bottom element of a circular buffer and then pops that element.
     */
    #define POP_BOTTOM_CIRCBUFF_V(ptr, buffer)                                                                                  \
        PEEK_BOTTOM_CIRCBUFF(ptr, buffer)                                                                                       \
        POP_BOTTOM_CIRCBUFF(buffer)

    /**
     * @def POP_CIRCBUFF_V(ptr, buffer)
     *   A synonym for POP_TOP_CIRCBUFF_V(ptr, buffer).
     */
    #define POP_CIRCBUFF_V(ptr, buffer) POP_TOP_CIRCBUFF_V(ptr, buffer)

    /**
     * @def POP_TOP_CIRCBUFF(buffer)
     *   Pops the top element of a circular buffer.
     */
    #define POP_TOP_CIRCBUFF(buffer) {                                                                                          \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        DEBUG_ASSERT(buffer##_size > 0)                                                                                         \
        if (buffer##_size == 1) {                                                                                               \
            buffer##_top    = NULL;                                                                                             \
            buffer##_bottom = NULL;                                                                                             \
        } else {                                                                                                                \
            buffer##_top    = (buffer##_top == buffer) ? buffer + buffer##_cap - 1 : buffer##_top - 1;                          \
        }                                                                                                                       \
        buffer##_size--;                                                                                                        \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
    }

    /**
     * @def POP_TOP_CIRCBUFF_V(ptr, buffer)
     *   Gets the top element of a circular buffer and then pops that element.
     */
    #define POP_TOP_CIRCBUFF_V(ptr, buffer)                                                                                     \
        PEEK_TOP_CIRCBUFF(ptr, buffer)                                                                                          \
        POP_TOP_CIRCBUFF(buffer)

    /**
     * @def PUSH_BOTTOM_CIRCBUFF(type, buffer, ptr)
     *   Pushes an element to the bottom of a circular buffer.
     */
    #define PUSH_BOTTOM_CIRCBUFF(type, buffer, ptr) {                                                                           \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        if (buffer##_bottom == NULL) {                                                                                          \
            buffer##_bottom = buffer;                                                                                           \
            buffer##_top    = buffer;                                                                                           \
        } else {                                                                                                                \
            REALLOC_CIRCBUFF_IF_NECESSARY(type, buffer)                                                                         \
            buffer##_bottom = (buffer##_bottom == buffer) ? buffer + buffer##_cap - 1 : buffer##_bottom - 1;                    \
        }                                                                                                                       \
        if (ptr == NULL) {                                                                                                      \
            memset(buffer##_bottom, 0, sizeof(type));                                                                           \
        } else {                                                                                                                \
            memcpy(buffer##_bottom, ptr, sizeof(type));                                                                         \
        }                                                                                                                       \
        buffer##_size++;                                                                                                        \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
    }

    /**
     * @def PUSH_BOTTOM_CIRCBUFF_C(type, buffer, ptr)
     *   Pushes an element to the bottom of a circular buffer (overwrites, NO resizes).
     */
    #define PUSH_BOTTOM_CIRCBUFF_C(type, buffer, ptr) {                                                                         \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        if (buffer##_bottom == NULL) {                                                                                          \
            buffer##_bottom = buffer;                                                                                           \
            buffer##_top    = buffer;                                                                                           \
        } else {                                                                                                                \
            buffer##_bottom = (buffer##_bottom == buffer) ? buffer + buffer##_cap - 1 : buffer##_bottom - 1;                    \
        }                                                                                                                       \
        if (ptr == NULL) {                                                                                                      \
            memset(buffer##_bottom, 0, sizeof(type));                                                                           \
        } else {                                                                                                                \
            memcpy(buffer##_bottom, ptr, sizeof(type));                                                                         \
        }                                                                                                                       \
        if (buffer##_size == buffer##_cap) {                                                                                    \
            DEBUG_ASSERT(buffer##_top == buffer##_bottom)                                                                       \
            buffer##_top    = (buffer##_top == buffer) ? buffer + buffer##_cap - 1 : buffer##_top - 1;                          \
        } else {                                                                                                                \
            buffer##_size++;                                                                                                    \
        }                                                                                                                       \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
    }

    /**
     * @def PUSH_BOTTOM_CIRCBUFF_N(type, ptr, buffer)
     *   Pushes a zero (or NULL) element to the bottom of a circular buffer and then peeks it.
     */
    #define PUSH_BOTTOM_CIRCBUFF_N(type, ptr, buffer)                                                                           \
        PUSH_BOTTOM_CIRCBUFF(type, buffer, NULL)                                                                                \
        ptr = buffer##_bottom;

    /**
     * @def PUSH_BOTTOM_CIRCBUFF_NC(type, ptr, buffer)
     *   Pushes a zero (or NULL) element to the bottom of a circular buffer and then peeks it (overwrites, NO resizes).
     */
    #define PUSH_BOTTOM_CIRCBUFF_NC(type, ptr, buffer)                                                                          \
        PUSH_BOTTOM_CIRCBUFF_C(type, buffer, NULL)                                                                              \
        ptr = buffer##_bottom;

    /**
     * @def PUSH_CIRCBUFF(type, buffer, ptr)
     *   A synonym for PUSH_TOP_CIRCBUFF(type, buffer, ptr).
     */
    #define PUSH_CIRCBUFF(type, buffer, ptr) PUSH_TOP_CIRCBUFF(type, buffer, ptr)

    /**
     * @def PUSH_CIRCBUFF_C(type, buffer, ptr)
     *   A synonym for PUSH_TOP_CIRCBUFF_C(type, buffer, ptr).
     */
    #define PUSH_CIRCBUFF_C(type, buffer, ptr) PUSH_TOP_CIRCBUFF_C(type, buffer, ptr)

    /**
     * @def PUSH_CIRCBUFF_N(type, ptr, buffer)
     *   A synonym for PUSH_TOP_CIRCBUFF_N(type, ptr, buffer).
     */
    #define PUSH_CIRCBUFF_N(type, ptr, buffer) PUSH_TOP_CIRCBUFF_N(type, ptr, buffer)

    /**
     * @def PUSH_CIRCBUFF_NC(type, ptr, buffer)
     *   A synonym for PUSH_TOP_CIRCBUFF_NC(type, ptr, buffer).
     */
    #define PUSH_CIRCBUFF_NC(type, ptr, buffer) PUSH_TOP_CIRCBUFF_NC(type, ptr, buffer)

    /**
     * @def PUSH_TOP_CIRCBUFF(type, buffer, ptr)
     *   Pushes an element to the top of a circular buffer.
     */
    #define PUSH_TOP_CIRCBUFF(type, buffer, ptr) {                                                                              \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        if (buffer##_top == NULL) {                                                                                             \
            buffer##_top    = buffer;                                                                                           \
            buffer##_bottom = buffer;                                                                                           \
        } else {                                                                                                                \
            REALLOC_CIRCBUFF_IF_NECESSARY(type, buffer)                                                                         \
            buffer##_top    = (buffer##_top == buffer + buffer##_cap - 1) ? buffer : buffer##_top + 1;                          \
        }                                                                                                                       \
        if (ptr == NULL) {                                                                                                      \
            memset(buffer##_top, 0, sizeof(type));                                                                              \
        } else {                                                                                                                \
            memcpy(buffer##_top, ptr, sizeof(type));                                                                            \
        }                                                                                                                       \
        buffer##_size++;                                                                                                        \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
    }

    /**
     * @def PUSH_TOP_CIRCBUFF_C(type, buffer, ptr)
     *   Pushes an element to the top of a circular buffer (overwrites, NO resizes).
     */
    #define PUSH_TOP_CIRCBUFF_C(type, buffer, ptr) {                                                                            \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        if (buffer##_top == NULL) {                                                                                             \
            buffer##_top    = buffer;                                                                                           \
            buffer##_bottom = buffer;                                                                                           \
        } else {                                                                                                                \
            buffer##_top    = (buffer##_top == buffer + buffer##_cap - 1) ? buffer : buffer##_top + 1;                          \
        }                                                                                                                       \
        if (ptr == NULL) {                                                                                                      \
            memset(buffer##_top, 0, sizeof(type));                                                                              \
        } else {                                                                                                                \
            memcpy(buffer##_top, ptr, sizeof(type));                                                                            \
        }                                                                                                                       \
        if (buffer##_size == buffer##_cap) {                                                                                    \
            DEBUG_ASSERT(buffer##_bottom == buffer##_top)                                                                       \
            buffer##_bottom = (buffer##_bottom == buffer + buffer##_cap - 1) ? buffer : buffer##_bottom + 1;                    \
        } else {                                                                                                                \
            buffer##_size++;                                                                                                    \
        }                                                                                                                       \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
    }

    /**
     * @def PUSH_TOP_CIRCBUFF_N(type, ptr, buffer)
     *   Pushes a zero (or NULL) element to the top of a circular buffer and then peeks it.
     */
    #define PUSH_TOP_CIRCBUFF_N(type, ptr, buffer)                                                                              \
        PUSH_TOP_CIRCBUFF(type, buffer, NULL)                                                                                   \
        ptr = buffer##_top;

    /**
     * @def PUSH_TOP_CIRCBUFF_NC(type, ptr, buffer)
     *   Pushes a zero (or NULL) element to the top of a circular buffer and then peeks it (overwrites, NO resizes).
     */
    #define PUSH_TOP_CIRCBUFF_NC(type, ptr, buffer)                                                                             \
        PUSH_TOP_CIRCBUFF_C(type, buffer, NULL)                                                                                 \
        ptr = buffer##_top;

    /**
     * @def REALLOC_CIRCBUFF_IF_NECESSARY(type, buffer)
     *   Reallocates a circular buffer if it is necessary.
     */
    #define REALLOC_CIRCBUFF_IF_NECESSARY(type, buffer) {                                                                       \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        if (buffer##_size == buffer##_cap) {                                                                                    \
            DEBUG_ASSERT(buffer##_cap < UINT32_MAX >> 1)                                                                        \
            buffer##_cap <<= 1;                                                                                                 \
            type* const _new_buffer = malloc(buffer##_cap * sizeof(type));                                                      \
            DEBUG_EXECUTE(if (_new_buffer == NULL) REALLOC_ERROR)                                                               \
            if (buffer##_bottom < buffer##_top) {                                                                               \
                DEBUG_ASSERT(buffer##_bottom == buffer)                                                                         \
                memcpy(_new_buffer, buffer, buffer##_size * sizeof(type));                                                      \
            } else {                                                                                                            \
                size_t const _size = (size_t)(buffer + buffer##_cap - buffer##_bottom);                                         \
                memcpy(_new_buffer, buffer##_bottom, _size * sizeof(type));                                                     \
                memcpy(_new_buffer + _size, buffer, (size_t)(buffer##_top - buffer + 1) * sizeof(type));                        \
            }                                                                                                                   \
            free(buffer);                                                                                                       \
            buffer          = _new_buffer;                                                                                      \
            buffer##_bottom = buffer;                                                                                           \
            buffer##_top    = buffer + buffer##_size - 1;                                                                       \
        }                                                                                                                       \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
    }

    /**
     * @def ROTATE_CIRCBUFF(type, buffer, n)
     *   A synonym for ROTATE_DOWN_CIRCBUFF(type, buffer, n).
     */
    #define ROTATE_CIRCBUFF(type, buffer, n) ROTATE_DOWN_CIRCBUFF(type, buffer, n)

    /**
     * @def ROTATE_DOWN_CIRCBUFF(type, buffer, n)
     *   Pops the bottom element of a circular buffer and pushes it to the top, n times.
     */
    #define ROTATE_DOWN_CIRCBUFF(type, buffer, n) {                                                                             \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        REPEAT_CNTR(_dcntr_rotate_circbuff, n) {                                                                                \
            POP_BOTTOM_CIRCBUFF_V(type const* const _tmp, buffer)                                                               \
            PUSH_TOP_CIRCBUFF(type, buffer, _tmp)                                                                               \
        }                                                                                                                       \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
    }

    /**
     * @def ROTATE_UP_CIRCBUFF(type, buffer, n)
     *   Pops the top element of a circular buffer and pushes it to the bottom, n times.
     */
    #define ROTATE_UP_CIRCBUFF(type, buffer, n) {                                                                               \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        REPEAT_CNTR(_dcntr_rotate_circbuff, n) {                                                                                \
            POP_TOP_CIRCBUFF_V(type const* const _tmp, buffer)                                                                  \
            PUSH_BOTTOM_CIRCBUFF(type, buffer, _tmp)                                                                            \
        }                                                                                                                       \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
    }

    /**
     * @def SHIFT_DOWN_CIRCBUFF(buffer)
     *   A synonym for POP_BOTTOM_CIRCBUFF(buffer).
     */
    #define SHIFT_DOWN_CIRCBUFF(buffer) POP_BOTTOM_CIRCBUFF(buffer)

    /**
     * @def SHIFT_UP_CIRCBUFF(buffer)
     *   A synonym for POP_TOP_CIRCBUFF(buffer).
     */
    #define SHIFT_UP_CIRCBUFF(buffer) POP_TOP_CIRCBUFF(buffer)

    /**
     * @def SWAP_CIRCBUFFS(type, buff_A, buff_B)
     *   Swaps two circular buffers.
     */
    #define SWAP_CIRCBUFFS(type, buff_A, buff_B) {                                                                              \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buff_A))                                                                                 \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buff_B))                                                                                 \
        {                                                                                                                       \
            type* _tmp;                                                                                                         \
            _tmp = buff_A;          buff_A          = buff_B;           buff_B          = _tmp;                                 \
            _tmp = bottom_##buff_A; bottom_##buff_A = bottom_##buff_B;  bottom_##buff_B = _tmp;                                 \
            _tmp = top_##buff_A;    top_##buff_A    = top_##buff_B;     top_##buff_B    = _tmp;                                 \
        } {                                                                                                                     \
            uint32_t _tmp;                                                                                                      \
            _tmp = size_##buff_A;   size_##buff_A   = size_##buff_B;    size_##buffB    = _tmp;                                 \
            _tmp = cap_##buff_A;    cap_##buff_A    = cap_##buff_B;     cap_##buffB     = _tmp;                                 \
        }                                                                                                                       \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buff_A))                                                                                 \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buff_B))                                                                                 \
    }

    /**
     * @def UPGRADE_STACK_TO_CIRCBUFF_D(type, stack)
     *   Converts a stack to a circular buffer and declares the extra variables.
     */
    #define UPGRADE_STACK_TO_CIRCBUFF_D(type, stack) {                                                                          \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                                                     \
        type* stack##_bottom;                                                                                                   \
        type* stack##_top;                                                                                                      \
        UPGRADE_STACK_TO_CIRCBUFF(type, stack)                                                                                  \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(stack))                                                                                  \
    }

    /**
     * @def UPGRADE_STACK_TO_CIRCBUFF(type, stack)
     *   Converts a stack to a circular buffer.
     */
    #define UPGRADE_STACK_TO_CIRCBUFF(type, stack) {                                                                            \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                                                     \
        stack##_bottom  = (stack##_size == 0) ? NULL : stack;                                                                   \
        stack##_top     = (stack##_size == 0) ? NULL : stack + stack##_size - 1;                                                \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(stack))                                                                                  \
    }

#endif
