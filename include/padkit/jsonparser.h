/**
 * @file jsonparser.h
 * @brief Defines JSONParser.
 * @author Yavuz Koroglu
 */
#ifndef JSONPARSER_H
    #define JSONPARSER_H
    #include <stdbool.h>
    #include <stdio.h>

    /**
     * @def JSON_PARSER_INITIAL_STACK_CAP
     *   This initial capacity should usually work nicely.
     */
    #define JSON_PARSER_INITIAL_STACK_CAP   131072

    /**
     * @def JSON_PARSER_INITIAL_STR_CAP
     *   This initial capacity should usually work nicely.
     */
    #define JSON_PARSER_INITIAL_STR_CAP     131072

    /**
     * @def JSON_STACK_ARRAY
     *   The constant value representing a JSON array in a JSON stack.
     */
    #define JSON_STACK_ARRAY                0

    /**
     * @def JSON_STACK_END
     *   The constant value representing the end of a JSON root in a JSON stack.
     */
    #define JSON_STACK_END                  1

    /**
     * @def JSON_STACK_OBJECT
     *   The constant value representing a JSON object in a JSON stack.
     */
    #define JSON_STACK_OBJECT               2

    /**
     * @def JSON_STACK_LAST
     *   The highest valid value in any JSON stack.
     */
    #define JSON_STACK_LAST                 JSON_STACK_OBJECT

    /**
     * @def JSON_PARSER_INVALID
     *   An errorcode representing errors due to an invalid JSONParser.
     */
    #define JSON_PARSER_INVALID             -1

    /**
     * @def JSON_PARSER_OK
     *   An errorcode representing no errors (everything is OK).
     */
    #define JSON_PARSER_OK                  0

    /**
     * @def JSON_PARSER_MEMORY_ERROR
     *   An errorcode representing errors due to memory I/O.
     */
    #define JSON_PARSER_MEMORY_ERROR        1

    /**
     * @def JSON_PARSER_STACK_ERROR
     *   An errorcode representing errors due to corrupted JSON stack.
     */
    #define JSON_PARSER_STACK_ERROR         2

    /**
     * @def JSON_PARSER_STREAM_ERROR
     *   An errorcode representing errors due to file I/O.
     */
    #define JSON_PARSER_STREAM_ERROR        3

    /**
     * @def JSON_PARSER_STRING_ERROR
     *   An errorcode representing errors due to invalid strings.
     */
    #define JSON_PARSER_STRING_ERROR        4

    /**
     * @def JSON_PARSER_SYNTAX_ERROR
     *   An errorcode representing a syntax error in the input JSON.
     */
    #define JSON_PARSER_SYNTAX_ERROR        5

    /**
     * @def NOT_A_JSON_PARSER
     *   A special JSONParser denoting a NOT-JSONParser. This JSONParser fails the isValid_jsonp() test.
     */
    #define NOT_A_JSON_PARSER ((JSONParser){            \
        NULL, 0, 0, NULL, 0, 0, NULL, JSON_PARSER_OK,   \
        JSON_PARSER_DEFAULT_EVENTS                      \
    })

    /**
     * @struct JSONParser
     * @brief An object consisting everything necessary to parse a JSON file.
     *
     * @var JSONParser::inputStream
     *    A pointer to the input JSON file.
     * @var JSONParser::stack_cap
     *    The maximum number of elements the JSONParser can hold in its stack.
     * @var JSONParser::stack_size
     *    The total number of elements in the JSONParser stack.
     * @var JSONParser::stack
     *    The JSONParser stack.
     * @var JSONParser::str_cap
     *    The maximum number of characters the JSONParser can hold to parse a string.
     * @var JSONParser::str_len
     *    The total number of characters in the JSONParser string.
     * @var JSONParser::str
     *    The JSONParser string
     * @var JSONParser::errorCode
     *    An integer representing either a specific error or normal function during parsing.
     * @var JSONParser::atArrayEnd
     *    A pointer to the function called whenever a JSON array ends.
     * @var JSONParser::atArrayStart
     *    A pointer to the function called whenever a JSON array starts.
     * @var JSONParser::atFalse
     *    A pointer to the function called whenever a JSON value is a Boolean FALSE.
     * @var JSONParser::atNameEnd
     *    A pointer to the function called whenever a JSON name ends.
     * @var JSONParser::atNameStart
     *    A pointer to the function called whenever a JSON name starts.
     * @var JSONParser::atNull
     *    A pointer to the function called whenever a JSON value is a NULL.
     * @var JSONParser::atNumber
     *    A pointer to the function called whenever a JSON value is a number.
     * @var JSONParser::atObjectEnd
     *    A pointer to the function called whenever a JSON object ends.
     * @var JSONParser::atObjectStart
     *    A pointer to the function called whenever a JSON object starts.
     * @var JSONParser::atRootEnd
     *    A pointer to the function called whenever a JSON root ends.
     * @var JSONParser::atRootStart
     *    A pointer to the function called whenever a JSON root starts.
     * @var JSONParser::atString
     *    A pointer to the function called whenever a JSON value is a string.
     * @var JSONParser::atTrue
     *    A pointer to the function called whenever a JSON value is a Boolean TRUE.
     * @var JSONParser::atValueEnd
     *    A pointer to the function called whenever a JSON value ends.
     * @var JSONParser::atValueStart
     *    A pointer to the function called whenever a JSON value starts.
     */
    typedef struct JSONParserBody {
        FILE*           inputStream;
        size_t          stack_cap;
        size_t          stack_size;
        unsigned char*  stack;
        size_t          str_cap;
        size_t          str_len;
        char*           str;
        long            errorCode;
        void            (*atArrayEnd)   (struct JSONParserBody* const);
        void            (*atArrayStart) (struct JSONParserBody* const);
        void            (*atFalse)      (struct JSONParserBody* const);
        void            (*atNameEnd)    (struct JSONParserBody* const);
        void            (*atNameStart)  (struct JSONParserBody* const);
        void            (*atNull)       (struct JSONParserBody* const);
        void            (*atNumber)     (struct JSONParserBody* const, double const);
        void            (*atObjectEnd)  (struct JSONParserBody* const);
        void            (*atObjectStart)(struct JSONParserBody* const);
        void            (*atRootEnd)    (struct JSONParserBody* const);
        void            (*atRootStart)  (struct JSONParserBody* const);
        void            (*atString)     (struct JSONParserBody* const, char const* const, size_t const);
        void            (*atTrue)       (struct JSONParserBody* const);
        void            (*atValueEnd)   (struct JSONParserBody* const);
        void            (*atValueStart) (struct JSONParserBody* const);
    } JSONParser;

    /**
     * @brief An empty function that does nothing whenever a JSONParser raises a corresponding event.
     * @param jsonParser A pointer to the JSONParser.
     * @param number The number related to the JSON event.
     */
    void emptyNumberEvent_jsonp(JSONParser* const jsonParser, double const number);

    /**
     * @brief An empty function that does nothing whenever a JSONParser raises a corresponding event.
     * @param jsonParser A pointer to the JSONParser.
     * @param string The string related to the JSON event.
     * @param len The length of the string related to the JSON event.
     */
    void emptyStringEvent_jsonp(JSONParser* const jsonParser, char const* const string, size_t const len);

    /**
     * @brief An empty function that does nothing whenever a JSONParser raises a corresponding event.
     * @param jsonParser A pointer to the JSONParser.
     */
    void emptyVoidEvent_jsonp(JSONParser* const jsonParser);

    typedef void(*JSONParserNumberEvent)(JSONParser* const jsonParser, double const number);
    typedef void(*JSONParserStringEvent)(JSONParser* const jsonParser, char const* const string, size_t const len);
    typedef void(*JSONParserVoidEvent)(JSONParser* const jsonParser);

    /**
     * @def JSON_PARSER_DEFAULT_EVENTS
     *   By default, a JSONParser calls empty functions at every event.
     */
    #define JSON_PARSER_DEFAULT_EVENTS  \
        emptyVoidEvent_jsonp,           \
        emptyVoidEvent_jsonp,           \
        emptyVoidEvent_jsonp,           \
        emptyVoidEvent_jsonp,           \
        emptyVoidEvent_jsonp,           \
        emptyVoidEvent_jsonp,           \
        emptyNumberEvent_jsonp,         \
        emptyVoidEvent_jsonp,           \
        emptyVoidEvent_jsonp,           \
        emptyVoidEvent_jsonp,           \
        emptyVoidEvent_jsonp,           \
        emptyStringEvent_jsonp,         \
        emptyVoidEvent_jsonp,           \
        emptyVoidEvent_jsonp,           \
        emptyVoidEvent_jsonp

    /**
     * @brief Constructs a JSONParser.
     * @param jsonParser A pointer to the JSONParser.
     * @param inputStream A pointer to the input JSON file.
     * @param atArrayEnd A pointer to the function called whenever a JSON array ends.
     * @param atArrayStart A pointer to the function called whenever a JSON array starts.
     * @param atFalse A pointer to the function called whenever a JSON value is a Boolean FALSE.
     * @param atNameEnd A pointer to the function called whenever a JSON name ends.
     * @param atNameStart A pointer to the function called whenever a JSON name starts.
     * @param atNull A pointer to the function called whenever a JSON value is a NULL.
     * @param atNumber A pointer to the function called whenever a JSON value is a number.
     * @param atObjectEnd A pointer to the function called whenever a JSON object ends.
     * @param atObjectStart A pointer to the function called whenever a JSON object starts.
     * @param atRootEnd A pointer to the function called whenever a JSON root ends.
     * @param atRootStart A pointer to the function called whenever a JSON root starts.
     * @param atString A pointer to the function called whenever a JSON value is a string.
     * @param atTrue A pointer to the function called whenever a JSON value is a Boolean TRUE.
     * @param atValueEnd A pointer to the function called whenever a JSON value ends.
     * @param atValueStart A pointer to the function called whenever a JSON value starts.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    construct_jsonp(
        JSONParser* const       jsonParser,
        FILE* const             inputStream,
        JSONParserVoidEvent     atArrayEnd,
        JSONParserVoidEvent     atArrayStart,
        JSONParserVoidEvent     atFalse,
        JSONParserVoidEvent     atNameEnd,
        JSONParserVoidEvent     atNameStart,
        JSONParserVoidEvent     atNull,
        JSONParserNumberEvent   atNumber,
        JSONParserVoidEvent     atObjectEnd,
        JSONParserVoidEvent     atObjectStart,
        JSONParserVoidEvent     atRootEnd,
        JSONParserVoidEvent     atRootStart,
        JSONParserStringEvent   atString,
        JSONParserVoidEvent     atTrue,
        JSONParserVoidEvent     atValueEnd,
        JSONParserVoidEvent     atValueStart
    );

    /**
     * @brief Frees a JSONParser.
     * @param jsonParser A pointer to the JSONParser.
     */
    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    free_jsonp(JSONParser* const jsonParser);

    /**
     * @brief Checks if a JSONParser is valid.
     * @param jsonParser A pointer to the JSONParser.
     */
    bool isValid_jsonp(JSONParser const* const jsonParser);

    /**
     * @brief Parses a JSON file and returns errorcode.
     * @param jsonParser A pointer to the JSONParser.
     */
    long parseStream_jsonp(JSONParser* const jsonParser);
#endif
