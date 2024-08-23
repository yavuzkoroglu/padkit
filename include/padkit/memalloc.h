/**
 * @file memalloc.h
 * @brief Defines safe MALLOC and CALLOC macros.
 * @author Yavuz Koroglu
 */
#ifndef MEMALLOC_H
    #define MEMALLOC_H

    /**
     * @def MALLOC_ERROR
     *   The default error raised in case of a MALLOC error.
     */
    /**
     * @def CALLOC_ERROR
     *   The default error raised in case of a CALLOC error.
     */
    #ifndef NDEBUG
        #include "padkit/debug.h"
        #define MALLOC_ERROR    TERMINATE_ERROR_MSG("%s", "Error Because => MALLOC_ERROR")
        #define CALLOC_ERROR    TERMINATE_ERROR_MSG("%s", "Error Because => CALLOC_ERROR")
    #else
        #include <stdio.h>
        #include <stdlib.h>

        #define MALLOC_ERROR {                                  \
            fputs("Error Because => MALLOC_ERROR\n", stderr);   \
            exit(EXIT_FAILURE);                                 \
        }
        #define CALLOC_ERROR {                                  \
            fputs("Error Because => CALLOC_ERROR\n", stderr);   \
            exit(EXIT_FAILURE);                                 \
        }
    #endif

    /**
     * @brief Wraps malloc().
     *
     * @param[in] size A constant size (must be > 0 && < sqrt(SIZE_MAX + 1)).
     *
     * @return A pointer to an object.
     */
    void* mem_alloc(size_t const size);

    /**
     * @brief Wraps calloc().
     *
     * @param[in] nmemb A constant size (must be > 0 && < sqrt(SIZE_MAX + 1)).
     * @param[in] size A constant size (must be > 0 && < sqrt(SIZE_MAX + 1)).
     *
     * @return A pointer to an object.
     */
    void* mem_calloc(size_t const nmemb, size_t const size);
#endif
