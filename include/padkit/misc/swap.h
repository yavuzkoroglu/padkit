/**
 * @file swap.h
 * @brief A function for swapping two objects.
 * @author Yavuz KÖROĞLU
 */
#ifndef PADKIT_MISC_SWAP_H
    #define PADKIT_MISC_SWAP_H
    #include <stddef.h>

    /**
     * @brief Swaps two objects of the same size.
     * @param p1 A constant pointer to the first byte of the first object.
     * @param p2 A constant pointer to the first byte of the second object.
     * @param sz The size of an object in bytes.
     * @pre The pointers are non-null and the size is non-zero.
     */
    void swap(void* const p1, void* const p2, size_t const sz);
#endif
