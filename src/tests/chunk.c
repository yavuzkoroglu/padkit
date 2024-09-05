static void test_chunk(void);
static bool test_chunk_addIndeterminateItem_chunk(void);
static bool test_chunk_addItem_chunk(void);
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

    allTestsPass &= test_chunk_addIndeterminateItem_chunk();
    allTestsPass &= test_chunk_addItem_chunk();
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

static bool test_chunk_addIndeterminateItem_chunk(void) {
    void* item  = NULL;
    uint32_t sz = INVALID_UINT32;
    Chunk chunk = NOT_A_CHUNK;
    constructEmpty_chunk(chunk, 5, 2);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 0)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 0)

    addIndeterminateItem_chunk(chunk, 4);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 4)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 1)

    addIndeterminateItem_chunk(chunk, 1);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 5)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 2)

    addIndeterminateItem_chunk(chunk, 3);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 8)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 3)

    memcpy(get_chunk(chunk, 0), "abc", sz_item_chunk(chunk, 0));
    memcpy(get_chunk(chunk, 1), "", sz_item_chunk(chunk, 1));
    memcpy(get_chunk(chunk, 2), "de", sz_item_chunk(chunk, 2));

    item    = get_chunk(chunk, 0);
    sz      = sz_item_chunk(chunk, 0);
    TEST_FAIL_IF(sz != 4)
    TEST_FAIL_IF(memcmp(item, "abc", sz) != 0)

    item    = get_chunk(chunk, 1);
    sz      = sz_item_chunk(chunk, 1);
    TEST_FAIL_IF(sz != 1)
    TEST_FAIL_IF(memcmp(item, "", sz) != 0)

    item    = get_chunk(chunk, 2);
    sz      = sz_item_chunk(chunk, 2);
    TEST_FAIL_IF(sz != 3)
    TEST_FAIL_IF(memcmp(item, "de", sz) != 0)

    free_chunk(chunk);
    TEST_PASS
}

static bool test_chunk_addItem_chunk(void) {
    Chunk chunk = NOT_A_CHUNK;
    constructEmpty_chunk(chunk, 5, 2);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 0)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 0)

    addItem_chunk(chunk, 4, "abc");

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 4)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 1)

    addItem_chunk(chunk, 1, "");

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 5)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 2)

    addItem_chunk(chunk, 3, "de");

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 8)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 3)

    free_chunk(chunk);
    TEST_PASS
}

static bool test_chunk_append_chunk(void) {
    void* item  = NULL;
    uint32_t sz = INVALID_UINT32;
    Chunk chunk = NOT_A_CHUNK;
    constructEmpty_chunk(chunk, 5, 2);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 0)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 0)

    append_chunk(chunk, 3, "abc");

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 3)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 1)

    append_chunk(chunk, 3, "de");

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 6)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 1)

    item    = getLast_chunk(chunk);
    sz      = sz_itemLast_chunk(chunk);
    TEST_FAIL_IF(sz != 6)
    TEST_FAIL_IF(memcmp(item, "abcde", sz) != 0)

    free_chunk(chunk);
    TEST_PASS
}

static bool test_chunk_appendDuplicate_chunk(void) {
    void* item  = NULL;
    uint32_t sz = INVALID_UINT32;
    Chunk chunk = NOT_A_CHUNK;
    constructEmpty_chunk(chunk, 5, 2);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 0)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 0)

    append_chunk(chunk, 3, "abc");

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 3)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 1)

    appendDuplicate_chunk(chunk, 0);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 6)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 1)

    item    = getLast_chunk(chunk);
    sz      = sz_itemLast_chunk(chunk);
    TEST_FAIL_IF(sz != 6)
    TEST_FAIL_IF(memcmp(item, "abcabc", sz) != 0)

    free_chunk(chunk);
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

