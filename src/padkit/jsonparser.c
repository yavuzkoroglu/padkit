/**
 * @file jsonparser.c
 * @brief Implements the functions defined in jsonparser.h
 * @author Yavuz Koroglu
 */
#include <ctype.h>
#include <stdlib.h>
#include "padkit/jsonparser.h"

#define PUSH_JP(jp, element)                                            \
    if (jp->stack_size == jp->stack_cap) {                              \
        jp->stack_cap <<= 1;                                            \
        if (jp->stack_cap <= jp->stack_size) {                          \
            jp->errorCode = JSON_PARSER_STACK_ERROR;                    \
            return;                                                     \
        }                                                               \
        unsigned char* new_stack = realloc(jp->stack, jp->stack_cap);   \
        if (new_stack == NULL) {                                        \
            jp->errorCode = JSON_PARSER_MEMORY_ERROR;                   \
            return;                                                     \
        }                                                               \
        jp->stack = new_stack;                                          \
    }                                                                   \
    jp->stack[jp->stack_size++] = element

#define READ_JP(jp)                                                     \
    jp->ch = fgetc(jp->inputStream);                                    \
    while (isspace((char)jp->ch))                                       \
        jp->ch = fgetc(jp->inputStream);                                \
    int const i = jp->ch % 128 + 1

#define UNREAD_JP(jp)                                                   \
    if (ungetc(jp->ch, jp->inputStream) == EOF) {                       \
        jp->errorCode = JSON_PARSER_STREAM_ERROR;                       \
        return;                                                         \
    }

typedef void(*ParseFunction)(JSONParser* const);

static void err_jp(JSONParser* const jp);
static void s00_jp(JSONParser* const jp);
static void s01_jp(JSONParser* const jp);
static void s02_jp(JSONParser* const jp);
static void s03_jp(JSONParser* const jp);
static void s04_jp(JSONParser* const jp);
static void s05_jp(JSONParser* const jp);
static void s06_jp(JSONParser* const jp);
static void s07_jp(JSONParser* const jp);
static void s08_jp(JSONParser* const jp);
static void s09_jp(JSONParser* const jp);
static void s10_jp(JSONParser* const jp);
static void s11_jp(JSONParser* const jp);
static void s12_jp(JSONParser* const jp);
static void s13_jp(JSONParser* const jp);
static void s14_jp(JSONParser* const jp);
static void s15_jp(JSONParser* const jp);
static void s16_jp(JSONParser* const jp);
static void s17_jp(JSONParser* const jp);
static void s18_jp(JSONParser* const jp);
static void s18_jp(JSONParser* const jp);
static void s19_jp(JSONParser* const jp);
static void s20_jp(JSONParser* const jp);
static void s21_jp(JSONParser* const jp);
static void s22_jp(JSONParser* const jp);

static void err_jp(JSONParser* const jp) {
    jp->errorCode = JSON_PARSER_SYNTAX_ERROR;
}

static void s00_jp(JSONParser* const jp) {
    static ParseFunction nextState[129] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        s01_jp, s01_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 0..9 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 10..19 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 20..29 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 30..39 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 40..49 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 50..59 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 60..69 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 70..79 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 80..89 */
        err_jp, err_jp, s02_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 90..99 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 100..109 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 110..119 */
        err_jp, err_jp, err_jp, err_jp, s11_jp, err_jp, err_jp, err_jp, err_jp          /* 120..128 */
    };

    /* atRootStart() */
    if (jp->atRootStart != NULL) (*jp->atRootStart)();

    /* push(#) */
    PUSH_JP(jp, JSON_STACK_END);

    /* read() */
    READ_JP(jp);

    nextState[i](jp);
}

static void s01_jp(JSONParser* const jp) {
    /* atRootEnd() */
    if (jp->atRootEnd != NULL) (*jp->atRootEnd)();

    /* pop() */
    jp->stack_size--;

    #ifndef NDEBUG
        if (jp->stack_size != 0) jp->errorCode = JSON_PARSER_STACK_ERROR;
    #endif
}

static void s02_jp(JSONParser* const jp) {
    /* atArrayStart() */
    if (jp->atArrayStart != NULL) (*jp->atArrayStart)();

    /* push(A) */
    PUSH_JP(jp, JSON_STACK_ARRAY);

    s03_jp(jp);
}

static void s03_jp(JSONParser* const jp) {
    static ParseFunction nextState[129] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 0..9 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 10..19 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 20..29 */
        err_jp, err_jp, err_jp, err_jp, err_jp, s06_jp, err_jp, err_jp, err_jp, err_jp, /* 30..39 */
        err_jp, err_jp, err_jp, err_jp, s07_jp, err_jp, s07_jp, s07_jp, err_jp, s07_jp, /* 40..49 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, err_jp, /* 50..59 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 60..69 */
        s07_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 70..79 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 80..89 */
        err_jp, err_jp, s02_jp, err_jp, s04_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 90..99 */
        err_jp, err_jp, s07_jp, s09_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 100..109 */
        err_jp, s10_jp, err_jp, err_jp, err_jp, err_jp, err_jp, s08_jp, err_jp, err_jp, /* 110..119 */
        err_jp, err_jp, err_jp, err_jp, s11_jp, err_jp, err_jp, err_jp, err_jp          /* 120..128 */
    };

    /* read() */
    READ_JP(jp);

    nextState[i](jp);
}

