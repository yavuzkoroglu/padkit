/**
 * @file map.h
 * @brief Defines Map.
 * @author Yavuz Koroglu
 * @see Value
 */
#ifndef MAP_H
    #define MAP_H
    #include "padkit/mapping.h"

    /**
     * @def NOT_A_MAP
     *   A special Map denoting a NOT-Map. This Map cannot pass the isValid_map() test.
     */
    #define NOT_A_MAP ((Map){ 0, 0, NULL })

    /**
     * @struct Map
     * @brief An index-value map.
     *
     * @var Map::size
     *   The number of mappings.
     * @var Map::cap
     *   The capacity.
     * @var Map::mappings
     *   The array of mappings.
     */
    typedef struct MapBody {
        uint32_t size;
        uint32_t cap;
        Mapping* mappings;
    } Map;

    /**
     * @brief Performs a binary search among the mappings to find a key index.
     *
     * @param[in]    map A constant non-null pointer to at least one constant Map.
     * @param[in] key_id A constant 32-bit unsigned integer.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t binarySearchLeftmostKey_map(Map const map[static const 1], uint32_t const key_id);

    /**
     * @brief Performs a binary search among the mappings to find a key index.
     *
     * @param[in]    map A constant non-null pointer to at least one constant Map.
     * @param[in] key_id A constant 32-bit unsigned integer.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t binarySearchRightmostKey_map(Map const map[static const 1], uint32_t const key_id);

    /**
     * @brief Constructs an empty Map.
     *
     * @param[in,out]         map A constant non-null pointer to at least one Map.
     * @param[in]     initial_cap A constant 32-bit unsigned integer.
     */
    void constructEmpty_map(Map map[static const 1], uint32_t const initial_cap);

    /**
     * @brief Deletes the last map entry.
     *
     * @param[in,out] map A constant non-null pointer to at least one Map.
     */
    void deleteLast_map(Map map[static const 1]);

    /**
     * @brief Empties an Map without freeing.
     *
     * @param[in,out] map A constant non-null pointer to at least one Map.
     */
    void flush_map(Map map[static const 1]);

    /**
     * @brief Frees a Map.
     *
     * @param[in,out] map A constant non-null pointer to at least one Map.
     */
    void free_map(Map map[static const 1]);

    /**
     * @brief Inserts a Mapping to a Map.
     *
     * The same key_id may have multiple mappings.
     *
     * @param[in,out]    map A constant non-null pointer to at least one Map.
     * @param[in]     key_id A constant 32-bit unsigned integer.
     * @param[in]      value A constant Value.
     */
    void insert_map(Map map[static const 1], uint32_t const key_id, Value const value);

    /**
     * @brief Checks if a Map is valid.
     *
     * @param[in] map A constant non-null pointer to at least one constant Map.
     *
     * @return A Boolean value.
     */
    bool isValid_map(Map const map[static const 1]);

    /**
     * @brief Performs a backward linear search among the mappings to find a (key_id, Value) mapping.
     *
     * @param[in]             map A constant non-null pointer to at least one constant Map.
     * @param[in] search_start_id A constant 32-bit unsigned integer.
     * @param[in]          key_id A constant 32-bit unsigned integer.
     * @param[in]           value A constant Value.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t linearSearchBackward_map(
        Map const map[static const 1], uint32_t const search_start_id,
        uint32_t const key_id, Value const value
    );

    /**
     * @brief Performs a backward linear search among the mappings to find a key index.
     *
     * @param[in]             map A constant non-null pointer to at least one constant Map.
     * @param[in] search_start_id A constant 32-bit unsigned integer.
     * @param[in]          key_id A constant 32-bit unsigned integer.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t linearSearchBackwardKey_map(
        Map const map[static const 1], uint32_t const search_start_id, uint32_t const key_id
    );

    /**
     * @brief Performs a backward linear search among the mappings to find a value.
     *
     * @param[in]             map A constant non-null pointer to at least one constant Map.
     * @param[in] search_start_id A constant 32-bit unsigned integer.
     * @param[in]           value A constant Value.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t linearSearchBackwardValue_map(
        Map const map[static const 1], uint32_t const search_start_id, Value const value
    );

    /**
     * @brief Performs a forward linear search among the mappings to find a (key_id, Value) mapping.
     *
     * @param[in]             map A constant non-null pointer to at least one constant Map.
     * @param[in] search_start_id A constant 32-bit unsigned integer.
     * @param[in]          key_id A constant 32-bit unsigned integer.
     * @param[in]           value A constant Value.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t linearSearchForward_map(
        Map const map[static const 1], uint32_t const search_start_id,
        uint32_t const key_id, Value const value
    );

    /**
     * @brief Performs a forward linear search among the mappings to find a key index.
     *
     * @param[in]             map A constant non-null pointer to at least one constant Map.
     * @param[in] search_start_id A constant 32-bit unsigned integer.
     * @param[in]          key_id A constant 32-bit unsigned integer.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t linearSearchForwardKey_map(
        Map const map[static const 1], uint32_t const search_start_id, uint32_t const key_id
    );

    /**
     * @brief Performs a forward linear search among the mappings to find a value.
     *
     * @param[in]             map A constant non-null pointer to at least one constant Map.
     * @param[in] search_start_id A constant 32-bit unsigned integer.
     * @param[in]           value A constant Value.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t linearSearchForwardValue_map(
        Map const map[static const 1], uint32_t const search_start_id, Value const value
    );
#endif
