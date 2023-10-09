/**
 * @file tests.c
 * @brief Tests the padkit library.
 * @author Yavuz Koroglu
 */
#include "padkit.h"

static void test_chunk_c(void) {
    Chunk chunk1[1] = { NOT_A_CHUNK };
    Chunk chunk2[1] = { NOT_A_CHUNK };

    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(chunk1, CHUNK_RECOMMENDED_PARAMETERS))

    DEBUG_ERROR_IF(add_chunk(chunk1, "abc", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk1, "abc", 3))

    DEBUG_ERROR_IF(add_chunk(chunk1, "def", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk1, "def", 3))

    for (uint32_t i = 0; i < chunk1->nStrings; i++) {
        char const* str = get_chunk(chunk1, i);
        DEBUG_ERROR_IF(str == NULL)
        printf("%s", str);
    }
    puts("");

    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(chunk2, CHUNK_RECOMMENDED_PARAMETERS))

    DEBUG_ERROR_IF(add_chunk(chunk2, "fed", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk2, "fed", 3))

    DEBUG_ERROR_IF(add_chunk(chunk2, "cba", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(chunk2, "cba", 3))

    for (uint32_t i = 0; i < chunk2->nStrings; i++) {
        char const* str = get_chunk(chunk2, i);
        DEBUG_ERROR_IF(str == NULL)
        printf("%s", str);
    }
    puts("");

    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS))

    DEBUG_ASSERT_NDEBUG_EXECUTE(concat_chunk(strings, chunk1))
    DEBUG_ASSERT_NDEBUG_EXECUTE(concat_chunk(strings, chunk2))

    DEBUG_ASSERT_NDEBUG_EXECUTE(free_chunk(chunk1))
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_chunk(chunk2))

    for (uint32_t i = 0; i < strings->nStrings; i++) {
        char const* str = get_chunk(strings, i);
        DEBUG_ERROR_IF(str == NULL)
        printf("%s", str);
    }
    puts("");

    free_strings();
}

int main(void) {
    DEBUG_EXECUTE(puts("DEBUG_MODE"))
    NDEBUG_EXECUTE(puts("RELEASE_MODE"))

    test_chunk_c();

    return 0;
}
