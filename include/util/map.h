/**
 * @file map.h
 * @brief Defines Map.
 * @author Yavuz Koroglu
 * @see Value
 */
#ifndef MAP_H
    #define MAP_H
    #include "util/mapping.h"

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
     * @param map The Map.
     * @param key_id The key index.
     */
    uint32_t binarySearchLeftmostKey_map(Map const* const map, uint32_t const key_id);

    /**
     * @brief Performs a binary search among the mappings to find a key index.
     * @param map The Map.
     * @param key_id The key index.
     */
    uint32_t binarySearchRightmostKey_map(Map const* const map, uint32_t const key_id);

    /**
     * @brief Constructs an empty Map.
     * @param map A pointer to the Map.
     * @param initial_cap The initial capacity of the Map.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    constructEmpty_map(Map* map, uint32_t const initial_cap);

    /**
     * @brief Deletes the last map entry.
     * @param map The Map.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    deleteLast_map(Map* const map);

    /**
     * @brief Empties an Map without freeing.
     * @param map The Map.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    flush_map(Map* const map);

    /**
     * @brief Frees a Map.
     * @param map The Map.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    free_map(Map* const map);

    /**
     * @brief Inserts a Mapping to a Map.
     *
     * The same key_id may have multiple mappings.
     *
     * @param map The Map.
     * @param key_id The index of the key.
     * @param value The value.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    insert_map(Map* const map, uint32_t const key_id, Value const value);

    /**
     * @brief Checks if a Map is valid.
     * @param map The Map.
     */
    bool isValid_map(Map const* const map);

    /**
     * @brief Performs a backward linear search among the mappings to find a (key_id, Value) mapping.
     * @param map The Map.
     * @param search_start_id The index from which the search starts.
     * @param key_id The key index.
     * @param value The Value.
     */
    uint32_t linearSearchBackward_map(
        Map const* const map, uint32_t const search_start_id,
        uint32_t const key_id, Value const value
    );

    /**
     * @brief Performs a backward linear search among the mappings to find a key index.
     * @param map The Map.
     * @param search_start_id The index from which the search starts.
     * @param key_id The key index.
     */
    uint32_t linearSearchBackwardKey_map(
        Map const* const map, uint32_t const search_start_id, uint32_t const key_id
    );

    /**
     * @brief Performs a backward linear search among the mappings to find a value.
     * @param map The Map.
     * @param search_start_id The index from which the search starts.
     * @param value The value.
     */
    uint32_t linearSearchBackwardValue_map(
        Map const* const map, uint32_t const search_start_id, Value const value
    );

    /**
     * @brief Performs a forward linear search among the mappings to find a (key_id, Value) mapping.
     * @param map The Map.
     * @param search_start_id The index from which the search starts.
     * @param key_id The key index.
     * @param value The Value.
     */
    uint32_t linearSearchForward_map(
        Map const* const map, uint32_t const search_start_id,
        uint32_t const key_id, Value const value
    );

    /**
     * @brief Performs a forward linear search among the mappings to find a key index.
     * @param map The Map.
     * @param search_start_id The index from which the search starts.
     * @param key_id The key index.
     */
    uint32_t linearSearchForwardKey_map(
        Map const* const map, uint32_t const search_start_id, uint32_t const key_id
    );

    /**
     * @brief Performs a forward linear search among the mappings to find a value.
     * @param map The Map.
     * @param search_start_id The index from which the search starts.
     * @param value The value.
     */
    uint32_t linearSearchForwardValue_map(
        Map const* const map, uint32_t const search_start_id, Value const value
    );
#endif
