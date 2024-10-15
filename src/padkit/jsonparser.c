#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "padkit/jsonparser.h"
#include "padkit/memalloc.h"
#include "padkit/size.h"
#include "padkit/unused.h"

#define PEEK_JP(jp) jp->stack[jp->stack_len - 1]

#define POP_JP(jp) jp->stack_len--

#define PUSH_JP(jp, element)                                                \
    if (jp->stack_len == jp->stack_cap) {                                  \
        jp->stack_cap <<= 1;                                                \
        if (jp->stack_cap >= SZSZ_MAX) {                                    \
            jp->errorCode = JSON_PARSER_STACK_ERROR;                        \
            return;                                                         \
        }                                                                   \
        {                                                                   \
            unsigned char* new_stack = realloc(jp->stack, jp->stack_cap);   \
            if (new_stack == NULL) {                                        \
                jp->errorCode = JSON_PARSER_MEMORY_ERROR;                   \
                return;                                                     \
            }                                                               \
            jp->stack = new_stack;                                          \
        }                                                                   \
    }                                                                       \
    jp->stack[jp->stack_len++] = element

#define UNREAD_JP(jp)                                                       \
    if (ungetc(jp->str[0], jp->inputStream) == EOF) {                       \
        jp->errorCode = JSON_PARSER_STREAM_ERROR;                           \
        return;                                                             \
    }

typedef void(*ParseFunction)(JSONParser* const);

void emptyNumberEvent_jsonp(JSONParser* const jp, double const number) {
    MAYBE_UNUSED(jp)
    MAYBE_UNUSED(number)
}
void emptyStringEvent_jsonp(
    JSONParser* const jp,
    char const* const string,
    size_t const len
) {
    MAYBE_UNUSED(jp)
    MAYBE_UNUSED(string)
    MAYBE_UNUSED(len)
}
void emptyVoidEvent_jsonp(JSONParser* const jp) {
    MAYBE_UNUSED(jp)
}

static void err_jp(JSONParser* const jp);
static void s00_jp(JSONParser* const jp);
static void s01_jp(JSONParser* const jp);
static void s02_jp(JSONParser* const jp);
static void s03_jp(JSONParser* const jp);
static void s04_jp(JSONParser* const jp);
static void s05_jp(JSONParser* const jp);
static void s06_jp(JSONParser* const jp);
static void s07a_jp(JSONParser* const jp);
static void s07b_jp(JSONParser* const jp);
static void s07c_jp(JSONParser* const jp);
static void s07d_jp(JSONParser* const jp);
static void s07_jp(JSONParser* const jp);
static void s08_jp(JSONParser* const jp);
static void s09_jp(JSONParser* const jp);
static void s10_jp(JSONParser* const jp);
static void s11a_jp(JSONParser* const jp);
static void s11b_jp(JSONParser* const jp);
static void s11c_jp(JSONParser* const jp);
static void s11d_jp(JSONParser* const jp);
static void s11_jp(JSONParser* const jp);
static void s12_jp(JSONParser* const jp);
static void s13_jp(JSONParser* const jp);
static void s14_jp(JSONParser* const jp);
static void s15a_jp(JSONParser* const jp);
static void s15b_jp(JSONParser* const jp);
static void s15c_jp(JSONParser* const jp);
static void s15d_jp(JSONParser* const jp);
static void s15_jp(JSONParser* const jp);
static void s16_jp(JSONParser* const jp);
static void s17_jp(JSONParser* const jp);
static void s18_jp(JSONParser* const jp);
static void s18_jp(JSONParser* const jp);
static void s19_jp(JSONParser* const jp);
static void s20_jp(JSONParser* const jp);
static void s21_jp(JSONParser* const jp);
static void s22_jp(JSONParser* const jp);
static void s23_jp(JSONParser* const jp);
static void s24_jp(JSONParser* const jp);

static void err_jp(JSONParser* const jp) {
    jp->errorCode = JSON_PARSER_SYNTAX_ERROR;
}

