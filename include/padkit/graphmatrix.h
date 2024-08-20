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
     *
     * @param[in,out]   gmtx A constant non-null pointer to at least one GraphMatrix.
     * @param[in]     source A constant 32-bit unsigned integer.
     * @param[in]       sink A constant 32-bit unsigned integer.
     */
    void connect_gmtx(GraphMatrix gmtx[static const 1], uint32_t const source, uint32_t const sink);

    /**
     * @brief Make every possible connection in a GraphMatrix.
     *
     * @param[in,out]   gmtx A constant non-null pointer to at least one GraphMatrix.
     */
    void connectAll_gmtx(GraphMatrix gmtx[static const 1]);

    /**
     * @brief Constructs a fully disconnected GraphMatrix.
     *
     * @param[in,out]           gmtx A constant non-null pointer to at least one GraphMatrix.
     * @param[in]     initial_height A constant 32-bit unsigned integer.
     * @param[in]      initial_width A constant 32-bit unsigned integer.
     */
    void construct_gmtx(
        GraphMatrix gmtx[static const 1],
        uint32_t const initial_height, uint32_t const initial_width
    );

    /**
     * @brief Disconnects source->sink in a GraphMatrix.
     *
     * @param[in,out]   gmtx A constant non-null pointer to at least one GraphMatrix.
     * @param[in]     source A constant 32-bit unsigned integer.
     * @param[in]       sink A constant 32-bit unsigned integer.
     */
    void disconnect_gmtx(GraphMatrix gmtx[static const 1], uint32_t const source, uint32_t const sink);

    /**
     * @brief Disconnects everything in a GraphMatrix.
     *
     * @param[in,out] gmtx A constant non-null pointer to at least one GraphMatrix.
     */
    void disconnectAll_gmtx(GraphMatrix gmtx[static const 1]);

    /**
     * @brief Finds an outgoing edge.
     *
     * @param[in,out]                  gmtx A constant non-null pointer to at least one GraphMatrix.
     * @param[in]                    source A constant 32-bit unsigned integer.
     * @param[in]     highest_possible_sink A constant 32-bit unsigned integer.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t findSink_gmtx(
        GraphMatrix const gmtx[static const 1], uint32_t const source,
        uint32_t const highest_possible_sink
    );

    /**
     * @brief Finds an incoming edge.
     *
     * @param[in,out]                    gmtx A constant non-null pointer to at least one GraphMatrix.
     * @param[in]                        sink A constant 32-bit unsigned integer.
     * @param[in]     highest_possible_source A constant 32-bit unsigned integer.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t findSource_gmtx(
        GraphMatrix const gmtx[static const 1], uint32_t const sink,
        uint32_t const highest_possible_source
    );

    /**
     * @brief Frees the GraphMatrix.
     *
     * @param[in,out] gmtx A constant non-null pointer to at least one GraphMatrix.
     */
    void free_gmtx(GraphMatrix gmtx[static const 1]);

    /**
     * @brief Checks if a source is connected to a sink in a GraphMatrix.
     *
     * @param[in,out]   gmtx A constant non-null pointer to at least one constant GraphMatrix.
     * @param[in]     source A constant 32-bit unsigned integer.
     * @param[in]       sink A constant 32-bit unsigned integer.
     *
     * @return A Boolean value.
     */
    bool isConnected_gmtx(GraphMatrix const gmtx[static const 1], uint32_t const source, uint32_t const sink);

    /**
     * @brief Checks if a GraphMatrix is valid.
     *
     * @param[in,out] gmtx A constant non-null pointer to at least one constant GraphMatrix.
     *
     * @return A Boolean value.
     */
    bool isValid_gmtx(GraphMatrix const gmtx[static const 1]);

    /**
     * @brief Resizes a GraphMatrix if necessary.
     *
     * @param[in,out]       gmtx A constant non-null pointer to at least one GraphMatrix.
     * @param[in]     new_height A constant 32-bit unsigned integer.
     * @param[in]      new_width A constant 32-bit unsigned integer.
     */
    void resizeIfNecessary_gmtx(
        GraphMatrix gmtx[static const 1],
        uint32_t const new_height, uint32_t const new_width
    );
#endif
