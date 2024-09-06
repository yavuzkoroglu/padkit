static void test_hashtable(void);
static bool test_hashtable_isValid_htbl(void);

static void test_hashtable(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_hashtable_isValid_htbl();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_hashtable_isValid_htbl(void) {
    HashTable table[1] = { NOT_AN_HTBL };

    TEST_FAIL_IF(isValid_htbl(table))

    constructEmpty_htbl(table, HTBL_RECOMMENDED_PARAMETERS);

    TEST_FAIL_IF(!isValid_htbl(table))

    free_htbl(table);

    TEST_FAIL_IF(isValid_htbl(table))

    TEST_PASS
}