static void s00_jp(JSONParser* const jp) {
    /* atRootStart() */
    (*jp->atRootStart)(jp);

    /* push(#) */
    PUSH_JP(jp, JSON_STACK_END);

    s01_jp(jp);
}

static void s01_jp(JSONParser* const jp) {
    static ParseFunction nextState[256] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        s24_jp, err_jp, err_jp, s24_jp, s24_jp, err_jp, err_jp, err_jp, err_jp, s01_jp, /* 0..9 */
        s01_jp, s01_jp, s01_jp, s01_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 10..19 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 20..29 */
        err_jp, err_jp, s01_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 30..39 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 40..49 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 50..59 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 60..69 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 70..79 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 80..89 */
        err_jp, s02_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 90..99 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 100..109 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 110..119 */
        err_jp, err_jp, err_jp, s03_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 120..129 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 130..139 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 140..149 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 150..159 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 160..169 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 170..179 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 180..189 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 190..199 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 200..209 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 210..219 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 220..229 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 230..239 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 240..249 */
        err_jp, err_jp, err_jp, err_jp, err_jp, s24_jp                                  /* 250..255 */
    };

    /* read() */
    {
        unsigned char const i = (unsigned char)fgetc(jp->inputStream);
        nextState[i](jp);
    }
}

static void s02_jp(JSONParser* const jp) {
    /* atArrayStart() */
    (*jp->atArrayStart)(jp);

    /* push(A) */
    PUSH_JP(jp, JSON_STACK_ARRAY);

    s04_jp(jp);
}

static void s03_jp(JSONParser* const jp) {
    /* atObjectStart() */
    (*jp->atObjectStart)(jp);

    /* push(A) */
    PUSH_JP(jp, JSON_STACK_OBJECT);

    s05_jp(jp);
}

static void s04_jp(JSONParser* const jp) {
    static ParseFunction nextState[256] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, s04_jp, /* 0..9 */
        s04_jp, s04_jp, s04_jp, s04_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 10..19 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 20..29 */
        err_jp, err_jp, s04_jp, err_jp, s07a_jp,err_jp, err_jp, err_jp, err_jp, err_jp, /* 30..39 */
        err_jp, err_jp, err_jp, s08_jp, err_jp, s08_jp, s08_jp, err_jp, s08_jp, s08_jp, /* 40..49 */
        s08_jp, s08_jp, s08_jp, s08_jp, s08_jp, s08_jp, s08_jp, s08_jp, err_jp, err_jp, /* 50..59 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, s08_jp, /* 60..69 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 70..79 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 80..89 */
        err_jp, s02_jp, err_jp, s21_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 90..99 */
        err_jp, s08_jp, s10_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 100..109 */
        s06_jp, err_jp, err_jp, err_jp, err_jp, err_jp, s09_jp, err_jp, err_jp, err_jp, /* 110..119 */
        err_jp, err_jp, err_jp, s03_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 120..129 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 130..139 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 140..149 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 150..159 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 160..169 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 170..179 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 180..189 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 190..199 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 200..209 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 210..219 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 220..229 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 230..239 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 240..249 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp                                  /* 250..255 */
    };

    /* read() */
    {
        unsigned char const i = (unsigned char)fgetc(jp->inputStream);
        jp->str[0] = (char)i;
        nextState[i](jp);
    }
}

static void s05_jp(JSONParser* const jp) {
    static ParseFunction nextState[256] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, s05_jp, /* 0..9 */
        s05_jp, s05_jp, s05_jp, s05_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 10..19 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 20..29 */
        err_jp, err_jp, s05_jp, err_jp, s11a_jp,err_jp, err_jp, err_jp, err_jp, err_jp, /* 30..39 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 40..49 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 50..59 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 60..69 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 70..79 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 80..89 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 90..99 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 100..109 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 110..119 */
        err_jp, err_jp, err_jp, err_jp, err_jp, s22_jp, err_jp, err_jp, err_jp, err_jp, /* 120..129 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 130..139 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 140..149 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 150..159 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 160..169 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 170..179 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 180..189 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 190..199 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 200..209 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 210..219 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 220..229 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 230..239 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 240..249 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp                                  /* 250..255 */
    };

    /* read() */
    {
        unsigned char const i = (unsigned char)fgetc(jp->inputStream);
        nextState[i](jp);
    }
}

