#ifndef PADKIT_BITMATRIX_H
    #ifdef PADKIT_GRAPHMATRIX_H
        #error
    #endif
    #define PADKIT_BITMATRIX_H
    #define PADKIT_GRAPHMATRIX_H
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stdint.h>

    #define NOT_A_BIT_MATRIX                                        ((BitMatrix){ 0, 0, NULL })

    #define NOT_A_GRAPH_MATRIX                                      NOT_A_BIT_MATRIX

    typedef struct BitMatrixBody {
        uint32_t    height;
        uint32_t    width;
        uint64_t*   array;
    } BitMatrix, GraphMatrix;

    extern void (* const connect_gmtx)(
        GraphMatrix* const gmtx,
        uint32_t const source,
        uint32_t const sink
    );

    extern void (* const connectAll_gmtx)(GraphMatrix* const gmtx);

    void construct_bmtx(void* const p_bmtx, ...);

    extern void (* const construct_gmtx)(void* const p_gmtx, ...);

    void destruct_bmtx(void* const p_bmtx);

    extern void (* const destruct_gmtx)(void* const p_gmtx);

    extern void (* const disconnect_gmtx)(
        GraphMatrix* const gmtx,
        uint32_t const source,
        uint32_t const sink
    );

    extern void (* const disconnectAll_gmtx)(GraphMatrix* const gmtx);

    uint32_t findInCol_bmtx(
        BitMatrix const* const bmtx,
        uint32_t const col,
        uint32_t const highest_possible_row,
        bool const value
    );

    uint32_t findInRow_bmtx(
        BitMatrix const* const bmtx,
        uint32_t const row,
        uint32_t const highest_possible_col,
        bool const value
    );

    #define findSink_gmtx(gmtx, source, highest_possible_sink)      \
        findInRow_bmtx(gmtx, source, highest_possible_sink, 1)

    #define findSource_gmtx(gmtx, source, highest_possible_source)  \
        findInCol_bmtx(gmtx, sink, highest_possible_source, 1)

    bool get_bmtx(
        BitMatrix const* const bmtx,
        uint32_t const row,
        uint32_t const col
    );

    bool isAllocated_bmtx(void const* const p_bmtx);

    extern bool (* const isAllocated_gmtx)(void const* const p_gmtx);

    extern bool (* const isConnected_gmtx)(
        GraphMatrix const* const gmtx,
        uint32_t const source,
        uint32_t const sink
    );

    bool isValid_bmtx(void const* const p_bmtx);

    extern bool (* const isValid_gmtx)(void const* const p_gmtx);

    void resizeIfNecessary_bmtx(
        BitMatrix* const bmtx,
        uint32_t const new_height,
        uint32_t const new_width
    );

    extern void (* const resizeIfNecessary_gmtx)(
        GraphMatrix* const gmtx,
        uint32_t const new_height,
        uint32_t const new_width
    );

    void set_bmtx(
        BitMatrix* const bmtx,
        uint32_t const row,
        uint32_t const col
    );

    void setAll_bmtx(BitMatrix* const bmtx);

    void unset_bmtx(
        BitMatrix* const bmtx,
        uint32_t const row,
        uint32_t const col
    );

    void unsetAll_bmtx(BitMatrix* const bmtx);

    void vconstruct_bmtx(
        void* const p_bmtx,
        va_list args
    );

    extern void (* const vconstruct_gmtx)(
        void* const p_gmtx,
        va_list args
    );
#endif
