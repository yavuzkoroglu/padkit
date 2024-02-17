/**
 * @file graphmatrix.h
 * @brief Defines GraphMatrix.
 * @author Yavuz Koroglu
 */
#ifndef GRAPHMATRIX_H
    #define GRAPHMATRIX_H
    #include <stdbool.h>
    #include <stdint.h>

    /**
     * @def NOT_A_GRAPH_MATRIX
     *   A special GraphMatrix denoting a NOT-GraphMatrix. This GraphMatrix cannot pass the isValid_gmtx() test.
     */
    #define NOT_A_GRAPH_MATRIX ((GraphMatrix){ 0, 0, NULL })

    /**
     * @struct GraphMatrix
     * @brief Matrix representation of a directed graph.
     *
     * @var GraphMatrix::height
     *   Height of the matrix.
     * @var GraphMatrix::width
     *   Width of the matrix.
     * @var GraphMatrix::array
     *   The array representation of the matrix.
     */
    typedef struct GraphMatrixBody {
        uint32_t    height;
        uint32_t    width;
        uint64_t*   array;
    } GraphMatrix;

    /**
     * @brief Connects a source to a sink in a GraphMatrix.
     * @param gmtx The GraphMatrix.
     * @param source The source.
     * @param sink The sink.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    connect_gmtx(GraphMatrix* const gmtx, uint32_t const source, uint32_t const sink);

    /**
     * @brief Make every possible connection in a GraphMatrix.
     * @param gmtx The GraphMatrix.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    connectAll_gmtx(GraphMatrix* const gmtx);

    /**
     * @brief Constructs a fully disconnected GraphMatrix.
     * @param gmtx A pointer to the GraphMatrix.
     * @param initial_height The initial height of the GraphMatrix.
     * @param initial_width The initial width of the GraphMatrix.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    construct_gmtx(GraphMatrix* gmtx, uint32_t const initial_height, uint32_t const initial_width);

    /**
     * @brief Disconnects source->sink in a GraphMatrix.
     * @param gmtx The GraphMatrix.
     * @param source The source.
     * @param sink The sink.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    disconnect_gmtx(GraphMatrix* const gmtx, uint32_t const source, uint32_t const sink);

    /**
     * @brief Disconnects everything in a GraphMatrix.
     * @param gmtx The GraphMatrix.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    disconnectAll_gmtx(GraphMatrix* const gmtx);

    /**
     * @brief Finds an outgoing edge.
     * @param gmtx The GraphMatrix.
     * @param source The source.
     * @param highest_possible_sink Sinks higher than this do NOT count.
     */
    uint32_t findSink_gmtx(
        GraphMatrix const* const gmtx, uint32_t const source,
        uint32_t const highest_possible_sink
    );

    /**
     * @brief Finds an incoming edge.
     * @param gmtx The GraphMatrix.
     * @param sink The sink.
     * @param highest_possible_source Sources higher than this do NOT count.
     */
    uint32_t findSource_gmtx(
        GraphMatrix const* const gmtx, uint32_t const sink,
        uint32_t const highest_possible_source
    );

    /**
     * @brief Frees the GraphMatrix.
     * @param gmtx The GraphMatrix.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    free_gmtx(GraphMatrix* const gmtx);

    /**
     * @brief Checks if a source is connected to a sink in a GraphMatrix.
     * @param gmtx The GraphMatrix.
     * @param source The source.
     * @param sink The sink.
     */
    bool isConnected_gmtx(GraphMatrix const* const gmtx, uint32_t const source, uint32_t const sink);

    /**
     * @brief Checks if a GraphMatrix is valid.
     * @param gmtx The GraphMatrix.
     */
    bool isValid_gmtx(GraphMatrix const* const gmtx);

    /**
     * @brief Resizes a GraphMatrix if necessary.
     * @param gmtx The GraphMatrix.
     * @param new_height The new height of the GraphMatrix.
     * @param new_width The new width of the GraphMatrix.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    resizeIfNecessary_gmtx(GraphMatrix* const gmtx, uint32_t const new_height, uint32_t const new_width);
#endif