static void s06_jp(JSONParser* const jp) {
    static ParseFunction nextState[2] = { err_jp, s19_jp };

    char ull[3];

    /* atValueStart() */
    (*jp->atValueStart)(jp);

    /* atNull('ull') */
    (*jp->atNull)(jp);

    /* atValueEnd() */
    (*jp->atValueEnd)(jp);

    nextState[(fread(ull, 1, 3, jp->inputStream) == 3 && ull[0] == 'u' && ull[1] == 'l' && ull[2] == 'l')](jp);
}

static void s07a_jp(JSONParser* const jp) {
    /* atValueStart() */
    (*jp->atValueStart)(jp);

    /* len = 0 */
    jp->str_len = 0;

    s07b_jp(jp);
}
static void s07b_jp(JSONParser* const jp) {
    static ParseFunction nextState[256] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        err_jp, err_jp, err_jp, err_jp, err_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 0..9 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 10..19 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 20..29 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07d_jp,s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 30..39 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 40..49 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 50..59 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 60..69 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 70..79 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 80..89 */
        s07_jp, s07_jp, s07c_jp,s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 90..99 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 100..109 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 110..119 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 120..129 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 130..139 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 140..149 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 150..159 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 160..169 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 170..179 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 180..189 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 190..199 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 200..209 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 210..219 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 220..229 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 230..239 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, s07_jp,  /* 240..249 */
        s07_jp, s07_jp, s07_jp, s07_jp, s07_jp, err_jp                                   /* 250..255 */
    };

    /* str[len] = read() */
    {
        unsigned char const i = (unsigned char)(jp->str[jp->str_len] = (char)fgetc(jp->inputStream));
        nextState[i](jp);
    }
}
static void s07c_jp(JSONParser* const jp) {
    /* read() */
    fgetc(jp->inputStream);

    s07b_jp(jp);
}
static void s07d_jp(JSONParser* const jp) {
    /* str[len] = '\0' */
    jp->str[jp->str_len] = '\0';

    /* atString(str, len) */
    (*jp->atString)(jp, jp->str, jp->str_len);

    /* atValueEnd() */
    (*jp->atValueEnd)(jp);

    s19_jp(jp);
}
static void s07_jp(JSONParser* const jp) {
    /* len++ */
    jp->str_len++;

    if (jp->str_len == jp->str_cap) {
        size_t const new_cap = jp->str_cap << 1;
        if (new_cap >= SZSZ_MAX) {
            jp->errorCode = JSON_PARSER_STRING_ERROR;
            return;
        }
        jp->str_cap = new_cap;
        {
            char* new_str = realloc(jp->str, new_cap);
            if (new_str == NULL) {
                jp->errorCode = JSON_PARSER_MEMORY_ERROR;
                return;
            }
            jp->str = new_str;
        }
    }

    s07b_jp(jp);
}

static void s08_jp(JSONParser* const jp) {
    double num;

    /* atValueStart() */
    (*jp->atValueStart)(jp);

    /* unread() */
    UNREAD_JP(jp)

    /* atNumber(%lf) */
    if (fscanf(jp->inputStream, "%lf", &num) == 0) {
        jp->errorCode = JSON_PARSER_SYNTAX_ERROR;
        return;
    }
    (*jp->atNumber)(jp, num);

    /* atValueEnd() */
    (*jp->atValueEnd)(jp);

    s19_jp(jp);
}

