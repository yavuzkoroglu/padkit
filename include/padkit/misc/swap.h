/**
 * @file swap.h
 * @brief A function for swapping an \c Item with another.
 * @author Yavuz KÖROĞLU
 * @see item.h
 */
#ifndef PADKIT_MISC_SWAP_H
    #define PADKIT_MISC_SWAP_H
    #include <stddef.h>

    /**
     * @brief Swaps an \c Item with another of the same size.
     * @param p1 A constant pointer to the first byte of the first \c Item.
     * @param p2 A constant pointer to the first byte of the second \c Item.
     * @param sz The size of an \c Item in bytes.
     * @pre The pointers are nonnull and the size is nonzero.
     * @see \c Item
     */
    void swap(void* const p1, void* const p2, size_t const sz);
#endif
