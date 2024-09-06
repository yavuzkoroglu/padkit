static void test_indextable(void);
static bool test_indextable_constructEmpty_itbl(void);
static bool test_indextable_flush_itbl(void);
static bool test_indextable_free_itbl(void);
static bool test_indextable_grow_itbl(void);
static bool test_indextable_insert_itbl(void);
static bool test_indextable_isValid_itbl(void);

static void test_indextable(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_indextable_constructEmpty_itbl();
    allTestsPass &= test_indextable_flush_itbl();
    allTestsPass &= test_indextable_free_itbl();
    allTestsPass &= test_indextable_grow_itbl();
    allTestsPass &= test_indextable_insert_itbl();
    allTestsPass &= test_indextable_isValid_itbl();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_indextable_constructEmpty_itbl(void) {
    IndexTable table[1] = { NOT_AN_ITBL };
    constructEmpty_itbl(table, 1000000, 75, 1000000);
    free_itbl(table);
    TEST_PASS
}

static bool test_indextable_flush_itbl(void) {
    IndexTable table[1] = { NOT_AN_ITBL };
    constructEmpty_itbl(table, ITBL_RECOMMENDED_PARAMETERS);

    TEST_FAIL_IF(table->load != 0)

    insert_itbl(table, 0, 0, ITBL_RELATION_ONE_TO_ONE, ITBL_BEHAVIOR_REPLACE);

    TEST_FAIL_IF(table->load != 1)

    insert_itbl(table, 1, 1, ITBL_RELATION_ONE_TO_ONE, ITBL_BEHAVIOR_REPLACE);

    TEST_FAIL_IF(table->load != 2)

    flush_itbl(table);

    TEST_FAIL_IF(table->load != 0)

    free_itbl(table);
    TEST_PASS
}

static bool test_indextable_free_itbl(void) {
    IndexTable table[1] = { NOT_AN_ITBL };
    constructEmpty_itbl(table, 1, 1, 1);
    TEST_FAIL_IF(!isValid_itbl(table))
    free_itbl(table);
    TEST_FAIL_IF(isValid_itbl(table))
    TEST_PASS
}

#define ALICE 0
#define HARRY 1
#define LENNY 2
#define WENDY 3
static bool test_indextable_insert_itbl(void) {
    uint32_t const age[] = { [ALICE]=12, [HARRY]=33, [LENNY]=3, [WENDY]=24 };
    #define PEOPLE_COUNT (sizeof(age) / sizeof(uint32_t))

    uint32_t const score[][PEOPLE_COUNT] = {
        { [ALICE]=35, [HARRY]=24, [LENNY]=65, [WENDY]=22 },
        { [ALICE]=32, [HARRY]=28, [LENNY]=85, [WENDY]=22 }
    };

    IndexTable ages[1]      = { NOT_AN_ITBL };
    IndexTable scores[1]    = { NOT_AN_ITBL };
    constructEmpty_itbl(ages, ITBL_RECOMMENDED_PARAMETERS);
    constructEmpty_itbl(scores, ITBL_RECOMMENDED_PARAMETERS);

    for (uint_fast64_t person = ALICE; person < PEOPLE_COUNT; person++) {
        int const ageInsert = insert_itbl(
            ages,
            person,
            age[person],
            ITBL_RELATION_ONE_TO_ONE,
            ITBL_BEHAVIOR_RESPECT
        );
        TEST_FAIL_IF(ageInsert == ITBL_INSERT_NOT_UNIQUE)
        TEST_FAIL_IF(ages->load != person + 1)
    }

    for (uint_fast64_t person = ALICE; person < PEOPLE_COUNT; person++) {
        int const scoreInsert = insert_itbl(
            scores,
            person,
            score[0][person],
            ITBL_RELATION_ONE_TO_ONE,
            ITBL_BEHAVIOR_RESPECT
        );
        TEST_FAIL_IF(scoreInsert == ITBL_INSERT_NOT_UNIQUE)
    }

    for (uint_fast64_t person = ALICE; person < PEOPLE_COUNT; person++) {
        int const scoreInsert = insert_itbl(
            scores,
            person,
            score[1][person],
            ITBL_RELATION_ONE_TO_ONE,
            ITBL_BEHAVIOR_REPLACE
        );
        TEST_FAIL_IF(scoreInsert == ITBL_INSERT_UNIQUE)
    }

    for (uint_fast64_t person = ALICE; person < PEOPLE_COUNT; person++) {
        int const scoreInsert = insert_itbl(
            scores,
            person,
            score[0][person],
            ITBL_RELATION_ONE_TO_MANY,
            ITBL_BEHAVIOR_RESPECT
        );
        TEST_FAIL_IF(scoreInsert == ITBL_INSERT_UNIQUE)
    }

    for (uint_fast64_t person = ALICE; person < PEOPLE_COUNT; person++) {
        IndexMapping* ageMapping = getFirstMapping_itbl(ages, person);
        TEST_FAIL_IF(ageMapping == NULL)
        TEST_FAIL_IF(ageMapping->value != age[person])

        ageMapping = nextMapping_itbl(ages, ageMapping);
        TEST_FAIL_IF(ageMapping != NULL)
    }

    for (uint_fast64_t person = ALICE; person < PEOPLE_COUNT; person++) {
        IndexMapping* scoreMapping = getFirstMapping_itbl(scores, person);
        TEST_FAIL_IF(scoreMapping == NULL)
        TEST_FAIL_IF(scoreMapping->value != score[1][person])

        scoreMapping = nextMapping_itbl(scores, scoreMapping);
        TEST_FAIL_IF(scoreMapping == NULL)
        TEST_FAIL_IF(scoreMapping->value != score[0][person])
    }

    #undef PEOPLE_COUNT
    free_itbl(ages);
    free_itbl(scores);
    TEST_PASS
}
#undef ALICE
#undef HARRY
#undef LENNY
#undef WENDY

static bool test_indextable_grow_itbl(void) {
    IndexTable table[1] = { NOT_AN_ITBL };
    constructEmpty_itbl(table, ITBL_RECOMMENDED_PARAMETERS);

    insert_itbl(table, 8215102, 8215102, ITBL_RELATION_ONE_TO_ONE, ITBL_BEHAVIOR_RESPECT);

    TEST_FAIL_IF(getFirstMapping_itbl(table, 8215102) == NULL)

    grow_itbl(table);

    TEST_FAIL_IF(getFirstMapping_itbl(table, 8215102) == NULL)

    free_itbl(table);
    TEST_PASS
}

static bool test_indextable_isValid_itbl(void) {
    IndexTable table[1] = { NOT_AN_ITBL };

    TEST_FAIL_IF(isValid_itbl(table))

    constructEmpty_itbl(table, ITBL_RECOMMENDED_PARAMETERS);

    TEST_FAIL_IF(!isValid_itbl(table))

    free_itbl(table);

    TEST_FAIL_IF(isValid_itbl(table))

    TEST_PASS
}
