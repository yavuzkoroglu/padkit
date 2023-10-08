/**
 * @file chunktable.h
 * @brief Defines ChunkTable.
 * @author Yavuz Koroglu
 */
#ifndef CHUNK_TABLE_H
    #define CHUNK_TABLE_H
    #include "util/chunk.h"

    /**
     * @def NOT_A_CHUNK_TABLE_ENTRY
     *   A special ChunkTableEntry denoting a NOT-ChunkTableEntry.
     */
    #define NOT_A_CHUNK_TABLE_ENTRY \
        ((ChunkTableEntry){ 0xFFFFFFFF, 0xFFFFFFFF })

    /**
     * @def NOT_A_CHUNK_TABLE
     *   A special ChunkTable denoting a NOT-ChunkTable. This ChunkTable cannot pass the isValid_ctbl() test.
     */
    #define NOT_A_CHUNK_TABLE \
        ((ChunkTable){ 0, 0, NULL, 0, 0, NULL, NULL, NULL })

    /**
     * @def CHUNK_TABLE_RECOMMENDED_INITIAL_CAP
     *   This initial capacity should work nicely in most situations.
     */
    #define CHUNK_TABLE_RECOMMENDED_INITIAL_CAP BUFSIZ

    /**
     * @def CHUNK_TABLE_RECOMMENDED_LOAD_PERCENT
     *   This load percent should work nicely in most situations.
     */
    #define CHUNK_TABLE_RECOMMENDED_LOAD_PERCENT 75

    /**
     * @def CHUNK_Table_RECOMMENDED_PARAMETERS
     *   Recommended parameters for a typical ChunkTable
     */
    #define CHUNK_TABLE_RECOMMENDED_PARAMETERS \
        CHUNK_TABLE_RECOMMENDED_INITIAL_CAP, CHUNK_TABLE_RECOMMENDED_LOAD_PERCENT

    /**
     * @def CHUNK_TABLE_INITIAL_ROW_CAP
     *   This initial capacity should work nicely at all times, we should NOT expect too many collisions.
     */
    #define CHUNK_TABLE_INITIAL_ROW_CAP 4

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
     * @var ChunkTable::table
     *   The table of entries
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
     * @param tbl A pointer to the ChunkTable.
     * @param initial_cap The initial capacity.
     * @param loadPercent Load percent.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    constructEmpty_ctbl(ChunkTable* tbl, uint32_t const initial_cap, uint32_t const loadPercent);

    /**
     * @brief Flushes the contents of a ChunkTable.
     * @param tbl A pointer to the ChunkTable.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    flush_ctbl(ChunkTable* const tbl);

    /**
     * @brief Frees a ChunkTable.
     * @param tbl A pointer to the ChunkTable.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    free_ctbl(ChunkTable* const tbl);

    /**
     * @brief Gets the ChunkTableEntry of a given key.
     * @param tbl A pointer to the ChunkTable.
     * @param chunk A pointer to the chunk where the key resides.
     * @param key The key string.
     * @param key_len The key length.
     */
    ChunkTableEntry* get_ctbl(
        ChunkTable const* const tbl, Chunk const* const chunk,
        char const* key, uint64_t const key_len
    );

    /**
     * @brief Gets the entry count of a ChunkTable.
     * @param tbl A pointer to the ChunkTable.
     */
    uint32_t getEntryCount_ctbl(ChunkTable const* const tbl);

    /**
     * @brief Gets the ChunkTableEntry of a given key and value.
     * @param tbl A pointer to the ChunkTable.
     * @param chunk A pointer to the chunk where the key resides.
     * @param key The key string.
     * @param key_len The key length.
     * @param value The value.
     */
    ChunkTableEntry* getExact_ctbl(
        ChunkTable const* const tbl, Chunk const* const chunk,
        char const* key, uint64_t const key_len, uint32_t const value
    );

    /**
     * @brief Gets the key count of a ChunkTable.
     * @param tbl A pointer to the ChunkTable.
     */
    uint32_t getKeyCount_ctbl(ChunkTable const* const tbl);

    /**
     * @brief Inserts (replaces if exists) a ChunkTableEntry.
     * @param tbl A pointer to the ChunkTable.
     * @param chunk The chunk where the keys reside.
     * @param key_id The key index.
     * @param value The value.
     */
    #ifndef NDEBUG
        #define CTBL_INSERT_ERROR        0
    #endif
    #define CTBL_INSERT_OK               1
    #define CTBL_INSERT_DUPLICATE_ENTRY -1
    #define CTBL_INSERT_DUPLICATE_KEY   -2
    #define CTBL_BEHAVIOR_MULTIPLE       0
    #define CTBL_BEHAVIOR_REPLACE        1
    #define CTBL_BEHAVIOR_UNIQUE         2
    int insert_ctbl(
        ChunkTable* const tbl, Chunk const* const chunk,
        uint32_t const key_id, uint32_t const value,
        int const ctbl_insert_behavior
    );

    /**
     * @brief Checks a table if it is valid.
     * @param tbl A pointer to the ChunkTable.
     */
    bool isValid_ctbl(ChunkTable const* const tbl);

    /**
     * @brief Checks if a ChunkTableEntry is valid.
     * @param entry The ChunkTableEntry.
     */
    bool isValid_cte(ChunkTableEntry const* const entry);
#endif

