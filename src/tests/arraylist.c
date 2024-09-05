static int compar_char(void const* a, void const* b);

static void test_arraylist(void);
static bool test_arraylist_add_alist(void);
static bool test_arraylist_addIndeterminate_alist(void);
static bool test_arraylist_addZeros_alist(void);
static bool test_arraylist_bsearch_alist(void);
static bool test_arraylist_concat_alist(void);
static bool test_arraylist_constructEmpty_alist(void);
static bool test_arraylist_flush_alist(void);
static bool test_arraylist_free_alist(void);
static bool test_arraylist_get_alist(void);
static bool test_arraylist_getLast_alist(void);
static bool test_arraylist_isSorted_alist(void);
static bool test_arraylist_isValid_alist(void);
static bool test_arraylist_lsearch_alist(void);
static bool test_arraylist_qsort_alist(void);
static bool test_arraylist_removeLast_alist(void);
static bool test_arraylist_reverse_alist(void);
static bool test_arraylist_set_alist(void);
static bool test_arraylist_setZeros_alist(void);

static int compar_char(void const* a, void const* b) {
    return (*(char const*)a - *(char const*)b);
}

static void test_arraylist(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_arraylist_add_alist();
    allTestsPass &= test_arraylist_addIndeterminate_alist();
    allTestsPass &= test_arraylist_addZeros_alist();
    allTestsPass &= test_arraylist_bsearch_alist();
    allTestsPass &= test_arraylist_concat_alist();
    allTestsPass &= test_arraylist_constructEmpty_alist();
    allTestsPass &= test_arraylist_flush_alist();
    allTestsPass &= test_arraylist_free_alist();
    allTestsPass &= test_arraylist_get_alist();
    allTestsPass &= test_arraylist_getLast_alist();
    allTestsPass &= test_arraylist_isSorted_alist();
    allTestsPass &= test_arraylist_isValid_alist();
    allTestsPass &= test_arraylist_lsearch_alist();
    allTestsPass &= test_arraylist_qsort_alist();
    allTestsPass &= test_arraylist_removeLast_alist();
    allTestsPass &= test_arraylist_reverse_alist();
    allTestsPass &= test_arraylist_set_alist();
    allTestsPass &= test_arraylist_setZeros_alist();

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
        int const* const value = get_alist(list, i);
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

    TEST_FAIL_IF(strncmp(add_alist(list, sizeof(letters), letters), letters, 8) != 0)

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

static bool test_arraylist_constructEmpty_alist(void) {
    ArrayList list[2] = { NOT_AN_ALIST, NOT_AN_ALIST };
    constructEmpty_alist(list, sizeof(int), 1);
    constructEmpty_alist(list + 1, sizeof(int), SZ32_MAX - 1);

    TEST_FAIL_IF(!isValid_alist(list))
    TEST_FAIL_IF(!isValid_alist(list + 1))

    free_alist(list);
    free_alist(list + 1);
    TEST_PASS
}

static bool test_arraylist_flush_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    constructEmpty_alist(list, sizeof(int), 5);

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != 5)

    flush_alist(list);

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != 5)

    addZeros_alist(list, 5);

    TEST_FAIL_IF(list->size != 5)
    TEST_FAIL_IF(list->cap != 5)

    flush_alist(list);

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != 5)

    free_alist(list);
    TEST_PASS
}

static bool test_arraylist_free_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    constructEmpty_alist(list, sizeof(int), SZ32_MAX - 1);
    free_alist(list);
    TEST_PASS
}

static bool test_arraylist_get_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1]       = { NOT_AN_ALIST };
    constructEmpty_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    add_alist(list, nGrades, grades);

    TEST_FAIL_IF(list->size != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    for (uint32_t i = 0; i < list->size; i++) {
        int const* const grade = get_alist(list, i);
        TEST_FAIL_IF(*grade != grades[i])
    }

    free_alist(list);
    TEST_PASS
}

static bool test_arraylist_getLast_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1]       = { NOT_AN_ALIST };
    constructEmpty_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    add_alist(list, nGrades, grades);

    TEST_FAIL_IF(list->size != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[nGrades - 1] != *(int*)getLast_alist(list))

    free_alist(list);
    TEST_PASS
}

static bool test_arraylist_isSorted_alist(void) {
    char const unsorted[]       = { 'd', 'l', 'q', 'k', 'x', 'a', 'm', 'n' };
    char const sorted[]         = { 'a', 'd', 'k', 'l', 'm', 'n', 'q', 'x' };
    ArrayList unsortedList[1]   = { NOT_AN_ALIST };
    ArrayList sortedList[1]     = { NOT_AN_ALIST };

    constructEmpty_alist(unsortedList, 1, sizeof(unsorted));
    constructEmpty_alist(sortedList, 1, sizeof(sorted));

    TEST_FAIL_IF(!isSorted_alist(unsortedList, compar_char))
    TEST_FAIL_IF(!isSorted_alist(sortedList, compar_char))

    add_alist(unsortedList, sizeof(unsorted), unsorted);
    add_alist(sortedList, sizeof(sorted), sorted);

    TEST_FAIL_IF(isSorted_alist(unsortedList, compar_char))
    TEST_FAIL_IF(!isSorted_alist(sortedList, compar_char))

    free_alist(unsortedList);
    free_alist(sortedList);
    TEST_PASS
}

