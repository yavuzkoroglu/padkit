static void test_hash(void);
static bool test_hash_hash32_str(void);
static bool test_hash_hash64_str(void);

static void test_hash(void) {
    bool all_tests_pass = 1;

    all_tests_pass &= test_hash_hash32_str();
    all_tests_pass &= test_hash_hash64_str();

    if (all_tests_pass) TESTS_PASS_MESSAGE
}

static bool test_hash_hash32_str(void) {
    TEST_FAIL_IF(hash32_str("", 0) != 5381)
    TEST_FAIL_IF(hash32_str("a", 0) != 5381)
    TEST_FAIL_IF(hash32_str("a", 1) != 177670)

    TEST_PASS
}

static bool test_hash_hash64_str(void) {
    TEST_FAIL_IF(hash64_str("", 0) != 5381)
    TEST_FAIL_IF(hash64_str("a", 0) != 5381)
    TEST_FAIL_IF(hash64_str("a", 1) != 177670)

    TEST_PASS
}
