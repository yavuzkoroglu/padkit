/**
 * @file tests.c
 * @brief Tests the padkit library.
 * @author Yavuz Koroglu
 */
#include "padkit.h"

static Chunk strings[1];

#define TEST_FAIL_MESSAGE(trigger) \
    printf("FAIL => %s():%d, Trigger => "#trigger"\n", __func__, __LINE__)

#define TEST_PASS_MESSAGE \
    printf("PASS => %s():%d\n", __func__, __LINE__)

#define TEST_FAIL_IF(condition) \
    if (condition) { TEST_FAIL_MESSAGE(#condition); return; }

#define TEST_PASS TEST_PASS_MESSAGE;

static void test_chunk_add(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS)
    )

    DEBUG_ERROR_IF(add_chunk(strings, "abc", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(add_chunk(strings, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "", 0))

    DEBUG_ERROR_IF(add_chunk(strings, "defg", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "defg", 3))

    TEST_FAIL_IF(strings->len != 8)
    TEST_FAIL_IF(strings->nStrings != 3)
    TEST_PASS

    DEBUG_ABORT_IF(!free_chunk(strings))
    NDEBUG_EXECUTE(free_chunk(strings))
}

static void test_chunk_addIndex(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS)
    )

    DEBUG_ERROR_IF(add_chunk(strings, "abc", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(addIndex_chunk(strings, 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(addIndex_chunk(strings, 0))

    TEST_FAIL_IF(strings->len != 7)
    TEST_FAIL_IF(strings->nStrings != 2)
    TEST_FAIL_IF(!str_eq(getFirst_chunk(strings), getLast_chunk(strings)))
    TEST_PASS

    DEBUG_ABORT_IF(!free_chunk(strings))
    NDEBUG_EXECUTE(free_chunk(strings))
}

static void test_chunk_addRandomUUID(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS)
    )

    DEBUG_ERROR_IF(addRandomUUID_chunk(strings, 1) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(addRandomUUID_chunk(strings, 1))

    TEST_FAIL_IF(strings->len != 37)
    TEST_FAIL_IF(strings->nStrings != 1)
    TEST_PASS

    DEBUG_ABORT_IF(!free_chunk(strings))
    NDEBUG_EXECUTE(free_chunk(strings))
}

static void test_chunk_append(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS)
    )

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

    DEBUG_ABORT_IF(!free_chunk(strings))
    NDEBUG_EXECUTE(free_chunk(strings))
}

static void test_chunk_appendIndex(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS)
    )

    DEBUG_ERROR_IF(append_chunk(strings, "abc", 3) == NULL)
    NDEBUG_EXECUTE(append_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(appendIndex_chunk(strings, 0) == NULL)
    NDEBUG_EXECUTE(appendIndex_chunk(strings, 0))

    TEST_FAIL_IF(strings->len != 6)
    TEST_FAIL_IF(strings->nStrings != 1)
    TEST_FAIL_IF(!STR_EQ_CONST(strings->start, "abcabc"))
    TEST_PASS

    DEBUG_ABORT_IF(!free_chunk(strings))
    NDEBUG_EXECUTE(free_chunk(strings))
}

static void test_chunk_appendSpace(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS)
    )

    DEBUG_ERROR_IF(appendSpace_chunk(strings, 131072) == NULL)
    NDEBUG_EXECUTE(appendSpace_chunk(strings, 131072))

    TEST_FAIL_IF(strings->len != 0)
    TEST_FAIL_IF(strings->nStrings != 0)
    TEST_PASS

    DEBUG_ABORT_IF(!free_chunk(strings))
    NDEBUG_EXECUTE(free_chunk(strings))
}

static void test_chunk_concat(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS)
    )

    Chunk chunk[2][1] = { { NOT_A_CHUNK }, { NOT_A_CHUNK } };

    for (int i = 0; i < 2; i++) {
        DEBUG_ASSERT_NDEBUG_EXECUTE(
            constructEmpty_chunk(chunk[i], CHUNK_RECOMMENDED_PARAMETERS)
        )
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

    DEBUG_ABORT_IF(!free_chunk(strings))
    NDEBUG_EXECUTE(free_chunk(strings))
}

