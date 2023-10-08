#include <string.h>
#include "util/bliterals.h"
#include "util/debug.h"
#include "util/graphmatrix.h"

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
    ldiv_t const edge  = ldiv(edge_id, 8);

    gmtx->array[edge.quot] |= ((uint8_t)B_10000000 >> edge.rem);

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
    #ifndef NDEBUG
        if (!isValid_gmtx(gmtx)) return 0;
    #endif

    uint64_t const size = (uint64_t)gmtx->height * (uint64_t)gmtx->width;
    uint64_t const nFullChars = size >> 3;
    memset(gmtx->array, B_11111111, nFullChars);

    switch (size & B_111) {
        case B_001: gmtx->array[nFullChars] = (uint8_t)B_10000000; break;
        case B_010: gmtx->array[nFullChars] = (uint8_t)B_11000000; break;
        case B_011: gmtx->array[nFullChars] = (uint8_t)B_11100000; break;
        case B_100: gmtx->array[nFullChars] = (uint8_t)B_11110000; break;
        case B_101: gmtx->array[nFullChars] = (uint8_t)B_11111000; break;
        case B_110: gmtx->array[nFullChars] = (uint8_t)B_11111100; break;
        case B_111: gmtx->array[nFullChars] = (uint8_t)B_11111110;
    }

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
        if (gmtx == NULL) return 0;
    #endif

    uint64_t const size = (((uint64_t)initial_height * (uint64_t)initial_width) >> 3) + 1;
    #ifndef NDEBUG
        if (size == 0) return 0;
    #endif

    *gmtx = (GraphMatrix){ initial_height, initial_width, calloc(size, sizeof(uint8_t)) };
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
    ldiv_t const edge  = ldiv(edge_id, 8);

    gmtx->array[edge.quot] &= ~((uint8_t)B_10000000 >> edge.rem);

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
    uint64_t const nFullChars = size >> 3;
    memset(gmtx->array, B_00000000, nFullChars + !!(size & B_111));

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
    #ifndef NDEBUG
        return 1;
    #endif
}

bool isConnected_gmtx(
    GraphMatrix const* const gmtx, uint32_t const source, uint32_t const sink
) {
    DEBUG_ASSERT(isValid_gmtx(gmtx))
    long const edge_id = (long)gmtx->width * (long)source + (long)sink;
    ldiv_t const edge = ldiv(edge_id, 8);

    return (gmtx->array[edge.quot] & ((uint8_t)B_10000000 >> edge.rem));
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
    for (uint32_t source = 0; source < gmtx->height - 1; source++) {
        for (uint32_t sink = 0; sink < gmtx->width - 1; sink++) {
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
    free_gmtx(gmtx);
    *gmtx = *new_gmtx;

    #ifndef NDEBUG
        return 1;
    #endif
}
