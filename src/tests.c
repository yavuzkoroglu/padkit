#include <inttypes.h>
#include <string.h>
#include "padkit.h"

#define TEST_FAIL(trigger) TEST_FAIL_MESSAGE(trigger) return 0;
#define TEST_PASS return 1;

#define TEST_FAIL_MESSAGE(trigger)  \
    printf("FAIL => %s::%s():%d, Trigger => "#trigger"\n", __FILE__, __func__, __LINE__);

#define TESTS_PASS_MESSAGE          \
    printf("PASS => %s\n", __FILE__);

#define TEST_FAIL_IF(condition)     \
    if (condition) { TEST_FAIL(condition) }

#include "tests/arraylist.c"
#include "tests/bitmatrix.c"
// #include "tests/chunk.c"
#include "tests/graphmatrix.c"
#include "tests/hash.c"
// #include "tests/indextable.c"
#include "tests/item.c"
#include "tests/jsonparser.c"
#include "tests/memalloc.c"
#include "tests/overlap.c"
#include "tests/prime.c"
// #include "tests/stack.c"
#include "tests/timestamp.c"

int main(void) {
    puts("");

    #ifndef NDEBUG
        puts(" NDEBUG is NOT defined");
    #else
        puts(" NDEBUG is defined");
    #endif

    puts("");

    puts(" PADKIT_VERSION = "PADKIT_VERSION);
    puts(" PADKIT_TARGET = "PADKIT_TARGET);

    puts("");

    printf(" (int16_t)B2(B(11111111), B(11110110)) = %"PRIi16"\n", (int16_t)B2(B(11111111), B(11110110)));

    puts("");

    printf(" INVALID_UINT32 = 0x%0*"PRIXMAX"\n", (2 * (int)sizeof(uintmax_t)), (uintmax_t)INVALID_UINT32);

    puts("");

    printf(" SZSZ_MAX = 0x%0*"PRIXMAX"\n", (2 * (int)sizeof(uintmax_t)), (uintmax_t)SZSZ_MAX);
    printf(" SZ32_MAX = 0x%0*"PRIXMAX"\n", (2 * (int)sizeof(uintmax_t)), (uintmax_t)SZ32_MAX);
    printf(" SZ64_MAX = 0x%0*"PRIXMAX"\n", (2 * (int)sizeof(uintmax_t)), (uintmax_t)SZ64_MAX);
    printf(" SZPTRDIFF_MAX = 0x%0*"PRIXMAX"\n", (2 * (int)sizeof(uintmax_t)), (uintmax_t)SZPTRDIFF_MAX);

    puts("");

    printf(" TS_FMT = \"%s\"\n", TS_FMT);
    printf(" TS_LEN = %"PRIuMAX"\n", (uintmax_t)TS_LEN);

    puts("");

    printf(" ALIST_RECOMMENDED_INITIAL_CAP = %"PRIuMAX"\n", (uintmax_t)ALIST_RECOMMENDED_INITIAL_CAP);
    /*
    printf(" ITBL_RECOMMENDED_MAX_PERCENT_LOAD = %"PRIuMAX"\n", (uintmax_t)ITBL_RECOMMENDED_MAX_PERCENT_LOAD);
    printf(" ITBL_RECOMMENDED_MIN_HEIGHT = %"PRIuMAX"\n", (uintmax_t)ITBL_RECOMMENDED_MIN_HEIGHT);
    */

    puts("");

    puts("src/tests.c");
    puts("-----------");
    test_arraylist();
    test_bitmatrix();
    // test_chunk();
    test_graphmatrix();
    test_hash();
    // test_indextable();
    test_item();
    test_jsonparser();
    test_memalloc();
    test_overlap();
    test_prime();
    // test_stack();
    test_timestamp();

    puts("");

    return EXIT_SUCCESS;
}
