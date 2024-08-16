/**
 * @file chunk.h
 * @brief Defines Chunk and its related functions.
 *
 * A Chunk is a chunk of heap memory. You can add several strings to a Chunk.
 * You can also append strings to the last string of the Chunk.
 * Freeing the Chunk frees all the allocated strings.
 * Modifying/expanding/removing strings from the middle of the Chunk may break the Chunk.
 *
 * @author Yavuz Koroglu
 */
#ifndef CHUNK_H
    #define CHUNK_H
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdint.h>

    /**
     * @def NOT_A_CHUNK
     *   A special Chunk denoting a NOT-Chunk. This Chunk cannot pass the isValid_chunk() test.
     */
    #define NOT_A_CHUNK \
        ((Chunk){0, 0, 0, NULL, NULL, 0})

    /**
     * @def CHUNK_RECOMMENDED_INITIAL_CAP
     *   This initial capacity should work nicely in most situations.
     */
    #define CHUNK_RECOMMENDED_INITIAL_CAP BUFSIZ

    /**
     * @def CHUNK_RECOMMENDED_INITIAL_STRINGS_CAP
     *   This initial capacity should work nicely in most situations.
     */
    #define CHUNK_RECOMMENDED_INITIAL_STRINGS_CAP BUFSIZ

    /**
     * @def CHUNK_RECOMMENDED_PARAMETERS
     *   Recommended parameters for a typical Chunk.
     */
    #define CHUNK_RECOMMENDED_PARAMETERS \
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
     * Copies n characters from the string to a
     * new string located at the end of the Chunk.
     * The new string is '\0' separated from the
     * previous string.
     *
     * @param chunk A pointer to the Chunk.
     * @param str The string.
     * @param n The number of characters to copy.
     */
    uint32_t add_chunk(Chunk* const chunk, char const* const str, uint64_t const n);

    /**
     * @brief Adds a string to a Chunk using the string's chunk index.
     *
     * WARNING: The string must be located at the same Chunk!
     *
     * @param chunk A pointer to the Chunk.
     * @param str_id The chunk index of the string.
     */
    uint32_t addIndex_chunk(Chunk* const chunk, uint32_t const str_id);

    /**
     * @brief Appends a string to the final string of a Chunk.
     *
     * This function is similar to add_chunk() but
     * does NOT respect the '\0' separator.
     *
     * @param chunk A pointer to the Chunk.
     * @param str The string.
     * @param n The number of characters to copy.
     */
    char const* append_chunk(Chunk* const chunk, char const* const str, uint64_t const n);

    /**
     * @brief Appends a string to the final string of a Chunk using the string's chunk index.
     *
     * WARNING: The string must be located at the same Chunk!
     *
     * @param chunk A pointer to the Chunk.
     * @param str_id The chunk index of the string.
     */
    char const* appendIndex_chunk(Chunk* const chunk, uint32_t const str_id);

    /**
     * @brief Appends space to the chunk if necessary.
     *
     * WARNING: Does NOT modify chunk->len
     *
     * @param chunk Thu chunk.
     * @param size The size of the space in bytes.
     */
    char* appendSpace_chunk(Chunk* const chunk, uint64_t const size);

    /**
     * @brief Adds all the strings from a Chunk to another Chunk.
     * @param to The destination Chunk.
     * @param from The source Chunk.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    concat_chunk(Chunk* const to, Chunk const* const from);

    /**
     * @brief Constructs an empty Chunk.
     * @param chunk A pointer to the Chunk.
     * @param initial_cap The initial capacity of the Chunk.
     * @param initial_stringsCap The initial capacity of the Chunk in terms of the number of strings.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    constructEmpty_chunk(Chunk* chunk, uint64_t const initial_cap, uint32_t const initial_stringsCap);

    /**
     * @brief Deletes an element from a Chunk.
     * @param chunk A pointer to the Chunk.
     * @param str_id The string index.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    delete_chunk(Chunk* const chunk, uint32_t const str_id);

    /**
     * @brief Deletes the last element in a Chunk.
     * @param chunk A pointer to the Chunk.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    deleteLast_chunk(Chunk* const chunk);

    /**
     * @brief Flushes the contents of a Chunk.
     * @param chunk A pointer to the Chunk.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    flush_chunk(Chunk* const chunk);

    /**
     * @brief Frees all the strings in a Chunk.
     * @param chunk A pointer to the Chunk.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    free_chunk(Chunk* const chunk);

    /**
     * @brief Reads a whole stream and adds it as strings to a Chunk.
     * @param chunk A pointer to the Chunk.
     * @param stream The input stream.
     * @param delimeters The list of delimeter characters. Will use isspace() if NULL given.
     */
    uint32_t fromStream_chunk(Chunk* const chunk, FILE* const stream, char const* delimeters);

    /**
     * @brief Reads a whole stream and adds it as one whole string to a Chunk.
     * @param chunk A pointer to the Chunk.
     * @param stream The input stream.
     */
    uint32_t fromStreamAsWhole_chunk(Chunk* const chunk, FILE* const stream);

    /**
     * @brief Gets a string with the given index from a chunk.
     * @param chunk A pointer to the constant Chunk.
     * @param str_id The string index.
     */
    char const* get_chunk(Chunk const* const chunk, uint32_t const str_id);

    /**
     * @brief Gets the first string from the chunk.
     * @param chunk A pointer to the constant Chunk.
     */
    char const* getFirst_chunk(Chunk const* const chunk);

    /**
     * @brief Gets the last string from the chunk.
     * @param chunk A pointer to the constant Chunk.
     */
    char const* getLast_chunk(Chunk const* const chunk);

    /**
     * @brief Checks if a Chunk is valid.
     * @param chunk A pointer to the constant Chunk.
     */
    bool isValid_chunk(Chunk const* const chunk);

    /**
     * @brief Splits the last string of a Chunk using delimeters.
     *
     * Default delimeters are equivalent to a check using isspace() function.
     *
     * @param chunk A pointer to the Chunk.
     * @param delimeters The list of delimeter characters. Will use isspace() if NULL given.
     */
    uint32_t splitLast_chunk(Chunk* const chunk, char const* delimeters);

    /* @brief Returns the length of a string in a Chunk.
     *
     * Normally, strlen() traverses the string to compute the length.
     * This function takes the difference between the end and the beginning of the string.
     *
     * @param chunk A pointer to the constant Chunk.
     * @param str_id The string index.
     */
    uint64_t strlen_chunk(Chunk const* const chunk, uint32_t const str_id);

    /* @brief Returns the length of the last string in a Chunk.
     * @param chunk A pointer to the constant Chunk.
     */
    uint64_t strlenLast_chunk(Chunk const* const chunk);
#endif
