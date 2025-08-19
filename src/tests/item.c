static void test_item(void);
static bool test_item_hash_item(void);
static bool test_item_isValid_item(void);

static void test_item(void) {
    bool all_tests_pass = 1;

    all_tests_pass &= test_item_hash_item();
    all_tests_pass &= test_item_isValid_item();

    if (all_tests_pass) TESTS_PASS_MESSAGE
}

static bool test_item_hash_item(void) {
    Item items[3] = {
        (Item){  "", 1, 0 },
        (Item){ "a", 1, 0 },
        (Item){ "a", 2, 0 }
    };
    uint32_t const hash_values[3] = {
        177573,
        177670,
        5863110
    };
    size_t const nItems = sizeof(items) / sizeof(Item);

    for (size_t i = 0; i < nItems; i++) {
        TEST_FAIL_IF(hash32_item(items[i]) != hash_values[i])
        TEST_FAIL_IF(hash64_item(items[i]) != (uint64_t)hash_values[i])
    }

    TEST_PASS
}

static bool test_item_isValid_item(void) {
    Item items[3] = {
        (Item){  "", 0, 0 },
        (Item){ "a", 1, SZ32_MAX },
        (Item){ NULL, 2, 0 }
    };

    TEST_FAIL_IF(!isValid_item(items[0]))
    TEST_FAIL_IF(isValid_item(items[1]))
    TEST_FAIL_IF(isValid_item(items[2]))

    TEST_PASS
}
