/**
 * @file tests.c
 * @brief Tests the padkit library.
 * @author Yavuz Koroglu
 */
#include <inttypes.h>
#include "padkit.h"

#define TEST_FAIL_MESSAGE(trigger) \
    printf("FAIL => %s::%s():%d, Trigger => "#trigger"\n", __FILE__, __func__, __LINE__)

#define TEST_PASS_MESSAGE \
    printf("PASS => %s::%s():%d\n", __FILE__, __func__, __LINE__)

#define TEST_FAIL_IF(condition) \
    if (condition) {TEST_FAIL_MESSAGE(#condition); exit(EXIT_FAILURE);}

#define TEST_PASS TEST_PASS_MESSAGE;

static void test_add_chunk(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS))

    DEBUG_ERROR_IF(add_chunk(strings, "abc", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(add_chunk(strings, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "", 0))

    DEBUG_ERROR_IF(add_chunk(strings, "defg", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "defg", 3))

    TEST_FAIL_IF(strings->len != 8)
    TEST_FAIL_IF(strings->nStrings != 3)
    TEST_PASS

    free_strings();
}

static void test_addIndex_chunk(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS))

    DEBUG_ERROR_IF(add_chunk(strings, "abc", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(addIndex_chunk(strings, 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(addIndex_chunk(strings, 0))

    TEST_FAIL_IF(strings->len != 7)
    TEST_FAIL_IF(strings->nStrings != 2)
    TEST_FAIL_IF(!str_eq(get_chunk(strings, 0), getLast_chunk(strings)))
    TEST_PASS

    free_strings();
}

static void test_append_chunk(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS))

    DEBUG_ERROR_IF(append_chunk(strings, "abc", 3) == NULL)
    NDEBUG_EXECUTE(append_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(append_chunk(strings, "", 0) == NULL)
    NDEBUG_EXECUTE(append_chunk(strings, "", 0))

    DEBUG_ERROR_IF(append_chunk(strings, "defg", 3) == NULL)
    NDEBUG_EXECUTE(append_chunk(strings, "defg", 3))

    TEST_FAIL_IF(strings->len != 6)
    TEST_FAIL_IF(strings->nStrings != 1)
    TEST_FAIL_IF(!STR_EQ_CONST(strings->start, "abcdef"))
    TEST_PASS

    free_strings();
}

static void test_appendIndex_chunk(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS))

    DEBUG_ERROR_IF(append_chunk(strings, "abc", 3) == NULL)
    NDEBUG_EXECUTE(append_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(appendIndex_chunk(strings, 0) == NULL)
    NDEBUG_EXECUTE(appendIndex_chunk(strings, 0))

    TEST_FAIL_IF(strings->len != 6)
    TEST_FAIL_IF(strings->nStrings != 1)
    TEST_FAIL_IF(!STR_EQ_CONST(strings->start, "abcabc"))
    TEST_PASS

    free_strings();
}

int main(void) {
    DEBUG_EXECUTE(puts("DEBUG_MODE"))
    NDEBUG_EXECUTE(puts("RELEASE_MODE"))

    test_add_chunk();
    test_addIndex_chunk();
    test_append_chunk();
    test_appendIndex_chunk();

    return 0;
}
