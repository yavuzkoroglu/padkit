#include <assert.h>
#include <string.h>
#include "padkit/bitmatrix.h"
#include "padkit/bliterals.h"
#include "padkit/invalid.h"
#include "padkit/memalloc.h"
#include "padkit/size.h"

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

void connect_gmtx(GraphMatrix gmtx[static const 1], uint32_t const source, uint32_t const sink) {
    uint32_t const new_height   = (gmtx->height > source) ? gmtx->height : source + 1;
    uint32_t const new_width    = (gmtx->width > sink) ? gmtx->width : sink + 1;
    uint64_t const edge_id      = (uint64_t)new_width * (uint64_t)source + (uint64_t)sink;

    assert(isValid_gmtx(gmtx));
    assert(source < SZ32_MAX);
    assert(sink < SZ32_MAX);

    resizeIfNecessary_gmtx(gmtx, new_height, new_width);

    gmtx->array[edge_id >> 6] |= (
        B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000) >>
        (edge_id % B_1000000)
    );
}

void connectAll_gmtx(GraphMatrix gmtx[static const 1]) {
    uint64_t const size         = (uint64_t)gmtx->height * (uint64_t)gmtx->width;
    uint64_t const nFullBlocks  = size >> 6;

    assert(isValid_gmtx(gmtx));

    memset(gmtx->array, B_11111111, nFullBlocks << 3);
    gmtx->array[nFullBlocks] = remainders[size % B_1000000];
}

void construct_bmtx(
    BitMatrix bmtx[static const 1],
    uint32_t const initial_height, uint32_t const initial_width
) {
    uint64_t const size = (((uint64_t)initial_height * (uint64_t)initial_width) >> 6) + 1;

    assert(initial_height > 0);
    assert(initial_height < SZ32_MAX);
    assert(initial_width > 0);
    assert(initial_width < SZ32_MAX);
    assert(size < SZ64_MAX);

    bmtx[0] = (GraphMatrix){ initial_height, initial_width, mem_calloc((size_t)size, sizeof(uint64_t)) };
}

void construct_gmtx(
    GraphMatrix gmtx[static const 1],
    uint32_t const initial_height, uint32_t const initial_width
) {
    uint64_t const size = (((uint64_t)initial_height * (uint64_t)initial_width) >> 6) + 1;

    assert(initial_height > 0);
    assert(initial_height < SZ32_MAX);
    assert(initial_width > 0);
    assert(initial_width < SZ32_MAX);
    assert(size < SZ64_MAX);

    gmtx[0] = (GraphMatrix){ initial_height, initial_width, mem_calloc((size_t)size, sizeof(uint64_t)) };
}

void disconnect_gmtx(GraphMatrix gmtx[static const 1], uint32_t const source, uint32_t const sink) {
    uint32_t const new_height   = (gmtx->height > source) ? gmtx->height : source + 1;
    uint32_t const new_width    = (gmtx->width > sink) ? gmtx->width : sink + 1;
    uint64_t const edge_id      = (uint64_t)new_width * (uint64_t)source + (uint64_t)sink;

    assert(isValid_gmtx(gmtx));
    assert(source < SZ32_MAX);
    assert(sink < SZ32_MAX);

    resizeIfNecessary_gmtx(gmtx, new_height, new_width);

    gmtx->array[edge_id >> 6] &= ~(
        B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000) >>
        (edge_id % B_1000000)
    );
}

void disconnectAll_gmtx(GraphMatrix gmtx[static const 1]) {
    uint64_t const size = (uint64_t)gmtx->height * (uint64_t)gmtx->width;
    uint64_t const nFullBlocks = size >> 6;

    assert(isValid_gmtx(gmtx));

    memset(gmtx->array, B_00000000, (nFullBlocks + !!(size % B_1000000)) << 3);
}

uint32_t findInCol_bmtx(
    BitMatrix bmtx[static const 1], uint32_t const col,
    uint32_t const highest_possible_row, bool const value
) {
    uint32_t row = highest_possible_row;

    assert(isValid_bmtx(bmtx));
    assert(row < bmtx->height);
    assert(col < bmtx->width);

    while (row != UINT32_MAX && get_bmtx(bmtx, row, col) != value)
        row--;

    return row < bmtx->height ? row : INVALID_UINT32;
}

uint32_t findInRow_bmtx(
    BitMatrix bmtx[static const 1], uint32_t const row,
    uint32_t const highest_possible_col, bool const value
) {
    uint32_t col = highest_possible_col;

    assert(isValid_bmtx(bmtx));
    assert(row < bmtx->height);
    assert(col < bmtx->width);

    while (col != UINT32_MAX && get_bmtx(bmtx, row, col) != value)
        col--;

    return col;
}

uint32_t findSink_gmtx(
    GraphMatrix const gmtx[static const 1], uint32_t const source,
    uint32_t const highest_possible_sink
) {
    uint32_t sink = highest_possible_sink;

    assert(isValid_gmtx(gmtx));
    assert(source < gmtx->height);
    assert(sink < gmtx->width);

    while (sink != UINT32_MAX && !isConnected_gmtx(gmtx, source, sink))
        sink--;

    return sink;
}

uint32_t findSource_gmtx(
    GraphMatrix const gmtx[static const 1], uint32_t const sink,
    uint32_t const highest_possible_source
) {
    uint32_t source = highest_possible_source;

    assert(isValid_gmtx(gmtx));
    assert(source < gmtx->height);
    assert(sink < gmtx->width);

    while (source != UINT32_MAX && !isConnected_gmtx(gmtx, source, sink))
        source--;

    return source;
}

