static void test_verbose(void);
static bool test_verbose_printf_verbose(void);

static void test_verbose(void) {
    bool all_tests_pass = 1;

    all_tests_pass &= test_verbose_printf_verbose();

    if (all_tests_pass) TESTS_PASS_MESSAGE
}

static bool test_verbose_printf_verbose(void) {
    TEST_FAIL_IF(printf_verbose("Hello, World!") != 0)

    verbose = 1;
    printf_verbose("This is a verbose message.");
    verbose = 0;

    TEST_PASS
}
