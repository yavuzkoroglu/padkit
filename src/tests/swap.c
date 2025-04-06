static void test_swap(void);
static bool test_swap_swap(void);

static void test_swap(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_swap_swap();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_swap_swap(void) {
    uint8_t a       = 16;
    int8_t b        = 12;
    char str1[128]  = "Clean";
    char str2[128]  = "Dream";

    swap(&a, &b, 1);
    TEST_FAIL_IF(a != 12)
    TEST_FAIL_IF(b != 16)

    swap(str1, str2, 1);
    TEST_FAIL_IF(strcmp(str2, "Cream") != 0)

    swap(str1, str2, 1);
    swap(str1, str2, 5);
    TEST_FAIL_IF(strcmp(str1, "Dream") != 0)
    TEST_FAIL_IF(strcmp(str2, "Clean") != 0)

    TEST_PASS
}
