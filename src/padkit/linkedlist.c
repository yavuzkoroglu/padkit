#include "padkit/debug.h"
#include "padkit/invalid.h"
#include "padkit/linkedlist.h"

void constructEmpty_llist(
    LinkedList list[static const 1],
    size_t const sz_element,
    uint32_t const initial_cap
) {
    size_t const sz_link = sz_element + sizeof(Link);

    DEBUG_ASSERT(sz_element > 0)
    DEBUG_ASSERT(sz_element < SZSZ_MAX)
    DEBUG_ASSERT(initial_cap > 0)
    DEBUG_ASSERT(initial_cap < SZ32_MAX)
    DEBUG_ASSERT(sz_link < SZSZ_MAX)

    list->sz_element    = sz_element;
    constructEmpty_alist(list->links, sz_link, initial_cap);
    list->firstLinkId   = INVALID_UINT32;
    list->lastLinkId    = INVALID_UINT32;
}

void flush_llist(LinkedList list[static const 1]) {
    DEBUG_ASSERT(isValid_llist(list))
    flush_alist(list->links);
    list->firstLinkId   = INVALID_UINT32;
    list->lastLinkId    = INVALID_UINT32;
}

void free_llist(LinkedList list[static const 1]) {
    DEBUG_ASSERT(isValid_llist(list))
    free_alist(list->links);
    list[0] = NOT_AN_LLIST;
}

void* get_llist(LinkedList const list[static const 1], uint32_t const id) {
    DEBUG_ASSERT(isValid_llist(list))
    DEBUG_ASSERT(id < list->links->size)

    if (id < list->links->size >> 1) {
        Link* link = get_alist(list->links, list->firstLinkId);
        for (uint32_t i = 0; i < id; i++)
            link = get_alist(list->links, link->nextLinkId);

        return link->data;
    } else {
        Link* link = get_alist(list->links, list->lastLinkId);
        for (uint32_t i = list->links->size - 1; i > id; i--)
            link = get_alist(list->links, link->prevLinkId);

        return link->data;
    }
}

void insert_llist(LinkedList const list[static const 1], uint32_t const id, void const* const ptr) {
    DEBUG_ASSERT(isValid_llist(list))

    if (list->links->size == 0) {
        DEBUG_ASSERT(id == 0)

        add_alist()

        list->firstLinkId   = 0;
        list->lastLinkId    = 0;
    } else {
        
    }
}

bool isValid_llist(LinkedList const list[static const 1]) {
    if (list->sz_element == 0)                      return 0;
    if (!isValid_alist(list->links))                return 0;
    if (list->links->size > 0) {
        if (list->firstLinkId >= list->links->size) return 0;
        if (list->lastLinkId >= list->links->size)  return 0;
    }

    return 1;
}