static void test_chunk_delete(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS)
    )

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

    DEBUG_ABORT_IF(!free_chunk(strings))
    NDEBUG_EXECUTE(free_chunk(strings))
}

static void test_chunk_deleteLast(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS)
    )

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

    DEBUG_ABORT_IF(!free_chunk(strings))
    NDEBUG_EXECUTE(free_chunk(strings))
}

static void test_chunk_fromStream(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS)
    )

    FILE* const stream = fopen("src/tests.c", "r");
    DEBUG_ERROR_IF(stream == NULL)

    DEBUG_ERROR_IF(fromStream_chunk(strings, stream, NULL) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(fromStream_chunk(strings, stream, NULL))

    TEST_FAIL_IF(!STR_CONTAINS_CONST(getFirst_chunk(strings), "/""**"))
    TEST_FAIL_IF(!STR_EQ_CONST(getFirst_chunk(strings), "/""**"))
    TEST_PASS

    DEBUG_ERROR_IF(fclose(stream) == EOF)
    NDEBUG_EXECUTE(fclose(stream))

    DEBUG_ABORT_IF(!free_chunk(strings))
    NDEBUG_EXECUTE(free_chunk(strings))
}

static void test_chunk_strlen(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS)
    )

    DEBUG_ERROR_IF(add_chunk(strings, "abc", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(add_chunk(strings, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "", 0))

    DEBUG_ERROR_IF(add_chunk(strings, "def", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "def", 3))

    TEST_FAIL_IF(strlen_chunk(strings, 1) != 0)
    TEST_FAIL_IF(strlen_chunk(strings, 2) != 3)
    TEST_PASS

    DEBUG_ABORT_IF(!free_chunk(strings))
    NDEBUG_EXECUTE(free_chunk(strings))
}

static void test_chunk_strlenLast(void) {
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS)
    )

    DEBUG_ERROR_IF(add_chunk(strings, "abc", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "abc", 3))

    DEBUG_ERROR_IF(add_chunk(strings, "def", 3) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "def", 3))

    DEBUG_ERROR_IF(add_chunk(strings, "", 0) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(add_chunk(strings, "", 0))

    TEST_FAIL_IF(strlenLast_chunk(strings) != 0)
    TEST_PASS

    DEBUG_ABORT_IF(!free_chunk(strings))
    NDEBUG_EXECUTE(free_chunk(strings))
}

static void test_cset(void) {
    ChunkSet set[1] = { NOT_A_CHUNK_SET };

    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_cset(set, CHUNK_SET_RECOMMENDED_PARAMETERS)
    )

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

