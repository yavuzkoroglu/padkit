static void test_arraylist(void);
static bool test_arraylist_add_alist(void);
static bool test_arraylist_addIndeterminate_alist(void);
static bool test_arraylist_addZeros_alist(void);
static bool test_arraylist_bsearch_alist(void);
static bool test_arraylist_concat_alist(void);

static int compar_char(void const* a, void const* b);

/*
static bool test_arraylist_constructEmpty_alist(void);
static bool test_arraylist_flush_alist(void);
static bool test_arraylist_free_alist(void);
static bool test_arraylist_get_alist(void);
static bool test_arraylist_isSorted_alist(void);
static bool test_arraylist_isValid_alist(void);
static bool test_arraylist_lsearch_alist(void);
static bool test_arraylist_qsort_alist(void);
static bool test_arraylist_removeLast_alist(void);
static bool test_arraylist_reverse_alist(void);
static bool test_arraylist_set_alist(void);
static bool test_arraylist_setZeros_alist(void);
*/

static void test_arraylist(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_arraylist_add_alist();
    allTestsPass &= test_arraylist_addIndeterminate_alist();
    allTestsPass &= test_arraylist_addZeros_alist();
    allTestsPass &= test_arraylist_bsearch_alist();
    allTestsPass &= test_arraylist_concat_alist();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_arraylist_add_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    constructEmpty_alist(list, 1, 4);

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != 4)

    TEST_FAIL_IF(strncmp(add_alist(list, 6, "Yavuz"), "Yavuz", 6) != 0)

    TEST_FAIL_IF(list->size != 6)
    TEST_FAIL_IF(list->cap != 8)

    TEST_FAIL_IF(strncmp(strncpy(add_alist(list, 7, NULL), "Dilara", 7), "Dilara", 7) != 0)

    TEST_FAIL_IF(list->size != 13)
    TEST_FAIL_IF(list->cap != 16)

    free_alist(list);
    TEST_PASS
}

static bool test_arraylist_addIndeterminate_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    constructEmpty_alist(list, sizeof(int), 1);

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != 1)

    addIndeterminate_alist(list, 5);

    TEST_FAIL_IF(list->size != 5)
    TEST_FAIL_IF(list->cap != 8)

    free_alist(list);
    TEST_PASS
}

static bool test_arraylist_addZeros_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    constructEmpty_alist(list, sizeof(int), 8);

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != 8)

    addZeros_alist(list, 8);

    TEST_FAIL_IF(list->size != 8)
    TEST_FAIL_IF(list->cap != 8)

    for (uint32_t i = 0; i < list->size; i++) {
        int* const value = get_alist(list, i);
        TEST_FAIL_IF(*value != 0)
    }

    free_alist(list);
    TEST_PASS
}

static bool test_arraylist_bsearch_alist(void) {
    char const letters[]    = { 'a', 'd', 'k', 'l', 'm', 'n', 'q', 'x' };
    ArrayList list[1]       = { NOT_AN_ALIST };
    constructEmpty_alist(list, 1, sizeof(letters));

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != sizeof(letters))

    TEST_FAIL_IF(strncmp(add_alist(list, sizeof(letters), letters), "adklmnqx", 8) != 0)

    TEST_FAIL_IF(list->size != sizeof(letters))
    TEST_FAIL_IF(list->cap != sizeof(letters))

    for (uint32_t i = 0; i < sizeof(letters); i++) {
        char* key[1] = { NULL };
        TEST_FAIL_IF(bsearch_alist((void**)key, list, letters + i, compar_char) != i)
        TEST_FAIL_IF(*key[0] != letters[i])
    }

    free_alist(list);
    TEST_PASS
}

static int compar_char(void const* a, void const* b) {
    return (*(char const*)a - *(char const*)b);
}

static bool test_arraylist_concat_alist(void) {
    ArrayList head[1] = { NOT_AN_ALIST };
    ArrayList tail[1] = { NOT_AN_ALIST };

    constructEmpty_alist(head, 1, 5);
    constructEmpty_alist(tail, 1, 5);

    TEST_FAIL_IF(head->size != 0)
    TEST_FAIL_IF(tail->size != 0)

    TEST_FAIL_IF(head->cap != 5)
    TEST_FAIL_IF(tail->cap != 5)

    concat_alist(head, tail);

    TEST_FAIL_IF(head->size != 0)
    TEST_FAIL_IF(tail->size != 0)

    TEST_FAIL_IF(head->cap != 5)
    TEST_FAIL_IF(tail->cap != 5)

    TEST_FAIL_IF(strncmp(add_alist(tail, 3, "abc"), "abc", 3) != 0)

    concat_alist(head, tail);

    TEST_FAIL_IF(head->size != 3)
    TEST_FAIL_IF(tail->size != 3)

    TEST_FAIL_IF(head->cap != 5)
    TEST_FAIL_IF(tail->cap != 5)

    TEST_FAIL_IF(strncmp(add_alist(tail, 3, "def"), "def", 3) != 0)

    concat_alist(head, tail);

    TEST_FAIL_IF(head->size != 9)
    TEST_FAIL_IF(tail->size != 6)

    TEST_FAIL_IF(head->cap != 10)
    TEST_FAIL_IF(tail->cap != 10)

    TEST_FAIL_IF(strncmp(head->array, "abcabcdef", 9) != 0)
    TEST_FAIL_IF(strncmp(tail->array, "abcdef", 6) != 0)

    free_alist(head);
    free_alist(tail);
    TEST_PASS
}
