static void test_hashmapping(void);
static bool test_hashmapping_isValid_hmpng(void);

static void test_hashmapping(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_hashmapping_isValid_hmpng();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_hashmapping_isValid_hmpng(void) {
    HashMapping mappings[] = {
        NOT_A_HASH_MAPPING,
        (HashMapping){ 0, 0, SZ32_MAX - 1 },
        (HashMapping){ 0, 0, SZ32_MAX },
        (HashMapping){ INVALID_UINT64, INVALID_UINT32, 0 }
    };

    HashMapping const* mapping = mappings;
    TEST_FAIL_IF(isValid_hmpng(mapping))

    mapping++;
    TEST_FAIL_IF(!isValid_hmpng(mapping))

    mapping++;
    TEST_FAIL_IF(isValid_hmpng(mapping))

    mapping++;
    TEST_FAIL_IF(!isValid_hmpng(mapping))

    TEST_PASS
}
