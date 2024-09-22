#ifndef PADKIT_ITEM_H
    #define PADKIT_ITEM_H
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>

    #define NOT_AN_ITEM ((Item){ NULL, 0, 0 })

    typedef struct ItemBody {
        void*       p;
        uint32_t    sz;
        uint32_t    offset;
    } Item;

    uint32_t hash32_item(Item const item[static const 1]);

    uint64_t hash64_item(Item const item[static const 1]);

    bool isValid_item(void const* const p_item);
#endif
