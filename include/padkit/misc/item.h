// An Item is a special element of a container with a size of its own.
#ifndef PADKIT_ITEM_H
    #define PADKIT_ITEM_H
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>

    #define NOT_AN_ITEM         ((Item){ NULL, 0, 0 })

    typedef struct ItemBody {
        void*       p;          // A pointer to the Item.
        uint32_t    sz;         // The size of the pointed Item in bytes.
        uint32_t    offset;     // The # of bytes from the pointer of the first Item in the container to this Item.
    } Item;

    bool areEquiv_item(
        Item const i1,
        Item const i2
    );

    uint32_t hash32_item(Item const item);

    uint64_t hash64_item(Item const item);

    bool isValid_item(Item const item);
#endif