static void s09_jp(JSONParser* const jp) {
    static ParseFunction nextState[2] = { err_jp, s19_jp };

    char rue[3];

    /* atValueStart() */
    (*jp->atValueStart)(jp);

    /* atTrue('rue') */
    (*jp->atTrue)(jp);

    /* atValueEnd() */
    (*jp->atValueEnd)(jp);

    nextState[(fread(rue, 1, 3, jp->inputStream) == 3 && rue[0] == 'r' && rue[1] == 'u' && rue[2] == 'e')](jp);
}

static void s10_jp(JSONParser* const jp) {
    static ParseFunction nextState[2] = { err_jp, s19_jp };

    char alse[4];

    /* atValueStart() */
    (*jp->atValueStart)(jp);

    /* atFalse('alse') */
    (*jp->atFalse)(jp);

    /* atValueEnd() */
    (*jp->atValueEnd)(jp);

    nextState[(
        fread(alse, 1, 4, jp->inputStream) == 4 &&
        alse[0] == 'a' && alse[1] == 'l'        &&
        alse[2] == 's' && alse[3] == 'e'
    )](jp);
}

static void s11a_jp(JSONParser* const jp) {
    /* atNameStart() */
    (*jp->atNameStart)(jp);

    /* len = 0 */
    jp->str_len = 0;

    s11b_jp(jp);
}
static void s11b_jp(JSONParser* const jp) {
    static ParseFunction nextState[256] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        err_jp, err_jp, err_jp, err_jp, err_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 0..9 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 10..19 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 20..29 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11d_jp,s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 30..39 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 40..49 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 50..59 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 60..69 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 70..79 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 80..89 */
        s11_jp, s11_jp, s11c_jp,s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 90..99 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 100..109 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 110..119 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 120..129 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 130..139 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 140..149 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 150..159 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 160..169 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 170..179 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 180..189 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 190..199 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 200..209 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 210..219 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 220..229 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 230..239 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, s11_jp,  /* 240..249 */
        s11_jp, s11_jp, s11_jp, s11_jp, s11_jp, err_jp                                   /* 250..255 */
    };

    /* str[len] = read() */
    {
        unsigned char const i = (unsigned char)(jp->str[jp->str_len] = (char)fgetc(jp->inputStream));
        nextState[i](jp);
    }
}
static void s11c_jp(JSONParser* const jp) {
    /* read() */
    fgetc(jp->inputStream);

    s11b_jp(jp);
}
static void s11d_jp(JSONParser* const jp) {
    /* str[len] = '\0' */
    jp->str[jp->str_len] = '\0';

    /* atString(str, len) */
    (*jp->atString)(jp, jp->str, jp->str_len);

    /* atNameEnd() */
    (*jp->atNameEnd)(jp);

    s12_jp(jp);
}
static void s11_jp(JSONParser* const jp) {
    /* len++ */
    jp->str_len++;

    if (jp->str_len == jp->str_cap) {
        size_t const new_cap = jp->str_cap << 1;
        if (new_cap >= SZSZ_MAX) {
            jp->errorCode = JSON_PARSER_STRING_ERROR;
            return;
        }
        jp->str_cap = new_cap;
        {
            char* new_str = realloc(jp->str, new_cap);
            if (new_str == NULL) {
                jp->errorCode = JSON_PARSER_MEMORY_ERROR;
                return;
            }
            jp->str = new_str;
        }
    }

    s11b_jp(jp);
}

static void s12_jp(JSONParser* const jp) {
    static ParseFunction nextState[256] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, s12_jp, /* 0..9 */
        s12_jp, s12_jp, s12_jp, s12_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 10..19 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 20..29 */
        err_jp, err_jp, s12_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 30..39 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 40..49 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, s13_jp, err_jp, /* 50..59 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 60..69 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 70..79 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 80..89 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 90..99 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 100..109 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 110..119 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 120..129 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 130..139 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 140..149 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 150..159 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 160..169 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 170..179 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 180..189 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 190..199 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 200..209 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 210..219 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 220..229 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 230..239 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 240..249 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp                                  /* 250..255 */
    };

    /* read() */
    {
        unsigned char const i = (unsigned char)fgetc(jp->inputStream);
        nextState[i](jp);
    }
}

