#ifndef PADKIT_ITEM_H
    #define PADKIT_ITEM_H
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>

    #define NOT_AN_ITEM         ((Item){ NULL, 0, 0 })

    typedef struct ItemBody {
        void*       p;
        uint32_t    sz;
        uint32_t    offset;
    } Item;

    bool areEquiv_item(
        Item const i1,
        Item const i2
    );

    uint32_t hash32_item(Item const item);

    uint64_t hash64_item(Item const item);

    bool isValid_item(Item const item);
#endif
