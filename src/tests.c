/**
 * @file tests.c
 * @brief Tests the padkit library.
 * @author Yavuz Koroglu
 */
#include <string.h>
#include "padkit.h"

/*
static Chunk strings[1];
*/

#define TEST_FAIL_MESSAGE(trigger) \
    printf("FAIL => %s():%d, Trigger => "#trigger"\n", __func__, __LINE__)

#define TEST_PASS_MESSAGE \
    printf("PASS => %s():%d\n", __func__, __LINE__)

#define TEST_FAIL_IF(condition) \
    if (condition) { TEST_FAIL_MESSAGE(#condition); return; }

#define TEST_PASS TEST_PASS_MESSAGE;

/*
static void test_chunk_add(void) {
    constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS);

    add_chunk(strings, "abc", 3);
    add_chunk(strings, "", 0);
    add_chunk(strings, "defg", 3);

    TEST_FAIL_IF(strings->len != 8)
    TEST_FAIL_IF(strings->nStrings != 3)
    TEST_PASS

    free_chunk(strings);
}

static void test_chunk_addIndex(void) {
    constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS);

    add_chunk(strings, "abc", 3);
    addIndex_chunk(strings, 0);

    TEST_FAIL_IF(strings->len != 7)
    TEST_FAIL_IF(strings->nStrings != 2)
    TEST_FAIL_IF(!str_eq(getFirst_chunk(strings), getLast_chunk(strings)))
    TEST_PASS

    free_chunk(strings);
}

static void test_chunk_append(void) {
    constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS);

    append_chunk(strings, "abc", 3);
    append_chunk(strings, "", 0);
    append_chunk(strings, "defg", 3);

    TEST_FAIL_IF(strings->len != 6)
    TEST_FAIL_IF(strings->nStrings != 1)
    TEST_FAIL_IF(!STR_EQ_CONST(strings->start, "abcdef"))
    TEST_PASS

    free_chunk(strings);
}

static void test_chunk_appendIndex(void) {
    constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS);

    append_chunk(strings, "abc", 3);
    appendIndex_chunk(strings, 0);

    TEST_FAIL_IF(strings->len != 6)
    TEST_FAIL_IF(strings->nStrings != 1)
    TEST_FAIL_IF(!STR_EQ_CONST(strings->start, "abcabc"))
    TEST_PASS

    free_chunk(strings);
}

static void test_chunk_appendSpace(void) {
    constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS);

    appendSpace_chunk(strings, 131072);

    TEST_FAIL_IF(strings->len != 0)
    TEST_FAIL_IF(strings->nStrings != 0)
    TEST_PASS

    free_chunk(strings);
}

static void test_chunk_concat(void) {
    Chunk chunk[2][1] = { { NOT_A_CHUNK }, { NOT_A_CHUNK } };

    constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS);

    for (int i = 0; i < 2; i++) {
        constructEmpty_chunk(chunk[i], CHUNK_RECOMMENDED_PARAMETERS);
        concat_chunk(strings, chunk[i]);
    }

    add_chunk(chunk[0], "abc", 3);
    add_chunk(chunk[1], "def", 3);

    for (int i = 0; i < 2; i++)
        concat_chunk(strings, chunk[i]);

    TEST_FAIL_IF(strings->len != 7)
    TEST_FAIL_IF(strings->nStrings != 2)
    TEST_PASS

    for (int i = 0; i < 2; i++)
        free_chunk(chunk[i]);

    free_chunk(strings);
}

static void test_chunk_delete(void) {
    constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS);

    add_chunk(strings, "abc", 3);
    add_chunk(strings, "", 0);
    add_chunk(strings, "def", 3);

    delete_chunk(strings, 1);
    delete_chunk(strings, 1);

    TEST_FAIL_IF(strings->len != 3)
    TEST_FAIL_IF(strings->nStrings != 1)
    TEST_PASS

    free_chunk(strings);
}

static void test_chunk_deleteLast(void) {
    constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS);

    add_chunk(strings, "abc", 3);
    add_chunk(strings, "def", 3);
    add_chunk(strings, "", 0);

    deleteLast_chunk(strings);

    TEST_FAIL_IF(strings->len != 7)
    TEST_FAIL_IF(strings->nStrings != 2)

    deleteLast_chunk(strings);
    deleteLast_chunk(strings);

    TEST_FAIL_IF(strings->len != 0)
    TEST_FAIL_IF(strings->start[0] != '\0')

    TEST_PASS

    free_chunk(strings);
}

static void test_chunk_fromStream(void) {
    FILE* const stream = fopen("src/tests.c", "r");
    DEBUG_ERROR_IF(stream == NULL)

    constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS);

    DEBUG_ERROR_IF(fromStream_chunk(strings, stream, NULL) == 0xFFFFFFFF)
    NDEBUG_EXECUTE(fromStream_chunk(strings, stream, NULL))

    TEST_FAIL_IF(!STR_CONTAINS_CONST(getFirst_chunk(strings), "/""**"))
    TEST_FAIL_IF(!STR_EQ_CONST(getFirst_chunk(strings), "/""**"))
    TEST_PASS

    DEBUG_ERROR_IF(fclose(stream) == EOF)
    NDEBUG_EXECUTE(fclose(stream))

    free_chunk(strings);
}

static void test_chunk_strlen(void) {
    constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS);

    add_chunk(strings, "abc", 3);
    add_chunk(strings, "", 0);
    add_chunk(strings, "def", 3);

    TEST_FAIL_IF(strlen_chunk(strings, 1) != 0)
    TEST_FAIL_IF(strlen_chunk(strings, 2) != 3)
    TEST_PASS

    free_chunk(strings);
}

static void test_chunk_strlenLast(void) {
    constructEmpty_chunk(strings, CHUNK_RECOMMENDED_PARAMETERS);

    add_chunk(strings, "abc", 3);
    add_chunk(strings, "def", 3);
    add_chunk(strings, "", 0);

    TEST_FAIL_IF(strlenLast_chunk(strings) != 0)
    TEST_PASS

    free_chunk(strings);
}

static void test_circbuff(void) {
    int* element;
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int z = 0;

    CircularBuffer buffer[1] = { NOT_A_CIRCBUFF };
    constructEmpty_cbuff(buffer, sizeof(int), 1);

    enqueue_cbuff(buffer, &a);

    TEST_FAIL_IF(buffer->size != 1)

    enqueue_cbuff(buffer, &b);

    TEST_FAIL_IF(buffer->size != 2)

    enqueue_cbuff(buffer, &c);

    TEST_FAIL_IF(buffer->size != 3)

    enqueue_cbuff(buffer, &d);

    TEST_FAIL_IF(buffer->size != 4)

    element = dequeue_cbuff(buffer);
    TEST_FAIL_IF(*element != a)

    rotate_cbuff(buffer, 2);

    element = peekBottom_cbuff(buffer);
    TEST_FAIL_IF(*element != d)

    element = get_cbuff(buffer, 1);
    TEST_FAIL_IF(*element != b)

    element = peekTop_cbuff(buffer);
    TEST_FAIL_IF(*element != c)

    REPEAT(buffer->cap) enqueue_o_cbuff(buffer, &z);

    for (uint32_t i = 0; i < buffer->size; i++) {
        element = get_cbuff(buffer, i);
        TEST_FAIL_IF(*element != z)
    }

    TEST_PASS

    free_cbuff(buffer);
}

static void test_cset(void) {
    ChunkSet set[1] = { NOT_A_CHUNK_SET };

    constructEmpty_cset(set, CHUNK_SET_RECOMMENDED_PARAMETERS);

    addKey_cset(set, "Apples", 6);
    addKey_cset(set, "Apples", 6);
    addKey_cset(set, "Oranges", 7);

    TEST_FAIL_IF(getKeyCount_cset(set) != 2)
    TEST_FAIL_IF(!STR_EQ_CONST(getKey_cset(set, 1), "Oranges"))
    TEST_FAIL_IF(getKeyId_cset(set, "Apples", 6) != 0)
    TEST_FAIL_IF(getKeyId_cset(set, "Pears", 5) != 0xFFFFFFFF)
    TEST_FAIL_IF(strlen_cset(set, 1) != 7)
    TEST_PASS

    flush_cset(set);
    free_cset(set);
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

    DEBUG_EXECUTE(uint32_t person_id[PEOPLE_COUNT])
    Chunk people[1]             = { NOT_A_CHUNK };
    ChunkTable ages[1]          = { NOT_A_CHUNK_TABLE };
    ChunkTable scores[1]        = { NOT_A_CHUNK_TABLE };
    CTblConstIterator itr[1]    = { NOT_A_CHUNK_TABLE_ITR };
    unsigned count_scores       = 0;

    constructEmpty_chunk(people, CHUNK_RECOMMENDED_PARAMETERS);
    constructEmpty_ctbl(ages, CHUNK_TABLE_RECOMMENDED_PARAMETERS);
    constructEmpty_ctbl(scores, CHUNK_TABLE_RECOMMENDED_PARAMETERS);

    for (unsigned person = ALICE; person < PEOPLE_COUNT; person++) {
        DEBUG_EXECUTE(person_id[person] = add_chunk(people, name[person], 5))
        DEBUG_ERROR_IF(person_id[person] != person)

        NDEBUG_EXECUTE(add_chunk(people, name[person], 5))
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
            case CTBL_INSERT_DUPLICATE_KEY:
            default:
                TEST_FAIL_MESSAGE(insert_ctbl);
                goto END_TEST_CTBL;
        }
    }

    for (unsigned exam = 0; exam < EXAM_COUNT; exam++) {
        for (unsigned person = ALICE; person < PEOPLE_COUNT; person++) {
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
                default:
                    TEST_FAIL_MESSAGE(insert_ctbl);
            }
        }
    }

    construct_ctblitr(itr, scores, people, name[ALICE], 5);

    while (next_ctblitr(itr) != NULL) count_scores++;

    TEST_FAIL_IF(count_scores != 2)

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
    flush_ctbl(ages);
    flush_ctbl(scores);

    free_ctbl(ages);
    free_ctbl(scores);
    free_chunk(people);

    #undef EXAM_COUNT
    #undef PEOPLE_COUNT
}
#undef ALICE
#undef HARRY
#undef LENNY
#undef WENDY

static void test_gmtx(void) {
    GraphMatrix gmtx[1] = { NOT_A_GRAPH_MATRIX };
    construct_gmtx(gmtx, 3, 3);
    connectAll_gmtx(gmtx);
    resizeIfNecessary_gmtx(gmtx, 4, 4);

    for (unsigned i = 0; i < 4; i++) {
        if (isConnected_gmtx(gmtx, i, i)) {
            disconnect_gmtx(gmtx, i, i);
        } else {
            connect_gmtx(gmtx, i, i);
        }
    }

    TEST_FAIL_IF(findSink_gmtx(gmtx, 3, 3) != 3)
    TEST_FAIL_IF(findSource_gmtx(gmtx, 3, 3) != 3)
    TEST_FAIL_IF(findSink_gmtx(gmtx, 0, 3) != 2)
    TEST_FAIL_IF(findSource_gmtx(gmtx, 2, 3) != 1)

    TEST_PASS

    disconnectAll_gmtx(gmtx);

    free_gmtx(gmtx);
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

    construct_jsonp(jp, fp, JSON_PARSER_DEFAULT_EVENTS);
    jp->atObjectStart = test_jsonp_countObjects;

    TEST_FAIL_IF(parseStream_jsonp(jp) != JSON_PARSER_OK)

    TEST_FAIL_IF(test_jsonp_objCount != 27)
    TEST_PASS

    DEBUG_ASSERT(fclose(fp) == 0)
    NDEBUG_EXECUTE(fclose(fp))

    free_jsonp(jp);
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
    constructEmpty_map(colleagues, BUFSIZ);

    for (unsigned i = 0; i < RELATIONS_COUNT; i++) {
        insert_map(colleagues, relations[i][0], VAL_UNSIGNED(relations[i][1]));
        insert_map(colleagues, relations[i][1], VAL_UNSIGNED(relations[i][0]));
    }

    insert_map(colleagues, JANE, VAL_UNSIGNED(JANE));
    deleteLast_map(colleagues);

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

    flush_map(colleagues);
    free_map(colleagues);

    #undef RELATIONS_COUNT
    #undef PEOPLE_COUNT
}
*/

static void test_overlap(void) {
    static char const a1[]      = "abcde";
    static char const a2[]      = "fghi";
    static char const* const a3 = a1 + 1;
    char const b1[]             = "jklmn";
    char const b2[]             = "opqr";
    char const* const b3        = b1 + 1;
    char* const c1              = mem_calloc(6, 1);
    char* const c2              = mem_calloc(4, 1);
    char const* const c3        = c1 + 1;
    memcpy(c1, "stuvw", 6);
    memcpy(c2, "xyz", 4);

    TEST_FAIL_IF(!overlaps_ptr(NULL, NULL, 0, 0))

    TEST_FAIL_IF(overlaps_ptr(NULL, a1, 0, 6))
    TEST_FAIL_IF(overlaps_ptr(NULL, a2, 0, 5))
    TEST_FAIL_IF(overlaps_ptr(NULL, a3, 0, 2))
    TEST_FAIL_IF(overlaps_ptr(NULL, b1, 0, 6))
    TEST_FAIL_IF(overlaps_ptr(NULL, b2, 0, 5))
    TEST_FAIL_IF(overlaps_ptr(NULL, b3, 0, 2))
    TEST_FAIL_IF(overlaps_ptr(NULL, c1, 0, 6))
    TEST_FAIL_IF(overlaps_ptr(NULL, c2, 0, 5))
    TEST_FAIL_IF(overlaps_ptr(NULL, c3, 0, 2))

    TEST_FAIL_IF(overlaps_ptr(a1, NULL, 6, 0))
    TEST_FAIL_IF(overlaps_ptr(a2, NULL, 5, 0))
    TEST_FAIL_IF(overlaps_ptr(a3, NULL, 2, 0))
    TEST_FAIL_IF(overlaps_ptr(b1, NULL, 6, 0))
    TEST_FAIL_IF(overlaps_ptr(b2, NULL, 5, 0))
    TEST_FAIL_IF(overlaps_ptr(b3, NULL, 2, 0))
    TEST_FAIL_IF(overlaps_ptr(c1, NULL, 6, 0))
    TEST_FAIL_IF(overlaps_ptr(c2, NULL, 5, 0))
    TEST_FAIL_IF(overlaps_ptr(c3, NULL, 2, 0))

    TEST_FAIL_IF(!overlaps_ptr(a1, a1, 6, 6))
    TEST_FAIL_IF(!overlaps_ptr(a2, a2, 5, 5))
    TEST_FAIL_IF(!overlaps_ptr(a3, a3, 2, 2))
    TEST_FAIL_IF(!overlaps_ptr(b1, b1, 6, 6))
    TEST_FAIL_IF(!overlaps_ptr(b2, b2, 5, 5))
    TEST_FAIL_IF(!overlaps_ptr(b3, b3, 2, 2))
    TEST_FAIL_IF(!overlaps_ptr(c1, c1, 6, 6))
    TEST_FAIL_IF(!overlaps_ptr(c2, c2, 5, 5))
    TEST_FAIL_IF(!overlaps_ptr(c3, c3, 2, 2))

    TEST_FAIL_IF(!overlaps_ptr(a1, a1 + 1, 6, 5))
    TEST_FAIL_IF(!overlaps_ptr(a2, a2 + 1, 5, 4))
    TEST_FAIL_IF(!overlaps_ptr(a3, a3 + 1, 2, 1))
    TEST_FAIL_IF(!overlaps_ptr(b1, b1 + 1, 6, 5))
    TEST_FAIL_IF(!overlaps_ptr(b2, b2 + 1, 5, 4))
    TEST_FAIL_IF(!overlaps_ptr(b3, b3 + 1, 2, 1))
    TEST_FAIL_IF(!overlaps_ptr(c1, c1 + 1, 6, 5))
    TEST_FAIL_IF(!overlaps_ptr(c2, c2 + 1, 5, 4))
    TEST_FAIL_IF(!overlaps_ptr(c3, c3 + 1, 2, 1))

    TEST_FAIL_IF(overlaps_ptr(a1, a2, 6, 5))
    TEST_FAIL_IF(!overlaps_ptr(a1, a3, 6, 2))
    TEST_FAIL_IF(overlaps_ptr(a1, b1, 6, 6))
    TEST_FAIL_IF(overlaps_ptr(a1, b2, 6, 5))
    TEST_FAIL_IF(overlaps_ptr(a1, b3, 6, 2))
    TEST_FAIL_IF(overlaps_ptr(a1, c1, 6, 6))
    TEST_FAIL_IF(overlaps_ptr(a1, c2, 6, 5))
    TEST_FAIL_IF(overlaps_ptr(a1, c3, 6, 2))

    TEST_FAIL_IF(overlaps_ptr(a2, a1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(a2, a3, 5, 2))
    TEST_FAIL_IF(overlaps_ptr(a2, b1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(a2, b2, 5, 5))
    TEST_FAIL_IF(overlaps_ptr(a2, b3, 5, 2))
    TEST_FAIL_IF(overlaps_ptr(a2, c1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(a2, c2, 5, 5))
    TEST_FAIL_IF(overlaps_ptr(a2, c3, 5, 2))

    TEST_FAIL_IF(!overlaps_ptr(a3, a1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(a3, a2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(a3, b1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(a3, b2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(a3, b3, 2, 2))
    TEST_FAIL_IF(overlaps_ptr(a3, c1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(a3, c2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(a3, c3, 2, 2))

    TEST_FAIL_IF(overlaps_ptr(b1, a1, 6, 6))
    TEST_FAIL_IF(overlaps_ptr(b1, a2, 6, 5))
    TEST_FAIL_IF(overlaps_ptr(b1, a3, 6, 2))
    TEST_FAIL_IF(overlaps_ptr(b1, b2, 6, 5))
    TEST_FAIL_IF(!overlaps_ptr(b1, b3, 6, 2))
    TEST_FAIL_IF(overlaps_ptr(b1, c1, 6, 6))
    TEST_FAIL_IF(overlaps_ptr(b1, c2, 6, 5))
    TEST_FAIL_IF(overlaps_ptr(b1, c3, 6, 2))

    TEST_FAIL_IF(overlaps_ptr(b2, a1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(b2, a2, 5, 5))
    TEST_FAIL_IF(overlaps_ptr(b2, a3, 5, 2))
    TEST_FAIL_IF(overlaps_ptr(b2, b1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(b2, b3, 5, 2))
    TEST_FAIL_IF(overlaps_ptr(b2, c1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(b2, c2, 5, 5))
    TEST_FAIL_IF(overlaps_ptr(b2, c3, 5, 2))

    TEST_FAIL_IF(overlaps_ptr(b3, a1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(b3, a2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(b3, a3, 2, 2))
    TEST_FAIL_IF(!overlaps_ptr(b3, b1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(b3, b2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(b3, c1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(b3, c2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(b3, c3, 2, 2))

    TEST_FAIL_IF(overlaps_ptr(c1, a1, 6, 6))
    TEST_FAIL_IF(overlaps_ptr(c1, a2, 6, 5))
    TEST_FAIL_IF(overlaps_ptr(c1, a3, 6, 2))
    TEST_FAIL_IF(overlaps_ptr(c1, b1, 6, 6))
    TEST_FAIL_IF(overlaps_ptr(c1, b2, 6, 5))
    TEST_FAIL_IF(overlaps_ptr(c1, b3, 6, 2))
    TEST_FAIL_IF(overlaps_ptr(c1, c2, 6, 5))
    TEST_FAIL_IF(!overlaps_ptr(c1, c3, 6, 2))

    TEST_FAIL_IF(overlaps_ptr(c2, a1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(c2, a2, 5, 5))
    TEST_FAIL_IF(overlaps_ptr(c2, a3, 5, 2))
    TEST_FAIL_IF(overlaps_ptr(c2, b1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(c2, b2, 5, 5))
    TEST_FAIL_IF(overlaps_ptr(c2, b3, 5, 2))
    TEST_FAIL_IF(overlaps_ptr(c2, c1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(c2, c3, 5, 2))

    TEST_FAIL_IF(overlaps_ptr(c3, a1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(c3, a2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(c3, a3, 2, 2))
    TEST_FAIL_IF(overlaps_ptr(c3, b1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(c3, b2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(c3, b3, 2, 2))
    TEST_FAIL_IF(!overlaps_ptr(c3, c1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(c3, c2, 2, 5))

    TEST_FAIL_IF(overlaps_ptr(c1, c3, 1, 2))
    TEST_FAIL_IF(!overlaps_ptr(c1, c3, 5, 1))

    TEST_PASS

    free(c1);
    free(c2);
}

/*
static void test_reallocate(void) {
    #define OLD_SIZE 1024
    #define NEW_SIZE 131072

    char* buffer            = mem_alloc(OLD_SIZE);
    char* const new_buffer  = REALLOCATE(buffer, OLD_SIZE, NEW_SIZE, 1);

    TEST_FAIL_IF(new_buffer != buffer)

    TEST_PASS

    free(buffer);
    #undef OLD_SIZE
    #undef NEW_SIZE
}

typedef struct ObjBody {
    uint32_t    x;
    uint32_t    y;
} Obj;

typedef struct ListBody {
    uint32_t    cap;
    uint32_t    size;
    Obj*        array;
} List;

static void test_reallocate_recalloc(void) {
    #define OLD_SIZE 256
    #define NEW_SIZE 131072

    char* buffer            = mem_calloc(OLD_SIZE, 1);
    char* const new_buffer  = RECALLOC(buffer, OLD_SIZE, NEW_SIZE, 1);
    List list[1]            = { (List){ 0, 0, NULL } };

    TEST_FAIL_IF(new_buffer != buffer)
    for (unsigned i = 0; i < NEW_SIZE; i++)
        TEST_FAIL_IF(new_buffer[i] != '\0')

    list->cap   = OLD_SIZE;
    list->size  = 0;
    list->array = calloc((size_t)list->cap, sizeof(Obj));
    DEBUG_ERROR_IF(list->array == NULL)

    REPEAT ((NEW_SIZE >> 1) + 1) {
        RECALLOC_IF_NECESSARY(Obj, list->array, uint32_t, list->cap, list->size)
        list->array[list->size++] = (Obj){1, 1};
    }

    TEST_FAIL_IF(list->size != (NEW_SIZE >> 1) + 1)
    TEST_FAIL_IF(list->cap != NEW_SIZE)
    TEST_FAIL_IF(list->array[list->size - 1].x != 1 || list->array[list->size - 1].y != 1)
    TEST_FAIL_IF(list->array[list->cap - 1].x != 0 || list->array[list->cap - 1].y != 0)

    TEST_PASS

    free(buffer);
    free(list->array);
    #undef OLD_SIZE
    #undef NEW_SIZE
}

static void test_stack(void) {
    int a = 1;
    int b = 5;
    int c = 3;
    int d = 4;

    Stack stack[1] = { NOT_A_STACK };
    constructEmpty_stack(stack, sizeof(int), 1);

    TEST_FAIL_IF(stack->size != 0)

    push_stack(stack, &a);

    TEST_FAIL_IF(stack->size != 1)
    TEST_FAIL_IF(*(int*)(peek_stack(stack)) != a)

    pushBottom_stack(stack, &b);

    TEST_FAIL_IF(stack->size != 2)
    TEST_FAIL_IF(*(int*)(peekTop_stack(stack)) != a)
    TEST_FAIL_IF(*(int*)(peekBottom_stack(stack)) != b)

    pop_stack(stack);

    TEST_FAIL_IF(stack->size != 1)
    TEST_FAIL_IF(*(int*)(peekTop_stack(stack)) != b)
    TEST_FAIL_IF(*(int*)(peekBottom_stack(stack)) != b)

    pushTop_stack(stack, &c);

    TEST_FAIL_IF(stack->size != 2)
    TEST_FAIL_IF(*(int*)(peekTop_stack(stack)) != c)
    TEST_FAIL_IF(*(int*)(peekBottom_stack(stack)) != b)

    reverse_stack(stack);

    TEST_FAIL_IF(stack->size != 2)
    TEST_FAIL_IF(*(int*)(peekTop_stack(stack)) != b)
    TEST_FAIL_IF(*(int*)(peekBottom_stack(stack)) != c)

    pushTop_stack(stack, &d);

    TEST_FAIL_IF(stack->size != 3)
    TEST_FAIL_IF(*(int*)(get_stack(stack, 0)) != c)
    TEST_FAIL_IF(*(int*)(get_stack(stack, 1)) != b)
    TEST_FAIL_IF(*(int*)(get_stack(stack, 2)) != d)

    rotate_stack(stack,2);

    TEST_FAIL_IF(stack->size != 3)
    TEST_FAIL_IF(*(int*)(get_stack(stack, 0)) != d)
    TEST_FAIL_IF(*(int*)(get_stack(stack, 1)) != c)
    TEST_FAIL_IF(*(int*)(get_stack(stack, 2)) != b)

    TEST_PASS

    free_stack(stack);
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
                break;
            default:
                break;
        }
    }

    TEST_PASS

    #undef VEGETABLE_COUNT
    #undef SEARCH_COUNT
}
#undef ONIONS
#undef SPINACH
*/

static void test_timestamp_get(void) {
    char const* timestamp = get_timestamp();

    TEST_FAIL_IF(strlen(timestamp) != TS_LEN)
    TEST_PASS
}

/*
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
*/

int main(void) {
    puts("");
    DEBUG_EXECUTE(puts("DEBUG_MODE => "__FILE__))
    NDEBUG_EXECUTE(puts("RELEASE_MODE => "__FILE__))

    /*
    test_chunk_add();
    test_chunk_addIndex();
    test_chunk_append();
    test_chunk_appendIndex();
    test_chunk_appendSpace();
    test_chunk_concat();
    test_chunk_delete();
    test_chunk_deleteLast();
    test_chunk_fromStream();
    test_chunk_strlen();
    test_chunk_strlenLast();
    test_circbuff();
    test_cset();
    test_ctbl();
    test_gmtx();
    test_jsonp();
    test_map();
    test_reallocate();
    test_reallocate_recalloc();
    test_stack();
    test_streq_mem_eq_n();
    test_streq_str_eq_n();
    test_streq_str_eq();
    test_streq_strcmp_as_comparator();
    test_val_areEqual();
    */
    test_overlap();
    test_timestamp_get();

    puts("");
    return 0;
}
