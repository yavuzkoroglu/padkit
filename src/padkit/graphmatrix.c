/**
 * @file graphmatrix.c
 * @brief Implements GraphMatrix functions.
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/bliterals.h"
#include "padkit/debug.h"
#include "padkit/graphmatrix.h"

#ifndef NDEBUG
bool
#else
void
#endif
connect_gmtx(GraphMatrix* const gmtx, uint32_t const source, uint32_t const sink) {
    #ifndef NDEBUG
        if (!isValid_gmtx(gmtx)) return 0;
    #endif

    uint32_t const new_height = (gmtx->height > source) ? gmtx->height : source;
    uint32_t const new_width  = (gmtx->width > sink) ? gmtx->width : sink;

    #ifndef NDEBUG
        if (!resizeIfNecessary_gmtx(gmtx, new_height, new_width)) return 0;
    #else
        resizeIfNecessary_gmtx(gmtx, new_height, new_width);
    #endif

    long const edge_id = (long)new_width * (long)source + (long)sink;
    ldiv_t const edge  = ldiv(edge_id, 64);

    gmtx->array[edge.quot] |= (B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000) >> edge.rem);

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
connectAll_gmtx(GraphMatrix* const gmtx) {
    static uint64_t const remainders[64] = {
        B8(B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 00 */
        B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 01 */
        B8(B_11000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 02 */
        B8(B_11100000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 03 */
        B8(B_11110000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 04 */
        B8(B_11111000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 05 */
        B8(B_11111100,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 06 */
        B8(B_11111110,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 07 */
        B8(B_11111111,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 08 */
        B8(B_11111111,B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 09 */
        B8(B_11111111,B_11000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 10 */
        B8(B_11111111,B_11100000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 11 */
        B8(B_11111111,B_11110000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 13 */
        B8(B_11111111,B_11111000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 14 */
        B8(B_11111111,B_11111100,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 15 */
        B8(B_11111111,B_11111110,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 16 */
        B8(B_11111111,B_11111111,B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 17 */
        B8(B_11111111,B_11111111,B_11000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 18 */
        B8(B_11111111,B_11111111,B_11100000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 19 */
        B8(B_11111111,B_11111111,B_11110000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 20 */
        B8(B_11111111,B_11111111,B_11111000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 21 */
        B8(B_11111111,B_11111111,B_11111100,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 22 */
        B8(B_11111111,B_11111111,B_11111110,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 23 */
        B8(B_11111111,B_11111111,B_11111111,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 24 */
        B8(B_11111111,B_11111111,B_11111111,B_10000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 25 */
        B8(B_11111111,B_11111111,B_11111111,B_11000000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 26 */
        B8(B_11111111,B_11111111,B_11111111,B_11100000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 27 */
        B8(B_11111111,B_11111111,B_11111111,B_11110000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 28 */
        B8(B_11111111,B_11111111,B_11111111,B_11111000,B_00000000,B_00000000,B_00000000,B_00000000),    /* 29 */
        B8(B_11111111,B_11111111,B_11111111,B_11111100,B_00000000,B_00000000,B_00000000,B_00000000),    /* 30 */
        B8(B_11111111,B_11111111,B_11111111,B_11111110,B_00000000,B_00000000,B_00000000,B_00000000),    /* 31 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_00000000,B_00000000,B_00000000,B_00000000),    /* 32 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_10000000,B_00000000,B_00000000,B_00000000),    /* 33 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11000000,B_00000000,B_00000000,B_00000000),    /* 34 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11100000,B_00000000,B_00000000,B_00000000),    /* 35 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11110000,B_00000000,B_00000000,B_00000000),    /* 36 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111000,B_00000000,B_00000000,B_00000000),    /* 37 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111100,B_00000000,B_00000000,B_00000000),    /* 38 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111110,B_00000000,B_00000000,B_00000000),    /* 39 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_00000000,B_00000000,B_00000000),    /* 40 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_10000000,B_00000000,B_00000000),    /* 41 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11000000,B_00000000,B_00000000),    /* 42 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11100000,B_00000000,B_00000000),    /* 43 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11110000,B_00000000,B_00000000),    /* 44 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111000,B_00000000,B_00000000),    /* 45 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111100,B_00000000,B_00000000),    /* 46 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111110,B_00000000,B_00000000),    /* 47 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_00000000,B_00000000),    /* 48 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_10000000,B_00000000),    /* 49 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11000000,B_00000000),    /* 50 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11100000,B_00000000),    /* 51 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11110000,B_00000000),    /* 52 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111000,B_00000000),    /* 53 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111100,B_00000000),    /* 54 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111110,B_00000000),    /* 55 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_00000000),    /* 56 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_10000000),    /* 57 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11000000),    /* 58 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11100000),    /* 59 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11110000),    /* 60 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111000),    /* 61 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111100),    /* 62 */
        B8(B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111111,B_11111110)     /* 63 */
    };

    #ifndef NDEBUG
        if (!isValid_gmtx(gmtx)) return 0;
    #endif

    uint64_t const size = (uint64_t)gmtx->height * (uint64_t)gmtx->width;
    uint64_t const nFullBlocks = size >> 6;
    memset(gmtx->array, B_11111111, nFullBlocks << 3);
    gmtx->array[nFullBlocks] = remainders[size & B_111111];

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
construct_gmtx(GraphMatrix* gmtx, uint32_t const initial_height, uint32_t const initial_width) {
    #ifndef NDEBUG
        if (gmtx == NULL)                   return 0;
        if (initial_height == 0)            return 0;
        if (initial_height == 0xFFFFFFFF)   return 0;
        if (initial_width == 0)             return 0;
        if (initial_width == 0xFFFFFFFF)    return 0;
    #endif

    uint64_t const size = (((uint64_t)initial_height * (uint64_t)initial_width) >> 6) + 1;
    #ifndef NDEBUG
        if (size == 0) return 0;
    #endif

    *gmtx = (GraphMatrix){ initial_height, initial_width, calloc(size, sizeof(uint64_t)) };
    #ifndef NDEBUG
        if (gmtx->array == NULL) return 0;
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
disconnect_gmtx(GraphMatrix* const gmtx, uint32_t const source, uint32_t const sink) {
    #ifndef NDEBUG
        if (!isValid_gmtx(gmtx)) return 0;
    #endif

    uint32_t const new_height = (gmtx->height > source) ? gmtx->height : source;
    uint32_t const new_width  = (gmtx->width > sink) ? gmtx->width : sink;

    #ifndef NDEBUG
        if (!resizeIfNecessary_gmtx(gmtx, new_height, new_width)) return 0;
    #else
        resizeIfNecessary_gmtx(gmtx, new_height, new_width);
    #endif

    long const edge_id = (long)new_width * (long)source + (long)sink;
    ldiv_t const edge  = ldiv(edge_id, 64);

    gmtx->array[edge.quot] &= ~(B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000) >> edge.rem);

    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
disconnectAll_gmtx(GraphMatrix* const gmtx) {
    #ifndef NDEBUG
        if (!isValid_gmtx(gmtx)) return 0;
    #endif

    uint64_t const size = (uint64_t)gmtx->height * (uint64_t)gmtx->width;
    uint64_t const nFullBlocks = size >> 6;
    memset(gmtx->array, B_00000000, (nFullBlocks + !!(size & B_111111)) << 3);

    #ifndef NDEBUG
        return 1;
    #endif
}

uint32_t findSink_gmtx(
    GraphMatrix const* const gmtx, uint32_t const source,
    uint32_t const highest_possible_sink
) {
    #ifndef NDEBUG
        if (!isValid_gmtx(gmtx)) return 0xFFFFFFFF;
    #endif

    uint32_t sink = highest_possible_sink;

    #ifndef NDEBUG
        if (source >= gmtx->height) return 0xFFFFFFFF;
        if (sink >= gmtx->width)    return 0xFFFFFFFF;
    #endif

    while (sink != 0xFFFFFFFF && !isConnected_gmtx(gmtx, source, sink))
        sink--;

    return sink;
}

uint32_t findSource_gmtx(
    GraphMatrix const* const gmtx, uint32_t const sink,
    uint32_t const highest_possible_source
) {
    #ifndef NDEBUG
        if (!isValid_gmtx(gmtx)) return 0xFFFFFFFF;
    #endif

    uint32_t source = highest_possible_source;

    #ifndef NDEBUG
        if (source >= gmtx->height) return 0xFFFFFFFF;
        if (sink >= gmtx->width)    return 0xFFFFFFFF;
    #endif

    while (source != 0xFFFFFFFF && !isConnected_gmtx(gmtx, source, sink))
        source--;

    return source;
}

#ifndef NDEBUG
bool
#else
void
#endif
free_gmtx(GraphMatrix* const gmtx) {
    free(gmtx->array);
    *gmtx = NOT_A_GRAPH_MATRIX;
    #ifndef NDEBUG
        return 1;
    #endif
}

bool isConnected_gmtx(
    GraphMatrix const* const gmtx, uint32_t const source, uint32_t const sink
) {
    DEBUG_ASSERT(isValid_gmtx(gmtx))
    long const edge_id = (long)gmtx->width * (long)source + (long)sink;
    ldiv_t const edge = ldiv(edge_id, 64);

    return (gmtx->array[edge.quot] & (B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000) >> edge.rem));
}

bool isValid_gmtx(GraphMatrix const* const gmtx) {
    return gmtx != NULL         &&
           gmtx->height != 0    &&
           gmtx->width != 0     &&
           gmtx->array != NULL;
}

#ifndef NDEBUG
bool
#else
void
#endif
resizeIfNecessary_gmtx(
    GraphMatrix* const gmtx, uint32_t const new_height, uint32_t const new_width
) {
    #ifndef NDEBUG
        if (!isValid_gmtx(gmtx))       return 0;
        if (new_height < gmtx->height) return 0;
        if (new_width < gmtx->width)   return 0;
    #endif

    if (new_height == gmtx->height && new_width == gmtx->width)
        #ifndef NDEBUG
            return 1;
        #else
            return;
        #endif

    GraphMatrix new_gmtx[1];
    #ifndef NDEBUG
        if (!construct_gmtx(new_gmtx, new_height, new_width)) return 0;
    #else
        construct_gmtx(new_gmtx, new_height, new_width);
    #endif

    /* Remake all the previous connections. */
    for (uint32_t source = 0; source < gmtx->height; source++) {
        for (uint32_t sink = 0; sink < gmtx->width; sink++) {
            if (isConnected_gmtx(gmtx, source, sink)) {
                #ifndef NDEBUG
                    if (!connect_gmtx(new_gmtx, source, sink)) return 0;
                #else
                    connect_gmtx(new_gmtx, source, sink);
                #endif
            }
        }
    }

    /* Replace the old GraphMatrix. */
    #ifndef NDEBUG
        if (!free_gmtx(gmtx)) return 0;
    #else
        free_gmtx(gmtx);
    #endif
    *gmtx = *new_gmtx;

    #ifndef NDEBUG
        return 1;
    #endif
}
