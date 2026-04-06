/**
 * @file memalloc.h
 * @brief Memory allocation error macros and functions.
 * @author Yavuz KÖROĞLU
 * @see error.h
 */
#ifndef PADKIT_MISC_MEMALLOC_H
    #define PADKIT_MISC_MEMALLOC_H
    #include <stddef.h>
    #include "padkit/error.h"

    /**
     * @brief Prints "Cause => MALLOC_ERROR" and terminates with \c EXIT_FAILURE.
     */
    #define MALLOC_ERROR TERMINATE_ERROR_MSG("Cause => MALLOC_ERROR")

    /**
     * @brief Prints "Cause => CALLOC_ERROR" and terminates with \c EXIT_FAILURE.
     */
    #define CALLOC_ERROR TERMINATE_ERROR_MSG("Cause => CALLOC_ERROR")

    /**
     * @brief Prints "Cause => REALLOC_ERROR" and terminates with \c EXIT_FAILURE.
     */
    #define REALLOC_ERROR TERMINATE_ERROR_MSG("Cause => REALLOC_ERROR")

    /**
     * @brief Prints "Cause => RECALLOC_ERROR" and terminates with \c EXIT_FAILURE.
     */
    #define RECALLOC_ERROR TERMINATE_ERROR_MSG("Cause => RECALLOC_ERROR")

    /**
     * @brief Allocates \c sz bytes of memory and returns a <tt>void*</tt> to the first byte.
     * @param sz The number of bytes to allocate (size).
     * @return A pointer to the first byte that is allocated.
     * @warning Does NOT return \c NULL. Instead, terminates with \c MALLOC_ERROR if the allocation fails.
     * @warning sz > SZSZ_MAX raises MALLOC_ERROR.
     * @pre \c sz is nonzero.
     * @see size.h
     */
    void* memalloc(size_t const sz);

    /**
     * @brief Allocates \c sz bytes of memory whose bytes are all zero.
     * @param sz The number of bytes to allocate (size).
     * @return A pointer to the first byte that is allocated.
     * @warning Does NOT return \c NULL. Instead, terminates with \c CALLOC_ERROR if the allocation fails.
     * @warning Allocations larger than SZSZ_MAX raises CALLOC_ERROR.
     * @pre \c n and \c sz_elem are nonzero.
     * @see size.h
     */
    void* memcalloc(size_t const n, size_t const sz_elem);

    /**
     * @brief Allocates \c new_sz bytes of memory for the old memory area that starts with <tt>*p_p</tt>.
     * @param p_p A pointer to a constant Object's first byte pointer.
     * @param new_sz The size of the new memory area in bytes.
     * @warning Terminates with \c REALLOC_ERROR if the allocation fails.
     * @warning new_sz > SZSZ_MAX raises REALLOC_ERROR.
     * @warning Any pointer <tt>q = *p_p</tt> will be invalid, unless <tt>&q = p_p</tt>.
     * @pre \c p_p is nonnull and \c new_sz is nonzero.
     * @see size.h
     */
    void memrealloc(void** const p_p, size_t const new_sz);

    /**
     * @brief Allocates new memory for an Object and sets the extra bytes to all zeros.
     * @param p_p A pointer to a constant Object's first byte pointer.
     * @param old_n The number of elements in the Object.
     * @param new_n The new number of elements.
     * @param sz_elem Size of one element in bytes.
     * @warning Terminates with \c RECALLOC_ERROR if the allocation fails.
     * @warning Allocations larger than SZSZ_MAX raises RECALLOC_ERROR.
     * @warning Any pointer <tt>q = *p_p</tt> will be invalid, unless <tt>&q = p_p</tt>.
     * @pre \c p_p is nonnull, \c old_n and sz_elem are nonzero.
     * @see size.h
     */
    void memrecalloc(
        void** const p_p,
        size_t const old_n,
        size_t const new_n,
        size_t const sz_elem
    );
#endif
