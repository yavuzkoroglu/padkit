/**
 * @file jsonparser.h
 * @brief Defines JSONParser.
 * @author Yavuz Koroglu
 */
#ifndef JSONPARSER_H
    #define JSONPARSER_H
    #include <stdbool.h>
    #include <stdio.h>

    #define JSON_PARSER_INITIAL_STACK_CAP   131072
    #define JSON_PARSER_INITIAL_STR_CAP     131072

    #define JSON_STACK_ARRAY                0
    #define JSON_STACK_END                  1
    #define JSON_STACK_OBJECT               2
    #define JSON_STACK_LAST                 JSON_STACK_OBJECT

    #define JSON_PARSER_INVALID             -1
    #define JSON_PARSER_OK                  0
    #define JSON_PARSER_MEMORY_ERROR        1
    #define JSON_PARSER_STACK_ERROR         2
    #define JSON_PARSER_STREAM_ERROR        3
    #define JSON_PARSER_STRING_ERROR        4
    #define JSON_PARSER_SYNTAX_ERROR        5

    #define NOT_A_JSON_PARSER ((JSONParser){                        \
        NULL, 0, 0, NULL, 0, NULL, '\0', JSON_PARSER_OK,            \
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, \
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, \
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL  \
    })

    typedef struct JSONParserBody {
        FILE*           inputStream;
        size_t          stack_cap;
        size_t          stack_size;
        unsigned char*  stack;
        size_t          str_cap;
        size_t          str_len;
        char*           str;
        long            errorCode;
        void            (*atArrayEnd)   (struct JSONParserBody const* const);
        void            (*atArrayStart) (struct JSONParserBody const* const);
        void            (*atFalse)      (struct JSONParserBody const* const);
        void            (*atNameEnd)    (struct JSONParserBody const* const);
        void            (*atNameStart)  (struct JSONParserBody const* const);
        void            (*atNull)       (struct JSONParserBody const* const);
        void            (*atNumber)     (struct JSONParserBody const* const, double const);
        void            (*atObjectEnd)  (struct JSONParserBody const* const);
        void            (*atObjectStart)(struct JSONParserBody const* const);
        void            (*atRootEnd)    (struct JSONParserBody const* const);
        void            (*atRootStart)  (struct JSONParserBody const* const);
        void            (*atString)     (struct JSONParserBody const* const, char const* const, size_t const);
        void            (*atTrue)       (struct JSONParserBody const* const);
        void            (*atValueEnd)   (struct JSONParserBody const* const);
        void            (*atValueStart) (struct JSONParserBody const* const);
    } JSONParser;

    void emptyNumberEvent_jsonp(JSONParser const* const jsonParser, double const number);
    void emptyStringEvent_jsonp(JSONParser const* const jsonParser, char const* const string, size_t const len);
    void emptyVoidEvent_jsonp(JSONParser const* const jsonParser);

    typedef void(*JSONParserNumberEvent)(JSONParser const* const jsonParser, double const number);
    typedef void(*JSONParserStringEvent)(JSONParser const* const jsonParser, char const* const string, size_t const len);
    typedef void(*JSONParserVoidEvent)(JSONParser const* const jsonParser);

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

    #ifndef NDEBUG
    bool
    #else
    void
    #endif
    free_jsonp(JSONParser* const jsonParser);

    bool isValid_jsonp(JSONParser const* const jsonParser);

    long parseStream_jsonp(JSONParser* const jsonParser);
#endif