#define ALICE 0
#define HARRY 1
#define LENNY 2
#define WENDY 3
static void test_ctbl(void) {
    unsigned const age[] = { [ALICE]=12, [HARRY]=33, [LENNY]=3, [WENDY]=24 };
    #define PEOPLE_COUNT sizeof(age) / sizeof(unsigned)

    unsigned const score[][PEOPLE_COUNT] =
        {
            { [ALICE]=135, [HARRY]=124, [LENNY]=165, [WENDY]=122 },
            { [ALICE]=132, [HARRY]=128, [LENNY]=85, [WENDY]=122 }
        };
    #define EXAM_COUNT sizeof(score) / sizeof(score[0])

    char const* const name[PEOPLE_COUNT] =
        { [ALICE]="Alice", [HARRY]="Harry", [LENNY]="Lenny", [WENDY]="Wendy" };

    uint32_t person_id[PEOPLE_COUNT];

    Chunk people[1] = { NOT_A_CHUNK };
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_chunk(people, CHUNK_RECOMMENDED_PARAMETERS)
    )

    ChunkTable ages[1] = { NOT_A_CHUNK_TABLE };
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_ctbl(ages, CHUNK_TABLE_RECOMMENDED_PARAMETERS)
    )

    ChunkTable scores[1] = { NOT_A_CHUNK_TABLE };
    DEBUG_ASSERT_NDEBUG_EXECUTE(
        constructEmpty_ctbl(scores, CHUNK_TABLE_RECOMMENDED_PARAMETERS)
    )

    for (unsigned person = ALICE; person < PEOPLE_COUNT; person++) {
        person_id[person] = add_chunk(people, name[person], 5);
        DEBUG_ERROR_IF(person_id[person] != person)
    }

    switch (
        insert_ctbl(
            ages, people,
            ALICE, 725,
            CTBL_BEHAVIOR_UNIQUE
        )
    ) {
        case CTBL_INSERT_OK:
            break;
        #ifndef NDEBUG
        case CTBL_INSERT_ERROR:
            TEST_FAIL_MESSAGE(insert_ctbl);
            goto END_TEST_CTBL;
        #endif
        case CTBL_INSERT_DUPLICATE_KEY:
        default:
            TEST_FAIL_MESSAGE(insert_ctbl);
            goto END_TEST_CTBL;
    }

    switch (
        insert_ctbl(
            ages, people,
            ALICE, age[ALICE],
            CTBL_BEHAVIOR_REPLACE
        )
    ) {
        case CTBL_INSERT_DUPLICATE_KEY:
        case CTBL_INSERT_OK:
            break;
        #ifndef NDEBUG
        case CTBL_INSERT_ERROR:
        #endif
        default:
            TEST_FAIL_MESSAGE(insert_ctbl);
            goto END_TEST_CTBL;
    }

    for (unsigned person = HARRY; person < PEOPLE_COUNT; person++) {
        switch (
            insert_ctbl(
                ages, people,
                person, age[person],
                CTBL_BEHAVIOR_UNIQUE
            )
        ) {
            case CTBL_INSERT_OK:
                break;
            #ifndef NDEBUG
            case CTBL_INSERT_ERROR:
            #endif
            case CTBL_INSERT_DUPLICATE_KEY:
            default:
                TEST_FAIL_MESSAGE(insert_ctbl);
                goto END_TEST_CTBL;
        }
    }

    for (unsigned exam = 0; exam < EXAM_COUNT; exam++) {
        for (unsigned person = ALICE; person < PEOPLE_COUNT; person++) {
            #ifndef NDEBUG
                switch (
                    insert_ctbl(
                        scores, people, person,
                        score[exam][person],
                        CTBL_BEHAVIOR_MULTIPLE
                    )
                ) {
                    case CTBL_INSERT_DUPLICATE_ENTRY:
                    case CTBL_INSERT_OK:
                        break;
                    case CTBL_INSERT_ERROR:
                    default:
                        TEST_FAIL_MESSAGE(insert_ctbl);
                }
            #else
                insert_ctbl(
                    scores, people,
                    person, score[exam][person],
                    CTBL_BEHAVIOR_MULTIPLE
                );
            #endif
        }
    }

    TEST_FAIL_IF(getKeyCount_ctbl(ages) != PEOPLE_COUNT)
    TEST_FAIL_IF(getKeyCount_ctbl(scores) != PEOPLE_COUNT)

    TEST_FAIL_IF(getEntryCount_ctbl(ages) != PEOPLE_COUNT)
    TEST_FAIL_IF(getEntryCount_ctbl(scores) != PEOPLE_COUNT * EXAM_COUNT - 1)

    TEST_FAIL_IF(get_ctbl(ages, people, "Alice", 5) == NULL)
    TEST_FAIL_IF(get_ctbl(scores, people, "Luke", 4) != NULL)
    TEST_FAIL_IF(getExact_ctbl(scores, people, "Wendy", 5, 122) == NULL)
    TEST_FAIL_IF(getExact_ctbl(ages, people, "Alice", 5, 1) != NULL)

    TEST_PASS

END_TEST_CTBL:
    DEBUG_ASSERT_NDEBUG_EXECUTE(flush_ctbl(ages))
    DEBUG_ASSERT_NDEBUG_EXECUTE(flush_ctbl(scores))
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_ctbl(ages))
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_ctbl(scores))
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_chunk(people))

    #undef EXAM_COUNT
    #undef PEOPLE_COUNT
}
#undef ALICE
#undef HARRY
#undef LENNY
#undef WENDY

