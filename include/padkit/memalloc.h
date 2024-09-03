#ifndef PADKIT_MEMALLOC_H
    #define PADKIT_MEMALLOC_H
    #include <stddef.h>
    #include "padkit/error.h"

    #define MALLOC_ERROR    TERMINATE_ERROR_MSG("%s", "Cause => MALLOC_ERROR")
    #define CALLOC_ERROR    TERMINATE_ERROR_MSG("%s", "Cause => CALLOC_ERROR")
    #define REALLOC_ERROR   TERMINATE_ERROR_MSG("%s", "Cause => REALLOC_ERROR")
    #define RECALLOC_ERROR  TERMINATE_ERROR_MSG("%s", "Cause => RECALLOC_ERROR")

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
