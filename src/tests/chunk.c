static void test_chunk(void);
static bool test_chunk_addItem_chunk(void);
static bool test_chunk_addIndeterminateItem_chunk(void);
static bool test_chunk_append_chunk(void);
static bool test_chunk_appendDuplicate_chunk(void);
static bool test_chunk_concat_chunk(void);
static bool test_chunk_constructEmpty_chunk(void);
static bool test_chunk_delete_chunk(void);
static bool test_chunk_deleteLast_chunk(void);
static bool test_chunk_duplicateItem_chunk(void);
static bool test_chunk_flush_chunk(void);
static bool test_chunk_free_chunk(void);
static bool test_chunk_fromStream_chunk(void);
static bool test_chunk_fromStreamAsWhole_chunk(void);
static bool test_chunk_get_chunk(void);
static bool test_chunk_getLast_chunk(void);
static bool test_chunk_isValid_chunk(void);
static bool test_chunk_splitLast_chunk(void);
static bool test_chunk_sz_item_chunk(void);
static bool test_chunk_sz_itemLast_chunk(void);

static void test_chunk(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_chunk_addItem_chunk();
    allTestsPass &= test_chunk_addIndeterminateItem_chunk();
    allTestsPass &= test_chunk_append_chunk();
    allTestsPass &= test_chunk_appendDuplicate_chunk();
    allTestsPass &= test_chunk_concat_chunk();
    allTestsPass &= test_chunk_constructEmpty_chunk();
    allTestsPass &= test_chunk_delete_chunk();
    allTestsPass &= test_chunk_deleteLast_chunk();
    allTestsPass &= test_chunk_duplicateItem_chunk();
    allTestsPass &= test_chunk_flush_chunk();
    allTestsPass &= test_chunk_free_chunk();
    allTestsPass &= test_chunk_fromStream_chunk();
    allTestsPass &= test_chunk_fromStreamAsWhole_chunk();
    allTestsPass &= test_chunk_get_chunk();
    allTestsPass &= test_chunk_getLast_chunk();
    allTestsPass &= test_chunk_isValid_chunk();
    allTestsPass &= test_chunk_splitLast_chunk();
    allTestsPass &= test_chunk_sz_item_chunk();
    allTestsPass &= test_chunk_sz_itemLast_chunk();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_chunk_addItem_chunk(void) {
    TEST_PASS
}

static bool test_chunk_addIndeterminateItem_chunk(void) {
    TEST_PASS
}

static bool test_chunk_append_chunk(void) {
    TEST_PASS
}

static bool test_chunk_appendDuplicate_chunk(void) {
    TEST_PASS
}

static bool test_chunk_concat_chunk(void) {
    TEST_PASS
}

static bool test_chunk_constructEmpty_chunk(void) {
    TEST_PASS
}

static bool test_chunk_delete_chunk(void) {
    TEST_PASS
}

static bool test_chunk_deleteLast_chunk(void) {
    TEST_PASS
}

static bool test_chunk_duplicateItem_chunk(void) {
    TEST_PASS
}

static bool test_chunk_flush_chunk(void) {
    TEST_PASS
}

static bool test_chunk_free_chunk(void) {
    TEST_PASS
}

static bool test_chunk_fromStream_chunk(void) {
    TEST_PASS
}

static bool test_chunk_fromStreamAsWhole_chunk(void) {
    TEST_PASS
}

static bool test_chunk_get_chunk(void) {
    TEST_PASS
}

static bool test_chunk_getLast_chunk(void) {
    TEST_PASS
}

static bool test_chunk_isValid_chunk(void) {
    TEST_PASS
}

static bool test_chunk_splitLast_chunk(void) {
    TEST_PASS
}

static bool test_chunk_sz_item_chunk(void) {
    TEST_PASS
}

static bool test_chunk_sz_itemLast_chunk(void) {
    TEST_PASS
}

