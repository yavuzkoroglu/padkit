static void test_chunktable(void);

static bool test_chunktable_construct_ctbl(void);
static bool test_chunktable_constructEmpty_ctbl(void);
static bool test_chunktable_destruct_ctbl(void);
static bool test_chunktable_flush_ctbl(void);
static bool test_chunktable_isAllocated_ctbl(void);
static bool test_chunktable_isValid_ctbl(void);
static bool test_chunktable_searchInsert_ctbl(void);
static bool test_chunktable_vconstruct_ctbl(size_t const n_parameters, ...);

static void test_chunktable(void) {
    bool all_tests_pass = 1;

    all_tests_pass &= test_chunktable_construct_ctbl();
    all_tests_pass &= test_chunktable_constructEmpty_ctbl();
    all_tests_pass &= test_chunktable_destruct_ctbl();
    all_tests_pass &= test_chunktable_flush_ctbl();
    all_tests_pass &= test_chunktable_isAllocated_ctbl();
    all_tests_pass &= test_chunktable_isValid_ctbl();
    all_tests_pass &= test_chunktable_searchInsert_ctbl();
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

static bool test_chunktable_flush_ctbl(void) {
    TEST_SAME_AS test_chunktable_searchInsert_ctbl();
}

static bool test_chunktable_isAllocated_ctbl(void) {
    TEST_SAME_AS test_chunktable_construct_ctbl();
}

static bool test_chunktable_isValid_ctbl(void) {
    TEST_SAME_AS test_chunktable_construct_ctbl();
}

static bool test_chunktable_searchInsert_ctbl(void) {
    bool result;
    ChunkMapping* c_mapping;
    ChunkTable ctbl[1] = { NOT_A_CTBL };
    construct_ctbl(ctbl, 33, 75, 37, 30, 22);

    c_mapping = searchInsert_ctbl(&result, ctbl, ITEM_LIT("Alice"), 3, CTBL_MODE_SEARCH);
    TEST_FAIL_IF(result != CTBL_SEARCH_NOT_FOUND)
    TEST_FAIL_IF(c_mapping != NULL)

    flush_ctbl(ctbl);
    TEST_FAIL_IF(LEN_CTBL(ctbl) != 0)

    c_mapping = searchInsert_ctbl(&result, ctbl, ITEM_LIT("Alice"), 3, CTBL_MODE_SEARCH);
    TEST_FAIL_IF(result != CTBL_SEARCH_NOT_FOUND)
    TEST_FAIL_IF(c_mapping != NULL)

    c_mapping = searchInsert_ctbl(&result, ctbl, ITEM_LIT("Alice"), 3, CTBL_MODE_INSERT_RESPECT);
    TEST_FAIL_IF(result != CTBL_RESPECT_UNIQUE)
    TEST_FAIL_IF(c_mapping == NULL)
    TEST_FAIL_IF(c_mapping->chunk_id != 0)
    TEST_FAIL_IF(c_mapping->value != 3)

    c_mapping = searchInsert_ctbl(&result, ctbl, ITEM_LIT("Alice"), 5, CTBL_MODE_INSERT_REPLACE);
    TEST_FAIL_IF(result != CTBL_REPLACE_CHANGED)
    TEST_FAIL_IF(c_mapping == NULL)
    TEST_FAIL_IF(c_mapping->chunk_id != 0)
    TEST_FAIL_IF(c_mapping->value != 5)

    c_mapping = searchInsert_ctbl(&result, ctbl, ITEM_LIT("Alice"), 5, CTBL_MODE_INSERT_REPLACE);
    TEST_FAIL_IF(result != CTBL_REPLACE_NO_CHANGES)
    TEST_FAIL_IF(c_mapping == NULL)
    TEST_FAIL_IF(c_mapping->chunk_id != 0)
    TEST_FAIL_IF(c_mapping->value != 5)

    c_mapping = searchInsert_ctbl(&result, ctbl, ITEM_LIT("Alice"), 5, CTBL_MODE_INSERT_RESPECT);
    TEST_FAIL_IF(result != CTBL_RESPECT_UNIQUE)
    TEST_FAIL_IF(c_mapping == NULL)
    TEST_FAIL_IF(c_mapping->chunk_id != 0)
    TEST_FAIL_IF(c_mapping->value != 5)

    c_mapping = searchInsert_ctbl(&result, ctbl, ITEM_LIT("Alice"), 3, CTBL_MODE_INSERT_RESPECT);
    TEST_FAIL_IF(result != CTBL_RESPECT_NOT_UNIQUE)
    TEST_FAIL_IF(c_mapping == NULL)
    TEST_FAIL_IF(c_mapping->chunk_id != 0)
    TEST_FAIL_IF(c_mapping->value != 5)

    c_mapping = searchInsert_ctbl(&result, ctbl, ITEM_LIT("Alice"), 5, CTBL_MODE_SEARCH);
    TEST_FAIL_IF(result != CTBL_SEARCH_FOUND)
    TEST_FAIL_IF(c_mapping == NULL)
    TEST_FAIL_IF(c_mapping->chunk_id != 0)
    TEST_FAIL_IF(c_mapping->value != 5)

    c_mapping = searchInsert_ctbl(&result, ctbl, ITEM_LIT("Alice"), INVALID_UINT32, CTBL_MODE_SEARCH);
    TEST_FAIL_IF(result != CTBL_SEARCH_FOUND)
    TEST_FAIL_IF(c_mapping == NULL)
    TEST_FAIL_IF(c_mapping->chunk_id != 0)
    TEST_FAIL_IF(c_mapping->value != 5)

    c_mapping = searchInsert_ctbl(&result, ctbl, ITEM_LIT("Alice"), 22, CTBL_MODE_SEARCH);
    TEST_FAIL_IF(result != CTBL_SEARCH_NOT_FOUND)
    TEST_FAIL_IF(c_mapping != NULL)

    flush_ctbl(ctbl);
    TEST_FAIL_IF(LEN_CTBL(ctbl) != 0)

    c_mapping = searchInsert_ctbl(&result, ctbl, ITEM_LIT("Alice"), INVALID_UINT32, CTBL_MODE_SEARCH);
    TEST_FAIL_IF(result != CTBL_SEARCH_NOT_FOUND)
    TEST_FAIL_IF(c_mapping != NULL)

    for (char c = 'a'; c <= 'z'; c++) {
        char buf[1] = { c };
        searchInsert_ctbl(NULL, ctbl, (Item){ buf, sizeof(buf), 0}, (uint32_t)c, 2);
    }

    for (char c = 'a'; c <= 'z'; c++) {
        char buf[1] = { c };
        c_mapping = searchInsert_ctbl(
            &result, ctbl, (Item){ buf, sizeof(buf), 0}, INVALID_UINT32, CTBL_MODE_SEARCH
        );
        TEST_FAIL_IF(c_mapping->value != (uint32_t)c)
    }

    destruct_ctbl(ctbl);
    TEST_PASS
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