static void test_gmtx(void) {
    GraphMatrix gmtx[1] = { NOT_A_GRAPH_MATRIX };
    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_gmtx(gmtx, 3, 3))

    DEBUG_ASSERT_NDEBUG_EXECUTE(connectAll_gmtx(gmtx))

    DEBUG_ASSERT_NDEBUG_EXECUTE(resizeIfNecessary_gmtx(gmtx, 4, 4))

    for (unsigned i = 0; i < 4; i++) {
        if (isConnected_gmtx(gmtx, i, i)) {
            DEBUG_ASSERT_NDEBUG_EXECUTE(disconnect_gmtx(gmtx, i, i))
        } else {
            DEBUG_ASSERT_NDEBUG_EXECUTE(connect_gmtx(gmtx, i, i))
        }
    }

    TEST_FAIL_IF(findSink_gmtx(gmtx, 3, 3) != 3)
    TEST_FAIL_IF(findSource_gmtx(gmtx, 3, 3) != 3)
    TEST_FAIL_IF(findSink_gmtx(gmtx, 0, 3) != 2)
    TEST_FAIL_IF(findSource_gmtx(gmtx, 2, 3) != 1)

    TEST_PASS

    DEBUG_ASSERT_NDEBUG_EXECUTE(disconnectAll_gmtx(gmtx))
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_gmtx(gmtx))
}

static unsigned test_jsonp_objCount = 0;
static void test_jsonp_countObjects(JSONParser* const jp) {
    test_jsonp_objCount++;
}
static void test_jsonp(void) {
    JSONParser jp[1];
    char const* const filename = "test_artifacts/model002.json";
    FILE* const fp = fopen(filename, "r");
    TEST_FAIL_IF(fp == NULL)

    DEBUG_ASSERT_NDEBUG_EXECUTE(construct_jsonp(jp, fp, JSON_PARSER_DEFAULT_EVENTS))
    jp->atObjectStart = test_jsonp_countObjects;

    TEST_FAIL_IF(parseStream_jsonp(jp) != JSON_PARSER_OK)

    TEST_FAIL_IF(test_jsonp_objCount != 27)
    TEST_PASS

    DEBUG_ASSERT_NDEBUG_EXECUTE(free_jsonp(jp))
    DEBUG_ASSERT(fclose(fp) == 0)
    NDEBUG_EXECUTE(fclose(fp))
}

