static unsigned test_jsonp_objCount = 0;

static void test_jsonp_countObjects(JSONParser* const jp);

static void test_jsonparser(void);
static bool test_jsonparser_parseStream_jsonp(void);

static void test_jsonp_countObjects(JSONParser* const jp) {
    MAYBE_UNUSED(jp)
    test_jsonp_objCount++;
}

static void test_jsonparser(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_jsonparser_parseStream_jsonp();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_jsonparser_parseStream_jsonp(void) {
    JSONParser jp[1]        = { NOT_A_JSON_PARSER };
    char const filename[]   = "test_artifacts/model002.json";

    FILE* const fp = fopen(filename, "r");
    TEST_FAIL_IF(fp == NULL)

    construct_jsonp(jp, fp, JSON_PARSER_DEFAULT_EVENTS);
    jp->atObjectStart = test_jsonp_countObjects;

    TEST_FAIL_IF(parseStream_jsonp(jp) != JSON_PARSER_OK)

    TEST_FAIL_IF(test_jsonp_objCount != 27)

    fclose(fp);

    free_jsonp(jp);

    TEST_PASS
}
