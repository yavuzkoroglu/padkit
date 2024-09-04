static void test_graphmatrix(void);
static bool test_graphmatrix_connect_gmtx(void);
static bool test_graphmatrix_connectAll_gmtx(void);
static bool test_graphmatrix_construct_gmtx(void);
static bool test_graphmatrix_disconnect_gmtx(void);
static bool test_graphmatrix_disconnectAll_gmtx(void);
static bool test_graphmatrix_findSink_gmtx(void);
static bool test_graphmatrix_findSource_gmtx(void);
static bool test_graphmatrix_free_gmtx(void);
static bool test_graphmatrix_isConnected_gmtx(void);
static bool test_graphmatrix_isValid_gmtx(void);
static bool test_graphmatrix_resizeIfNecessary_gmtx(void);

static void test_graphmatrix(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_graphmatrix_construct_gmtx();
    allTestsPass &= test_graphmatrix_findSink_gmtx();
    allTestsPass &= test_graphmatrix_findSource_gmtx();
    allTestsPass &= test_graphmatrix_free_gmtx();
    allTestsPass &= test_graphmatrix_isConnected_gmtx();
    allTestsPass &= test_graphmatrix_isValid_gmtx();
    allTestsPass &= test_graphmatrix_resizeIfNecessary_gmtx();
    allTestsPass &= test_graphmatrix_connect_gmtx();
    allTestsPass &= test_graphmatrix_connectAll_gmtx();
    allTestsPass &= test_graphmatrix_disconnect_gmtx();
    allTestsPass &= test_graphmatrix_disconnectAll_gmtx();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_graphmatrix_connect_gmtx(void) {
    GraphMatrix gmtx[1] = { NOT_A_GRAPH_MATRIX };
    construct_gmtx(gmtx, 122, 115);

    connect_gmtx(gmtx, 0, 92);
    connect_gmtx(gmtx, 92, 88);
    connect_gmtx(gmtx, 88, 53);
    connect_gmtx(gmtx, 53, 121);
    connect_gmtx(gmtx, 121, 0);

    TEST_FAIL_IF(!isConnected_gmtx(gmtx, 0, 92))
    TEST_FAIL_IF(!isConnected_gmtx(gmtx, 92, 88))
    TEST_FAIL_IF(!isConnected_gmtx(gmtx, 88, 53))
    TEST_FAIL_IF(!isConnected_gmtx(gmtx, 53, 121))
    TEST_FAIL_IF(!isConnected_gmtx(gmtx, 121, 0))

    free_gmtx(gmtx);
    TEST_PASS
}

static bool test_graphmatrix_connectAll_gmtx(void) {
    GraphMatrix gmtx[1] = { NOT_A_GRAPH_MATRIX };
    construct_gmtx(gmtx, 115, 122);

    for (uint32_t source = 0; source < 115; source++)
        for (uint32_t sink = 0; sink < 122; sink++)
            TEST_FAIL_IF(isConnected_gmtx(gmtx, source, sink))

    connectAll_gmtx(gmtx);

    for (uint32_t source = 0; source < 115; source++)
        for (uint32_t sink = 0; sink < 122; sink++)
            TEST_FAIL_IF(!isConnected_gmtx(gmtx, source, sink))

    TEST_PASS
}

static bool test_graphmatrix_construct_gmtx(void) {
    GraphMatrix gmtx[2] = { NOT_A_GRAPH_MATRIX, NOT_A_GRAPH_MATRIX };
    construct_gmtx(gmtx, 1, 1);
    construct_gmtx(gmtx + 1, 131072, 131072);
    free_gmtx(gmtx);
    free_gmtx(gmtx + 1);
    TEST_PASS
}

static bool test_graphmatrix_disconnect_gmtx(void) {
    GraphMatrix gmtx[1] = { NOT_A_GRAPH_MATRIX };
    construct_gmtx(gmtx, 115, 115);

    connectAll_gmtx(gmtx);

    disconnect_gmtx(gmtx, 0, 92);
    disconnect_gmtx(gmtx, 92, 88);
    disconnect_gmtx(gmtx, 88, 53);
    disconnect_gmtx(gmtx, 53, 121);
    disconnect_gmtx(gmtx, 121, 0);

    TEST_FAIL_IF(isConnected_gmtx(gmtx, 0, 92))
    TEST_FAIL_IF(isConnected_gmtx(gmtx, 92, 88))
    TEST_FAIL_IF(isConnected_gmtx(gmtx, 88, 53))
    TEST_FAIL_IF(isConnected_gmtx(gmtx, 53, 121))
    TEST_FAIL_IF(isConnected_gmtx(gmtx, 121, 0))

    TEST_FAIL_IF(isConnected_gmtx(gmtx, 118, 3))
    TEST_FAIL_IF(isConnected_gmtx(gmtx, 12, 119))

    TEST_FAIL_IF(!isConnected_gmtx(gmtx, 32, 53))
    TEST_FAIL_IF(!isConnected_gmtx(gmtx, 53, 0))

    free_gmtx(gmtx);
    TEST_PASS
    TEST_PASS
}

static bool test_graphmatrix_disconnectAll_gmtx(void) {
    GraphMatrix gmtx[1] = { NOT_A_GRAPH_MATRIX };
    construct_gmtx(gmtx, 115, 122);

    for (uint32_t source = 0; source < 115; source++)
        for (uint32_t sink = 0; sink < 122; sink++)
            TEST_FAIL_IF(isConnected_gmtx(gmtx, source, sink))

    connectAll_gmtx(gmtx);

    for (uint32_t source = 0; source < 115; source++)
        for (uint32_t sink = 0; sink < 122; sink++)
            TEST_FAIL_IF(!isConnected_gmtx(gmtx, source, sink))

    disconnectAll_gmtx(gmtx);

    for (uint32_t source = 0; source < 115; source++)
        for (uint32_t sink = 0; sink < 122; sink++)
            TEST_FAIL_IF(isConnected_gmtx(gmtx, source, sink))

    TEST_PASS
}

static bool test_graphmatrix_findSink_gmtx(void) {
    GraphMatrix gmtx[1] = { NOT_A_GRAPH_MATRIX };
    construct_gmtx(gmtx, 3, 4);

    for (uint32_t source = 0; source < 3; source++)
        TEST_FAIL_IF(findSink_gmtx(gmtx, source, 2) != INVALID_UINT32)

    connectAll_gmtx(gmtx);

    for (uint32_t source = 0; source < 3; source++)
        for (uint32_t sink = 0; sink < 4; sink++)
            TEST_FAIL_IF(findSink_gmtx(gmtx, source, sink) != sink)

    free_gmtx(gmtx);
    TEST_PASS
}

static bool test_graphmatrix_findSource_gmtx(void) {
    GraphMatrix gmtx[1] = { NOT_A_GRAPH_MATRIX };
    construct_gmtx(gmtx, 4, 3);

    for (uint32_t sink = 0; sink < 3; sink++)
        TEST_FAIL_IF(findSource_gmtx(gmtx, sink, 2) != INVALID_UINT32)

    connectAll_gmtx(gmtx);

    for (uint32_t source = 0; source < 4; source++)
        for (uint32_t sink = 0; sink < 3; sink++)
            TEST_FAIL_IF(findSource_gmtx(gmtx, sink, source) != source)

    free_gmtx(gmtx);
    TEST_PASS
}

static bool test_graphmatrix_free_gmtx(void) {
    GraphMatrix gmtx[1] = { NOT_A_GRAPH_MATRIX };
    construct_gmtx(gmtx, 131072, 131072);
    free_gmtx(gmtx);
    TEST_PASS
}

static bool test_graphmatrix_isConnected_gmtx(void) {
    GraphMatrix gmtx[1] = { NOT_A_GRAPH_MATRIX };
    construct_gmtx(gmtx, 4, 3);

    for (uint32_t source = 0; source < 4; source++)
        for (uint32_t sink = 0; sink < 3; sink++)
            TEST_FAIL_IF(isConnected_gmtx(gmtx, source, sink))

    connectAll_gmtx(gmtx);

    for (uint32_t source = 0; source < 4; source++)
        for (uint32_t sink = 0; sink < 3; sink++)
            TEST_FAIL_IF(!isConnected_gmtx(gmtx, source, sink))

    disconnect_gmtx(gmtx, 3, 3);

    for (uint32_t source = 0; source < 4; source++) {
        TEST_FAIL_IF(isConnected_gmtx(gmtx, source, 3))
        for (uint32_t sink = 0; sink < 3; sink++)
            TEST_FAIL_IF(!isConnected_gmtx(gmtx, source, sink))
    }

    TEST_PASS
}

static bool test_graphmatrix_isValid_gmtx(void) {
    GraphMatrix gmtx[2] = { NOT_A_GRAPH_MATRIX, NOT_A_GRAPH_MATRIX };

    TEST_FAIL_IF(isValid_gmtx(gmtx))
    TEST_FAIL_IF(isValid_gmtx(gmtx + 1))

    construct_gmtx(gmtx, 1, 1);
    construct_gmtx(gmtx + 1, 131072, 131072);

    TEST_FAIL_IF(!isValid_gmtx(gmtx))
    TEST_FAIL_IF(!isValid_gmtx(gmtx + 1))

    free_gmtx(gmtx);
    free_gmtx(gmtx + 1);

    TEST_FAIL_IF(isValid_gmtx(gmtx))
    TEST_FAIL_IF(isValid_gmtx(gmtx + 1))

    TEST_PASS
}

static bool test_graphmatrix_resizeIfNecessary_gmtx(void) {
    GraphMatrix gmtx[1] = { NOT_A_GRAPH_MATRIX };
    construct_gmtx(gmtx, 4, 3);

    TEST_FAIL_IF(gmtx->height != 4)
    TEST_FAIL_IF(gmtx->width != 3)

    resizeIfNecessary_gmtx(gmtx, 4, 3);

    TEST_FAIL_IF(gmtx->height != 4)
    TEST_FAIL_IF(gmtx->width != 3)

    resizeIfNecessary_gmtx(gmtx, 4, 4);

    TEST_FAIL_IF(gmtx->height != 4)
    TEST_FAIL_IF(gmtx->width != 4)

    resizeIfNecessary_gmtx(gmtx, 5, 4);

    TEST_FAIL_IF(gmtx->height != 5)
    TEST_FAIL_IF(gmtx->width != 4)

    TEST_PASS
}
