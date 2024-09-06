static void test_indextable(void);
static bool test_indextable_isValid_itbl(void);

static void test_indextable(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_indextable_isValid_itbl();

    if (allTestsPass) TESTS_PASS_MESSAGE
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
