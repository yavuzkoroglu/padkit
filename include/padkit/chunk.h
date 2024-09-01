/**
 * @file chunk.h
 * @brief Defines Chunk and its related functions.
 *
 * A Chunk is a chunk of heap memory. You can add several strings to a Chunk.
 * You can also append strings to the last string of the Chunk.
 * Freeing the Chunk frees all the allocated strings.
 *
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_CHUNK_H
    #define PADKIT_CHUNK_H
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdint.h>

    /**
     * @def NOT_A_CHUNK
     *   A special Chunk that cannot pass the isValid_chunk() test.
     */
    #define NOT_A_CHUNK                             ((Chunk){0, 0, 0, NULL, NULL, 0})

    /**
     * @def CHUNK_RECOMMENDED_INITIAL_CAP
     *   This initial capacity should work nicely in most situations.
     */
    #define CHUNK_RECOMMENDED_INITIAL_CAP           (BUFSIZ)

    /**
     * @def CHUNK_RECOMMENDED_INITIAL_STRINGS_CAP
     *   This initial capacity should work nicely in most situations.
     */
    #define CHUNK_RECOMMENDED_INITIAL_STRINGS_CAP   (BUFSIZ)

    /**
     * @def CHUNK_RECOMMENDED_PARAMETERS
     *   Recommended parameters for a typical Chunk.
     */
    #define CHUNK_RECOMMENDED_PARAMETERS            \
        CHUNK_RECOMMENDED_INITIAL_CAP, CHUNK_RECOMMENDED_INITIAL_STRINGS_CAP

    /**
     * @struct Chunk
     * @brief A chunk of strings located in heap memory.
     *
     * @var Chunk::cap
     *   The Chunk capacity.
     * @var Chunk::nStrings
     *   The number of strings in the Chunk.
     * @var Chunk::stringsCap
     *   The maximum number of strings the Chunk can track.
     * @var Chunk::stringOffsets
     *   The list of offsets from strings to Chunk::start.
     * @var Chunk::start
     *   A pointer to the beginning of the Chunk.
     * @var Chunk::len
     *   The length of the Chunk.
     */
    typedef struct ChunkBody {
        uint64_t  cap;
        uint32_t  nStrings;
        uint32_t  stringsCap;
        uint64_t* stringOffsets;
        char*     start;
        uint64_t  len;
    } Chunk;

    /**
     * @brief Adds a string to a Chunk.
     *
     * Copies n characters from str to a
     * new string located at the end of chunk.
     * The new string is '\0' separated from the
     * previous string in the chunk.
     *
     * @param[in,out] chunk A constant non-null pointer to at least one Chunk.
     * @param[in]       str A constant restricted non-null pointer to at least one character.
     * @param[in]         n A constant 64-bit unsigned integer.
     *
     * @return A 32-bit unsigned integer (the chunk index of the added string).
     */
    uint32_t add_chunk(
        Chunk chunk[static const 1],
        char const str[static const restrict 1],
        uint64_t const n
    );

    /**
     * @brief Re-inserts one string of a Chunk to the end of that Chunk.
     *
     * str_id must be smaller than chunk->nStrings.
     *
     * @param[in,out]  chunk A constant non-null pointer to at least one Chunk.
     * @param[in]     str_id A constant 32-bit unsigned integer.
     *
     * @return A 32-bit unsigned integer (the chunk index of the added string).
     */
    uint32_t addIndex_chunk(Chunk chunk[static const 1], uint32_t const str_id);

    /**
     * @brief Appends a string to the final string of a Chunk.
     *
     * This function is similar to add_chunk() but
     * does NOT separate from the previous string
     * using a '\0' separator.
     *
     * When chunk->nStrings is zero, append_chunk is equivalent to add_chunk.
     *
     * @param[in,out] chunk A constant non-null pointer to at least one Chunk.
     * @param[in]       str A constant restricted non-null pointer to at least one character.
     * @param[in]         n A constant 64-bit unsigned integer.
     *
     * @return A pointer to a character constant (the beginning of the last string in the chunk).
     */
    char const* append_chunk(
        Chunk chunk[static const 1],
        char const str[static const restrict 1],
        uint64_t const n
    );

    /**
     * @brief Appends one string of a Chunk to the last string of that Chunk.
     *
     * str_id must be smaller than chunk->nStrings.
     *
     * @param[in,out]  chunk A constant non-null pointer to at least one Chunk.
     * @param[in]     str_id A constant 32-bit unsigned integer.
     *
     * @return A pointer to a character constant (the beginning of the last string in the chunk).
     */
    char const* appendIndex_chunk(Chunk chunk[static const 1], uint32_t const str_id);

    /**
     * @brief Appends space to (increases the capacity of) a Chunk if necessary.
     *
     * Does NOT modify chunk->len.
     *
     * @param[in,out] chunk A constant non-null pointer to at least one Chunk.
     * @param[in]      size A constant 64-bit unsigned integer.
     *
     * @return A pointer to a character constant (the beginning of the appended space).
     */
    char* appendSpace_chunk(Chunk chunk[static const 1], uint64_t const size);

    /**
     * @brief Adds all the strings from a source Chunk to a destination Chunk.
     *
     * @param[in,out]   to A constant non-null pointer to at least one Chunk.
     * @param[in]     from A constant non-null pointer to at least one Chunk.
     */
    void concat_chunk(Chunk to[static const 1], Chunk const from[static const 1]);

    /**
     * @brief Constructs an empty Chunk.
     *
     * @param[in,out]              chunk A constant non-null pointer to at least one Chunk.
     * @param[in]            initial_cap A constant 64-bit unsigned integer.
     * @param[in]     initial_stringsCap A constant 32-bit unsigned integer.
     */
    void constructEmpty_chunk(
        Chunk chunk[static const 1],
        uint64_t const initial_cap,
        uint32_t const initial_stringsCap
    );

    /**
     * @brief Deletes an element from a Chunk.
     *
     * @param[in,out]  chunk A constant non-null pointer to at least one Chunk.
     * @param[in]     str_id A constant 32-bit unsigned integer.
     */
    void delete_chunk(Chunk chunk[static const 1], uint32_t const str_id);

    /**
     * @brief Deletes the last element in a Chunk.
     *
     * @param[in,out] chunk A constant non-null pointer to at least one Chunk.
     */
    void deleteLast_chunk(Chunk chunk[static const 1]);

    /**
     * @brief Flushes the contents of a Chunk.
     *
     * @param[in,out] chunk A constant non-null pointer to at least one Chunk.
     */
    void flush_chunk(Chunk chunk[static const 1]);

    /**
     * @brief Frees all the strings in a Chunk.
     *
     * @param[in,out] chunk A constant non-null pointer to at least one Chunk.
     */
    void free_chunk(Chunk chunk[static const 1]);

    /**
     * @brief Reads a whole stream and adds it as strings to a Chunk.
     *
     * NULL delimeters will be replaced by the default delimeters.
     *
     * @param[in,out]      chunk A constant non-null pointer to at least one Chunk.
     * @param[in,out]     stream A constant non-null pointer to at least one FILE.
     * @param[in]     delimeters A pointer to an array of constant characters.
     *
     * @return A 32-bit unsigned integer (The chunk index of the first string read).
     */
    uint32_t fromStream_chunk(
        Chunk chunk[static const 1],
        FILE stream[static const 1],
        char const delimeters[]
    );

    /**
     * @brief Reads a whole stream and adds it as one whole string to a Chunk.
     *
     * @param[in,out]  chunk A constant non-null pointer to at least one Chunk.
     * @param[in,out] stream A constant non-null pointer to at least one FILE.
     *
     * @return A 32-bit unsigned integer (The chunk index of the string read).
     */
    uint32_t fromStreamAsWhole_chunk(Chunk chunk[static const 1], FILE stream[static const 1]);

    /**
     * @brief Gets a string with the given index from a chunk.
     *
     * @param[in,out]  chunk A constant non-null pointer to at least one constant Chunk.
     * @param[in]     str_id A constant 32-bit unsigned integer.
     *
     * @return A pointer to a character constant.
     */
    char const* get_chunk(Chunk const chunk[static const 1], uint32_t const str_id);

    /**
     * @brief Gets the first string from the chunk.
     *
     * @param[in,out] chunk A constant non-null pointer to at least one constant Chunk.
     *
     * @return A pointer to a character constant.
     */
    char const* getFirst_chunk(Chunk const chunk[static const 1]);

    /**
     * @brief Gets the last string from the chunk.
     *
     * @param[in,out] chunk A constant non-null pointer to at least one constant Chunk.
     *
     * @return A pointer to a character constant.
     */
    char const* getLast_chunk(Chunk const chunk[static const 1]);

    /**
     * @brief Checks if a Chunk is valid.
     *
     * @param[in,out] chunk A constant non-null pointer to at least one constant Chunk.
     *
     * @return A Boolean value.
     */
    bool isValid_chunk(Chunk const chunk[static const 1]);

    /**
     * @brief Splits the last string of a Chunk using delimeters.
     *
     * NULL delimeters will be replaced by the default delimeters.
     *
     * @param[in,out]      chunk A constant non-null pointer to at least one Chunk.
     * @param[in]     delimeters A pointer to an array of constant characters.
     *
     * @return A 32-bit unsigned integer (The number of strings generated).
     */
    uint32_t splitLast_chunk(Chunk chunk[static const 1], char const delimeters[]);

    /* @brief Returns the length of a string in a Chunk.
     *
     * Normally, strlen() traverses the string to compute the length.
     * This function takes the difference between the end and the beginning of the string.
     *
     * @param[in,out]  chunk A non-null pointer to at least one constant Chunk.
     * @param[in]     str_id A constant 32-bit unsigned integer.
     *
     * @return A 64-bit unsigned integer.
     */
    uint64_t strlen_chunk(Chunk const chunk[static const 1], uint32_t const str_id);

    /* @brief Returns the length of the last string in a Chunk.
     *
     * @param[in,out] chunk A non-null pointer to at least one constant Chunk.
     *
     * @return A 64-bit unsigned integer.
     */
    uint64_t strlenLast_chunk(Chunk const chunk[static const 1]);
#endif
