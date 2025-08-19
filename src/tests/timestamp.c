static void test_timestamp(void);
static bool test_timestamp_get(void);

static void test_timestamp(void) {
    bool all_tests_pass = 1;

    all_tests_pass &= test_timestamp_get();

    if (all_tests_pass) TESTS_PASS_MESSAGE
}

static bool test_timestamp_get(void) {
    char const* timestamp = get_timestamp();

    TEST_FAIL_IF(strlen(timestamp) != TS_LEN)

    TEST_PASS
}
