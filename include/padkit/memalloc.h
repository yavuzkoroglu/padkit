#ifndef PADKIT_MEMALLOC_H
    #define PADKIT_MEMALLOC_H
    #include <stddef.h>
    #include "padkit/error.h"

    #define MALLOC_ERROR    TERMINATE_ERROR_MSG("Cause => MALLOC_ERROR")
    #define CALLOC_ERROR    TERMINATE_ERROR_MSG("Cause => CALLOC_ERROR")
    #define REALLOC_ERROR   TERMINATE_ERROR_MSG("Cause => REALLOC_ERROR")
    #define RECALLOC_ERROR  TERMINATE_ERROR_MSG("Cause => RECALLOC_ERROR")

    void* mem_alloc(size_t const sz);

    void* mem_calloc(size_t const n, size_t const sz_elem);

    void mem_realloc(void** const p_p, size_t const new_sz);

    void mem_recalloc(
        void** const p_p,
        size_t const old_n,
        size_t const new_n,
        size_t const sz_elem
    );
#endif
