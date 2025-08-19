static void test_overlap(void);
static bool test_overlap_overlaps_ptr(void);

static void test_overlap(void) {
    bool all_tests_pass = 1;

    all_tests_pass &= test_overlap_overlaps_ptr();

    if (all_tests_pass) TESTS_PASS_MESSAGE
}

static bool test_overlap_overlaps_ptr(void) {
    static char const a1[]      = "abcde";
    static char const a2[]      = "fghi";
    static char const* const a3 = a1 + 1;
    char const b1[]             = "jklmn";
    char const b2[]             = "opqr";
    char const* const b3        = b1 + 1;
    char* const c1              = mem_calloc(6, 1);
    char* const c2              = mem_calloc(4, 1);
    char const* const c3        = c1 + 1;
    memcpy(c1, "stuvw", 6);
    memcpy(c2, "xyz", 4);

    TEST_FAIL_IF(overlaps_ptr(NULL, a1, 0, 6))
    TEST_FAIL_IF(overlaps_ptr(NULL, a2, 0, 5))
    TEST_FAIL_IF(overlaps_ptr(NULL, a3, 0, 2))
    TEST_FAIL_IF(overlaps_ptr(NULL, b1, 0, 6))
    TEST_FAIL_IF(overlaps_ptr(NULL, b2, 0, 5))
    TEST_FAIL_IF(overlaps_ptr(NULL, b3, 0, 2))
    TEST_FAIL_IF(overlaps_ptr(NULL, c1, 0, 6))
    TEST_FAIL_IF(overlaps_ptr(NULL, c2, 0, 5))
    TEST_FAIL_IF(overlaps_ptr(NULL, c3, 0, 2))

    TEST_FAIL_IF(overlaps_ptr(a1, NULL, 6, 0))
    TEST_FAIL_IF(overlaps_ptr(a2, NULL, 5, 0))
    TEST_FAIL_IF(overlaps_ptr(a3, NULL, 2, 0))
    TEST_FAIL_IF(overlaps_ptr(b1, NULL, 6, 0))
    TEST_FAIL_IF(overlaps_ptr(b2, NULL, 5, 0))
    TEST_FAIL_IF(overlaps_ptr(b3, NULL, 2, 0))
    TEST_FAIL_IF(overlaps_ptr(c1, NULL, 6, 0))
    TEST_FAIL_IF(overlaps_ptr(c2, NULL, 5, 0))
    TEST_FAIL_IF(overlaps_ptr(c3, NULL, 2, 0))

    TEST_FAIL_IF(!overlaps_ptr(a1, a1, 6, 6))
    TEST_FAIL_IF(!overlaps_ptr(a2, a2, 5, 5))
    TEST_FAIL_IF(!overlaps_ptr(a3, a3, 2, 2))
    TEST_FAIL_IF(!overlaps_ptr(b1, b1, 6, 6))
    TEST_FAIL_IF(!overlaps_ptr(b2, b2, 5, 5))
    TEST_FAIL_IF(!overlaps_ptr(b3, b3, 2, 2))
    TEST_FAIL_IF(!overlaps_ptr(c1, c1, 6, 6))
    TEST_FAIL_IF(!overlaps_ptr(c2, c2, 5, 5))
    TEST_FAIL_IF(!overlaps_ptr(c3, c3, 2, 2))

    TEST_FAIL_IF(!overlaps_ptr(a1, a1 + 1, 6, 5))
    TEST_FAIL_IF(!overlaps_ptr(a2, a2 + 1, 5, 4))
    TEST_FAIL_IF(!overlaps_ptr(a3, a3 + 1, 2, 1))
    TEST_FAIL_IF(!overlaps_ptr(b1, b1 + 1, 6, 5))
    TEST_FAIL_IF(!overlaps_ptr(b2, b2 + 1, 5, 4))
    TEST_FAIL_IF(!overlaps_ptr(b3, b3 + 1, 2, 1))
    TEST_FAIL_IF(!overlaps_ptr(c1, c1 + 1, 6, 5))
    TEST_FAIL_IF(!overlaps_ptr(c2, c2 + 1, 5, 4))
    TEST_FAIL_IF(!overlaps_ptr(c3, c3 + 1, 2, 1))

    TEST_FAIL_IF(overlaps_ptr(a1, a2, 6, 5))
    TEST_FAIL_IF(!overlaps_ptr(a1, a3, 6, 2))
    TEST_FAIL_IF(overlaps_ptr(a1, b1, 6, 6))
    TEST_FAIL_IF(overlaps_ptr(a1, b2, 6, 5))
    TEST_FAIL_IF(overlaps_ptr(a1, b3, 6, 2))
    TEST_FAIL_IF(overlaps_ptr(a1, c1, 6, 6))
    TEST_FAIL_IF(overlaps_ptr(a1, c2, 6, 5))
    TEST_FAIL_IF(overlaps_ptr(a1, c3, 6, 2))

    TEST_FAIL_IF(overlaps_ptr(a2, a1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(a2, a3, 5, 2))
    TEST_FAIL_IF(overlaps_ptr(a2, b1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(a2, b2, 5, 5))
    TEST_FAIL_IF(overlaps_ptr(a2, b3, 5, 2))
    TEST_FAIL_IF(overlaps_ptr(a2, c1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(a2, c2, 5, 5))
    TEST_FAIL_IF(overlaps_ptr(a2, c3, 5, 2))

    TEST_FAIL_IF(!overlaps_ptr(a3, a1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(a3, a2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(a3, b1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(a3, b2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(a3, b3, 2, 2))
    TEST_FAIL_IF(overlaps_ptr(a3, c1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(a3, c2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(a3, c3, 2, 2))

    TEST_FAIL_IF(overlaps_ptr(b1, a1, 6, 6))
    TEST_FAIL_IF(overlaps_ptr(b1, a2, 6, 5))
    TEST_FAIL_IF(overlaps_ptr(b1, a3, 6, 2))
    TEST_FAIL_IF(overlaps_ptr(b1, b2, 6, 5))
    TEST_FAIL_IF(!overlaps_ptr(b1, b3, 6, 2))
    TEST_FAIL_IF(overlaps_ptr(b1, c1, 6, 6))
    TEST_FAIL_IF(overlaps_ptr(b1, c2, 6, 5))
    TEST_FAIL_IF(overlaps_ptr(b1, c3, 6, 2))

    TEST_FAIL_IF(overlaps_ptr(b2, a1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(b2, a2, 5, 5))
    TEST_FAIL_IF(overlaps_ptr(b2, a3, 5, 2))
    TEST_FAIL_IF(overlaps_ptr(b2, b1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(b2, b3, 5, 2))
    TEST_FAIL_IF(overlaps_ptr(b2, c1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(b2, c2, 5, 5))
    TEST_FAIL_IF(overlaps_ptr(b2, c3, 5, 2))

    TEST_FAIL_IF(overlaps_ptr(b3, a1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(b3, a2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(b3, a3, 2, 2))
    TEST_FAIL_IF(!overlaps_ptr(b3, b1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(b3, b2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(b3, c1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(b3, c2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(b3, c3, 2, 2))

    TEST_FAIL_IF(overlaps_ptr(c1, a1, 6, 6))
    TEST_FAIL_IF(overlaps_ptr(c1, a2, 6, 5))
    TEST_FAIL_IF(overlaps_ptr(c1, a3, 6, 2))
    TEST_FAIL_IF(overlaps_ptr(c1, b1, 6, 6))
    TEST_FAIL_IF(overlaps_ptr(c1, b2, 6, 5))
    TEST_FAIL_IF(overlaps_ptr(c1, b3, 6, 2))
    TEST_FAIL_IF(overlaps_ptr(c1, c2, 6, 5))
    TEST_FAIL_IF(!overlaps_ptr(c1, c3, 6, 2))

    TEST_FAIL_IF(overlaps_ptr(c2, a1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(c2, a2, 5, 5))
    TEST_FAIL_IF(overlaps_ptr(c2, a3, 5, 2))
    TEST_FAIL_IF(overlaps_ptr(c2, b1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(c2, b2, 5, 5))
    TEST_FAIL_IF(overlaps_ptr(c2, b3, 5, 2))
    TEST_FAIL_IF(overlaps_ptr(c2, c1, 5, 6))
    TEST_FAIL_IF(overlaps_ptr(c2, c3, 5, 2))

    TEST_FAIL_IF(overlaps_ptr(c3, a1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(c3, a2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(c3, a3, 2, 2))
    TEST_FAIL_IF(overlaps_ptr(c3, b1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(c3, b2, 2, 5))
    TEST_FAIL_IF(overlaps_ptr(c3, b3, 2, 2))
    TEST_FAIL_IF(!overlaps_ptr(c3, c1, 2, 6))
    TEST_FAIL_IF(overlaps_ptr(c3, c2, 2, 5))

    TEST_FAIL_IF(overlaps_ptr(c1, c3, 1, 2))
    TEST_FAIL_IF(!overlaps_ptr(c1, c3, 5, 1))

    free(c1);
    free(c2);

    TEST_PASS
}
