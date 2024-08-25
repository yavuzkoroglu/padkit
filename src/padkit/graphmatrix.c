/**
 * @file graphmatrix.c
 * @brief Implements GraphMatrix functions.
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit/bliterals.h"
#include "padkit/debug.h"
#include "padkit/graphmatrix.h"
#include "padkit/memalloc.h"

void connect_gmtx(GraphMatrix gmtx[static const 1], uint32_t const source, uint32_t const sink) {
    DEBUG_ASSERT(isValid_gmtx(gmtx))
    DEBUG_ASSERT(source < INT32_MAX)
    DEBUG_ASSERT(sink < INT32_MAX)
    {
        uint32_t const new_height = (gmtx->height > source) ? gmtx->height : source;
        uint32_t const new_width  = (gmtx->width > sink) ? gmtx->width : sink;

        resizeIfNecessary_gmtx(gmtx, new_height, new_width);

        {
            uint64_t const edge_id = (uint64_t)new_width * (uint64_t)source + (uint64_t)sink;
            gmtx->array[edge_id >> 6] |= (
                B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000) >>
                (edge_id % B_01000000)
            );
        }
    }
}

void connectAll_gmtx(GraphMatrix gmtx[static const 1]) {
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

    DEBUG_ASSERT(isValid_gmtx(gmtx))

    {
        uint64_t const size = (uint64_t)gmtx->height * (uint64_t)gmtx->width;
        uint64_t const nFullBlocks = size >> 6;
        memset(gmtx->array, B_11111111, nFullBlocks << 3);
        gmtx->array[nFullBlocks] = remainders[size & B_111111];
    }
}

void construct_gmtx(
    GraphMatrix gmtx[static const 1],
    uint32_t const initial_height, uint32_t const initial_width
) {
    DEBUG_ASSERT(initial_height > 0)
    DEBUG_ASSERT(initial_height < INT32_MAX)
    DEBUG_ASSERT(initial_width > 0)
    DEBUG_ASSERT(initial_width < INT32_MAX)
    {
        uint64_t const size = (((uint64_t)initial_height * (uint64_t)initial_width) >> 6) + 1;
        *gmtx = (GraphMatrix){ initial_height, initial_width, mem_calloc((size_t)size, sizeof(uint64_t)) };
    }
}

void disconnect_gmtx(GraphMatrix gmtx[static const 1], uint32_t const source, uint32_t const sink) {
    DEBUG_ASSERT(isValid_gmtx(gmtx))
    DEBUG_ASSERT(source < INT32_MAX)
    DEBUG_ASSERT(sink < INT32_MAX)
    {
        uint32_t const new_height = (gmtx->height > source) ? gmtx->height : source;
        uint32_t const new_width  = (gmtx->width > sink) ? gmtx->width : sink;

        resizeIfNecessary_gmtx(gmtx, new_height, new_width);

        {
            uint64_t const edge_id = (uint64_t)new_width * (uint64_t)source + (uint64_t)sink;
            gmtx->array[edge_id >> 6] &= ~(
                B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000) >>
                (edge_id % B_01000000)
            );
        }
    }
}

void disconnectAll_gmtx(GraphMatrix gmtx[static const 1]) {
    DEBUG_ASSERT(isValid_gmtx(gmtx))
    {
        uint64_t const size = (uint64_t)gmtx->height * (uint64_t)gmtx->width;
        uint64_t const nFullBlocks = size >> 6;
        memset(gmtx->array, B_00000000, (nFullBlocks + !!(size & B_111111)) << 3);
    }
}

uint32_t findSink_gmtx(
    GraphMatrix const gmtx[static const 1], uint32_t const source,
    uint32_t const highest_possible_sink
) {
    DEBUG_ASSERT(isValid_gmtx(gmtx))
    {
        uint32_t sink = highest_possible_sink;

        DEBUG_ASSERT(source < gmtx->height)
        DEBUG_ASSERT(sink < gmtx->width)

        while (sink != UINT32_MAX && !isConnected_gmtx(gmtx, source, sink))
            sink--;

        return sink;
    }
}

uint32_t findSource_gmtx(
    GraphMatrix const gmtx[static const 1], uint32_t const sink,
    uint32_t const highest_possible_source
) {
    DEBUG_ASSERT(isValid_gmtx(gmtx))
    {
        uint32_t source = highest_possible_source;

        DEBUG_ASSERT(source < gmtx->height)
        DEBUG_ASSERT(sink < gmtx->width)

        while (source != UINT32_MAX && !isConnected_gmtx(gmtx, source, sink))
            source--;

        return source;
    }
}

void free_gmtx(GraphMatrix gmtx[static const 1]) {
    DEBUG_ABORT_UNLESS(isValid_gmtx(gmtx))

    free(gmtx->array);
    gmtx[0] = NOT_A_GRAPH_MATRIX;
}

bool isConnected_gmtx(
    GraphMatrix const gmtx[static const 1], uint32_t const source, uint32_t const sink
) {
    DEBUG_ASSERT(isValid_gmtx(gmtx))
    DEBUG_ASSERT(source < gmtx->height)
    DEBUG_ASSERT(sink < gmtx->width)
    {
        uint64_t const edge_id = (uint64_t)gmtx->width * (uint64_t)source + (uint64_t)sink;
        return (gmtx->array[edge_id >> 6] & (
            B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000) >>
            (edge_id % B_01000000))
        );
    }
}

bool isValid_gmtx(GraphMatrix const gmtx[static const 1]) {
    return gmtx->height != 0    &&
           gmtx->width != 0     &&
           gmtx->array != NULL;
}

void resizeIfNecessary_gmtx(
    GraphMatrix gmtx[static const 1],
    uint32_t const new_height, uint32_t const new_width
) {
    DEBUG_ASSERT(isValid_gmtx(gmtx))
    DEBUG_ERROR_IF(new_height < gmtx->height)
    DEBUG_ERROR_IF(new_width < gmtx->width)

    if (new_height == gmtx->height && new_width == gmtx->width)
        return;

    {
        GraphMatrix new_gmtx[1] = { NOT_A_GRAPH_MATRIX };
        construct_gmtx(new_gmtx, new_height, new_width);

        /* Remake all the previous connections. */
        for (uint32_t source = 0; source < gmtx->height; source++)
            for (uint32_t sink = 0; sink < gmtx->width; sink++)
                if (isConnected_gmtx(gmtx, source, sink))
                    connect_gmtx(new_gmtx, source, sink);

        /* Replace the old GraphMatrix. */
        free_gmtx(gmtx);
        gmtx[0] = new_gmtx[0];
    }
}
