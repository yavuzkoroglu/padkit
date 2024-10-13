static void test_verbose(void);
static bool test_verbose_printf_verbose(void);

static void test_verbose(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_verbose_printf_verbose();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_verbose_printf_verbose(void) {
    TEST_FAIL_IF(printf_verbose("Hello, World!") != 0)

    verbose = 1;
    printf_verbose("This is a verbose message.");
    verbose = 0;

    TEST_PASS
}
