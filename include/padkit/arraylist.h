#ifndef PADKIT_ARRAYLIST_H
    #define PADKIT_ARRAYLIST_H
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdio.h>

    #define NOT_AN_ALIST                        ((ArrayList){ 0, 0, 0, NULL })

    #ifndef ALIST_RECOMMENDED_INITIAL_CAP
        #define ALIST_RECOMMENDED_INITIAL_CAP   (BUFSIZ)
    #endif

    typedef struct ArrayListBody {
        size_t      sz_elem;
        uint32_t    cap;
        uint32_t    len;
        char*       arr;
    } ArrayList;

    void* addDuplicate_alist(
        ArrayList list[static const 1],
        uint32_t const id
    );

    void* addDuplicates_alist(
        ArrayList list[static const 1],
        uint32_t const id,
        uint32_t const n
    );

    void* addElement_alist(
        ArrayList list[static const 1],
        void const* const p
    );

    void* addElements_alist(
        ArrayList list[static const 1],
        void const* const p,
        uint32_t const n
    );

    void* addIndeterminate_alist(ArrayList list[static const 1]);

    void* addIndeterminates_alist(
        ArrayList list[static const 1],
        uint32_t const n
    );

    void* addZero_alist(ArrayList list[static const 1]);

    void* addZeros_alist(
        ArrayList list[static const 1],
        uint32_t const n
    );

    uint32_t bsearch_alist(
        void* key[static const 1],
        ArrayList const list[static const 1],
        void const* const p,
        int (*cmp)(void const*, void const*)
    );

    void concat_alist(
        ArrayList head[static const 1],
        ArrayList const tail[static const 1]
    );

    void construct_alist(void* const p_list, ...);

    void constructEmpty_alist(
        ArrayList list[static const 1],
        size_t const sz_elem,
        uint32_t const init_cap
    );

    void deleteElement_alist(
        ArrayList list[static const 1],
        uint32_t const id
    );

    void deleteElements_alist(
        ArrayList list[static const 1],
        uint32_t const id,
        uint32_t const n
    );

    void destruct_alist(void* const p_list);

    void flush_alist(ArrayList list[static const 1]);

    void* get_alist(
        ArrayList const list[static const 1],
        uint32_t const id
    );

    void* getFirst_alist(ArrayList const list[static const 1]);

    void* getLast_alist(ArrayList const list[static const 1]);

    bool isAllocated_alist(void const* const p_list);

    bool isSorted_alist(
        ArrayList const list[static const 1],
        int (*cmp)(void const*, void const*)
    );

    bool isValid_alist(void const* const p_list);

    uint32_t lsearch_alist(
        void* key[static const 1],
        ArrayList const list[static const 1],
        void const* const p
    );

    void qsort_alist(
        ArrayList const list[static const 1],
        int (*cmp)(void const*, void const*)
    );

    void* removeLast_alist(ArrayList list[static const 1], uint32_t const n);

    void reverse_alist(ArrayList list[static const 1]);

    void* setDuplicate_alist(
        ArrayList list[static const 1],
        uint32_t const orig_id,
        uint32_t const dup_id
    );

    void* setDuplicates_alist(
        ArrayList list[static const 1],
        uint32_t const orig_id,
        uint32_t const dup_id,
        uint32_t const n
    );

    void* setElement_alist(
        ArrayList list[static const 1],
        uint32_t const id,
        void const* const p
    );

    void* setElements_alist(
        ArrayList list[static const 1],
        uint32_t const id,
        void const* const p,
        uint32_t const n
    );

    void* setZero_alist(
        ArrayList list[static const 1],
        uint32_t const id
    );

    void* setZeros_alist(
        ArrayList list[static const 1],
        uint32_t const id,
        uint32_t const n
    );

    void vconstruct_alist(void* const p_list, va_list args);
#endif