static void s13_jp(JSONParser* const jp) {
    static ParseFunction nextState[256] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, s13_jp, /* 0..9 */
        s13_jp, s13_jp, s13_jp, s13_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 10..19 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 20..29 */
        err_jp, err_jp, s13_jp, err_jp, s15a_jp,err_jp, err_jp, err_jp, err_jp, err_jp, /* 30..39 */
        err_jp, err_jp, err_jp, s16_jp, err_jp, s16_jp, s16_jp, err_jp, s16_jp, s16_jp, /* 40..49 */
        s16_jp, s16_jp, s16_jp, s16_jp, s16_jp, s16_jp, s16_jp, s16_jp, err_jp, err_jp, /* 50..59 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 60..69 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 70..79 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 80..89 */
        err_jp, s02_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 90..99 */
        err_jp, err_jp, s18_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 100..109 */
        s14_jp, err_jp, err_jp, err_jp, err_jp, err_jp, s17_jp, err_jp, err_jp, err_jp, /* 110..119 */
        err_jp, err_jp, err_jp, s03_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 120..129 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 130..139 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 140..149 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 150..159 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 160..169 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 170..179 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 180..189 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 190..199 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 200..209 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 210..219 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 220..229 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 230..239 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 240..249 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp                                  /* 250..255 */
    };

    /* read() */
    {
        unsigned char const i = (unsigned char)fgetc(jp->inputStream);
        jp->str[0] = (char)i;
        nextState[i](jp);
    }
}

static void s14_jp(JSONParser* const jp) {
    static ParseFunction nextState[2] = { err_jp, s20_jp };

    char ull[3];

    /* atValueStart() */
    (*jp->atValueStart)(jp);

    /* atNull('ull') */
    (*jp->atNull)(jp);

    /* atValueEnd() */
    (*jp->atValueEnd)(jp);

    nextState[(fread(ull, 1, 3, jp->inputStream) == 3 && ull[0] == 'u' && ull[1] == 'l' && ull[2] == 'l')](jp);
}

static void s15a_jp(JSONParser* const jp) {
    /* atValueStart() */
    (*jp->atValueStart)(jp);

    /* len = 0 */
    jp->str_len = 0;

    s15b_jp(jp);
}
static void s15b_jp(JSONParser* const jp) {
    static ParseFunction nextState[256] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        err_jp, err_jp, err_jp, err_jp, err_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 0..9 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 10..19 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 20..29 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15d_jp,s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 30..39 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 40..49 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 50..59 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 60..69 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 70..79 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 80..89 */
        s15_jp, s15_jp, s15c_jp,s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 90..99 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 100..109 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 110..119 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 120..129 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 130..139 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 140..149 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 150..159 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 160..169 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 170..179 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 180..189 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 190..199 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 200..209 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 210..219 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 220..229 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 230..239 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, s15_jp,  /* 240..249 */
        s15_jp, s15_jp, s15_jp, s15_jp, s15_jp, err_jp                                   /* 250..255 */
    };

    /* str[len] = read() */
    {
        unsigned char const i = (unsigned char)(jp->str[jp->str_len] = (char)fgetc(jp->inputStream));
        nextState[i](jp);
    }
}
static void s15c_jp(JSONParser* const jp) {
    /* read() */
    fgetc(jp->inputStream);

    s15b_jp(jp);
}
static void s15d_jp(JSONParser* const jp) {
    /* str[len] = '\0' */
    jp->str[jp->str_len] = '\0';

    /* atString(str, len) */
    (*jp->atString)(jp, jp->str, jp->str_len);

    /* atValueEnd() */
    (*jp->atValueEnd)(jp);

    s20_jp(jp);
}
static void s15_jp(JSONParser* const jp) {
    /* len++ */
    jp->str_len++;

    if (jp->str_len == jp->str_cap) {
        size_t const new_cap = jp->str_cap << 1;
        if (new_cap >= SZSZ_MAX) {
            jp->errorCode = JSON_PARSER_STRING_ERROR;
            return;
        }
        jp->str_cap = new_cap;
        {
            char* new_str = realloc(jp->str, new_cap);
            if (new_str == NULL) {
                jp->errorCode = JSON_PARSER_MEMORY_ERROR;
                return;
            }
            jp->str = new_str;
        }
    }

    s15b_jp(jp);
}

