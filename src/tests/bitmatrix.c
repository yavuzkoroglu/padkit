static void test_bitmatrix(void);
static bool test_bitmatrix_construct_bmtx(void);
static bool test_bitmatrix_findInCol_bmtx(void);
static bool test_bitmatrix_findInRow_bmtx(void);
static bool test_bitmatrix_free_bmtx(void);
static bool test_bitmatrix_get_bmtx(void);
static bool test_bitmatrix_isValid_bmtx(void);
static bool test_bitmatrix_resizeIfNecessary_bmtx(void);
static bool test_bitmatrix_set_bmtx(void);
static bool test_bitmatrix_setAll_bmtx(void);
static bool test_bitmatrix_unset_bmtx(void);
static bool test_bitmatrix_unsetAll_bmtx(void);

static void test_bitmatrix(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_bitmatrix_construct_bmtx();
    allTestsPass &= test_bitmatrix_findInCol_bmtx();
    allTestsPass &= test_bitmatrix_findInRow_bmtx();
    allTestsPass &= test_bitmatrix_free_bmtx();
    allTestsPass &= test_bitmatrix_get_bmtx();
    allTestsPass &= test_bitmatrix_isValid_bmtx();
    allTestsPass &= test_bitmatrix_resizeIfNecessary_bmtx();
    allTestsPass &= test_bitmatrix_set_bmtx();
    allTestsPass &= test_bitmatrix_setAll_bmtx();
    allTestsPass &= test_bitmatrix_unset_bmtx();
    allTestsPass &= test_bitmatrix_unsetAll_bmtx();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_bitmatrix_construct_bmtx(void) {
    TEST_PASS
}

static bool test_bitmatrix_findInCol_bmtx(void) {
    TEST_PASS
}

static bool test_bitmatrix_findInRow_bmtx(void) {
    TEST_PASS
}

static bool test_bitmatrix_free_bmtx(void) {
    TEST_PASS
}

static bool test_bitmatrix_get_bmtx(void) {
    TEST_PASS
}

static bool test_bitmatrix_isValid_bmtx(void) {
    TEST_PASS
}

static bool test_bitmatrix_resizeIfNecessary_bmtx(void) {
    TEST_PASS
}

static bool test_bitmatrix_set_bmtx(void) {
    TEST_PASS
}

static bool test_bitmatrix_setAll_bmtx(void) {
    TEST_PASS
}

static bool test_bitmatrix_unset_bmtx(void) {
    TEST_PASS
}

static bool test_bitmatrix_unsetAll_bmtx(void) {
    TEST_PASS
}
