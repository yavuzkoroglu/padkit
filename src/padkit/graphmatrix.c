/**
 * @file graphmatrix.c
 * @brief Implements GraphMatrix functions.
 * @author Yavuz Koroglu
 */
#include <string.h>
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
                0b10000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000u >>
                (edge_id % 0b01000000u)
            );
        }
    }
}

void connectAll_gmtx(GraphMatrix gmtx[static const 1]) {
    static uint64_t const remainders[64] = {
        0b00000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 00 */
        0b10000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 01 */
        0b11000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 02 */
        0b11100000'00000000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 03 */
        0b11110000'00000000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 04 */
        0b11111000'00000000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 05 */
        0b11111100'00000000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 06 */
        0b11111110'00000000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 07 */
        0b11111111'00000000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 08 */
        0b11111111'10000000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 09 */
        0b11111111'11000000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 10 */
        0b11111111'11100000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 11 */
        0b11111111'11110000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 12 */
        0b11111111'11111000'00000000'00000000'00000000'00000000'00000000'00000000u, /* 13 */
        0b11111111'11111100'00000000'00000000'00000000'00000000'00000000'00000000u, /* 14 */
        0b11111111'11111110'00000000'00000000'00000000'00000000'00000000'00000000u, /* 15 */
        0b11111111'11111111'00000000'00000000'00000000'00000000'00000000'00000000u, /* 16 */
        0b11111111'11111111'10000000'00000000'00000000'00000000'00000000'00000000u, /* 17 */
        0b11111111'11111111'11000000'00000000'00000000'00000000'00000000'00000000u, /* 18 */
        0b11111111'11111111'11100000'00000000'00000000'00000000'00000000'00000000u, /* 19 */
        0b11111111'11111111'11110000'00000000'00000000'00000000'00000000'00000000u, /* 20 */
        0b11111111'11111111'11111000'00000000'00000000'00000000'00000000'00000000u, /* 21 */
        0b11111111'11111111'11111100'00000000'00000000'00000000'00000000'00000000u, /* 22 */
        0b11111111'11111111'11111110'00000000'00000000'00000000'00000000'00000000u, /* 23 */
        0b11111111'11111111'11111111'00000000'00000000'00000000'00000000'00000000u, /* 24 */
        0b11111111'11111111'11111111'10000000'00000000'00000000'00000000'00000000u, /* 25 */
        0b11111111'11111111'11111111'11000000'00000000'00000000'00000000'00000000u, /* 26 */
        0b11111111'11111111'11111111'11100000'00000000'00000000'00000000'00000000u, /* 27 */
        0b11111111'11111111'11111111'11110000'00000000'00000000'00000000'00000000u, /* 28 */
        0b11111111'11111111'11111111'11111000'00000000'00000000'00000000'00000000u, /* 29 */
        0b11111111'11111111'11111111'11111100'00000000'00000000'00000000'00000000u, /* 30 */
        0b11111111'11111111'11111111'11111110'00000000'00000000'00000000'00000000u, /* 31 */
        0b11111111'11111111'11111111'11111111'00000000'00000000'00000000'00000000u, /* 32 */
        0b11111111'11111111'11111111'11111111'10000000'00000000'00000000'00000000u, /* 33 */
        0b11111111'11111111'11111111'11111111'11000000'00000000'00000000'00000000u, /* 34 */
        0b11111111'11111111'11111111'11111111'11100000'00000000'00000000'00000000u, /* 35 */
        0b11111111'11111111'11111111'11111111'11110000'00000000'00000000'00000000u, /* 36 */
        0b11111111'11111111'11111111'11111111'11111000'00000000'00000000'00000000u, /* 37 */
        0b11111111'11111111'11111111'11111111'11111100'00000000'00000000'00000000u, /* 38 */
        0b11111111'11111111'11111111'11111111'11111110'00000000'00000000'00000000u, /* 39 */
        0b11111111'11111111'11111111'11111111'11111111'00000000'00000000'00000000u, /* 40 */
        0b11111111'11111111'11111111'11111111'11111111'10000000'00000000'00000000u, /* 41 */
        0b11111111'11111111'11111111'11111111'11111111'11000000'00000000'00000000u, /* 42 */
        0b11111111'11111111'11111111'11111111'11111111'11100000'00000000'00000000u, /* 43 */
        0b11111111'11111111'11111111'11111111'11111111'11110000'00000000'00000000u, /* 44 */
        0b11111111'11111111'11111111'11111111'11111111'11111000'00000000'00000000u, /* 45 */
        0b11111111'11111111'11111111'11111111'11111111'11111100'00000000'00000000u, /* 46 */
        0b11111111'11111111'11111111'11111111'11111111'11111110'00000000'00000000u, /* 47 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'00000000'00000000u, /* 48 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'10000000'00000000u, /* 49 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11000000'00000000u, /* 50 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11100000'00000000u, /* 51 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11110000'00000000u, /* 52 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11111000'00000000u, /* 53 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11111100'00000000u, /* 54 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11111110'00000000u, /* 55 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11111111'00000000u, /* 56 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11111111'10000000u, /* 57 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11111111'11000000u, /* 58 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11111111'11100000u, /* 59 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11111111'11110000u, /* 60 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11111111'11111000u, /* 61 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11111111'11111100u, /* 62 */
        0b11111111'11111111'11111111'11111111'11111111'11111111'11111111'11111110u  /* 63 */
    };

    DEBUG_ASSERT(isValid_gmtx(gmtx))

    {
        uint64_t const size = (uint64_t)gmtx->height * (uint64_t)gmtx->width;
        uint64_t const nFullBlocks = size >> 6;
        memset(gmtx->array, 0b11111111u, nFullBlocks << 3);
        gmtx->array[nFullBlocks] = remainders[size & 0b111111u];
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
                0b10000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000u >>
                (edge_id % 0b01000000u)
            );
        }
    }
}

void disconnectAll_gmtx(GraphMatrix gmtx[static const 1]) {
    DEBUG_ASSERT(isValid_gmtx(gmtx))
    {
        uint64_t const size         = (uint64_t)gmtx->height * (uint64_t)gmtx->width;
        uint64_t const nFullBlocks  = size >> 6;
        memset(gmtx->array, 0b00000000u, (nFullBlocks + !!(size & 0b111111u)) << 3);
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
            0b10000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000u >> (edge_id % 0b01000000u)
        ));
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

