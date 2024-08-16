/**
 * @file reallocate.h
 * @brief Defines a safe REALLOCATE macro accompanied with a _reallocate() function.
 * @author Yavuz Koroglu
 */
#ifndef REALLOCATE_H
    #define REALLOCATE_H
    #include <stdbool.h>

    /**
     * @def REALLOC_ERROR
     *   The default error raised in case of a reallocate() error.
     */
    /**
     * @def RECALLOC_ERROR
     *   The default error raised in case of a recalloc() error.
     */
    #ifndef NDEBUG
        #include "padkit/debug.h"

        #define REALLOC_ERROR   TERMINATE_ERROR_MSG("%s", "Error Because => REALLOCATE_ERROR")
        #define RECALLOC_ERROR  TERMINATE_ERROR_MSG("%s", "Error Because => RECALLOC_ERROR")
    #else
        #include <stdio.h>
        #include <stdlib.h>

        #define REALLOC_ERROR {                                                         \
            fputs("Error Because => REALLOCATE_ERROR\n", stderr);                       \
            exit(EXIT_FAILURE);                                                         \
        }
        #define RECALLOC_ERROR {                                                        \
            fputs("Error Because => RECALLOC_ERROR\n", stderr);                         \
            exit(EXIT_FAILURE);                                                         \
        }
    #endif

    /**
     * @def REALLOCATE
     *   A wrapper macro for a standard reallocate() call.
     */
    #define REALLOCATE(ptr, old_n, new_n, type) \
        reallocate((void**)&(ptr), (size_t)(old_n), (size_t)(new_n), sizeof(type))

    /**
     * @def RECALLOC
     *   A wrapper macro for a standard recalloc() call.
     */
    #define RECALLOC(ptr, old_n, new_n, type) \
        recalloc((void**)&(ptr), (size_t)(old_n), (size_t)(new_n), sizeof(type))

    /**
     * @def REALLOC_IF_NECESSARY
     *   Calls reallocate() on an object array if necessary.
     */
    #define REALLOC_IF_NECESSARY(obj_t, obj, obj_cap_t, obj_cap, obj_sz) {              \
        obj_cap_t _new_cap = obj_cap;                                                   \
        while (_new_cap <= (obj_cap_t)obj_sz) {                                         \
            _new_cap <<= 1;                                                             \
            if (_new_cap <= obj_cap) REALLOC_ERROR                                      \
        }                                                                               \
        if (_new_cap > obj_cap) {                                                       \
            if (REALLOCATE(obj, obj_cap, _new_cap, obj_t) == NULL) REALLOC_ERROR        \
            obj_cap = _new_cap;                                                         \
        }                                                                               \
    }

    /**
     * @def RECALLOC_IF_NECESSARY
     *   Calls recalloc() on an object array if necessary.
     */
    #define RECALLOC_IF_NECESSARY(obj_t, obj, obj_cap_t, obj_cap, obj_sz) {             \
        obj_cap_t _new_cap = obj_cap;                                                   \
        while (_new_cap <= (obj_cap_t)obj_sz) {                                         \
            _new_cap <<= 1;                                                             \
            if (_new_cap <= obj_cap) RECALLOC_ERROR                                     \
        }                                                                               \
        if (_new_cap > obj_cap) {                                                       \
            if (RECALLOC(obj, obj_cap, _new_cap, obj_t) == NULL) RECALLOC_ERROR         \
            obj_cap = _new_cap;                                                         \
        }                                                                               \
    }

    /**
     * @brief A reallocator that uses realloc().
     * @param ptrptr A pointer to the pointer to be reallocated.
     * @param old_element_count The old element count.
     * @param new_element_count The new element count.
     * @param element_size Size of one element in bytes.
     */
    void* reallocate(
        void** ptrptr, size_t const old_element_count,
        size_t const new_element_count, size_t const element_size
    );

    /**
     * @brief A reallocator that uses calloc() & memcpy() instead of realloc().
     * @param ptrptr A pointer to the pointer to be reallocated.
     * @param old_element_count The old element count.
     * @param new_element_count The new element count.
     * @param element_size Size of one element in bytes.
     */
    void* recalloc(
        void** ptrptr, size_t const old_element_count,
        size_t const new_element_count, size_t const element_size
    );
#endif