static void s16_jp(JSONParser* const jp) {
    double num;

    /* atValueStart() */
    (*jp->atValueStart)(jp);

    /* unread() */
    UNREAD_JP(jp)

    /* atNumber(%lf) */
    if (fscanf(jp->inputStream, "%lf", &num) == 0) {
        jp->errorCode = JSON_PARSER_SYNTAX_ERROR;
        return;
    }
    (*jp->atNumber)(jp, num);

    /* atValueEnd() */
    (*jp->atValueEnd)(jp);

    s20_jp(jp);
}

static void s17_jp(JSONParser* const jp) {
    static ParseFunction nextState[2] = { err_jp, s20_jp };

    char rue[3];

    /* atValueStart() */
    (*jp->atValueStart)(jp);

    /* atTrue('rue') */
    (*jp->atTrue)(jp);

    /* atValueEnd() */
    (*jp->atValueEnd)(jp);

    nextState[(fread(rue, 1, 3, jp->inputStream) == 3 && rue[0] == 'r' && rue[1] == 'u' && rue[2] == 'e')](jp);
}

static void s18_jp(JSONParser* const jp) {
    static ParseFunction nextState[2] = { err_jp, s20_jp };

    char alse[4];

    /* atValueStart() */
    (*jp->atValueStart)(jp);

    /* atFalse('alse') */
    (*jp->atFalse)(jp);

    /* atValueEnd() */
    (*jp->atValueEnd)(jp);

    nextState[(
        fread(alse, 1, 4, jp->inputStream) == 4 &&
        alse[0] == 'a' && alse[1] == 'l'        &&
        alse[2] == 's' && alse[3] == 'e'
    )](jp);
}

static void s19_jp(JSONParser* const jp) {
    static ParseFunction nextState[256] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, s19_jp, /* 0..9 */
        s19_jp, s19_jp, s19_jp, s19_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 10..19 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 20..29 */
        err_jp, err_jp, s19_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 30..39 */
        err_jp, err_jp, err_jp, err_jp, s04_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 40..49 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 50..59 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 60..69 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 70..79 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 80..89 */
        err_jp, err_jp, err_jp, s21_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 90..99 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 100..109 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 110..119 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 120..129 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 130..139 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 140..149 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 150..159 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 160..169 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 170..179 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 180..189 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 190..199 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 200..209 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 210..219 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 220..229 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 230..239 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 240..249 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp                                  /* 250..255 */
    };

    /* read() */
    {
        unsigned char const i = (unsigned char)fgetc(jp->inputStream);
        nextState[i](jp);
    }
}

static void s20_jp(JSONParser* const jp) {
    static ParseFunction nextState[256] = {
      /*-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*
       |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |
       *-------*-------*-------*-------*-------*-------*-------*-------*-------*-------*/
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, s20_jp, /* 0..9 */
        s20_jp, s20_jp, s20_jp, s20_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 10..19 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 20..29 */
        err_jp, err_jp, s20_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 30..39 */
        err_jp, err_jp, err_jp, err_jp, s05_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 40..49 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 50..59 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 60..69 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 70..79 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 80..89 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 90..99 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 100..109 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 110..119 */
        err_jp, err_jp, err_jp, err_jp, err_jp, s22_jp, err_jp, err_jp, err_jp, err_jp, /* 120..129 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 130..139 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 140..149 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 150..159 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 160..169 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 170..179 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 180..189 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 190..199 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 200..209 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 210..219 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 220..229 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 230..239 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, err_jp, /* 240..249 */
        err_jp, err_jp, err_jp, err_jp, err_jp, err_jp                                  /* 250..255 */
    };

    /* read() */
    {
        unsigned char const i = (unsigned char)fgetc(jp->inputStream);
        nextState[i](jp);
    }
}