#define ALISON 0
#define ARNOLD 1
#define JAKE   2
#define JANE   3
static void test_map(void) {
    static unsigned const relations[][2] =
        { { ALISON, JAKE }, { ARNOLD, JAKE } };

    #define RELATIONS_COUNT (sizeof(relations) / sizeof(relations[0]))

    Map colleagues[1] = { NOT_A_MAP };
    DEBUG_ASSERT_NDEBUG_EXECUTE(constructEmpty_map(colleagues, BUFSIZ))

    for (unsigned i = 0; i < RELATIONS_COUNT; i++) {
        DEBUG_ASSERT_NDEBUG_EXECUTE(
            insert_map(colleagues, relations[i][0], VAL_UNSIGNED(relations[i][1]))
        )
        DEBUG_ASSERT_NDEBUG_EXECUTE(
            insert_map(colleagues, relations[i][1], VAL_UNSIGNED(relations[i][0]))
        )
    }

    DEBUG_ASSERT_NDEBUG_EXECUTE(
        insert_map(colleagues, JANE, VAL_UNSIGNED(JANE))
    )
    DEBUG_ASSERT_NDEBUG_EXECUTE(deleteLast_map(colleagues))

    TEST_FAIL_IF(colleagues->size != 4)
    TEST_FAIL_IF(
        binarySearchLeftmostKey_map(colleagues, ALISON) != ALISON
    )
    TEST_FAIL_IF(
        binarySearchLeftmostKey_map(colleagues, JANE) != colleagues->size
    )
    TEST_FAIL_IF(
        binarySearchRightmostKey_map(colleagues, ARNOLD) != ARNOLD
    )
    TEST_FAIL_IF(
        binarySearchRightmostKey_map(colleagues, JANE) != colleagues->size - 1
    )
    TEST_FAIL_IF(
        linearSearchBackward_map(
            colleagues, colleagues->size - 1,
            JAKE, VAL_UNSIGNED(ALISON)
        ) != 2
    )
    TEST_FAIL_IF(
        linearSearchBackward_map(
            colleagues, colleagues->size - 1,
            JANE, VAL_UNSIGNED(ALISON)
        ) != colleagues->size - 1
    )
    TEST_FAIL_IF(
        linearSearchBackwardKey_map(
            colleagues, colleagues->size - 1,
            JAKE
        ) != 3
    )
    TEST_FAIL_IF(
        linearSearchBackwardKey_map(
            colleagues, colleagues->size - 1,
            JANE
        ) != colleagues->size - 1
    )
    TEST_FAIL_IF(
        linearSearchBackwardValue_map(
            colleagues, colleagues->size - 1,
            VAL_UNSIGNED(ARNOLD)
        ) != 3
    )
    TEST_FAIL_IF(
        linearSearchBackwardValue_map(
            colleagues, colleagues->size - 1,
            VAL_UNSIGNED(JANE)
        ) != 0xFFFFFFFF
    )
    TEST_FAIL_IF(
        linearSearchForward_map(
            colleagues, 0,
            JAKE, VAL_UNSIGNED(ALISON)
        ) != 2
    )
    TEST_FAIL_IF(
        linearSearchForward_map(
            colleagues, 0,
            JANE, VAL_UNSIGNED(ALISON)
        ) != colleagues->size
    )
    TEST_FAIL_IF(
        linearSearchForwardKey_map(
            colleagues, 0,
            JAKE
        ) != 2
    )
    TEST_FAIL_IF(
        linearSearchForwardKey_map(
            colleagues, 0,
            JANE
        ) != colleagues->size
    )
    TEST_FAIL_IF(
        linearSearchForwardValue_map(
            colleagues, 0,
            VAL_UNSIGNED(ARNOLD)
        ) != 3
    )
    TEST_FAIL_IF(
        linearSearchForwardValue_map(
            colleagues, 0,
            VAL_UNSIGNED(JANE)
        ) != colleagues->size
    )

    TEST_PASS

    DEBUG_ASSERT_NDEBUG_EXECUTE(flush_map(colleagues))
    DEBUG_ASSERT_NDEBUG_EXECUTE(free_map(colleagues))

    #undef RELATIONS_COUNT
    #undef PEOPLE_COUNT
}

static void test_reallocate(void) {
    #define OLD_SIZE 1024
    #define NEW_SIZE 131072

    char* buffer = malloc(OLD_SIZE);
    DEBUG_ERROR_IF(buffer == NULL)

    char* const new_buffer =
        reallocate((void**)(&buffer), OLD_SIZE, NEW_SIZE, 1);

    DEBUG_ERROR_IF(new_buffer == NULL)

    TEST_FAIL_IF(new_buffer != buffer)

    TEST_PASS

    free(buffer);
    #undef OLD_SIZE
    #undef NEW_SIZE
}

static void test_reallocate_recalloc(void) {
    #define OLD_SIZE 1024
    #define NEW_SIZE 131072

    char* buffer = calloc(1024, 1);
    DEBUG_ERROR_IF(buffer == NULL)

    char* const new_buffer =
        recalloc((void**)(&buffer), OLD_SIZE, NEW_SIZE, 1);

    DEBUG_ERROR_IF(new_buffer == NULL)

    TEST_FAIL_IF(new_buffer != buffer)
    for (unsigned i = 0; i < NEW_SIZE; i++)
        TEST_FAIL_IF(new_buffer[i] != '\0')

    TEST_PASS

    free(buffer);
    #undef OLD_SIZE
    #undef NEW_SIZE
}

static void test_streq_mem_eq_n(void) {
    static char const* str[] = { "abc", "", "bca", "cab", "abc", "?" };
    static unsigned const len[] = { 3, 0, 3, 3, 3, 1 };

    #define STRING_COUNT (sizeof(str) / sizeof(char*))

    unsigned eq_count = 0;
    for (unsigned i = 0; i < STRING_COUNT - 1; i++)
        for (unsigned j = i + 1; j < STRING_COUNT; j++)
            eq_count += mem_eq_n(str[i], str[j], len[i] + 1);

    TEST_FAIL_IF(eq_count != 1)
    TEST_PASS

    #undef STRING_COUNT
}

