static void test_bitmatrix(void);
static bool test_bitmatrix_construct_bmtx(void);
static bool test_bitmatrix_findInCol_bmtx(void);
static bool test_bitmatrix_findInRow_bmtx(void);
static bool test_bitmatrix_destruct_bmtx(void);
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
    allTestsPass &= test_bitmatrix_destruct_bmtx();
    allTestsPass &= test_bitmatrix_findInCol_bmtx();
    allTestsPass &= test_bitmatrix_findInRow_bmtx();
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
    BitMatrix bmtx[2] = { NOT_A_BMATRIX, NOT_A_BMATRIX };
    construct_bmtx(bmtx, 1, 1);
    construct_bmtx(bmtx + 1, 131072, 131072);
    destruct_bmtx(bmtx);
    destruct_bmtx(bmtx + 1);
    TEST_PASS
}

static bool test_bitmatrix_destruct_bmtx(void) {
    BitMatrix bmtx[1] = { NOT_A_BMATRIX };
    construct_bmtx(bmtx, 131072, 131072);
    destruct_bmtx(bmtx);
    TEST_PASS
}

static bool test_bitmatrix_findInCol_bmtx(void) {
    BitMatrix bmtx[1] = { NOT_A_BMATRIX };
    construct_bmtx(bmtx, 4, 3);

    for (uint32_t col = 0; col < 3; col++)
        TEST_FAIL_IF(findInCol_bmtx(bmtx, col, 2, 1) != INVALID_UINT32)

    for (uint32_t row = 0; row < 4; row++)
        for (uint32_t col = 0; col < 3; col++)
            TEST_FAIL_IF(findInCol_bmtx(bmtx, col, row, 0) != row)

    destruct_bmtx(bmtx);
    TEST_PASS
}

static bool test_bitmatrix_findInRow_bmtx(void) {
    BitMatrix bmtx[1] = { NOT_A_BMATRIX };
    construct_bmtx(bmtx, 3, 4);

    for (uint32_t row = 0; row < 3; row++)
        TEST_FAIL_IF(findInRow_bmtx(bmtx, row, 2, 1) != INVALID_UINT32)

    for (uint32_t row = 0; row < 3; row++)
        for (uint32_t col = 0; col < 4; col++)
            TEST_FAIL_IF(findInRow_bmtx(bmtx, row, col, 0) != col)

    destruct_bmtx(bmtx);
    TEST_PASS
}

static bool test_bitmatrix_get_bmtx(void) {
    BitMatrix bmtx[1] = { NOT_A_BMATRIX };
    construct_bmtx(bmtx, 4, 3);

    for (uint32_t row = 0; row < bmtx->height; row++)
        for (uint32_t col = 0; col < bmtx->width; col++)
            TEST_FAIL_IF(get_bmtx(bmtx, row, col) == 1)

    setAll_bmtx(bmtx);

    for (uint32_t row = 0; row < bmtx->height; row++)
        for (uint32_t col = 0; col < bmtx->width; col++)
            TEST_FAIL_IF(get_bmtx(bmtx, row, col) == 0)

    unset_bmtx(bmtx, bmtx->height - 1, bmtx->width);

    for (uint32_t row = 0; row < bmtx->height; row++) {
        TEST_FAIL_IF(get_bmtx(bmtx, row, bmtx->width - 1) == 1)
        for (uint32_t col = 0; col < bmtx->width - 1; col++)
            TEST_FAIL_IF(get_bmtx(bmtx, row, col) == 0)
    }

    destruct_bmtx(bmtx);
    TEST_PASS
}

static bool test_bitmatrix_isValid_bmtx(void) {
    BitMatrix bmtx[2] = { NOT_A_BMATRIX, NOT_A_BMATRIX };

    TEST_FAIL_IF(isValid_bmtx(bmtx))
    TEST_FAIL_IF(isValid_bmtx(bmtx + 1))

    construct_bmtx(bmtx, 1, 1);
    construct_bmtx(bmtx + 1, 131072, 131072);

    TEST_FAIL_IF(!isValid_bmtx(bmtx))
    TEST_FAIL_IF(!isValid_bmtx(bmtx + 1))

    destruct_bmtx(bmtx);
    destruct_bmtx(bmtx + 1);

    TEST_FAIL_IF(isValid_bmtx(bmtx))
    TEST_FAIL_IF(isValid_bmtx(bmtx + 1))

    TEST_PASS
}

