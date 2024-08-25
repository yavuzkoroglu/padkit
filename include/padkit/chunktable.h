/**
 * @file chunktable.h
 * @brief Defines ChunkTable.
 * @author Yavuz Koroglu
 */
#ifndef CHUNK_TABLE_H
    #define CHUNK_TABLE_H
    #include "padkit/chunk.h"

    /**
     * @def NOT_A_CHUNK_TABLE_ENTRY
     *   A special ChunkTableEntry denoting a NOT-ChunkTableEntry.
     */
    #define NOT_A_CHUNK_TABLE_ENTRY                 ((ChunkTableEntry){ UINT32_MAX, UINT32_MAX })

    /**
     * @def NOT_A_CHUNK_TABLE
     *   A special ChunkTable denoting a NOT-ChunkTable. This ChunkTable cannot pass the isValid_ctbl() test.
     */
    #define NOT_A_CHUNK_TABLE                       ((ChunkTable){ 0, 0, NULL, 0, 0, NULL, NULL, NULL })

    /**
     * @def NOT_A_CHUNK_TABLE_ITR
     *   A special CTblConstIterator denoting a NOT-CTblConstIterator.
     */
    #define NOT_A_CHUNK_TABLE_ITR                   ((CTblConstIterator){ NULL, NULL, NULL, 0, NULL })

    /**
     * @def CHUNK_TABLE_RECOMMENDED_INITIAL_CAP
     *   This initial capacity should work nicely in most situations.
     */
    #define CHUNK_TABLE_RECOMMENDED_INITIAL_CAP     (BUFSIZ)

    /**
     * @def CHUNK_TABLE_RECOMMENDED_LOAD_PERCENT
     *   This load percent should work nicely in most situations.
     */
    #define CHUNK_TABLE_RECOMMENDED_LOAD_PERCENT    (75)

    /**
     * @def CHUNK_TABLE_RECOMMENDED_PARAMETERS
     *   Recommended parameters for a typical ChunkTable
     */
    #define CHUNK_TABLE_RECOMMENDED_PARAMETERS      \
        CHUNK_TABLE_RECOMMENDED_INITIAL_CAP, CHUNK_TABLE_RECOMMENDED_LOAD_PERCENT

    /**
     * @def CHUNK_TABLE_INITIAL_ROW_CAP
     *   This initial capacity should work nicely at all times, we should NOT expect too many collisions.
     */
    #define CHUNK_TABLE_INITIAL_ROW_CAP             (4)

    /**
     * @struct ChunkTableEntry
     * @brief A ChunkTableEntry is a key_id-value pair.
     *
     * @var ChunkTableEntry::key_id
     *   The key index.
     * @var ChunkTableEntry::value
     *   The value.
     */
    typedef struct ChunkTableEntryBody {
        uint32_t key_id;
        uint32_t value;
    } ChunkTableEntry;

    /**
     * @brief Checks if a ChunkTableEntry is valid.
     *
     * @param[in] entry A constant non-null pointer to at least one constant ChunkTableEntry.
     *
     * @return A Boolean value.
     */
    bool isValid_cte(ChunkTableEntry const entry[static const 1]);

    /**
     * @struct ChunkTable
     * @brief A ChunkTable is a full-fledged self-adjusting hash table.
     *
     * @var ChunkTable::nKeys
     *   The number of keys.
     * @var ChunkTable::capKeys
     *   The maximum number of keys the ChunkTable can house without readjustment.
     * @var ChunkTable::keys
     *   The list of keys.
     * @var ChunkTable::loadPercent
     *   The load percent.
     * @var ChunkTable::nRows
     *   The # of rows in the table.
     * @var ChunkTable::rowSizes
     *   The # of entries in each row.
     * @var ChunkTable::rowCaps
     *   The capacity in each row.
     * @var ChunkTable::rows
     *   A pointer to the first row in the array of ChunkTableEntry rows.
     */
    typedef struct ChunkTableBody {
        uint32_t          nKeys;
        uint32_t          capKeys;
        uint32_t*         keys;
        uint32_t          loadPercent;
        uint32_t          nRows;
        uint32_t*         rowSizes;
        uint32_t*         rowCaps;
        ChunkTableEntry** rows;
    } ChunkTable;

    /**
     * @brief Constructs an empty ChunkTable.
     *
     * loadPercent <= 100
     *
     * @param[in,out]         tbl A constant non-null pointer to at least one ChunkTable.
     * @param[in]     initial_cap A constant 32-bit unsigned integer.
     * @param[in]     loadPercent A constant 32-bit unsigned integer.
     */
    void constructEmpty_ctbl(
        ChunkTable tbl[static const 1],
        uint32_t const initial_cap, uint32_t const loadPercent
    );

    /**
     * @brief Flushes the contents of a ChunkTable.
     *
     * @param[in,out] tbl A constant non-null pointer to at least one ChunkTable.
     */
    void flush_ctbl(ChunkTable tbl[static const 1]);

    /**
     * @brief Frees a ChunkTable.
     *
     * @param[in,out] tbl A constant non-null pointer to at least one ChunkTable.
     */
    void free_ctbl(ChunkTable tbl[static const 1]);

    /**
     * @brief Gets the ChunkTableEntry of a given key.
     *
     * @param[in]     tbl A constant non-null pointer to at least one constant ChunkTable.
     * @param[in]   chunk A constant non-null pointer to at least one constant Chunk.
     * @param[in]     key A constant non-null pointer to at least one constant character.
     * @param[in] key_len A constant 64-bit unsigned integer.
     *
     * @return A pointer to a ChunkTableEntry.
     */
    ChunkTableEntry* get_ctbl(
        ChunkTable const tbl[static const 1], Chunk const chunk[static const 1],
        char const key[static const 1], uint64_t const key_len
    );

    /**
     * @brief Gets the entry count of a ChunkTable.
     *
     * @param[in] tbl A constant non-null pointer to at least one constant ChunkTable.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t getEntryCount_ctbl(ChunkTable const tbl[static const 1]);

    /**
     * @brief Gets the ChunkTableEntry of a given key and value.
     *
     * @param[in]     tbl A constant non-null pointer to at least one constant ChunkTable.
     * @param[in]   chunk A constant non-null pointer to at least one constant Chunk.
     * @param[in]     key A constant non-null pointer to at least one constant character.
     * @param[in] key_len A constant 64-bit unsigned integer.
     * @param[in]   value A constant 32-bit unsigned integer.
     *
     * @return A pointer to a ChunkTableEntry.
     */
    ChunkTableEntry* getExact_ctbl(
        ChunkTable const tbl[static const 1], Chunk const chunk[static const 1],
        char const key[static const 1], uint64_t const key_len, uint32_t const value
    );

    /**
     * @brief Gets the key count of a ChunkTable.
     *
     * @param tbl A constant non-null pointer to at least one constant ChunkTable.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t getKeyCount_ctbl(ChunkTable const tbl[static const 1]);

    /* Return values for insert_ctbl */
    #define CTBL_INSERT_OK                      (0)
    #define CTBL_INSERT_DUPLICATE_ENTRY         (1)
    #define CTBL_INSERT_DUPLICATE_KEY           (2)

    /* Values for ctbl_insert_behavior */
    #define CTBL_BEHAVIOR_MULTIPLE              (0)
    #define CTBL_BEHAVIOR_REPLACE               (1)
    #define CTBL_BEHAVIOR_UNIQUE                (2)
    #define CTBL_BEHAVIOR_FIRST                 CTBL_BEHAVIOR_MULTIPLE
    #define CTBL_BEHAVIOR_LAST                  CTBL_BEHAVIOR_UNIQUE
    #define IS_VALID_CTBL_INSERT_BEHAVIOR(b)    (CTBL_BEHAVIOR_FIRST <= b && b <= CTBL_BEHAVIOR_LAST)

    /**
     * @brief Inserts (replaces if exists) a ChunkTableEntry.
     *
     * @param[in,out]                  tbl A constant non-null pointer to at least one ChunkTable.
     * @param[in,out]                chunk A constant non-null pointer to at least one constant Chunk.
     * @param[in]                   key_id A constant 32-bit unsigned integer.
     * @param[in]                    value A constant 32-bit unsigned integer.
     * @param[in]     ctbl_insert_behavior A constant signed integer (see CTBL_BEHAVIOR_xxx).
     *
     * @return An integer (errorcode, see CTBL_INSERT_xxx).
     */
    int insert_ctbl(
        ChunkTable tbl[static const 1], Chunk const chunk[static const 1],
        uint32_t const key_id, uint32_t const value,
        int const ctbl_insert_behavior
    );

    /**
     * @brief Checks a table if it is valid.
     *
     * @param[in] tbl A constant non-null pointer to at least one ChunkTable.
     *
     * @return A Boolean value.
     */
    bool isValid_ctbl(ChunkTable const tbl[static const 1]);

    /**
     * @struct CTblConstIterator
     * @brief A constant ChunkTable iterator.
     *
     * @var CTblConstIterator::tbl
     *   The ChunkTable that is iterated.
     * @var CTblConstIterator::chunk
     *   The Chunk where the key is located.
     * @var CTblConstIterator::key
     *   The key string that is searched for.
     * @var CTblConstIterator::key_len
     *   The key string length.
     * @var CTblConstIterator::entry
     *   The current iterated ChunkTableEntry.
     */
    typedef struct CTblConstIteratorBody {
        ChunkTable const*       tbl;
        Chunk const*            chunk;
        char const*             key;
        uint64_t                key_len;
        ChunkTableEntry const*  entry;
    } CTblConstIterator;

    /**
     * @brief Constructs a CTblConstIterator.
     *
     * @param[in,out]     itr A constant non-null pointer to at least one CTblConstIterator.
     * @param[in]         tbl A constant non-null pointer to at least one constant ChunkTable.
     * @param[in]       chunk A constant non-null pointer to at least one constant Chunk.
     * @param[in]         key A constant non-null pointer to at least one constant character.
     * @param[in]     key_len A constant 64-bit unsigned integer.
     */
    void construct_ctblitr(
        CTblConstIterator itr[static const 1],
        ChunkTable const tbl[static const 1], Chunk const chunk[static const 1],
        char const key[static const 1], uint64_t const key_len
    );

    /**
     * @brief Checks if a CTblConstIterator is valid.
     *
     * @param[in] itr A constant non-null pointer to at least one constant CTblConstIterator.
     *
     * @return A Boolean value.
     */
    bool isValid_ctblitr(CTblConstIterator const itr[static const 1]);

    /**
     * @brief Iterates to the next ChunkTableEntry.
     *
     * @param[in,out] itr A constant non-null pointer to at least one CTblConstIterator.
     *
     * @return A pointer to a constant ChunkTableEntry.
     */
    ChunkTableEntry const* next_ctblitr(CTblConstIterator itr[static const 1]);
#endif

