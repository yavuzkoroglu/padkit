/**
 * @file overlap.h
 * @brief Defines a check for overlapping pointers.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_OVERLAP_H
    #define PADKIT_OVERLAP_H
    #include <stdbool.h>
    #include <stddef.h>

    /**
     * @brief Checks if two pointers overlap.
     *
     * => A null pointer overlaps with only another null pointer.
     * => A pointer that points to a zero-byte object cannot overlap with anything.
     *
     * @param[in]  p0 A constant pointer to a constant object.
     * @param[in] sz0 A constant size.
     * @param[in] p1 A constant pointer to a constant object.
     * @param[in] sz1 A constant size.
     *
     * @return A Boolean value.
     */
    bool overlaps_ptr(void const* const p0, void const* const p1, size_t const sz0, size_t const sz1);
#endif
