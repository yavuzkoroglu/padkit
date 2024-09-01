/**
 * @file memalloc.h
 * @brief Defines safe memory allocation functions.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_MEMALLOC_H
    #define PADKIT_MEMALLOC_H
    #include <stddef.h>

    /**
     * @brief Wraps malloc().
     *
     * @param[in] size A constant size (must be > 0 && < SZSZ_MAX).
     *
     * @return A pointer to an object.
     */
    void* mem_alloc(size_t const size);

    /**
     * @brief Wraps calloc().
     *
     * @param[in]   nmemb A constant size (must be > 0 && < SZSZ_MAX).
     * @param[in] sz_memb A constant size (must be > 0 && < SZSZ_MAX).
     *
     * @return A pointer to an object.
     */
    void* mem_calloc(size_t const nmemb, size_t const sz_memb);

    /**
     * @brief Reallocates a pointer using realloc().
     *
     * @param[in,out] ptrptr A constant non-null pointer to an object pointer.
     * @param[in]     new_sz A constant size (must be > 0 && < SZSZ_MAX).
     */
    void mem_realloc(void* ptrptr[static const 1], size_t const new_sz);

    /**
     * @brief Reallocates a pointer using calloc() and memcpy().
     *
     * @param[in,out]    ptrptr A constant non-null pointer to an object pointer.
     * @param[in]     old_nmemb A constant size (must be > 0 && < SZSZ_MAX).
     * @param[in]     new_nmemb A constant size (must be > 0 && < SZSZ_MAX).
     * @param[in]       sz_memb A constant size (must be > 0 && < SZSZ_MAX).
     */
    void mem_recalloc(
        void* ptrptr[static const 1],
        size_t const old_nmemb,
        size_t const new_nmemb,
        size_t const sz_memb
    );
#endif
