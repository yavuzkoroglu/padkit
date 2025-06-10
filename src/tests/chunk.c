static void test_chunk(void);
static bool test_chunk_add_chunk(void);
static bool test_chunk_addDup_chunk(void);
static bool test_chunk_addIndeterminate_chunk(void);
static bool test_chunk_addIndeterminateN_chunk(void);
static bool test_chunk_isValid_chunk(void);

static void test_chunk(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_chunk_add_chunk();
    allTestsPass &= test_chunk_addDup_chunk();
    allTestsPass &= test_chunk_addIndeterminate_chunk();
    allTestsPass &= test_chunk_addIndeterminateN_chunk();
    allTestsPass &= test_chunk_isValid_chunk();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_chunk_add_chunk(void) {
    Item item       = NOT_AN_ITEM;
    Chunk chunk[1]  = { NOT_A_CHUNK };
    constructEmpty_chunk(chunk, 5, 2);

    item = add_chunk(chunk, "abc", sizeof("abc"));
    TEST_FAIL_IF(item.p == NULL)
    TEST_FAIL_IF(item.sz != sizeof("abc"))
    TEST_FAIL_IF(item.offset != 0)
    TEST_FAIL_IF(memcmp(item.p, "abc", sizeof("abc")) != 0)

    destruct_chunk(chunk);
    TEST_PASS
}

static bool test_chunk_addDup_chunk(void) {
    TEST_PASS
}

static bool test_chunk_addIndeterminate_chunk(void) {
    Item item       = NOT_AN_ITEM;
    Chunk chunk[1]  = { NOT_A_CHUNK };
    constructEmpty_chunk(chunk, 5, 2);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 0)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 0)

    item = addIndeterminate_chunk(chunk, 4);
    TEST_FAIL_IF(item.p == NULL)
    TEST_FAIL_IF(item.sz != 4)
    TEST_FAIL_IF(item.offset != 0)

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 4)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 1)

    item = addIndeterminate_chunk(chunk, 1);
    TEST_FAIL_IF(item.p == NULL)
    TEST_FAIL_IF(item.sz != 1)
    TEST_FAIL_IF(item.offset != 4)

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 5)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 2)

    item = addIndeterminate_chunk(chunk, 3);
    TEST_FAIL_IF(item.p == NULL)
    TEST_FAIL_IF(item.sz != 3)
    TEST_FAIL_IF(item.offset != 5)

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 8)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 3)

    destruct_chunk(chunk);
    TEST_PASS
}

static bool test_chunk_addIndeterminateN_chunk(void) {
    Item item = NOT_AN_ITEM;
    Chunk chunk[1] = { NOT_A_CHUNK };
    constructEmpty_chunk(chunk, 5, 2);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 0)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 0)

    item = addIndeterminateN_chunk(chunk, 3, 4);
    TEST_FAIL_IF(item.p == NULL)
    TEST_FAIL_IF(item.sz != 4)
    TEST_FAIL_IF(item.offset != 0)

    iterateNext_item(&item);
    TEST_FAIL_IF(item.p == NULL)
    TEST_FAIL_IF(item.sz != 4)
    TEST_FAIL_IF(item.offset != 4)

    iterateNext_item(&item);
    TEST_FAIL_IF(item.p == NULL)
    TEST_FAIL_IF(item.sz != 4)
    TEST_FAIL_IF(item.offset != 8)

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 12)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 3)

    destruct_chunk(chunk);
    TEST_PASS
}

static bool test_chunk_isValid_chunk(void) {
    Chunk chunk[1] = { NOT_A_CHUNK };
    TEST_FAIL_IF(isValid_chunk(chunk))

    constructEmpty_chunk(chunk, 1, 1);
    TEST_FAIL_IF(!isValid_chunk(chunk))

    destruct_chunk(chunk);
    TEST_FAIL_IF(isValid_chunk(chunk))

    TEST_PASS
}
