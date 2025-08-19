static void test_indextable(void);
static bool test_indextable_constructEmpty_itbl(void);
static bool test_indextable_flush_itbl(void);
static bool test_indextable_destruct_itbl(void);
static bool test_indextable_grow_itbl(void);
static bool test_indextable_insert_itbl(void);
static bool test_indextable_isValid_itbl(void);

static void test_indextable(void) {
    bool all_tests_pass = 1;

    all_tests_pass &= test_indextable_constructEmpty_itbl();
    all_tests_pass &= test_indextable_flush_itbl();
    all_tests_pass &= test_indextable_destruct_itbl();
    all_tests_pass &= test_indextable_grow_itbl();
    all_tests_pass &= test_indextable_insert_itbl();
    all_tests_pass &= test_indextable_isValid_itbl();

    if (all_tests_pass) TESTS_PASS_MESSAGE
}

static bool test_indextable_constructEmpty_itbl(void) {
    IndexTable table[1] = { NOT_AN_ITBL };
    constructEmpty_itbl(table, 1000000, 75, 1000000);
    destruct_itbl(table);
    TEST_PASS
}

static bool test_indextable_flush_itbl(void) {
    IndexTable table[1] = { NOT_AN_ITBL };
    constructEmpty_itbl(table, ITBL_RECOMMENDED_PARAMETERS);

    TEST_FAIL_IF(table->load != 0)

    insert_itbl(NULL, table, 0, 0, ITBL_RELATION_ONE_TO_ONE, ITBL_BEHAVIOR_REPLACE);

    TEST_FAIL_IF(table->load != 1)

    insert_itbl(NULL, table, 1, 1, ITBL_RELATION_ONE_TO_ONE, ITBL_BEHAVIOR_REPLACE);

    TEST_FAIL_IF(table->load != 2)

    flush_itbl(table);

    TEST_FAIL_IF(table->load != 0)

    destruct_itbl(table);
    TEST_PASS
}

static bool test_indextable_destruct_itbl(void) {
    IndexTable table[1] = { NOT_AN_ITBL };
    constructEmpty_itbl(table, 1, 1, 1);
    TEST_FAIL_IF(!isValid_itbl(table))
    destruct_itbl(table);
    TEST_FAIL_IF(isValid_itbl(table))
    TEST_PASS
}

#define ALICE 0
#define HARRY 1
#define LENNY 2
#define WENDY 3
static bool test_indextable_insert_itbl(void) {
    bool age_result;
    bool score_result;
    IndexMapping* age_mapping;
    IndexMapping* score_mapping;

    uint32_t const age[] = { [ALICE]=12, [HARRY]=33, [LENNY]=3, [WENDY]=24 };
    #define PEOPLE_COUNT (sizeof(age) / sizeof(uint32_t))

    uint32_t const score[][PEOPLE_COUNT] = {
        { [ALICE]=35, [HARRY]=24, [LENNY]=65, [WENDY]=22 },
        { [ALICE]=32, [HARRY]=28, [LENNY]=85, [WENDY]=22 }
    };

    IndexTable ages[1]              = { NOT_AN_ITBL };
    IndexTable scores[1]            = { NOT_AN_ITBL };
    constructEmpty_itbl(ages, ITBL_RECOMMENDED_PARAMETERS);
    constructEmpty_itbl(scores, ITBL_RECOMMENDED_PARAMETERS);

    for (uint_fast64_t person = ALICE; person < PEOPLE_COUNT; person++) {
        age_mapping = insert_itbl(
            &age_result,
            ages,
            person,
            age[person],
            ITBL_RELATION_ONE_TO_ONE,
            ITBL_BEHAVIOR_RESPECT
        );
        TEST_FAIL_IF(age_result == ITBL_INSERT_NOT_UNIQUE)
        TEST_FAIL_IF(ages->load != person + 1)
    }

    for (uint_fast64_t person = ALICE; person < PEOPLE_COUNT; person++) {
        score_mapping = insert_itbl(
            &score_result,
            scores,
            person,
            score[0][person],
            ITBL_RELATION_ONE_TO_ONE,
            ITBL_BEHAVIOR_RESPECT
        );
        TEST_FAIL_IF(score_result == ITBL_INSERT_NOT_UNIQUE)
    }

    for (uint_fast64_t person = ALICE; person < PEOPLE_COUNT; person++) {
        score_mapping = insert_itbl(
            &score_result,
            scores,
            person,
            score[1][person],
            ITBL_RELATION_ONE_TO_ONE,
            ITBL_BEHAVIOR_REPLACE
        );
        TEST_FAIL_IF(score_result == ITBL_INSERT_UNIQUE)
    }

    for (uint_fast64_t person = ALICE; person < PEOPLE_COUNT; person++) {
        score_mapping = insert_itbl(
            &score_result,
            scores,
            person,
            score[0][person],
            ITBL_RELATION_ONE_TO_MANY,
            ITBL_BEHAVIOR_RESPECT
        );
        if (person == WENDY) {
            TEST_FAIL_IF(score_result == ITBL_INSERT_UNIQUE)
        } else {
            TEST_FAIL_IF(score_result == ITBL_INSERT_NOT_UNIQUE)
        }
    }

    for (uint_fast64_t person = ALICE; person < PEOPLE_COUNT; person++) {
        age_mapping = findFirstMapping_itbl(ages, person);
        TEST_FAIL_IF(age_mapping == NULL)
        TEST_FAIL_IF(age_mapping->value != age[person])

        age_mapping = nextMapping_itbl(ages, age_mapping);
        TEST_FAIL_IF(age_mapping != NULL)
    }

    for (uint_fast64_t person = ALICE; person < PEOPLE_COUNT; person++) {
        score_mapping = findFirstMapping_itbl(scores, person);
        TEST_FAIL_IF(score_mapping == NULL)
        TEST_FAIL_IF(score_mapping->value != score[1][person])

        score_mapping = nextMapping_itbl(scores, score_mapping);
        TEST_FAIL_IF(score_mapping == NULL)
        TEST_FAIL_IF(score_mapping->value != score[0][person])
    }

    #undef PEOPLE_COUNT
    destruct_itbl(ages);
    destruct_itbl(scores);
    TEST_PASS
}
#undef ALICE
#undef HARRY
#undef LENNY
#undef WENDY

static bool test_indextable_grow_itbl(void) {
    IndexTable table[1] = { NOT_AN_ITBL };
    constructEmpty_itbl(table, ITBL_RECOMMENDED_PARAMETERS);

    insert_itbl(NULL, table, 8215102, 8215102, ITBL_RELATION_ONE_TO_ONE, ITBL_BEHAVIOR_RESPECT);

    TEST_FAIL_IF(findFirstMapping_itbl(table, 8215102) == NULL)

    grow_itbl(table);

    TEST_FAIL_IF(findFirstMapping_itbl(table, 8215102) == NULL)

    destruct_itbl(table);
    TEST_PASS
}

static bool test_indextable_isValid_itbl(void) {
    IndexTable table[1] = { NOT_AN_ITBL };

    TEST_FAIL_IF(isValid_itbl(table))

    constructEmpty_itbl(table, ITBL_RECOMMENDED_PARAMETERS);

    TEST_FAIL_IF(!isValid_itbl(table))

    destruct_itbl(table);

    TEST_FAIL_IF(isValid_itbl(table))

    TEST_PASS
}