static bool test_bitmatrix_resizeIfNecessary_bmtx(void) {
    BitMatrix bmtx[1] = { NOT_A_BMATRIX };
    construct_bmtx(bmtx, 4, 3);

    TEST_FAIL_IF(bmtx->height != 4)
    TEST_FAIL_IF(bmtx->width != 3)

    resizeIfNecessary_bmtx(bmtx, 4, 3);

    TEST_FAIL_IF(bmtx->height != 4)
    TEST_FAIL_IF(bmtx->width != 3)

    resizeIfNecessary_bmtx(bmtx, 4, 4);

    TEST_FAIL_IF(bmtx->height != 4)
    TEST_FAIL_IF(bmtx->width != 4)

    resizeIfNecessary_bmtx(bmtx, 5, 4);

    TEST_FAIL_IF(bmtx->height != 5)
    TEST_FAIL_IF(bmtx->width != 4)

    destruct_bmtx(bmtx);
    TEST_PASS
}

static bool test_bitmatrix_set_bmtx(void) {
    BitMatrix bmtx[1] = { NOT_A_BMATRIX };
    construct_bmtx(bmtx, 122, 115);

    set_bmtx(bmtx, 0, 92);
    set_bmtx(bmtx, 92, 88);
    set_bmtx(bmtx, 88, 53);
    set_bmtx(bmtx, 53, 121);
    set_bmtx(bmtx, 121, 0);

    TEST_FAIL_IF(get_bmtx(bmtx, 0, 92) == 0)
    TEST_FAIL_IF(get_bmtx(bmtx, 92, 88) == 0)
    TEST_FAIL_IF(get_bmtx(bmtx, 88, 53) == 0)
    TEST_FAIL_IF(get_bmtx(bmtx, 53, 121) == 0)
    TEST_FAIL_IF(get_bmtx(bmtx, 121, 0) == 0)

    TEST_FAIL_IF(get_bmtx(bmtx, 0, 0) == 1)

    destruct_bmtx(bmtx);
    TEST_PASS
}

static bool test_bitmatrix_setAll_bmtx(void) {
    BitMatrix bmtx[1] = { NOT_A_BMATRIX };
    construct_bmtx(bmtx, 115, 122);

    for (uint32_t row = 0; row < bmtx->height; row++)
        for (uint32_t col = 0; col < bmtx->width; col++)
            TEST_FAIL_IF(get_bmtx(bmtx, row, col) == 1)

    setAll_bmtx(bmtx);

    for (uint32_t row = 0; row < bmtx->height; row++)
        for (uint32_t col = 0; col < bmtx->width; col++)
            TEST_FAIL_IF(get_bmtx(bmtx, row, col) == 0)

    destruct_bmtx(bmtx);
    TEST_PASS
}

static bool test_bitmatrix_unset_bmtx(void) {
    BitMatrix bmtx[1] = { NOT_A_BMATRIX };
    construct_bmtx(bmtx, 121, 115);

    setAll_bmtx(bmtx);

    unset_bmtx(bmtx, 0, 92);
    unset_bmtx(bmtx, 92, 88);
    unset_bmtx(bmtx, 88, 53);
    unset_bmtx(bmtx, 53, 121);
    unset_bmtx(bmtx, 121, 0);

    TEST_FAIL_IF(get_bmtx(bmtx, 0, 92) == 1)
    TEST_FAIL_IF(get_bmtx(bmtx, 92, 88) == 1)
    TEST_FAIL_IF(get_bmtx(bmtx, 88, 53) == 1)
    TEST_FAIL_IF(get_bmtx(bmtx, 53, 121) == 1)
    TEST_FAIL_IF(get_bmtx(bmtx, 121, 0) == 1)

    TEST_FAIL_IF(get_bmtx(bmtx, 118, 3) == 0)
    TEST_FAIL_IF(get_bmtx(bmtx, 12, 119) == 1)

    TEST_FAIL_IF(get_bmtx(bmtx, 32, 53) == 0)
    TEST_FAIL_IF(get_bmtx(bmtx, 53, 0) == 0)

    destruct_bmtx(bmtx);
    TEST_PASS
}

static bool test_bitmatrix_unsetAll_bmtx(void) {
    BitMatrix bmtx[1] = { NOT_A_BMATRIX };
    construct_bmtx(bmtx, 115, 122);

    for (uint32_t row = 0; row < 115; row++)
        for (uint32_t col = 0; col < 122; col++)
            TEST_FAIL_IF(get_bmtx(bmtx, row, col) == 1)

    setAll_bmtx(bmtx);

    for (uint32_t row = 0; row < 115; row++)
        for (uint32_t col = 0; col < 122; col++)
            TEST_FAIL_IF(get_bmtx(bmtx, row, col) == 0)

    unsetAll_bmtx(bmtx);

    for (uint32_t row = 0; row < 115; row++)
        for (uint32_t col = 0; col < 122; col++)
            TEST_FAIL_IF(get_bmtx(bmtx, row, col) == 1)

    destruct_bmtx(bmtx);
    TEST_PASS
}
