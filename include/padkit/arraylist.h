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

    #define addAll_alist(head, tail)                concatN_alist(head, tail, 1)

    extern void (* const addAllN_alist)(
        ArrayList* const head,
        ArrayList const* const tail,
        uint32_t const n
    );

    #define addDup_alist(list, id)                  addDupN_alist(list, id, 1)

    #define addDupFirst_alist(list)                 addDupN_alist(list, 0, 1)

    #define addDupFirstN_alist(list, n)             addDupN_alist(list, 0, n)

    #define addDupLast_alist(list)                  addDupLastN_alist(list, 1)

    void* addDupLastN_alist(
        ArrayList* const list,
        uint32_t const n
    );

    void* addDupN_alist(
        ArrayList* const list,
        uint32_t const id,
        uint32_t const n
    );

    void* addDupSameN_alist(
        ArrayList* const list,
        uint32_t const id,
        uint32_t const n
    );

    void* addF_alist(
        ArrayList* const alist,
        FILE* const fp,
        uint32_t const max_n_buf
    );

    #define addIndeterminate_alist(list)            addN_alist(list, NULL, 1)

    #define addIndeterminateN_alist(list, n)        addN_alist(list, NULL, n)

    void* addN_alist(
        ArrayList* const list,
        void const* const p,
        uint32_t const n
    );

    void* addSameN_alist(
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

    #define concat_alist(head, tail)                concatN_alist(head, tail, 1)

    void concatN_alist(
        ArrayList* const head,
        ArrayList const* const tail,
        uint32_t const n
    );

    void construct_alist(void* const p_list, ...);

    void constructEmpty_alist(
        ArrayList* const list,
        size_t const sz_elem,
        uint32_t const init_cap
    );

    #define delete_alist(list, id)                  deleteN_alist(list, id, 1)

    extern void (* const deleteAll_alist)(ArrayList* const list);

    #define deleteFirst_alist(list)                 deleteN_alist(list, 0, 1)

    #define deleteFirstN_alist(list, n)             deleteN_alist(list, 0, n)

    #define deleteLast_alist(list)                  deleteLastN_alist(list, 1)

    void deleteLastN_alist(
        ArrayList* const list,
        uint32_t const n
    );

    void deleteN_alist(
        ArrayList* const list,
        uint32_t const id,
        uint32_t const n
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

    void* insertDupNSame_alist(
        ArrayList* const list,
        uint32_t const dup_id,
        uint32_t const orig_id,
        uint32_t const n
    );

    #define insertIndeterminate_alist(list, id)     insertN_alist(list, id, NULL, 1)

    #define insertIndeterminateN_alist(list, id, n) insertN_alist(list, id, NULL, n)

    void* insertN_alist(
        ArrayList* const list,
        uint32_t const id,
        void const* const p,
        uint32_t const n
    );

    /* TBI */
    void* insertNSame_alist(
        ArrayList* const list,
        uint32_t const id,
        void const* const p,
        uint32_t const n
    );

    #define insertZeros_alist(list, id)             insertZerosN_alist(list, id, 1)

    void* insertZerosN_alist(
        ArrayList* const list,
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

    #define peek_alist(list)                        getLastN_alist(list, 1)

    #define peekBottom_alist(list)                  getN_alist(list, 0, 1)

    #define peekBottomN_alist(list, n)              getN_alist(list, 0, n)

    extern void* (* const peekN_alist)(
        ArrayList const* const list,
        uint32_t const n
    );

    #define peekTop_alist(list)                     getLastN_alist(list, 1)

    extern void* (* const peekTopN_alist)(
        ArrayList const* const list,
        uint32_t const n
    );

    #define pop_alist(list)                         removeLastN_alist(list, 1)

    #define popBottom_alist(list)                   removeN_alist(list, 0, 1)

    #define popBottomN_alist(list, n)               removeN_alist(list, 0, n)

    #define popN_alist(list, n)                     removeLastN_alist(list, n)

    #define popTop_alist(list)                      removeLastN_alist(list, 1)

    #define popTopN_alist(list, n)                  removeLastN_alist(list, n)

    #define push_alist(list, p)                     addN_alist(list, p, 1)

    #define pushBottom_alist(list, p)               pushBottomN_alist(list, p, 1)

    void* pushBottomN_alist(
        ArrayList* const list,
        void const* const p,
        uint32_t const n
    );

    /* TBI */
    void* pushBottomNSame_alist(
        ArrayList* const list,
        void const* const p,
        uint32_t const n
    );

    #define pushIndeterminate_alist(list)           addN_alist(list, NULL, 1)

    #define pushIndeterminateBottom_alist(list)     pushBottomN_alist(list, NULL, 1)

    #define pushIndeterminateBottomN_alist(list, n) pushBottomN_alist(list, NULL, n)

    #define pushIndeterminateN_alist(list, n)       addN_alist(list, NULL, n)

    #define pushIndeterminateTop_alist(list)        addN_alist(list, NULL, 1)

    #define pushIndeterminateTopN_alist(list, n)    addN_alist(list, NULL, n)

    extern void* (* const pushN_alist)(
        ArrayList* const list,
        void const* const p,
        uint32_t const n
    );

    /* TBI */
    extern void* (* const pushNSame_alist)(
        ArrayList* const list,
        void const* const p,
        uint32_t const n
    );

    #define pushTop_alist(list, p)                  add_alist(list, p)

    extern void* (* const pushTopN_alist)(
        ArrayList* const list,
        void const* const p,
        uint32_t const n
    );

    #define pushZeros_alist(list)                   addZerosN_alist(list, 1)

    #define pushZerosBottom_alist(list)             pushZerosBottomN_alist(list, 1)

    void* pushZerosBottomN_alist(
        ArrayList* const list,
        uint32_t const n
    );

    extern void* (* const pushZerosN_alist)(
        ArrayList* const list,
        uint32_t const n
    );

    #define pushZerosTop_alist(list)                addZerosN_alist(list, 1)

    extern void* (* const pushZerosTopN_alist)(
        ArrayList* const list,
        uint32_t const n
    );

    void qsort_alist(
        ArrayList* const list,
        int (*cmp)(void const*, void const*)
    );

    #define remove_alist(list, id)                  removeN_alist(list, id, 1)

    void* removeAll_alist(ArrayList* const list);

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

    #define rotate_alist(list)                      rotateDownN_alist(list, 1)

    #define rotateDown_alist(list)                  rotateDownN_alist(list, 1)

    void rotateDownN_alist(
        ArrayList* const alist,
        uint32_t n
    );

    extern void (* const rotateN_alist)(
        ArrayList* const alist,
        uint32_t n
    );

    #define rotateUp_alist(list)                    rotateUpN_alist(list, 1)

    void rotateUpN_alist(
        ArrayList* const alist,
        uint32_t n
    );

    #define set_alist(list, id, p)                  setN_alist(list, id, p, 1)

    void* setAll_alist(
        ArrayList* const list,
        void const* const p
    );

    #define setDup_alist(list, dup_id, orig_id)     setDupN_alist(list, dup_id, orig_id, 1)

    void* setDupN_alist(
        ArrayList* const list,
        uint32_t const dup_id,
        uint32_t const orig_id,
        uint32_t const n
    );

    void* setDupSameN_alist(
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

    void* setSameN_alist(
        ArrayList* const list,
        uint32_t const id,
        void const* const p,
        uint32_t const n
    );

    #define setZeros_alist(list, id)                setN_alist(list, id, NULL, 1)

    #define setZerosN_alist(list, id, n)            setN_alist(list, id, NULL, n)

    #define swap_alist(list, id1, id0)              swapN_alist(list, id1, id0, 1)

    void swapN_alist(
        ArrayList* const list,
        uint32_t const id1,
        uint32_t const id0,
        uint32_t const n
    );

    void vconstruct_alist(
        void* const p_list,
        va_list args
    );
#endif
