static void test_indextable(void);
static bool test_indextable_constructEmpty_itbl(void);
static bool test_indextable_flush_itbl(void);
static bool test_indextable_free_itbl(void);
static bool test_indextable_isValid_itbl(void);

static void test_indextable(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_indextable_constructEmpty_itbl();
    allTestsPass &= test_indextable_flush_itbl();
    allTestsPass &= test_indextable_free_itbl();
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

static bool test_indextable_isValid_itbl(void) {
    IndexTable table[1] = { NOT_AN_ITBL };

    TEST_FAIL_IF(isValid_itbl(table))

    constructEmpty_itbl(table, ITBL_RECOMMENDED_PARAMETERS);

    TEST_FAIL_IF(!isValid_itbl(table))

    free_itbl(table);

    TEST_FAIL_IF(isValid_itbl(table))

    TEST_PASS
}
