static void test_hash(void);
static bool test_hash_hash_str(void);

static void test_hash(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_hash_hash_str();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_hash_hash_str(void) {
    TEST_FAIL_IF(hash_str("", 0) != 5381)
    TEST_FAIL_IF(hash_str("a", 0) != 5381)
    TEST_FAIL_IF(hash_str("a", 1) != 177670)

    TEST_PASS
}