static void test_streq_str_eq_n(void) {
    static char const* str[] = { "abc", "..", "bca", "cab", "abc", "..\n" };
    static unsigned const len[] = { 3, 2, 3, 3, 3, 3 };

    #define STRING_COUNT (sizeof(str) / sizeof(char*))

    unsigned eq_count = 0;
    for (unsigned i = 0; i < STRING_COUNT - 1; i++)
        for (unsigned j = i + 1; j < STRING_COUNT; j++)
            eq_count += str_eq_n(str[i], str[j], len[i]);

    TEST_FAIL_IF(eq_count != 2)
    TEST_PASS

    #undef STRING_COUNT
}

static void test_streq_str_eq(void) {
    static char const* str[] = { "abc", "", "bca", "cab", "abc", "?" };

    #define STRING_COUNT (sizeof(str) / sizeof(char*))

    unsigned eq_count = 0;
    for (unsigned i = 0; i < STRING_COUNT - 1; i++)
        for (unsigned j = i + 1; j < STRING_COUNT; j++)
            eq_count += str_eq(str[i], str[j]);

    TEST_FAIL_IF(eq_count != 1)
    TEST_PASS

    #undef STRING_COUNT
}

#define ONIONS  0
#define SPINACH 1
static void test_streq_strcmp_as_comparator(void) {
    static char const* const vegetables[] =
        { "Broccoli", "Cabbages", "Carrots", "Onions", "Tomatoes" };

    #define VEGETABLE_COUNT (sizeof(vegetables) / sizeof(char*))

    static char const* const searched_key[] =
        { "Onions", "Spinach" };

    #define SEARCH_COUNT (sizeof(searched_key) / sizeof(char*))

    for (unsigned i = 0; i < SEARCH_COUNT; i++) {
        char const* const* const match =
            bsearch(
                searched_key[i], vegetables,
                VEGETABLE_COUNT, sizeof(char*),
                strcmp_as_comparator
            );

        switch (i) {
            case ONIONS:
                TEST_FAIL_IF(match == NULL)
                break;
            case SPINACH:
                TEST_FAIL_IF(match != NULL)
        }
    }

    TEST_PASS

    #undef VEGETABLE_COUNT
    #undef SEARCH_COUNT
}
#undef ONIONS
#undef SPINACH

static void test_timestamp_get(void) {
    char const* timestamp = get_timestamp();

    TEST_FAIL_IF(strlen(timestamp) != 19)
    TEST_PASS
}

static void test_val_areEqual(void) {
    Value value[] =
        { VAL_UNSIGNED(0), VAL_UNSIGNED(12), VAL_FLOAT(0.0f), VAL_INT(12) };

    #define VALUE_COUNT (sizeof(value) / sizeof(Value))

    unsigned eq_count = 0;
    for (unsigned i = 0; i < VALUE_COUNT; i++) {
        for (unsigned j = 0; j < VALUE_COUNT; j++) {
            DEBUG_ASSERT(isValid_val(value[j]))
            eq_count += areEqual_val(value[i], value[j]);
        }
    }

    TEST_FAIL_IF(eq_count != 4)
    TEST_PASS

    #undef VALUE_COUNT
}

int main(void) {
    puts("");
    DEBUG_EXECUTE(puts("DEBUG_MODE => "__FILE__))
    NDEBUG_EXECUTE(puts("RELEASE_MODE => "__FILE__))

    test_chunk_add();
    test_chunk_addIndex();
    test_chunk_addRandomUUID();
    test_chunk_append();
    test_chunk_appendIndex();
    test_chunk_appendSpace();
    test_chunk_concat();
    test_chunk_delete();
    test_chunk_deleteLast();
    test_chunk_fromStream();
    test_chunk_strlen();
    test_chunk_strlenLast();
    test_cset();
    test_ctbl();
    test_gmtx();
    test_jsonp();
    test_map();
    test_reallocate();
    test_reallocate_recalloc();
    test_streq_mem_eq_n();
    test_streq_str_eq_n();
    test_streq_str_eq();
    test_streq_strcmp_as_comparator();
    test_timestamp_get();
    test_val_areEqual();

    puts("");
    return 0;
}