static void s21_jp(JSONParser* const jp) {
    /* pop() */
    POP_JP(jp);

    /* atArrayEnd() */
    (*jp->atArrayEnd)(jp);

    s23_jp(jp);
}

static void s22_jp(JSONParser* const jp) {
    /* pop() */
    POP_JP(jp);

    /* atObjectEnd() */
    (*jp->atObjectEnd)(jp);

    s23_jp(jp);
}

static void s23_jp(JSONParser* const jp) {
    static ParseFunction nextState[] = {
        [JSON_STACK_ARRAY]  = s19_jp,
        [JSON_STACK_OBJECT] = s20_jp,
        [JSON_STACK_END]    = s24_jp
    };

    /* peek() */
    {
        unsigned char const i = PEEK_JP(jp);
        nextState[i](jp);
    }
}

static void s24_jp(JSONParser* const jp) {
    /* pop() */
    POP_JP(jp);

    /* atRootEnd() */
    (*jp->atRootEnd)(jp);

    if (jp->stack_len != 0) jp->errorCode = JSON_PARSER_STACK_ERROR;
}


void construct_jsonp(void* const p_jsonParser, ...) {
    va_list args;
    va_start(args, p_jsonParser);
    vconstruct_jsonp(p_jsonParser, args);
    va_end(args);
}

void destruct_jsonp(void* const p_jsonParser) {
    JSONParser* const jsonParser = (JSONParser*)p_jsonParser;
    assert(isAllocated_jsonp(jsonParser));
    free(jsonParser->stack);
    free(jsonParser->str);
    *jsonParser = NOT_A_JSON_PARSER;
}

bool isAllocated_jsonp(void const* const p_jsonParser) {
    JSONParser const* const jsonParser = (JSONParser const*)p_jsonParser;

    if (jsonParser == NULL) {
        return 0;
    } else if (jsonParser->inputStream == NULL) {
        assert(jsonParser->stack == NULL);
        assert(jsonParser->str == NULL);
        return 0;
    } else {
        assert(jsonParser->stack != NULL);
        assert(jsonParser->str != NULL);
        return 1;
    }
}

bool isValid_jsonp(void const* const p_jsonParser) {
    JSONParser const* const jsonParser = (JSONParser const*)p_jsonParser;

    if (!isAllocated_jsonp(jsonParser))                 return 0;
    if (jsonParser->stack_cap == 0)                     return 0;
    if (jsonParser->stack_cap >= SZSZ_MAX)              return 0;
    if (jsonParser->stack_len > jsonParser->stack_cap) return 0;
    if (jsonParser->str_cap == 0)                       return 0;
    if (jsonParser->str_cap >= SZSZ_MAX)                return 0;
    return 1;
}

long parseStream_jsonp(JSONParser* const jsonParser) {
    if (!isValid_jsonp(jsonParser)) return JSON_PARSER_INVALID;

    jsonParser->errorCode = JSON_PARSER_OK;
    s00_jp(jsonParser);

    return jsonParser->errorCode;
}

