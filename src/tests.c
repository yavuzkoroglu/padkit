/**
 * @file tests.c
 * @brief Tests the padkit library.
 * @author Yavuz Koroglu
 */
#include "padkit.h"

#define TEST_FAIL_MESSAGE(trigger) \
    printf("FAIL => %s():%d, Trigger => "#trigger"\n", __func__, __LINE__)

#define TEST_PASS_MESSAGE \
    printf("PASS => %s():%d\n", __func__, __LINE__)

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
    TEST_FAIL_IF(!str_eq(getFirst_chunk(strings), getLast_chunk(strings)))
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

static void test_appendSpace_chunk(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS))

    DEBUG_ERROR_IF(appendSpace_chunk(strings, 131072) == NULL)
    NDEBUG_EXECUTE(appendSpace_chunk(strings, 131072))

    TEST_FAIL_IF(strings->len != 0)
    TEST_FAIL_IF(strings->nStrings != 0)
    TEST_PASS

    free_strings();
}

static void test_concat_chunk(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS))

    Chunk chunk[2][1] = { { NOT_A_CHUNK }, { NOT_A_CHUNK } };

    for (int i = 0; i < 2; i++) {
        DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(chunk[i], CHUNK_RECOMMENDED_PARAMETERS))
        DEBUG_ASSERT_NDEBUG_EXECUTE(concat_chunk(strings, chunk[i]))
    }

    DEBUG_ERROR_IF(add_chunk(chunk[0], "abc", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk[0], "abc", 3))

    DEBUG_ERROR_IF(add_chunk(chunk[1], "def", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk[1], "def", 3))

    for (int i = 0; i < 2; i++)
        DEBUG_ASSERT_NDEBUG_EXECUTE(concat_chunk(strings, chunk[i]))

    TEST_FAIL_IF(strings->len != 7)
    TEST_FAIL_IF(strings->nStrings != 2)
    TEST_PASS

    for (int i = 0; i < 2; i++)
        DEBUG_ASSERT_NDEBUG_EXECUTE(free_chunk(chunk[i]))
    free_strings();
}

static void test_delete_chunk(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS))

    DEBUG_ERROR_IF(add_chunk(strings, "abc", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(add_chunk(strings, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "", 0))

    DEBUG_ERROR_IF(add_chunk(strings, "def", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "def", 3))

    DEBUG_ASSERT_NDEBUG_EXECUTE(delete_chunk(strings, 1))
    DEBUG_ASSERT_NDEBUG_EXECUTE(delete_chunk(strings, 1))

    TEST_FAIL_IF(strings->len != 3)
    TEST_FAIL_IF(strings->nStrings != 1)
    TEST_PASS

    free_strings();
}

static void test_deleteLast_chunk(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS))

    DEBUG_ERROR_IF(add_chunk(strings, "abc", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(add_chunk(strings, "def", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "def", 3))

    DEBUG_ERROR_IF(add_chunk(strings, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "", 0))

    DEBUG_ASSERT_NDEBUG_EXECUTE(deleteLast_chunk(strings))

    TEST_FAIL_IF(strings->len != 7)
    TEST_FAIL_IF(strings->nStrings != 2)

    DEBUG_ASSERT_NDEBUG_EXECUTE(deleteLast_chunk(strings))
    DEBUG_ASSERT_NDEBUG_EXECUTE(deleteLast_chunk(strings))

    TEST_FAIL_IF(strings->len != 0)
    TEST_FAIL_IF(strings->start[0] != '\0')

    TEST_PASS

    free_strings();
}

static void test_fromStream_chunk(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS))

    FILE* const stream = fopen("src/tests.c", "r");
    DEBUG_ERROR_IF(stream == NULL)

    DEBUG_ERROR_IF(fromStream_chunk(strings, stream, NULL) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(fromStream_chunk(strings, stream, NULL))

    TEST_FAIL_IF(!STR_CONTAINS_CONST(getFirst_chunk(strings), "/""**"))
    TEST_FAIL_IF(!STR_EQ_CONST(getFirst_chunk(strings), "/""**"))
    TEST_PASS

    DEBUG_ERROR_IF(fclose(stream) == EOF)
    NDEBUG_EXECUTE(fclose(stream))

    free_strings();
}

static void test_strlen_chunk(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS))

    DEBUG_ERROR_IF(add_chunk(strings, "abc", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(add_chunk(strings, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "", 0))

    DEBUG_ERROR_IF(add_chunk(strings, "def", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "def", 3))

    TEST_FAIL_IF(strlen_chunk(strings, 1) != 0)
    TEST_FAIL_IF(strlen_chunk(strings, 2) != 3)
    TEST_PASS

    free_strings();
}

static void test_strlenLast_chunk(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS))

    DEBUG_ERROR_IF(add_chunk(strings, "abc", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(add_chunk(strings, "def", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "def", 3))

    DEBUG_ERROR_IF(add_chunk(strings, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "", 0))

    TEST_FAIL_IF(strlenLast_chunk(strings) != 0)
    TEST_PASS

    free_strings();
}

static void test_cset(void) {
    ChunkSet set[1] = { NOT_A_CHUNK_SET };

    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_cset(set, CHUNK_SET_RECOMMENDED_PARAMETERS))

    DEBUG_ERROR_IF(addKey_cset(set, "Apples", 6) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(addKey_cset(set, "Apples", 6))

    DEBUG_ERROR_IF(addKey_cset(set, "Apples", 6) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(addKey_cset(set, "Apples", 6))

    DEBUG_ERROR_IF(addKey_cset(set, "Oranges", 7) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(addKey_cset(set, "Oranges", 7))

    TEST_FAIL_IF(getKeyCount_cset(set) != 2)
    TEST_FAIL_IF(!STR_EQ_CONST(getKey_cset(set, 1), "Oranges"))
    TEST_FAIL_IF(getKeyId_cset(set, "Apples", 6) != 0)
    TEST_FAIL_IF(getKeyId_cset(set, "Pears", 5) != 0xFFFFFFFF)
    TEST_FAIL_IF(strlen_cset(set, 1) != 7)
    TEST_PASS

    DEBUG_ASSERT_NDEBUG_EXECUTE(flush_cset(set))
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_cset(set))
}

int main(void) {
    puts("");
    DEBUG_EXECUTE(puts("DEBUG_MODE => "__FILE__))
    NDEBUG_EXECUTE(puts("RELEASE_MODE => "__FILE__))

    puts("");
    puts("test_..._chunk()");
    puts("================");
    test_add_chunk();
    test_addIndex_chunk();
    test_append_chunk();
    test_appendIndex_chunk();
    test_appendSpace_chunk();
    test_concat_chunk();
    test_delete_chunk();
    test_deleteLast_chunk();
    test_fromStream_chunk();
    test_strlen_chunk();
    test_strlenLast_chunk();

    puts("");
    puts("test_..._chunkset()");
    puts("================");
    test_cset();

    puts("");
    return 0;
}
