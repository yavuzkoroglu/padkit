/**
 * @file overlap.h
 * @brief A function for checking memory area overlaps.
 * @author Yavuz KÖROĞLU
 * @see \c Item
 *
 * There is no standard way to check if two pointers overlap.
 * To make things worse, unless they belong the same memory area, comparison operators such as < and > are unreliable.
 * The only way to compare two arbitrary non-null pointers is to compare these pointers byte by byte.
 */
#ifndef PADKIT_MISC_OVERLAP_H
    #define PADKIT_MISC_OVERLAP_H
    #include <stdbool.h>
    #include <stddef.h>

    /**
     * @brief Checks if an \c Item overlaps with another.
     * @param p0 A constant pointer to the first constant \c Item's first byte.
     * @param p1 A constant pointer to the second constant \c Item's first byte.
     * @param sz0 Size of the first \c Item in bytes.
     * @param sz1 Size of the second \c Item in bytes.
     * @returns <tt>1</tt> if the pointers overlap and <tt>0</tt> otherwise.
     * @warning This is a computationally expensive task.
     * @important Use this in assertions in debug mode only.
     * @important A null pointer overlaps only with another null pointer.
     * @important A pointer that points to a zero-sized entity cannot overlap with anything.
     * @see \c Item
     */
    bool overlaps_ptr(
        void const* const p0,
        void const* const p1,
        size_t const sz0,
        size_t const sz1
    );
#endif
