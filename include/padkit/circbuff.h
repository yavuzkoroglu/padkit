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
    #define ALLOCATE_CIRCBUFF(type, buffer, initial_cap)                                                                        \
        DEBUG_ASSERT(buffer == NULL)                                                                                            \
        DEBUG_ASSERT(initial_cap > 0)                                                                                           \
        DEBUG_ASSERT(initial_cap < UINT32_MAX / sizeof(type))                                                                   \
        cap_##buffer    = (uint32_t)initial_cap;                                                                                \
        buffer          = malloc(initial_cap * sizeof(type));                                                                   \
        DEBUG_ERROR_IF(buffer == NULL)

    /**
     * @def CONSTRUCT_EMPTY_CIRCBUFF(type, buffer, initial_cap)
     *   Allocates an empty circular buffer.
     */
    #define CONSTRUCT_EMPTY_CIRCBUFF(type, buffer, initial_cap)                                                                 \
        ALLOCATE_CIRCBUFF(type, buffer, initial_cap)                                                                            \
        size_##buffer   = 0;                                                                                                    \
        top_##buffer    = NULL;                                                                                                 \
        bottom_##buffer = NULL;

    /**
     * @def CREATE_EMPTY_CIRCBUFF(type, buffer, initial_cap)
     *   Declares and constructs an empty circular buffer.
     */
    #define CREATE_EMPTY_CIRCBUFF(type, buffer, initial_cap)                                                                    \
        DEBUG_ASSERT(initial_cap > 0)                                                                                           \
        DEBUG_ASSERT(initial_cap < UINT32_MAX / sizeof(type))                                                                   \
        uint32_t size_##buffer  = 0;                                                                                            \
        uint32_t cap_##buffer   = (uint32_t)initial_cap;                                                                        \
        type* buffer            = malloc((size_t)initial_cap * sizeof(type));                                                   \
        DEBUG_ERROR_IF(buffer == NULL)                                                                                          \
        type* top_##buffer      = NULL;                                                                                         \
        type* bottom_##buffer   = NULL;

    /**
     * @def DECLARE_CIRCBUFF(type, buffer)
     *   Delares all the variables related to a circular buffer.
     */
    #define DECLARE_CIRCBUFF(type, buffer)                                                                                      \
        uint32_t size_##buffer;                                                                                                 \
        uint32_t cap_##buffer;                                                                                                  \
        type* buffer;                                                                                                           \
        type* top_##buffer;                                                                                                     \
        type* bottom_##buffer;

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
    #define DOWNGRADE_CIRCBUFF_TO_STACK(type, buffer)                                                                           \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        if (bottom_##buffer > buffer) {                                                                                         \
            size_t const _size_in_bytes = (size_t)size_##buffer * sizeof(buffer[0]);                                            \
            DEBUG_ASSERT(_size_in_bytes >= (size_t)size_##buffer)                                                               \
            if (bottom_##buffer <= top_##buffer) {                                                                              \
                memmove(buffer, bottom_##buffer, _size_in_bytes);                                                               \
            } else {                                                                                                            \
                type* const _tmp = malloc(_size_in_bytes);                                                                      \
                DEBUG_ERROR_IF(_tmp == NULL)                                                                                    \
                memcpy(_tmp, bottom_##buffer, (size_t)(buffer + cap_##buffer - bottom_##buffer) * sizeof(buffer[0]));           \
                memcpy(_tmp, (type*)(_tmp+cap_##buffer-bottom_##buffer), (size_t)(top_##buffer-buffer+1) * sizeof(buffer[0]));  \
                memcpy(buffer, _tmp, _size_in_bytes);                                                                           \
                free(_tmp);                                                                                                     \
            }                                                                                                                   \
        }                                                                                                                       \
        bottom_##buffer = NULL;                                                                                                 \
        top_##buffer    = NULL;

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
    #define FLUSH_CIRCBUFF(buffer)                                                                                              \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        size_##buffer   = 0;                                                                                                    \
        top_##buffer    = NULL;                                                                                                 \
        bottom_##buffer = NULL;

    /**
     * @def FREE_CIRCBUFF(buffer)
     *   Deallocates and invalidates a circular buffer.
     */
    #define FREE_CIRCBUFF(buffer)                                                                                               \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        free(buffer);                                                                                                           \
        INVALIDATE_CIRCBUFF(buffer)

    /**
     * @def GET_CIRCBUFF(ptr, buffer, i)
     *   Gets the ith element from the bottom of a circular buffer.
     */
    #define GET_CIRCBUFF(ptr, buffer, i)                                                                                        \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        DEBUG_ASSERT(i < size_##buffer)                                                                                         \
        ptr = ((bottom_##buffer + i < buffer + cap_##buffer) ? bottom_##buffer + i : top_##buffer - (size_##buffer - i - 1));

    /**
     * @def INVALIDATE_CIRCBUFF(buffer)
     *   Invalidates a circular buffer so it cannot pass the IS_VALID_CIRCBUFF(buffer) test.
     */
    #define INVALIDATE_CIRCBUFF(buffer)                                                                                         \
        size_##buffer   = 0;                                                                                                    \
        cap_##buffer    = 0;                                                                                                    \
        buffer          = NULL;                                                                                                 \
        top_##buffer    = NULL;                                                                                                 \
        bottom_##buffer = NULL;

    /**
     * @def IS_VALID_CIRCBUFF(buffer)
     *   A Boolean expression that checks if a buffer is valid.
     */
    #define IS_VALID_CIRCBUFF(buffer) (                                                                                         \
            (buffer != NULL)                                &&                                                                  \
            (size_##buffer <= cap_##buffer)                 &&                                                                  \
            (cap_##buffer > 0)                              &&                                                                  \
            (cap_##buffer < UINT32_MAX / sizeof(buffer[0]))   &&                                                                \
            (                                                                                                                   \
                (                                                                                                               \
                    (bottom_##buffer == top_##buffer)                                                                       &&  \
                    (size_##buffer <= 1)                                                                                        \
                ) || (                                                                                                          \
                    (top_##buffer < bottom_##buffer)                                                                        &&  \
                    (top_##buffer >= buffer)                                                                                &&  \
                    (bottom_##buffer < buffer + cap_##buffer)                                                               &&  \
                    ((uint32_t)((top_##buffer - buffer + 1) + (buffer + cap_##buffer - bottom_##buffer)) == size_##buffer)      \
                ) || (                                                                                                          \
                    (bottom_##buffer < top_##buffer)                                                                        &&  \
                    (bottom_##buffer >= buffer)                                                                             &&  \
                    (top_##buffer < buffer + cap_##buffer)                                                                  &&  \
                    ((uint32_t)(top_##buffer - bottom_##buffer + 1) == size_##buffer)                                           \
                )                                                                                                               \
            )                                                                                                                   \
        )

    /**
     * @def PEEK_BOTTOM_CIRCBUFF(ptr, buffer)
     *   Peeks the bottom element of a circular buffer.
     */
    #define PEEK_BOTTOM_CIRCBUFF(ptr, buffer)                                                                                   \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        DEBUG_ERROR_IF(bottom_##buffer == NULL)                                                                                 \
        ptr = bottom_##buffer;

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
        DEBUG_ERROR_IF(top_##buffer == NULL)                                                                                    \
        ptr = top_##buffer;

    /**
     * @def POP_BOTTOM_CIRCBUFF(buffer)
     *   Pops the bottom element in a circular buffer.
     */
    #define POP_BOTTOM_CIRCBUFF(buffer)                                                                                         \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        DEBUG_ASSERT(size_##buffer > 0)                                                                                         \
        if (size_##buffer == 1) {                                                                                               \
            bottom_##buffer = NULL;                                                                                             \
            top_##buffer    = NULL;                                                                                             \
        } else {                                                                                                                \
            bottom_##buffer = (bottom_##buffer == buffer + cap_##buffer - 1) ? buffer: bottom_##buffer + 1;                     \
        }                                                                                                                       \
        size_##buffer--;

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
    #define POP_TOP_CIRCBUFF(buffer)                                                                                            \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        DEBUG_ASSERT(size_##buffer > 0)                                                                                         \
        if (size_##buffer == 1) {                                                                                               \
            top_##buffer    = NULL;                                                                                             \
            bottom_##buffer = NULL;                                                                                             \
        } else {                                                                                                                \
            top_##buffer    = (top_##buffer == buffer) ? buffer + cap_##buffer - 1 : top_##buffer - 1;                          \
        }                                                                                                                       \
        size_##buffer--;

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
    #define PUSH_BOTTOM_CIRCBUFF(type, buffer, ptr)                                                                             \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        if (bottom_##buffer == NULL) {                                                                                          \
            bottom_##buffer = buffer;                                                                                           \
            top_##buffer    = buffer;                                                                                           \
        } else {                                                                                                                \
            REALLOC_CIRCBUFF_IF_NECESSARY(type, buffer)                                                                         \
            bottom_##buffer = (bottom_##buffer == buffer) ? buffer + cap_##buffer - 1 : bottom_##buffer - 1;                    \
        }                                                                                                                       \
        if (ptr == NULL) {                                                                                                      \
            memset(bottom_##buffer, 0, sizeof(type));                                                                           \
        } else {                                                                                                                \
            memcpy(bottom_##buffer, ptr, sizeof(type));                                                                         \
        }                                                                                                                       \
        size_##buffer++;

    /**
     * @def PUSH_BOTTOM_CIRCBUFF_C(type, buffer, ptr)
     *   Pushes an element to the bottom of a circular buffer (overwrites, NO resizes).
     */
    #define PUSH_BOTTOM_CIRCBUFF_C(type, buffer, ptr)                                                                           \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        if (bottom_##buffer == NULL) {                                                                                          \
            bottom_##buffer = buffer;                                                                                           \
            top_##buffer    = buffer;                                                                                           \
        } else {                                                                                                                \
            bottom_##buffer = (bottom_##buffer == buffer) ? buffer + cap_##buffer - 1 : bottom_##buffer - 1;                    \
        }                                                                                                                       \
        if (ptr == NULL) {                                                                                                      \
            memset(bottom_##buffer, 0, sizeof(type));                                                                           \
        } else {                                                                                                                \
            memcpy(bottom_##buffer, ptr, sizeof(type));                                                                         \
        }                                                                                                                       \
        if (size_##buffer == cap_##buffer) {                                                                                    \
            DEBUG_ASSERT(top_##buffer == bottom_##buffer)                                                                       \
            top_##buffer    = (top_##buffer == buffer) ? buffer + cap_##buffer - 1 : top_##buffer - 1;                          \
        } else {                                                                                                                \
            size_##buffer++;                                                                                                    \
        }

    /**
     * @def PUSH_BOTTOM_CIRCBUFF_N(type, ptr, buffer)
     *   Pushes a zero (or NULL) element to the bottom of a circular buffer and then peeks it.
     */
    #define PUSH_BOTTOM_CIRCBUFF_N(type, ptr, buffer)                                                                           \
        PUSH_BOTTOM_CIRCBUFF(type, buffer, NULL)                                                                                \
        ptr = bottom_##buffer;

    /**
     * @def PUSH_BOTTOM_CIRCBUFF_NC(type, ptr, buffer)
     *   Pushes a zero (or NULL) element to the bottom of a circular buffer and then peeks it (overwrites, NO resizes).
     */
    #define PUSH_BOTTOM_CIRCBUFF_NC(type, ptr, buffer)                                                                          \
        PUSH_BOTTOM_CIRCBUFF_C(type, buffer, NULL)                                                                              \
        ptr = bottom_##buffer;

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
    #define PUSH_TOP_CIRCBUFF(type, buffer, ptr)                                                                                \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        if (top_##buffer == NULL) {                                                                                             \
            top_##buffer    = buffer;                                                                                           \
            bottom_##buffer = buffer;                                                                                           \
        } else {                                                                                                                \
            REALLOC_CIRCBUFF_IF_NECESSARY(type, buffer)                                                                         \
            top_##buffer    = (top_##buffer == buffer + cap_##buffer - 1) ? buffer : top_##buffer + 1;                          \
        }                                                                                                                       \
        if (ptr == NULL) {                                                                                                      \
            memset(top_##buffer, 0, sizeof(type));                                                                              \
        } else {                                                                                                                \
            memcpy(top_##buffer, ptr, sizeof(type));                                                                            \
        }                                                                                                                       \
        size_##buffer++;

    /**
     * @def PUSH_TOP_CIRCBUFF_C(type, buffer, ptr)
     *   Pushes an element to the top of a circular buffer (overwrites, NO resizes).
     */
    #define PUSH_TOP_CIRCBUFF_C(type, buffer, ptr)                                                                              \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        if (top_##buffer == NULL) {                                                                                             \
            top_##buffer    = buffer;                                                                                           \
            bottom_##buffer = buffer;                                                                                           \
        } else {                                                                                                                \
            top_##buffer    = (top_##buffer == buffer + cap_##buffer - 1) ? buffer : top_##buffer + 1;                          \
        }                                                                                                                       \
        if (ptr == NULL) {                                                                                                      \
            memset(top_##buffer, 0, sizeof(type));                                                                              \
        } else {                                                                                                                \
            memcpy(top_##buffer, ptr, sizeof(type));                                                                            \
        }                                                                                                                       \
        if (size_##buffer == cap_##buffer) {                                                                                    \
            DEBUG_ASSERT(bottom_##buffer == top_##buffer)                                                                       \
            bottom_##buffer = (bottom_##buffer == buffer + cap_##buffer - 1) ? buffer : bottom_##buffer + 1;                    \
        } else {                                                                                                                \
            size_##buffer++;                                                                                                    \
        }

    /**
     * @def PUSH_TOP_CIRCBUFF_N(type, ptr, buffer)
     *   Pushes a zero (or NULL) element to the top of a circular buffer and then peeks it.
     */
    #define PUSH_TOP_CIRCBUFF_N(type, ptr, buffer)                                                                              \
        PUSH_TOP_CIRCBUFF(type, buffer, NULL)                                                                                   \
        ptr = top_##buffer;

    /**
     * @def PUSH_TOP_CIRCBUFF_NC(type, ptr, buffer)
     *   Pushes a zero (or NULL) element to the top of a circular buffer and then peeks it (overwrites, NO resizes).
     */
    #define PUSH_TOP_CIRCBUFF_NC(type, ptr, buffer)                                                                             \
        PUSH_TOP_CIRCBUFF_C(type, buffer, NULL)                                                                                 \
        ptr = top_##buffer;

    /**
     * @def REALLOC_CIRCBUFF_IF_NECESSARY(type, buffer)
     *   Reallocates a circular buffer if it is necessary.
     */
    #define REALLOC_CIRCBUFF_IF_NECESSARY(type, buffer)                                                                         \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        if (size_##buffer == cap_##buffer) {                                                                                    \
            DEBUG_ASSERT(cap_##buffer < UINT32_MAX >> 1)                                                                        \
            cap_##buffer <<= 1;                                                                                                 \
            type* const _new_buffer = malloc(cap_##buffer * sizeof(type));                                                      \
            DEBUG_EXECUTE(if (_new_buffer == NULL) REALLOC_ERROR)                                                               \
            if (bottom_##buffer < top_##buffer) {                                                                               \
                DEBUG_ASSERT(bottom_##buffer == buffer)                                                                         \
                memcpy(_new_buffer, buffer, size_##buffer * sizeof(type));                                                      \
            } else {                                                                                                            \
                size_t const _size = (size_t)(buffer + cap_##buffer - bottom_##buffer);                                         \
                memcpy(_new_buffer, bottom_##buffer, _size * sizeof(type));                                                     \
                memcpy(_new_buffer + _size, buffer, (size_t)(top_##buffer - buffer + 1) * sizeof(type));                        \
            }                                                                                                                   \
            free(buffer);                                                                                                       \
            buffer          = _new_buffer;                                                                                      \
            bottom_##buffer = buffer;                                                                                           \
            top_##buffer    = buffer + size_##buffer - 1;                                                                       \
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
    #define ROTATE_DOWN_CIRCBUFF(type, buffer, n)                                                                               \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        REPEAT_CNTR(_dcntr_rotate_circbuff, n) {                                                                                \
            POP_BOTTOM_CIRCBUFF_V(type const* const _tmp, buffer)                                                               \
            PUSH_TOP_CIRCBUFF(type, buffer, _tmp)                                                                               \
        }

    /**
     * @def ROTATE_UP_CIRCBUFF(type, buffer, n)
     *   Pops the top element of a circular buffer and pushes it to the bottom, n times.
     */
    #define ROTATE_UP_CIRCBUFF(type, buffer, n)                                                                                 \
        DEBUG_ASSERT(IS_VALID_CIRCBUFF(buffer))                                                                                 \
        REPEAT_CNTR(_dcntr_rotate_circbuff, n) {                                                                                \
            POP_TOP_CIRCBUFF_V(type const* const _tmp, buffer)                                                                  \
            PUSH_BOTTOM_CIRCBUFF(type, buffer, _tmp)                                                                            \
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
            type* _tmp;                                                                                                         \
            _tmp = buff_A;          buff_A          = buff_B;           buff_B          = _tmp;                                 \
            _tmp = bottom_##buff_A; bottom_##buff_A = bottom_##buff_B;  bottom_##buff_B = _tmp;                                 \
            _tmp = top_##buff_A;    top_##buff_A    = top_##buff_B;     top_##buff_B    = _tmp;                                 \
        } {                                                                                                                     \
            uint32_t _tmp;                                                                                                      \
            _tmp = size_##buff_A;   size_##buff_A   = size_##buff_B;    size_##buffB    = _tmp;                                 \
            _tmp = cap_##buff_A;    cap_##buff_A    = cap_##buff_B;     cap_##buffB     = _tmp;                                 \
        }

    /**
     * @def UPGRADE_STACK_TO_CIRCBUFF_D(type, stack)
     *   Converts a stack to a circular buffer and declares the extra variables.
     */
    #define UPGRADE_STACK_TO_CIRCBUFF_D(type, stack)                                                                            \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                                                     \
        type* bottom_##stack;                                                                                                   \
        type* top_##stack;                                                                                                      \
        UPGRADE_STACK_TO_CIRCBUFF(type, stack)

    /**
     * @def UPGRADE_STACK_TO_CIRCBUFF(type, stack)
     *   Converts a stack to a circular buffer.
     */
    #define UPGRADE_STACK_TO_CIRCBUFF(type, stack)                                                                              \
        DEBUG_ASSERT(IS_VALID_STACK(stack))                                                                                     \
        if (size_##stack == 0) {                                                                                                \
            bottom_##stack  = NULL;                                                                                             \
            top_##stack     = NULL;                                                                                             \
        } else {                                                                                                                \
            bottom_##stack  = (size_##stack == 0) ? NULL : stack;                                                               \
            top_##stack     = (size_##stack == 0) ? NULL : stack + size_##stack - 1;                                            \
        }

#endif
