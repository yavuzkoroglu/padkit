#ifndef PADKIT_ARRAYLIST_H
    #define PADKIT_ARRAYLIST_H
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdio.h>

    #define NOT_AN_ALIST                            ((ArrayList){ 0, 0, 0, NULL })

    #ifndef ALIST_RECOMMENDED_INITIAL_CAP
        #define ALIST_RECOMMENDED_INITIAL_CAP       (BUFSIZ)
    #endif

    typedef struct ArrayListBody {
        size_t      sz_elem;
        uint32_t    cap;
        uint32_t    len;
        char*       arr;
    } ArrayList;

    #define add_alist(list, p)                      addN_alist(list, p, 1)

    #define addDup_alist(list, id)                  addDupN_alist(list, id, 1)

    void* addDupN_alist(
        ArrayList* const list,
        uint32_t const id,
        uint32_t const n
    );

    #define addIndeterminate_alist(list)            add_alist(list, NULL)

    #define addIndeterminateN_alist(list, n)        addN_alist(list, NULL, n)

    void* addN_alist(
        ArrayList* const list,
        void const* const p,
        uint32_t const n
    );

    #define addZeros_alist(list)                    addZerosN_alist(list, 1)

    void* addZerosN_alist(
        ArrayList* const list,
        uint32_t const n
    );

    uint32_t bsearch_alist(
        void** const p_key,
        ArrayList const* const list,
        void const* const p,
        int (*cmp)(void const*, void const*)
    );

    void concat_alist(
        ArrayList* const head,
        ArrayList const* const tail
    );

    void construct_alist(void* const p_list, ...);

    void constructEmpty_alist(
        ArrayList* const list,
        size_t const sz_elem,
        uint32_t const init_cap
    );

    void destruct_alist(void* const p_list);

    void flush_alist(ArrayList* const list);

    #define get_alist(list, id)                     getN_alist(list, id, 1)

    #define getFirst_alist(list)                    getN_alist(list, 0, 1)

    #define getFirstN_alist(list, n)                getN_alist(list, 0, n)

    #define getLast_alist(list)                     getLastN_alist(list, 1)

    void* getLastN_alist(
        ArrayList const* const list,
        uint32_t const n
    );

    void* getN_alist(
        ArrayList const* const list,
        uint32_t const id,
        uint32_t const n
    );

    #define insert_alist(list, id, p)               insertN_alist(list, id, p, 1)

    #define insertDup_alist(list, dup_id, orig_id)  insertDupN_alist(list, dup_id, orig_id, 1)

    void* insertDupN_alist(
        ArrayList* const list,
        uint32_t const dup_id,
        uint32_t const orig_id,
        uint32_t const n
    );

    #define insertIndeterminate_alist(list, id)     insertN_alist(list, id, NULL, 1)

    #define insertIndeterminateN_alist(list, id, n) insertN_alist(list, id, NULL, n)

    void* insertN_alist(
        ArrayList* list,
        uint32_t const id,
        void const* const p,
        uint32_t const n
    );

    #define insertZeros_alist(list, id)             insertZerosN_alist(list, id, 1)

    void* insertZerosN_alist(
        ArrayList* list,
        uint32_t const id,
        uint32_t const n
    );

    bool isAllocated_alist(void const* const p_list);

    bool isSorted_alist(
        ArrayList const* const list,
        int (*cmp)(void const*, void const*)
    );

    bool isValid_alist(void const* const p_list);

    uint32_t lsearch_alist(
        void** const p_key,
        ArrayList const* const list,
        void const* const p
    );

    #define peek_alist(list)                        peekTop_alist(list)

    #define peekBottom_alist(list)                  getFirst_alist(list)

    #define peekBottomN_alist(list, n)              getFirstN_alist(list, n)

    #define peekN_alist(list, n)                    peekTopN_alist(list, n)

    #define peekTop_alist(list)                     getLast_alist(list)

    #define peekTopN_alist(list, n)                 getLastN_alist(list, n)

    #define pop_alist(list)                         popTop_alist(list)

    #define popBottom_alist(list)                   removeFirst_alist(list)

    #define popBottomN_alist(list, n)               removeFirstN_alist(list, n)

    #define popN_alist(list, n)                     popTopN_alist(list, n)

    #define popTop_alist(list)                      removeLast_alist(list)

    #define popTopN_alist(list, n)                  removeLastN_alist(list, n)

    #define push_alist(list, p)                     pushTop_alist(list, p)

    #define pushBottom_alist(list, p)               pushBottomN_alist(list, p, 1)

    #define pushBottomN_alist(list, p, n) (         \
            list->len == 0                          \
                ? addN_alist(list, p, n)            \
                : insertN_alist(list, 0, p, n)      \
        )

    #define pushIndeterminate_alist(list)           push_alist(list, NULL)

    #define pushIndeterminateBottom_alist(list)     pushBottom_alist(list, NULL)

    #define pushIndeterminateBottomN_alist(list, n) pushBottomN_alist(list, NULL, n)

    #define pushIndeterminateN_alist(list, n)       pushN_alist(list, NULL, n)

    #define pushIndeterminateTop_alist(list)        pushTop_alist(list, NULL)

    #define pushIndeterminateTopN_alist(list, n)    pushTopN_alist(list, NULL, n)

    #define pushN_alist(list, p, n)                 pushTopN_alist(list, p, n)

    #define pushTop_alist(list, p)                  add_alist(list, p)

    #define pushTopN_alist(list, p, n)              addN_alist(list, p, n)

    #define pushZeros_alist(list)                   addZeros_alist(list)

    #define pushZerosBottom_alist(list)             pushZerosBottomN_alist(list, 1)

    #define pushZerosBottomN_alist(list, n) (       \
            list->len == 0                          \
                ? addZerosN_alist(list, n)          \
                : insertZerosN_alist(list, 0, n)    \
        )

    #define pushZerosN_alist(list, n)               addZerosN_alist(list, n)

    #define pushZerosTop_alist(list)                addZeros_alist(list)

    #define pushZerosTopN_alist(list, n)            addZerosN_alist(list, n)

    void qsort_alist(
        ArrayList* const list,
        int (*cmp)(void const*, void const*)
    );

    #define remove_alist(list, id)                  removeN_alist(list, id, 1)

    #define removeFirst_alist(list)                 removeN_alist(list, 0, 1)

    #define removeFirstN_alist(list, n)             removeN_alist(list, 0, n)

    #define removeLast_alist(list)                  removeLastN_alist(list, 1)

    void* removeLastN_alist(
        ArrayList* const list,
        uint32_t const n
    );

    void* removeN_alist(
        ArrayList* const list,
        uint32_t const id,
        uint32_t const n
    );

    void reverse_alist(ArrayList* const list);

    #define rotate_alist(list)                      rotateDown_alist(list)

    #define rotateDown_alist(list)                  rotateDownN_alist(list, 1)

    void rotateDownN_alist(
        ArrayList* const alist,
        uint32_t n
    );

    #define rotateN_alist(list, n)                  rotateDownN_alist(list, n)

    #define rotateUp_alist(list)                    rotateUpN_alist(list, 1)

    void rotateUpN_alist(
        ArrayList* const alist,
        uint32_t n
    );

    #define set_alist(list, id, p)                  setN_alist(list, id, p, 1)

    #define setDup_alist(list, dup_id, orig_id)     setDupN_alist(list, dup_id, orig_id, 1)

    void* setDupN_alist(
        ArrayList* const list,
        uint32_t const dup_id,
        uint32_t const orig_id,
        uint32_t const n
    );

    void* setN_alist(
        ArrayList* const list,
        uint32_t const id,
        void const* const p,
        uint32_t const n
    );

    #define setZeros_alist(list, id)                setZerosN_alist(list, id, 1)

    #define setZerosN_alist(list, id, n)            setN_alist(list, id, NULL, n)

    #define swap_alist(list, id1, id0)              swapN_alist(list, id1, id0, 1)

    void swapN_alist(
        ArrayList* const list,
        uint32_t const id1,
        uint32_t const id0,
        uint32_t const n
    );

    void vconstruct_alist(void* const p_list, va_list args);
#endif
