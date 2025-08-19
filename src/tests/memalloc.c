static void test_memalloc(void);
static bool test_memalloc_mem_alloc(void);
static bool test_memalloc_mem_calloc(void);
static bool test_memalloc_mem_realloc(void);
static bool test_memalloc_mem_recalloc(void);

static void test_memalloc(void) {
    bool all_tests_pass = 1;

    all_tests_pass &= test_memalloc_mem_alloc();
    all_tests_pass &= test_memalloc_mem_calloc();
    all_tests_pass &= test_memalloc_mem_realloc();
    all_tests_pass &= test_memalloc_mem_recalloc();

    if (all_tests_pass) TESTS_PASS_MESSAGE
}

static bool test_memalloc_mem_alloc(void) {
    char* buffer[2] = { mem_alloc(131072), mem_alloc(1024) };

    memset(buffer[0], '\0', 131072);
    memcpy(buffer[1], buffer[0], 1024);

    TEST_FAIL_IF(buffer[1][1023] != '\0')

    free(buffer[0]);
    free(buffer[1]);

    TEST_PASS
}

static bool test_memalloc_mem_calloc(void) {
    char* buffer[2] = { mem_calloc(256, 256), mem_calloc(16, 16) };

    TEST_FAIL_IF(buffer[0][1023] != '\0')
    TEST_FAIL_IF(buffer[1][255] != '\0')

    free(buffer[0]);
    free(buffer[1]);

    TEST_PASS
}

static bool test_memalloc_mem_realloc(void) {
    char* buffer = mem_alloc(1024);

    mem_realloc((void**)&(buffer), 131072);

    memset(buffer, '\0', 131072);

    TEST_FAIL_IF(buffer[131071] != '\0')

    free(buffer);

    TEST_PASS
}

static bool test_memalloc_mem_recalloc(void) {
    char* buffer = mem_calloc(16, 16);

    mem_recalloc((void**)&(buffer), 16, 256, 16);

    TEST_FAIL_IF(buffer[4095] != '\0')

    free(buffer);

    TEST_PASS
}