void vconstruct_jsonp(void* const p_jsonParser, va_list args) {
    JSONParser* const jsonParser                    = (JSONParser*)p_jsonParser;
    FILE* const inputStream                         = va_arg(args, FILE*);
    JSONParserVoidEvent const eventAtArrayEnd       = va_arg(args, JSONParserVoidEvent);
    JSONParserVoidEvent const eventAtArrayStart     = va_arg(args, JSONParserVoidEvent);
    JSONParserVoidEvent const eventAtFalse          = va_arg(args, JSONParserVoidEvent);
    JSONParserVoidEvent const eventAtNameEnd        = va_arg(args, JSONParserVoidEvent);
    JSONParserVoidEvent const eventAtNameStart      = va_arg(args, JSONParserVoidEvent);
    JSONParserVoidEvent const eventAtNull           = va_arg(args, JSONParserVoidEvent);
    JSONParserNumberEvent const eventAtNumber       = va_arg(args, JSONParserNumberEvent);
    JSONParserVoidEvent const eventAtObjectEnd      = va_arg(args, JSONParserVoidEvent);
    JSONParserVoidEvent const eventAtObjectStart    = va_arg(args, JSONParserVoidEvent);
    JSONParserVoidEvent const eventAtRootEnd        = va_arg(args, JSONParserVoidEvent);
    JSONParserVoidEvent const eventAtRootStart      = va_arg(args, JSONParserVoidEvent);
    JSONParserStringEvent const eventAtString       = va_arg(args, JSONParserStringEvent);
    JSONParserVoidEvent const eventAtTrue           = va_arg(args, JSONParserVoidEvent);
    JSONParserVoidEvent const eventAtValueEnd       = va_arg(args, JSONParserVoidEvent);
    JSONParserVoidEvent const eventAtValueStart     = va_arg(args, JSONParserVoidEvent);

    assert(jsonParser != NULL);
    assert(inputStream != NULL);
    assert(!isAllocated_jsonp(p_jsonParser));

    jsonParser->inputStream     = inputStream;
    jsonParser->stack_cap       = JSON_PARSER_INITIAL_STACK_CAP;
    jsonParser->stack_len      = 0;
    jsonParser->stack           = mem_alloc(jsonParser->stack_cap);
    jsonParser->str_cap         = JSON_PARSER_INITIAL_STR_CAP;
    jsonParser->str             = mem_alloc(jsonParser->str_cap);
    jsonParser->errorCode       = JSON_PARSER_OK;
    jsonParser->atArrayEnd      =    eventAtArrayEnd == NULL ?   emptyVoidEvent_jsonp : eventAtArrayEnd;
    jsonParser->atArrayStart    =  eventAtArrayStart == NULL ?   emptyVoidEvent_jsonp : eventAtArrayStart;
    jsonParser->atFalse         =       eventAtFalse == NULL ?   emptyVoidEvent_jsonp : eventAtFalse;
    jsonParser->atNameEnd       =     eventAtNameEnd == NULL ?   emptyVoidEvent_jsonp : eventAtNameEnd;
    jsonParser->atNameStart     =   eventAtNameStart == NULL ?   emptyVoidEvent_jsonp : eventAtNameStart;
    jsonParser->atNull          =        eventAtNull == NULL ?   emptyVoidEvent_jsonp : eventAtNull;
    jsonParser->atNumber        =      eventAtNumber == NULL ? emptyNumberEvent_jsonp : eventAtNumber;
    jsonParser->atObjectEnd     =   eventAtObjectEnd == NULL ?   emptyVoidEvent_jsonp : eventAtObjectEnd;
    jsonParser->atObjectStart   = eventAtObjectStart == NULL ?   emptyVoidEvent_jsonp : eventAtObjectStart;
    jsonParser->atRootEnd       =     eventAtRootEnd == NULL ?   emptyVoidEvent_jsonp : eventAtRootEnd;
    jsonParser->atRootStart     =   eventAtRootStart == NULL ?   emptyVoidEvent_jsonp : eventAtRootStart;
    jsonParser->atString        =      eventAtString == NULL ? emptyStringEvent_jsonp : eventAtString;
    jsonParser->atTrue          =        eventAtTrue == NULL ?   emptyVoidEvent_jsonp : eventAtTrue;
    jsonParser->atValueEnd      =    eventAtValueEnd == NULL ?   emptyVoidEvent_jsonp : eventAtValueEnd;
    jsonParser->atValueStart    =  eventAtValueStart == NULL ?   emptyVoidEvent_jsonp : eventAtValueStart;
}
