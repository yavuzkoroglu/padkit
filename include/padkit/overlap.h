#ifndef PADKIT_OVERLAP_H
    #define PADKIT_OVERLAP_H
    #include <stdbool.h>
    #include <stddef.h>

    /* => A null pointer overlaps with only another null pointer.
     * => A pointer that points to a zero-byte object cannot overlap with anything. */
    bool overlaps_ptr(void const* const p0, void const* const p1, size_t const sz0, size_t const sz1);
#endif
