static void test_chunktable(void);

static bool test_chunktable_construct_ctbl(void);
static bool test_chunktable_constructEmpty_ctbl(void);
static bool test_chunktable_destruct_ctbl(void);
static bool test_chunktable_isAllocated_ctbl(void);
static bool test_chunktable_isValid_ctbl(void);
static bool test_chunktable_vconstruct_ctbl(size_t const n_parameters, ...);

static void test_chunktable(void) {
    bool all_tests_pass = 1;

    all_tests_pass &= test_chunktable_construct_ctbl();
    all_tests_pass &= test_chunktable_constructEmpty_ctbl();
    all_tests_pass &= test_chunktable_destruct_ctbl();
    all_tests_pass &= test_chunktable_isAllocated_ctbl();
    all_tests_pass &= test_chunktable_isValid_ctbl();
    all_tests_pass &= test_chunktable_vconstruct_ctbl(5, CTBL_RECOMMENDED_PARAMETERS);

    if (all_tests_pass) TESTS_PASS_MESSAGE
}

static bool test_chunktable_construct_ctbl(void) {
    ChunkTable ctbl[1] = { NOT_A_CTBL };

    TEST_FAIL_IF(isAllocated_ctbl(ctbl))
    TEST_FAIL_IF(isValid_ctbl(ctbl))

    construct_ctbl(ctbl, CTBL_RECOMMENDED_PARAMETERS);

    TEST_FAIL_IF(!isAllocated_ctbl(ctbl))
    TEST_FAIL_IF(!isValid_ctbl(ctbl))

    destruct_ctbl(ctbl);
    TEST_FAIL_IF(isAllocated_ctbl(ctbl))
    TEST_FAIL_IF(isValid_ctbl(ctbl))

    TEST_PASS
}

static bool test_chunktable_constructEmpty_ctbl(void) {
    ChunkTable ctbl[1] = { NOT_A_CTBL };

    TEST_FAIL_IF(isAllocated_ctbl(ctbl))
    TEST_FAIL_IF(isValid_ctbl(ctbl))

    constructEmpty_ctbl(ctbl, CTBL_RECOMMENDED_PARAMETERS);

    TEST_FAIL_IF(!isAllocated_ctbl(ctbl))
    TEST_FAIL_IF(!isValid_ctbl(ctbl))

    destruct_ctbl(ctbl);
    TEST_FAIL_IF(isAllocated_ctbl(ctbl))
    TEST_FAIL_IF(isValid_ctbl(ctbl))

    TEST_PASS
}

static bool test_chunktable_destruct_ctbl(void) {
    TEST_SAME_AS test_chunktable_construct_ctbl();
}

static bool test_chunktable_isAllocated_ctbl(void) {
    TEST_SAME_AS test_chunktable_construct_ctbl();
}

static bool test_chunktable_isValid_ctbl(void) {
    TEST_SAME_AS test_chunktable_construct_ctbl();
}

static bool test_chunktable_vconstruct_ctbl(size_t const n_parameters, ...) {
    ChunkTable ctbl[1] = { NOT_A_CTBL };
    va_list args;

    assert(n_parameters == 5);

    TEST_FAIL_IF(isAllocated_ctbl(ctbl))
    TEST_FAIL_IF(isValid_ctbl(ctbl))

    va_start(args, n_parameters);
    vconstruct_ctbl(ctbl, args);
    va_end(args);

    TEST_FAIL_IF(!isAllocated_ctbl(ctbl))
    TEST_FAIL_IF(!isValid_ctbl(ctbl))

    destruct_ctbl(ctbl);
    TEST_FAIL_IF(isAllocated_ctbl(ctbl))
    TEST_FAIL_IF(isValid_ctbl(ctbl))

    TEST_PASS
}