static bool test_arraylist_isValid_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    TEST_FAIL_IF(isValid_alist(list))

    constructEmpty_alist(list, 1, 1);
    TEST_FAIL_IF(!isValid_alist(list))

    free_alist(list);
    TEST_FAIL_IF(isValid_alist(list))

    TEST_PASS
}

static bool test_arraylist_lsearch_alist(void) {
    char const letters[]    = { 'd', 'l', 'q', 'k', 'x', 'a', 'm', 'n' };
    ArrayList list[1]       = { NOT_AN_ALIST };
    constructEmpty_alist(list, 1, sizeof(letters));

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != sizeof(letters))

    TEST_FAIL_IF(strncmp(add_alist(list, sizeof(letters), letters), letters, 8) != 0)

    TEST_FAIL_IF(list->size != sizeof(letters))
    TEST_FAIL_IF(list->cap != sizeof(letters))

    for (uint32_t i = 0; i < sizeof(letters); i++) {
        char* key[1] = { NULL };
        TEST_FAIL_IF(lsearch_alist((void**)key, list, letters + i) != i)
        TEST_FAIL_IF(*key[0] != letters[i])
    }

    free_alist(list);
    TEST_PASS
}

static bool test_arraylist_qsort_alist(void) {
    char const unsorted[]       = { 'd', 'l', 'q', 'k', 'x', 'a', 'm', 'n' };
    char const sorted[]         = { 'a', 'd', 'k', 'l', 'm', 'n', 'q', 'x' };
    ArrayList unsortedList[1]   = { NOT_AN_ALIST };
    ArrayList sortedList[1]     = { NOT_AN_ALIST };

    constructEmpty_alist(unsortedList, 1, sizeof(unsorted));
    constructEmpty_alist(sortedList, 1, sizeof(sorted));

    TEST_FAIL_IF(!isSorted_alist(unsortedList, compar_char))
    TEST_FAIL_IF(!isSorted_alist(sortedList, compar_char))

    add_alist(unsortedList, sizeof(unsorted), unsorted);
    add_alist(sortedList, sizeof(sorted), sorted);

    TEST_FAIL_IF(isSorted_alist(unsortedList, compar_char))
    TEST_FAIL_IF(!isSorted_alist(sortedList, compar_char))

    qsort_alist(unsortedList, compar_char);
    qsort_alist(sortedList, compar_char);

    TEST_FAIL_IF(!isSorted_alist(unsortedList, compar_char))
    TEST_FAIL_IF(!isSorted_alist(sortedList, compar_char))
    TEST_FAIL_IF(strncmp(unsortedList->array, sorted, sizeof(unsorted)) != 0)

    free_alist(unsortedList);
    free_alist(sortedList);
    TEST_PASS
}

static bool test_arraylist_removeLast_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1]       = { NOT_AN_ALIST };
    constructEmpty_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    add_alist(list, nGrades, grades);

    TEST_FAIL_IF(list->size != 5)
    TEST_FAIL_IF(list->cap != nGrades)

    {
        int* const values = removeLast_alist(list, 4);
        for (uint32_t i = 0; i < 4; i++)
            TEST_FAIL_IF(values[i] != grades[i + 1])
    }

    TEST_FAIL_IF(list->size != 1)
    TEST_FAIL_IF(list->cap != nGrades)

    {
        int* const grade = removeLast_alist(list, 1);
        TEST_FAIL_IF(*grade != grades[0])
    }

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    free_alist(list);
    TEST_PASS
}

static bool test_arraylist_reverse_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    constructEmpty_alist(list, 1, 6);

    reverse_alist(list);

    add_alist(list, 1, "s");
    reverse_alist(list);

    TEST_FAIL_IF(strncmp(list->array, "s", 1) != 0)

    add_alist(list, 5, "pacer");
    reverse_alist(list);

    TEST_FAIL_IF(strncmp(list->array, "recaps", 6) != 0)

    free_alist(list);
    TEST_PASS
}

static bool test_arraylist_set_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1] = { NOT_AN_ALIST };
    constructEmpty_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addZeros_alist(list, nGrades);

    TEST_FAIL_IF(list->size != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    set_alist(list, 0, nGrades, grades);

    for (uint32_t i = 0; i < nGrades; i++) {
        int const* const grade = get_alist(list, i);
        TEST_FAIL_IF(*grade != grades[i])
    }

    free_alist(list);
    TEST_PASS
}

static bool test_arraylist_setZeros_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1] = { NOT_AN_ALIST };
    constructEmpty_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->size != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    add_alist(list, nGrades, grades);

    TEST_FAIL_IF(list->size != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    for (uint32_t i = 0; i < nGrades; i++) {
        int const* const grade = get_alist(list, i);
        TEST_FAIL_IF(*grade != grades[i])
    }

    setZeros_alist(list, 0, nGrades);

    for (uint32_t i = 0; i < nGrades; i++) {
        int const* const grade = get_alist(list, i);
        TEST_FAIL_IF(*grade != 0)
    }

    free_alist(list);
    TEST_PASS
}
