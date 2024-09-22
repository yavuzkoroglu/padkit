static void test_element(void);
static bool test_element_isValid_elem(void);

static void test_hash(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_element_isValid_elem();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_element_isValid_elem(void) {
    Element e[2][1] = {
        { NOT_AN_ELEMENT },
        { NOT_AN_ELEMENT }
    };

    allocateIndeterminate_elem(e[1], 131072);

    TEST_PASS
}
