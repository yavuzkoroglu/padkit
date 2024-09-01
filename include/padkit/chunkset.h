/**
 * @file chunkset.h
 * @brief Defines ChunkSet.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_CHUNKSET_H
    #define PADKIT_CHUNKSET_H
    #include "padkit/chunk.h"

    /**
     * @def NOT_A_CHUNK_SET
     *   A special ChunkSet denoting a NOT-ChunkSet. This ChunkSet cannot pass the isValid_cset() test.
     */
    #define NOT_A_CHUNK_SET                     ((ChunkSet){ 0, 0, 0, NULL, NULL, 0, 0, 0, NULL, NULL, NULL })

    /**
     * @def CHUNK_SET_RECOMMENDED_LOAD_PERCENT
     *   This load percent should work nicely in most situations.
     */
    #define CHUNK_SET_RECOMMENDED_LOAD_PERCENT  (75)

    /**
     * @def CHUNK_SET_INITIAL_ROW_CAP
     *   This initial capacity should work nicely at all times, we should NOT expect too many collisions.
     */
    #define CHUNK_SET_INITIAL_ROW_CAP           (4)

    /**
     * @def CHUNK_SET_RECOMMENDED_PARAMETERS
     *   Recommended parameters for a typical ChunkSet
     */
    #define CHUNK_SET_RECOMMENDED_PARAMETERS    \
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
     * @brief Adds (or finds) a key string to a ChunkSet.
     *
     * @param[in,out] set A constant non-null pointer to at least one ChunkSet.
     * @param[in]     key A constant non-null pointer to at least one constant character.
     * @param[in]       n A constant 64-bit unsigned integer.
     *
     * @return A 32-bit unsigned integer (the chunk index of the added - or found - key).
     */
    uint32_t addKey_cset(ChunkSet set[static const 1], char const key[static const 1], uint64_t const n);

    /**
     * @brief Constructs an empty ChunkSet
     *
     * @param[in,out]                set A constant non-null pointer to at least one ChunkSet.
     * @param[in]            initial_cap A constant 64-bit unsigned integer.
     * @param[in]     initial_stringsCap A constant 32-bit unsigned integer.
     * @param[in]            loadPercent A constant 32-bit unsigned integer.
     */
    void constructEmpty_cset(
        ChunkSet set[static const 1], uint64_t const initial_cap,
        uint32_t const initial_stringsCap, uint32_t const loadPercent
    );

    /**
     * @brief Flushes the contents of a Chunk.
     *
     * @param[in,out] set A constant non-null pointer to at least one ChunkSet.
     */
    void flush_cset(ChunkSet set[static const 1]);

    /**
     * @brief Frees the ChunkSet.
     *
     * @param[in,out] set A constant non-null pointer to at least one ChunkSet.
     */
    void free_cset(ChunkSet set[static const 1]);

    /**
     * @brief Gets a key in a ChunkSet with given chunk index.
     *
     * @param[in]    set A constant non-null pointer to at least one constant ChunkSet.
     * @param[in] key_id A constant 32-bit unsigned integer.
     *
     * @return A pointer to a character constants (the begining of the string found, NULL otherwise).
     */
    char const* getKey_cset(ChunkSet const set[static const 1], uint32_t const key_id);

    /**
     * @brief Gets the number of keys in a ChunkSet.
     *
     * @param[in] set A constant non-null pointer to at least one constant ChunkSet.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t getKeyCount_cset(ChunkSet const set[static const 1]);

    /**
     * @brief Gets the chunk index of a key string.
     *
     * @param[in] set A constant non-null pointer to at least one constant ChunkSet.
     * @param[in] key A constant non-null pointer to at least one constant character.
     * @param[in]   n A constant 64-bit unsigned integer.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t getKeyId_cset(ChunkSet const set[static const 1], char const key[static const 1], uint64_t const n);

    /**
     * @brief Checks if a ChunkSet is valid.
     *
     * @param[in] set A constant non-null pointer to at least one constant ChunkSet.
     *
     * @return A Boolean value.
     */
    bool isValid_cset(ChunkSet const set[static const 1]);

    /**
     * @brief Gets the string length of a key indexed with key_id.
     *
     * @param[in]    set A constant non-null pointer to at least one constant ChunkSet.
     * @param[in] key_id A constant 32-bit unsigned integer.
     *
     * @return A 64-bit unsigned integer.
     */
    uint64_t strlen_cset(ChunkSet const set[static const 1], uint32_t const key_id);
#endif
