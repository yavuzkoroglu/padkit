/**
 * @file chunkset.h
 * @brief Defines ChunkSet.
 * @author Yavuz Koroglu
 */
#ifndef CHUNKSET_H
    #define CHUNKSET_H
    #include "padkit/chunk.h"

    /**
     * @def NOT_A_CHUNK_SET
     *   A special ChunkSet denoting a NOT-ChunkSet. This ChunkSet cannot pass the isValid_cset() test.
     */
    #define NOT_A_CHUNK_SET \
        ((ChunkSet){ 0, 0, 0, NULL, NULL, 0, 0, 0, NULL, NULL, NULL })

    /**
     * @def CHUNK_SET_RECOMMENDED_LOAD_PERCENT
     *   This load percent should work nicely in most situations.
     */
    #define CHUNK_SET_RECOMMENDED_LOAD_PERCENT 75

    /**
     * @def CHUNK_SET_INITIAL_ROW_CAP
     *   This initial capacity should work nicely at all times, we should NOT expect too many collisions.
     */
    #define CHUNK_SET_INITIAL_ROW_CAP 4

    /**
     * @def CHUNK_SET_RECOMMENDED_PARAMETERS
     *   Recommended parameters for a typical ChunkSet
     */
    #define CHUNK_SET_RECOMMENDED_PARAMETERS \
        CHUNK_RECOMMENDED_PARAMETERS, CHUNK_SET_RECOMMENDED_LOAD_PERCENT

    /**
     * @struct ChunkSet
     * @brief A special Chunk that never contains the same string twice.
     *
     * @var ChunkSet::cap
     *   The Chunk capacity.
     * @var ChunkSet::nStrings
     *   The number of strings in the Chunk.
     * @var ChunkSet::stringsCap
     *   The maximum number of strings the Chunk can track.
     * @var ChunkSet::stringOffsets
     *   The list of offsets from strings to Chunk::start.
     * @var ChunkSet::start
     *   A pointer to the beginning of the Chunk.
     * @var ChunkSet::len
     *   The length of the Chunk.
     * @var ChunkSet::loadPercent
     *   If the ratio ChunkSet::chunk.size > ChunkSet::loadPercent * ChunkSet::nRows, add more rows!
     * @var ChunkSet::rowSize
     *   # elements in the ith row.
     * @var ChunkSet::rowCap
     *   Capacity of the ith row.
     * @var ChunkSet::table
     *   A hash table, ensuring the same string never occurs twice.
     */
    typedef struct ChunkSetBody {
        /* Chunk Definitions */
        uint64_t   cap;
        uint32_t   nStrings;
        uint32_t   stringsCap;
        uint64_t*  stringOffsets;
        char*      start;
        uint64_t   len;
        /* ChunkSet Definitions */
        uint32_t   loadPercent;
        uint32_t   nRows;
        uint32_t*  rowSize;
        uint32_t*  rowCap;
        uint32_t** table;
    } ChunkSet;

    /**
     * @brief Adds a key string to a ChunkSet.
     * @param set The ChunkSet.
     * @param key The key string.
     * @param n The number of characters to copy.
     */
    uint32_t addKey_cset(ChunkSet* const set, char const* const key, uint64_t const n);

    /**
     * @brief Constructs an empty ChunkSet
     * @param set A pointer to the ChunkSet.
     * @param initial_cap The initial capacity of the ChunkSet's Chunk.
     * @param initial_stringsCap # of strings as this ChunkSet's capacity.
     * @param loadPercent The load factor as a percent.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    constructEmpty_cset(
        ChunkSet* set, uint64_t const initial_cap,
        uint32_t const initial_stringsCap, uint32_t const loadPercent
    );

    /**
     * @brief Flushes the contents of a Chunk.
     * @param set The ChunkSet.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    flush_cset(ChunkSet* const set);

    /**
     * @brief Frees the ChunkSet.
     * @param set The ChunkSet.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    free_cset(ChunkSet* const set);

    /**
     * @brief Gets a key in a ChunkSet with given chunk index.
     * @param set The ChunkSet.
     * @param key_id The chunk index of the key.
     */
    char const* getKey_cset(ChunkSet const* const set, uint32_t const key_id);

    /**
     * @brief Gets the number of keys in a ChunkSet.
     * @param set The ChunkSet.
     */
    uint32_t getKeyCount_cset(ChunkSet const* const set);

    /**
     * @brief Gets the chunk index of a key string.
     * @param set The ChunkSet.
     * @param key The key string.
     * @param n The key string length.
     */
    uint32_t getKeyId_cset(ChunkSet const* const set, char const* const key, uint64_t const n);

    /**
     * @brief Checks if a ChunkSet is valid.
     * @param set The ChunkSet.
     */
    bool isValid_cset(ChunkSet const* const set);

    /**
     * @brief Gets the string length of a key indexed with key_id.
     * @param set The ChunkSet.
     * @param key_id The chunk index of the key.
     */
    uint64_t strlen_cset(ChunkSet const* const set, uint32_t const key_id);
#endif
