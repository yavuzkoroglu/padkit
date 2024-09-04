static void test_jsonparser(void);
static bool test_jsonparser_construct_jsonp(void);
static bool test_jsonparser_free_jsonp(void);
static bool test_jsonparser_isValid_jsonp(void);
static bool test_jsonparser_parseStream_jsonp(void);

static void test_jsonparser(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_jsonparser_construct_jsonp();
    allTestsPass &= test_jsonparser_free_jsonp();
    allTestsPass &= test_jsonparser_isValid_jsonp();
    allTestsPass &= test_jsonparser_parseStream_jsonp();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_jsonparser_construct_jsonp(void) {
    TEST_PASS
}

static bool test_jsonparser_free_jsonp(void) {
    TEST_PASS
}

static bool test_jsonparser_isValid_jsonp(void) {
    TEST_PASS
}

static bool test_jsonparser_parseStream_jsonp(void) {
    TEST_PASS
}
