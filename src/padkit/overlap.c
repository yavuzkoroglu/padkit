#include "padkit/overlap.h"

/**
 * The following implementation comes from the second snippet of the accepted answer @
 *   https://stackoverflow.com/questions/74946095/is-it-possible-in-c-not-invoking-ub-to-check-if-two-objects-overlap
 *
 * The comments on the accepted answer is moved to a separate chat. There, H.S. claims that this algorithm fails,
 * if p1 points to an array that contains the whole array p0 points to.
 *
 * H.S.'s claim is FALSE.
 *
 * Ex: Let
 *   p0 = 0x02, sz0 = 3
 *   p1 = 0x01, sz1 = 5.
 *
 * The first IF:
 *   (0x02 == 0x01) => FALSE
 *
 * The first WHILE loop:
 *   (0x04 == 0x01) => FALSE
 *   (0x03 == 0x01) => FALSE
 *
 * The second WHILE loop:
 *   (0x05 == 0x02) => FALSE
 *   (0x04 == 0x02) => FALSE
 *   (0x03 == 0x02) => FALSE
 *   (0x02 == 0x02) => TRUE, so return 1.
 *
 */
bool overlaps_ptr(void const* const p0, void const* const p1, size_t const sz0, size_t const sz1) {
    char const* const p[2] = { p0, p1 };

    if (p[0] == NULL)   return (p[1] == NULL);
    if (p[1] == NULL)   return 0;
    if (sz0 == 0)       return 0;
    if (sz1 == 0)       return 0;
    if (p[0] == p[1])   return 1;

    if (sz0 > 1) {
        char const* q = p[0] + sz0;
        while (--q > p[0])
            if (q == p[1])
                return 1;
    }

    if (sz1 > 1) {
        char const* q = p[1] + sz1;
        while (--q > p[1])
            if (q == p[0])
                return 1;
    }

    return 0;
}
