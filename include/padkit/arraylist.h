#ifndef PADKIT_ARRAYLIST_H
    #define PADKIT_ARRAYLIST_H
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdio.h>

    #define NOT_AN_ALIST                    ((ArrayList){ 0, 0, 0, NULL })

    #define ALIST_RECOMMENDED_INITIAL_CAP   (BUFSIZ)

    typedef struct ArrayListBody {
        size_t      sz_element;
        uint32_t    cap;
        uint32_t    size;
        char*       array;
    } ArrayList;

    void* add_alist(ArrayList list[static const 1], uint32_t const n, void const* const restrict ptr);

    void* addIndeterminate_alist(ArrayList list[static const 1], uint32_t const n);

    void* addZeros_alist(ArrayList list[static const 1], uint32_t const n);

    uint32_t bsearch_alist(
        void* key[static const 1],
        ArrayList const list[static const 1],
        void const* const ptr,
        int (*compar)(void const*, void const*)
    );

    void concat_alist(ArrayList head[static const restrict 1], ArrayList const tail[static const restrict 1]);

    void constructEmpty_alist(
        ArrayList list[static const 1],
        size_t const sz_element,
        uint32_t const initial_cap
    );

    void flush_alist(ArrayList list[static const 1]);

    void free_alist(ArrayList list[static const 1]);

    void* get_alist(ArrayList const list[static const 1], uint32_t const id);

    bool isSorted_alist(ArrayList const list[static const 1], int (*compar)(void const*, void const*));

    bool isValid_alist(ArrayList const list[static const 1]);

    uint32_t lsearch_alist(void* key[static const 1], ArrayList const list[static const 1], void const* const ptr);

    void qsort_alist(ArrayList const list[static const 1], int (*compar)(void const*, void const*));

    void* removeLast_alist(ArrayList list[static const 1], uint32_t const n);

    void reverse_alist(ArrayList list[static const 1]);

    void* set_alist(
        ArrayList list[static const 1],
        uint32_t const startId,
        uint32_t const n,
        void const* const restrict ptr
    );

    void* setZeros_alist(ArrayList list[static const 1], uint32_t const startId, uint32_t const n);
#endif
