/**
 * @file item.h
 * @brief The related functions and the typedef for <tt>Item</tt>.
 * @author Yavuz KÖROĞLU
 * @see <tt>Item</tt>.
 */
#ifndef PADKIT_MISC_ITEM_H
    #define PADKIT_MISC_ITEM_H
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>

    /**
     * @brief Expands to an invalid \c Item.
     */
    #define NOT_AN_ITEM ((Item){ NULL, 0, 0 })

    /**
     * @brief An \c Item is a sequence of bytes.
     */
    typedef struct ItemBody {
        void*       p;          /**< A pointer to the first byte of the \c Item. */
        uint32_t    sz;         /**< The size of the \c Item in bytes. */
        uint32_t    offset;     /**< Used only if the \c Item resides in a \c Container. */
    } Item;

    /**
     * @brief Checks if two \c Item objects are equivalent.
     * @param i1 The first <tt>Item</tt>.
     * @param i2 The second <tt>Item</tt>.
     * @returns <tt>1</tt> if equivalent, <tt>0</tt> otherwise.
     * @pre Both \c Item objects are valid.
     */
    bool areEquiv_item(Item const i1, Item const i2);

    /**
     * @brief Computes a 32-bit unsigned hash value of a given <tt>Item</tt>.
     * @param item A constant <tt>Item</tt>.
     * @returns A 32-bit unsigned hash value of <tt>item</tt>.
     * @pre \c item is a valid <tt>Item</tt>.
     * @see hash.h
     */
    uint32_t hash32_item(Item const item);

    /**
     * @brief Computes a 64-bit unsigned hash value of a given <tt>Item</tt>.
     * @param item A constant <tt>Item</tt>.
     * @returns A 64-bit unsigned hash value of <tt>item</tt>.
     * @pre \c item is a valid <tt>Item</tt>.
     * @see hash.h
     */
    uint64_t hash64_item(Item const item);

    /**
     * @brief Checks if an \c Item is valid.
     * @param item A constant <tt>Item</tt>.
     * @returns <tt>1</tt> if valid, <tt>0</tt> otherwise.
     * @important An \c Item of zero size may seem counter-intuitive, but it is useful in containers.
     */
    bool isValid_item(Item const item);
#endif