static void s04_jp(JSONParser* const jp) {
    static ParseFunction nextState[JSON_STACK_LAST + 1] = {
        [JSON_STACK_ARRAY]  = s05_jp,
        [JSON_STACK_END]    = s01_jp,
        [JSON_STACK_OBJECT] = s13_jp
    };

    /* pop() */
    jp->stack_size--;

    /* atArrayEnd() */
    if (jp->atArrayEnd != NULL) (*jp->atArrayEnd)();

    /* peek() */
    unsigned char const i = jp->stack[jp->stack_size - 1];

    nextState[i](jp);
}

static void s05_jp(JSONParser* const jp) {
    static ParseFunction nextState[129] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 0..9 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 10..19 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 20..29 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 30..39 */
        err_jp, err_jp, err_jp, err_jp, err_jp, s03_jp, err_jp, err_jp, err_jp, err_jp, /* 40..49 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 50..59 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 60..69 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 70..79 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 80..89 */
        err_jp, err_jp, err_jp, err_jp, s04_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 90..99 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 100..109 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 110..119 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp          /* 120..128 */
    };

    /* read() */
    READ_JP(jp);

    nextState[i](jp);
}

static void s06_jp(JSONParser* const jp) {
}
static void s07_jp(JSONParser* const jp) {
}
static void s08_jp(JSONParser* const jp) {
}
static void s09_jp(JSONParser* const jp) {
}
static void s10_jp(JSONParser* const jp) {
}
static void s11_jp(JSONParser* const jp) {
}
static void s12_jp(JSONParser* const jp) {
}
static void s13_jp(JSONParser* const jp) {
}
static void s14_jp(JSONParser* const jp) {
}
static void s15_jp(JSONParser* const jp) {
}
static void s16_jp(JSONParser* const jp) {
}
static void s17_jp(JSONParser* const jp) {
}
static void s18_jp(JSONParser* const jp) {
}
static void s19_jp(JSONParser* const jp) {
}
static void s20_jp(JSONParser* const jp) {
}
static void s21_jp(JSONParser* const jp) {
}
static void s22_jp(JSONParser* const jp) {
}

#ifndef NDEBUG
bool
#else
void
#endif
construct_jsonp(
    JSONParser* const jsonParser,
    FILE* const inputStream,
    JSONParserVoidEvent* const eventAtArrayEnd,
    JSONParserVoidEvent* const eventAtArrayStart,
    JSONParserVoidEvent* const eventAtFalse,
    JSONParserVoidEvent* const eventAtNameEnd,
    JSONParserVoidEvent* const eventAtNameStart,
    JSONParserVoidEvent* const eventAtNull,
    JSONParserNumberEvent* const eventAtNumber,
    JSONParserVoidEvent* const eventAtObjectEnd,
    JSONParserVoidEvent* const eventAtObjectStart,
    JSONParserVoidEvent* const eventAtRootEnd,
    JSONParserVoidEvent* const eventAtRootStart,
    JSONParserStringEvent* const eventAtString,
    JSONParserVoidEvent* const eventAtTrue,
    JSONParserVoidEvent* const eventAtValueEnd,
    JSONParserVoidEvent* const eventAtValueStart
) {
    #ifndef NDEBUG
        if (jsonParser == NULL) return 0;
        if (inputStream == NULL) return 0;
    #endif

    jsonParser->inputStream   = inputStream;
    jsonParser->stack_cap     = JSON_PARSER_INITIAL_STACK_CAP;
    jsonParser->stack_size    = 0;
    jsonParser->stack         = malloc(jsonParser->stack_cap);
    #ifndef NDEBUG
        if (jsonParser->stack == NULL) return 0;
    #endif
    jsonParser->str_cap       = JSON_PARSER_INITIAL_STR_CAP;
    jsonParser->str           = malloc(jsonParser->str_cap);
    #ifndef NDEBUG
        if (jsonParser->str == NULL) return 0;
    #endif

    jsonParser->errorCode     = JSON_PARSER_OK;

    jsonParser->atArrayEnd    = eventAtArrayEnd;
    jsonParser->atArrayStart  = eventAtArrayStart;
    jsonParser->atFalse       = eventAtFalse;
    jsonParser->atNameEnd     = eventAtNameEnd;
    jsonParser->atNameStart   = eventAtNameStart;
    jsonParser->atNull        = eventAtNull;
    jsonParser->atNumber      = eventAtNumber;
    jsonParser->atObjectEnd   = eventAtObjectEnd;
    jsonParser->atObjectStart = eventAtObjectStart;
    jsonParser->atRootEnd     = eventAtRootEnd;
    jsonParser->atRootStart   = eventAtRootStart;
    jsonParser->atString      = eventAtString;
    jsonParser->atTrue        = eventAtTrue;
    jsonParser->atValueEnd    = eventAtValueEnd;
    jsonParser->atValueStart  = eventAtValueStart;

    #ifndef NDEBUG
        return 1;
    #endif
}

bool isValid_jsonp(JSONParser const* const jsonParser) {
    if (jsonParser == NULL)                             return 0;
    if (jsonParser->inputStream == NULL)                return 0;
    if (jsonParser->stack == NULL)                      return 0;
    if (jsonParser->stack_cap == 0)                     return 0;
    if (jsonParser->stack_size > jsonParser->stack_cap) return 0;
    if (jsonParser->str_cap == 0)                       return 0;
    if (jsonParser->str == NULL)                        return 0;
    return 1;
}

int parseStream_jsonp(JSONParser* const jsonParser) {
    #ifndef NDEBUG
        if (!isValid_jsonp(jsonParser))
            return JSON_PARSER_INVALID;
    #endif

    jsonParser->errorCode = JSON_PARSER_OK;
    s00_jp(jsonParser);

    return jsonParser->errorCode;
}
