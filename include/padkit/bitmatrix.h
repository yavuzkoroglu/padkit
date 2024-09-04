#ifndef PADKIT_BITMATRIX_H
    #ifdef PADKIT_GRAPHMATRIX_H
        #error
    #endif
    #define PADKIT_BITMATRIX_H
    #define PADKIT_GRAPHMATRIX_H
    #include <stdbool.h>
    #include <stdint.h>

    #define NOT_A_BIT_MATRIX    ((BitMatrix){ 0, 0, NULL })

    #define NOT_A_GRAPH_MATRIX  ((GraphMatrix){ 0, 0, NULL })

    typedef struct BitMatrixBody {
        uint32_t    height;
        uint32_t    width;
        uint64_t*   array;
    } BitMatrix, GraphMatrix;

    void connect_gmtx(GraphMatrix gmtx[static const 1], uint32_t const source, uint32_t const sink);

    void connectAll_gmtx(GraphMatrix gmtx[static const 1]);

    void construct_bmtx(
        BitMatrix bmtx[static const 1],
        uint32_t const initial_height, uint32_t const initial_width
    );

    void construct_gmtx(
        GraphMatrix gmtx[static const 1],
        uint32_t const initial_height, uint32_t const initial_width
    );

    void disconnect_gmtx(GraphMatrix gmtx[static const 1], uint32_t const source, uint32_t const sink);

    void disconnectAll_gmtx(GraphMatrix gmtx[static const 1]);

    uint32_t findInCol_bmtx(
        BitMatrix bmtx[static const 1], uint32_t const col,
        uint32_t const highest_possible_row, bool const value
    );

    uint32_t findInRow_bmtx(
        BitMatrix bmtx[static const 1], uint32_t const row,
        uint32_t const highest_possible_col, bool const value
    );

    uint32_t findSink_gmtx(
        GraphMatrix const gmtx[static const 1], uint32_t const source,
        uint32_t const highest_possible_sink
    );

    uint32_t findSource_gmtx(
        GraphMatrix const gmtx[static const 1], uint32_t const sink,
        uint32_t const highest_possible_source
    );

    void free_bmtx(BitMatrix bmtx[static const 1]);

    void free_gmtx(GraphMatrix gmtx[static const 1]);

    bool get_bmtx(BitMatrix const bmtx[static const 1], uint32_t const row, uint32_t const col);

    bool isConnected_gmtx(GraphMatrix const gmtx[static const 1], uint32_t const source, uint32_t const sink);

    bool isValid_bmtx(BitMatrix const bmtx[static const 1]);

    bool isValid_gmtx(GraphMatrix const gmtx[static const 1]);

    void resizeIfNecessary_bmtx(
        BitMatrix bmtx[static const 1],
        uint32_t const new_height, uint32_t const new_width
    );

    void resizeIfNecessary_gmtx(
        GraphMatrix gmtx[static const 1],
        uint32_t const new_height, uint32_t const new_width
    );

    void set_bmtx(BitMatrix bmtx[static const 1], uint32_t const row, uint32_t const col);

    void setAll_bmtx(BitMatrix bmtx[static const 1]);

    void unset_bmtx(BitMatrix bmtx[static const 1], uint32_t const row, uint32_t const col);

    void unsetAll_bmtx(BitMatrix bmtx[static const 1]);
#endif
