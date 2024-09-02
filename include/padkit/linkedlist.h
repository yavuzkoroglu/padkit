#ifndef PADKIT_LINKEDLIST_H
    #define PADKIT_LINKEDLIST_H
    #include "padkit/arraylist.h"

    /**
     * @def NOT_AN_LLIST
     *   A special LinkedList that cannot pass the isValid_llist() test.
     */
    #define NOT_AN_LLIST    ((LinkedList){ { NOT_A_STACK }, 0, 0 })

    typedef struct LinkBody {
        uint32_t    prevLinkId;
        uint32_t    nextLinkId;
        char        data[];
    } Link;

    typedef struct LinkedListBody {
        size_t      sz_element;
        ArrayList   links[1];
        uint32_t    firstLinkId;
        uint32_t    lastLinkId;
    } LinkedList;

    void constructEmpty_llist(
        LinkedList list[static const 1],
        size_t const sz_element,
        uint32_t const initial_cap
    );

    void flush_llist(LinkedList list[static const 1]);

    void free_llist(LinkedList list[static const 1]);

    void* get_llist(LinkedList const list[static const 1], uint32_t const id);

    bool isValid_llist(LinkedList const list[static const 1]);
#endif
