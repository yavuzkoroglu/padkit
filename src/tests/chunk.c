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
static bool test_chunk_free_chunk(void);
static bool test_chunk_fromStream_chunk(void);
static bool test_chunk_isValid_chunk(void);

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
    allTestsPass &= test_chunk_free_chunk();
    allTestsPass &= test_chunk_fromStream_chunk();
    allTestsPass &= test_chunk_isValid_chunk();

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
    Chunk head = NOT_A_CHUNK;
    Chunk tail = NOT_A_CHUNK;

    constructEmpty_chunk(head, 10, 10);
    constructEmpty_chunk(tail, 10, 10);

    concat_chunk(head, tail);

    TEST_FAIL_IF(AREA_CHUNK(head) != 0)

    addItem_chunk(head, 3, "abc");
    addItem_chunk(tail, 3, "def");

    TEST_FAIL_IF(AREA_CHUNK(head) != 3)
    TEST_FAIL_IF(memcmp(get_chunk(head, 0), "abc", 3) != 0)
    TEST_FAIL_IF(memcmp(get_chunk(tail, 0), "def", 3) != 0)

    concat_chunk(head, tail);

    TEST_FAIL_IF(AREA_CHUNK(head) != 6)
    TEST_FAIL_IF(memcmp(get_chunk(head, 0), "abcdef", 6) != 0)
    TEST_FAIL_IF(memcmp(get_chunk(tail, 0), "def", 3) != 0)

    free_chunk(head);
    free_chunk(tail);
    TEST_PASS
}

static bool test_chunk_constructEmpty_chunk(void) {
    Chunk chunk_A = NOT_A_CHUNK;
    Chunk chunk_B = NOT_A_CHUNK;
    constructEmpty_chunk(chunk_A, 1, 1);
    constructEmpty_chunk(chunk_B, 1000000, 1000000);
    free_chunk(chunk_A);
    free_chunk(chunk_B);
    TEST_PASS
}

static bool test_chunk_delete_chunk(void) {
    int celsius[]       = { 12, 41, 23, -3 };
    double humidities[] = { 80.5, 62.3, 34.5 };
    Chunk chunk         = NOT_A_CHUNK;
    constructEmpty_chunk(chunk, 1024, 2);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 0)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 0)

    addItem_chunk(chunk, sizeof(celsius), celsius);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != sizeof(celsius))
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 1)

    addItem_chunk(chunk, sizeof(humidities), humidities);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != sizeof(celsius) + sizeof(humidities))
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 2)

    delete_chunk(chunk, 0, 1);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != sizeof(humidities))
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 1)

    delete_chunk(chunk, 0, 1);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 0)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 0)

    free_chunk(chunk);
    TEST_PASS
}

static bool test_chunk_deleteLast_chunk(void) {
    int celsius[]       = { 12, 41, 23, -3 };
    double humidities[] = { 80.5, 62.3, 34.5 };
    Chunk chunk         = NOT_A_CHUNK;
    constructEmpty_chunk(chunk, 1024, 2);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 0)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 0)

    addItem_chunk(chunk, sizeof(celsius), celsius);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != sizeof(celsius))
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 1)

    addItem_chunk(chunk, sizeof(humidities), humidities);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != sizeof(celsius) + sizeof(humidities))
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 2)

    deleteLast_chunk(chunk, 1);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != sizeof(celsius))
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 1)

    deleteLast_chunk(chunk, 1);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 0)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 0)

    free_chunk(chunk);
    TEST_PASS
}

static bool test_chunk_duplicateItem_chunk(void) {
    Chunk chunk = NOT_A_CHUNK;
    constructEmpty_chunk(chunk, 1024, 16);

    addItem_chunk(chunk, 3, "abc");
    addItem_chunk(chunk, 3, "def");
    addItem_chunk(chunk, 2, "gh");

    duplicateItem_chunk(chunk, 1);

    TEST_FAIL_IF(memcmp(chunk->array, "abcdefghdef", AREA_CHUNK(chunk)) != 0)

    free_chunk(chunk);
    TEST_PASS
}

static bool test_chunk_free_chunk(void) {
    Chunk chunk = NOT_A_CHUNK;
    constructEmpty_chunk(chunk, 1000000, 1000000);
    free_chunk(chunk);
    TEST_PASS
}

static bool test_chunk_fromStream_chunk(void) {
    Chunk chunk         = NOT_A_CHUNK;
    FILE* const stream  = fopen("test_artifacts/words.txt", "r");
    TEST_FAIL_IF(stream == NULL)

    constructEmpty_chunk(chunk, 1024, 4);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 0)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 0)

    fromStream_chunk(chunk, stream, NULL, INVALID_SIZE);

    TEST_FAIL_IF(AREA_CHUNK(chunk) != 25)
    TEST_FAIL_IF(LEN_CHUNK(chunk) != 4)

    TEST_FAIL_IF(memcmp(chunk->array, "first\nsecond\nthird\nfourth\n", AREA_CHUNK(chunk)) != 0)

    fclose(stream);
    free_chunk(chunk);
    TEST_PASS
}

static bool test_chunk_isValid_chunk(void) {
    Chunk chunk = NOT_A_CHUNK;

    TEST_FAIL_IF(isValid_chunk(chunk))

    constructEmpty_chunk(chunk, 1000000, 1000000);

    TEST_FAIL_IF(!isValid_chunk(chunk))

    free_chunk(chunk);

    TEST_FAIL_IF(isValid_chunk(chunk))

    TEST_PASS
}
