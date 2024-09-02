#ifndef PADKIT_MEMALLOC_H
    #define PADKIT_MEMALLOC_H
    #include <stddef.h>

    void* mem_alloc(size_t const size);

    void* mem_calloc(size_t const nmemb, size_t const sz_memb);

    void mem_realloc(void* ptrptr[static const 1], size_t const new_sz);

    void mem_recalloc(
        void* ptrptr[static const 1],
        size_t const old_nmemb,
        size_t const new_nmemb,
        size_t const sz_memb
    );
#endif
