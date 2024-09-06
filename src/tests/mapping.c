static void test_mapping(void);
static bool test_mapping_isValid_mppng(void);

static void test_mapping(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_mapping_isValid_mppng();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_mapping_isValid_mppng(void) {
    Mapping mappings[] = {
        NOT_A_MAPPING,
        (Mapping){ 0, 0, SZ32_MAX - 1 },
        (Mapping){ 0, 0, SZ32_MAX },
        (Mapping){ INVALID_UINT64, INVALID_UINT32, 0 }
    };

    Mapping const* mapping = mappings;
    TEST_FAIL_IF(isValid_mppng(mapping))

    mapping++;
    TEST_FAIL_IF(!isValid_mppng(mapping))

    mapping++;
    TEST_FAIL_IF(isValid_mppng(mapping))

    mapping++;
    TEST_FAIL_IF(!isValid_mppng(mapping))

    TEST_PASS
}