void free_bmtx(BitMatrix bmtx[static const 1]) {
    assert(isValid_bmtx(bmtx));
    free(bmtx->array);
    bmtx[0] = NOT_A_BIT_MATRIX;
}

void free_gmtx(GraphMatrix gmtx[static const 1]) {
    assert(isValid_gmtx(gmtx));
    free(gmtx->array);
    gmtx[0] = NOT_A_GRAPH_MATRIX;
}

bool get_bmtx(BitMatrix const bmtx[static const 1], uint32_t const row, uint32_t const col) {
    uint64_t const bit_id = (uint64_t)bmtx->width * (uint64_t)row + (uint64_t)col;

    assert(isValid_bmtx(bmtx));
    assert(row < bmtx->height);
    assert(col < bmtx->width);

    return (bmtx->array[bit_id >> 6] & (
        B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000) >>
        (bit_id % B_01000000))
    );
}

bool isConnected_gmtx(GraphMatrix const gmtx[static const 1], uint32_t const source, uint32_t const sink) {
    uint64_t const edge_id = (uint64_t)gmtx->width * (uint64_t)source + (uint64_t)sink;

    assert(isValid_gmtx(gmtx));
    assert(source < gmtx->height);
    assert(sink < gmtx->width);

    return (gmtx->array[edge_id >> 6] & (
        B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000) >>
        (edge_id % B_01000000))
    );
}

bool isValid_bmtx(BitMatrix const bmtx[static const 1]) {
    if (bmtx->height == 0)          return 0;
    if (bmtx->height >= SZ32_MAX)   return 0;
    if (bmtx->width == 0)           return 0;
    if (bmtx->width >= SZ32_MAX)    return 0;
    if (bmtx->array == NULL)        return 0;

    return 1;
}

bool isValid_gmtx(GraphMatrix const gmtx[static const 1]) {
    if (gmtx->height == 0)          return 0;
    if (gmtx->height >= SZ32_MAX)   return 0;
    if (gmtx->width == 0)           return 0;
    if (gmtx->width >= SZ32_MAX)    return 0;
    if (gmtx->array == NULL)        return 0;

    return 1;
}

void resizeIfNecessary_bmtx(
    BitMatrix bmtx[static const 1],
    uint32_t const new_height, uint32_t const new_width
) {
    BitMatrix new_bmtx[1] = { NOT_A_BIT_MATRIX };

    assert(isValid_bmtx(bmtx));
    assert(new_height >= bmtx->height);
    assert(new_width >= bmtx->width);

    if (new_height == bmtx->height && new_width == bmtx->width)
        return;

    construct_bmtx(new_bmtx, new_height, new_width);

    /* Remake all the previous connections. */
    for (uint32_t row = 0; row < bmtx->height; row++)
        for (uint32_t col = 0; col < bmtx->width; col++)
            if (get_bmtx(bmtx, row, col) == 1)
                set_bmtx(new_bmtx, row, col);

    /* Replace the old BitMatrix. */
    free_bmtx(bmtx);
    bmtx[0] = new_bmtx[0];
}

void resizeIfNecessary_gmtx(
    GraphMatrix gmtx[static const 1],
    uint32_t const new_height, uint32_t const new_width
) {
    GraphMatrix new_gmtx[1] = { NOT_A_GRAPH_MATRIX };

    assert(isValid_gmtx(gmtx));
    assert(new_height >= gmtx->height);
    assert(new_width >= gmtx->width);

    if (new_height == gmtx->height && new_width == gmtx->width)
        return;

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

void set_bmtx(BitMatrix bmtx[static const 1], uint32_t const row, uint32_t const col) {
    uint32_t const new_height   = (bmtx->height > row) ? bmtx->height : row + 1;
    uint32_t const new_width    = (bmtx->width > col) ? bmtx->width : col + 1;
    uint64_t const bit_id       = (uint64_t)new_width * (uint64_t)row + (uint64_t)col;

    assert(isValid_bmtx(bmtx));
    assert(row < SZ32_MAX);
    assert(col < SZ32_MAX);

    resizeIfNecessary_bmtx(bmtx, new_height, new_width);

    bmtx->array[bit_id >> 6] |= (
        B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000) >>
        (bit_id % B_1000000)
    );
}

void setAll_bmtx(BitMatrix bmtx[static const 1]) {
    uint64_t const size         = (uint64_t)bmtx->height * (uint64_t)bmtx->width;
    uint64_t const nFullBlocks  = size >> 6;

    assert(isValid_bmtx(bmtx));

    memset(bmtx->array, B_11111111, nFullBlocks << 3);
    bmtx->array[nFullBlocks] = remainders[size % B_1000000];
}

void unset_bmtx(BitMatrix bmtx[static const 1], uint32_t const row, uint32_t const col) {
    uint32_t const new_height   = (bmtx->height > row) ? bmtx->height : row + 1;
    uint32_t const new_width    = (bmtx->width > col) ? bmtx->width : col + 1;
    uint64_t const bit_id       = (uint64_t)new_width * (uint64_t)row + (uint64_t)col;

    assert(isValid_bmtx(bmtx));
    assert(row < SZ32_MAX);
    assert(col < SZ32_MAX);

    resizeIfNecessary_bmtx(bmtx, new_height, new_width);

    bmtx->array[bit_id >> 6] &= ~(
        B8(B_10000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000,B_00000000) >>
        (bit_id % B_1000000)
    );
}

void unsetAll_bmtx(BitMatrix bmtx[static const 1]) {
    uint64_t const size = (uint64_t)bmtx->height * (uint64_t)bmtx->width;
    uint64_t const nFullBlocks = size >> 6;

    assert(isValid_bmtx(bmtx));

    memset(bmtx->array, B_00000000, (nFullBlocks + !!(size % B_1000000)) << 3);
}
