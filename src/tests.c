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

#include "tests/hash.c"
#include "tests/memalloc.c"
#include "tests/prime.c"
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
    puts("  PADKIT_TARGET = "PADKIT_TARGET);

    puts("");

    printf("%15"PRId16" = (int16_t)B2(B_11111111, B_11110110)\n", (int16_t)B2(B_11111111, B_11110110));

    puts("");

    printf(" INVALID_UINT32 = 0x%0*"PRIXMAX"\n", (2 * (int)sizeof(uintmax_t)), (uintmax_t)INVALID_UINT32);

    puts("");

    printf("       SZSZ_MAX = 0x%0*"PRIXMAX"\n", (2 * (int)sizeof(uintmax_t)), (uintmax_t)SZSZ_MAX);
    printf("       SZ32_MAX = 0x%0*"PRIXMAX"\n", (2 * (int)sizeof(uintmax_t)), (uintmax_t)SZ32_MAX);
    printf("       SZ64_MAX = 0x%0*"PRIXMAX"\n", (2 * (int)sizeof(uintmax_t)), (uintmax_t)SZ64_MAX);
    printf("  SZPTRDIFF_MAX = 0x%0*"PRIXMAX"\n", (2 * (int)sizeof(uintmax_t)), (uintmax_t)SZPTRDIFF_MAX);

    puts("");

    printf("         TS_FMT = \"%s\"\n", TS_FMT);
    printf("         TS_LEN = %"PRIXMAX"\n", (uintmax_t)TS_LEN);

    puts("");

    puts("src/tests.c");
    puts("-----------");
    test_hash();
    test_memalloc();
    test_prime();
    test_timestamp();

    puts("");

    return EXIT_SUCCESS;
}
