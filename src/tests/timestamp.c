static void test_timestamp(void);
static bool test_timestamp_get(void);

static void test_timestamp(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_timestamp_get();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_timestamp_get(void) {
    char const* timestamp = get_timestamp();

    TEST_FAIL_IF(strlen(timestamp) != TS_LEN)

    TEST_PASS
}
