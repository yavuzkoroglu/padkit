static int cmp_char(void const* a, void const* b);

static void test_arraylist(void);
static bool test_arraylist_addDuplicate_alist(void);
static bool test_arraylist_addDuplicates_alist(void);
static bool test_arraylist_addElement_alist(void);
static bool test_arraylist_addElements_alist(void);
static bool test_arraylist_addIndeterminate_alist(void);
static bool test_arraylist_addIndeterminates_alist(void);
static bool test_arraylist_addZero_alist(void);
static bool test_arraylist_addZeros_alist(void);
static bool test_arraylist_bsearch_alist(void);
static bool test_arraylist_concat_alist(void);
static bool test_arraylist_construct_alist(void);
static bool test_arraylist_constructEmpty_alist(void);
static bool test_arraylist_deleteElement_alist(void);
static bool test_arraylist_deleteElements_alist(void);
static bool test_arraylist_destruct_alist(void);
static bool test_arraylist_flush_alist(void);
static bool test_arraylist_get_alist(void);
static bool test_arraylist_getFirst_alist(void);
static bool test_arraylist_getLast_alist(void);
static bool test_arraylist_isAllocated_alist(void);
static bool test_arraylist_isSorted_alist(void);
static bool test_arraylist_isValid_alist(void);
static bool test_arraylist_lsearch_alist(void);
static bool test_arraylist_qsort_alist(void);
static bool test_arraylist_removeLast_alist(void);
static bool test_arraylist_reverse_alist(void);
static bool test_arraylist_setDuplicate_alist(void);
static bool test_arraylist_setDuplicates_alist(void);
static bool test_arraylist_setElement_alist(void);
static bool test_arraylist_setElements_alist(void);
static bool test_arraylist_setZero_alist(void);
static bool test_arraylist_setZeros_alist(void);
static bool test_arraylist_vconstruct_alist(size_t const nParameters, ...);

static int cmp_char(void const* a, void const* b) {
    return (*(char const*)a - *(char const*)b);
}

static void test_arraylist(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_arraylist_addDuplicate_alist();
    allTestsPass &= test_arraylist_addDuplicates_alist();
    allTestsPass &= test_arraylist_addElement_alist();
    allTestsPass &= test_arraylist_addElements_alist();
    allTestsPass &= test_arraylist_addIndeterminate_alist();
    allTestsPass &= test_arraylist_addIndeterminates_alist();
    allTestsPass &= test_arraylist_addZero_alist();
    allTestsPass &= test_arraylist_addZeros_alist();
    allTestsPass &= test_arraylist_bsearch_alist();
    allTestsPass &= test_arraylist_concat_alist();
    allTestsPass &= test_arraylist_construct_alist();
    allTestsPass &= test_arraylist_constructEmpty_alist();
    allTestsPass &= test_arraylist_deleteElement_alist();
    allTestsPass &= test_arraylist_deleteElements_alist();
    allTestsPass &= test_arraylist_destruct_alist();
    allTestsPass &= test_arraylist_flush_alist();
    allTestsPass &= test_arraylist_get_alist();
    allTestsPass &= test_arraylist_getFirst_alist();
    allTestsPass &= test_arraylist_getLast_alist();
    allTestsPass &= test_arraylist_isAllocated_alist();
    allTestsPass &= test_arraylist_isSorted_alist();
    allTestsPass &= test_arraylist_isValid_alist();
    allTestsPass &= test_arraylist_lsearch_alist();
    allTestsPass &= test_arraylist_qsort_alist();
    allTestsPass &= test_arraylist_removeLast_alist();
    allTestsPass &= test_arraylist_reverse_alist();
    allTestsPass &= test_arraylist_setDuplicate_alist();
    allTestsPass &= test_arraylist_setDuplicates_alist();
    allTestsPass &= test_arraylist_setElement_alist();
    allTestsPass &= test_arraylist_setElements_alist();
    allTestsPass &= test_arraylist_setZero_alist();
    allTestsPass &= test_arraylist_setZeros_alist();
    allTestsPass &= test_arraylist_vconstruct_alist(2, sizeof(int), 1000000);

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_arraylist_addDuplicate_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 3);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 3)

    addElements_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 3)

    addDuplicate_alist(list, 0);
    addDuplicate_alist(list, 3);
    addDuplicate_alist(list, 4);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 6)
    TEST_FAIL_IF(strncmp(list->arr, "abcaaa", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addDuplicates_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 3);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 3)

    addElements_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 3)

    addDuplicates_alist(list, 1, 2);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 6)
    TEST_FAIL_IF(strncmp(list->arr, "abcbc", 5) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addElement_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 5, 1);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1)

    addElement_alist(list, "Alice");
    addElement_alist(list, "Henry");
    addElement_alist(list, "Wendy");

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 4)
    TEST_FAIL_IF(strncmp(list->arr, "AliceHenryWendy", 15) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addElements_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 5, 1);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1)

    addElements_alist(list, "AliceHenryWendy", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 4)
    TEST_FAIL_IF(strncmp(list->arr, "AliceHenryWendy", 15) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addIndeterminate_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 1);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1)

    REPEAT(5)
        addIndeterminate_alist(list);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 8)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addIndeterminates_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 1);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1)

    addIndeterminates_alist(list, 5);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 8)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addZero_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 8);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 8)

    REPEAT(8)
        addZero_alist(list);

    TEST_FAIL_IF(list->len != 8)
    TEST_FAIL_IF(list->cap != 8)

    for (uint32_t i = 0; i < list->len; i++) {
        int const* const value = get_alist(list, i);
        TEST_FAIL_IF(*value != 0)
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addZeros_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 8);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 8)

    addZeros_alist(list, 8);

    TEST_FAIL_IF(list->len != 8)
    TEST_FAIL_IF(list->cap != 8)

    for (uint32_t i = 0; i < list->len; i++) {
        int const* const value = get_alist(list, i);
        TEST_FAIL_IF(*value != 0)
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_bsearch_alist(void) {
    char const letters[]    = { 'a', 'd', 'k', 'l', 'm', 'n', 'q', 'x' };
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, 1, sizeof(letters));

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != sizeof(letters))

    addElements_alist(list, letters, sizeof(letters));

    TEST_FAIL_IF(list->len != sizeof(letters))
    TEST_FAIL_IF(list->cap != sizeof(letters))

    for (uint32_t i = 0; i < sizeof(letters); i++) {
        char* key = NULL;
        TEST_FAIL_IF(bsearch_alist((void**)&key, list, letters + i, cmp_char) != i)
        TEST_FAIL_IF(key == NULL)
        TEST_FAIL_IF(*key != letters[i])
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_concat_alist(void) {
    ArrayList head[1] = { NOT_AN_ALIST };
    ArrayList tail[1] = { NOT_AN_ALIST };

    construct_alist(head, 1, 5);
    construct_alist(tail, 1, 5);

    TEST_FAIL_IF(head->len != 0)
    TEST_FAIL_IF(tail->len != 0)

    TEST_FAIL_IF(head->cap != 5)
    TEST_FAIL_IF(tail->cap != 5)

    concat_alist(head, tail);

    TEST_FAIL_IF(head->len != 0)
    TEST_FAIL_IF(tail->len != 0)

    TEST_FAIL_IF(head->cap != 5)
    TEST_FAIL_IF(tail->cap != 5)

    addElements_alist(tail, "abc", 3);

    concat_alist(head, tail);

    TEST_FAIL_IF(head->len != 3)
    TEST_FAIL_IF(tail->len != 3)

    TEST_FAIL_IF(head->cap != 5)
    TEST_FAIL_IF(tail->cap != 5)

    addElements_alist(tail, "def", 3);

    concat_alist(head, tail);

    TEST_FAIL_IF(head->len != 9)
    TEST_FAIL_IF(tail->len != 6)

    TEST_FAIL_IF(head->cap != 10)
    TEST_FAIL_IF(tail->cap != 10)

    TEST_FAIL_IF(strncmp(head->arr, "abcabcdef", 9) != 0)
    TEST_FAIL_IF(strncmp(tail->arr, "abcdef", 6) != 0)

    destruct_alist(head);
    destruct_alist(tail);
    TEST_PASS
}

static bool test_arraylist_construct_alist(void) {
    ArrayList list[2][1]    = { { NOT_AN_ALIST }, { NOT_AN_ALIST } };
    uint32_t const nLists   = sizeof(list) / sizeof(ArrayList);

    TEST_FAIL_IF(nLists != 2)

    construct_alist(list[0], sizeof(int), 1);
    construct_alist(list[1], sizeof(int), 1000000);

    for (uint32_t i = 0; i < nLists; i++) {
        TEST_FAIL_IF(!isValid_alist(list[i]))
        destruct_alist(list[i]);
    }

    TEST_PASS
}

static bool test_arraylist_constructEmpty_alist(void) {
    ArrayList list[2][1]    = { { NOT_AN_ALIST }, { NOT_AN_ALIST } };
    uint32_t const nLists   = sizeof(list) / sizeof(ArrayList);

    constructEmpty_alist(list[0], sizeof(int), 1);
    constructEmpty_alist(list[1], sizeof(int), 1000000);

    for (uint32_t i = 0; i < nLists; i++) {
        TEST_FAIL_IF(!isValid_alist(list[i]))
        destruct_alist(list[i]);
    }

    TEST_PASS
}

static bool test_arraylist_deleteElement_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 7);

    addElements_alist(list, "abefgcd", 7);

    TEST_FAIL_IF(strncmp(list->arr, "abefgcd", list->len) != 0)

    REPEAT(3)
        deleteElement_alist(list, 2);

    TEST_FAIL_IF(list->len != 4)
    TEST_FAIL_IF(strncmp(list->arr, "abcd", list->len) != 0)

    REPEAT(3)
        deleteElement_alist(list, 1);

    TEST_FAIL_IF(list->len != 1)
    TEST_FAIL_IF(strncmp(list->arr, "a", list->len) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_deleteElements_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 7);

    addElements_alist(list, "abefgcd", 7);

    TEST_FAIL_IF(strncmp(list->arr, "abefgcd", list->len) != 0)

    deleteElements_alist(list, 2, 3);

    TEST_FAIL_IF(list->len != 4)
    TEST_FAIL_IF(strncmp(list->arr, "abcd", list->len) != 0)

    deleteElements_alist(list, 1, 3);

    TEST_FAIL_IF(list->len != 1)
    TEST_FAIL_IF(strncmp(list->arr, "a", list->len) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_flush_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 5);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 5)

    flush_alist(list);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 5)

    addZeros_alist(list, 5);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 5)

    flush_alist(list);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 5)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_destruct_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 1000000);
    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_get_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addElements_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    for (uint32_t i = 0; i < list->len; i++) {
        int const* const grade = get_alist(list, i);
        TEST_FAIL_IF(*grade != grades[i])
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_getFirst_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addElements_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[0] != *(int*)getFirst_alist(list))

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_getLast_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addElements_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[nGrades - 1] != *(int*)getLast_alist(list))

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_isAllocated_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    TEST_FAIL_IF(isAllocated_alist(list))

    construct_alist(list, 1, 1);
    TEST_FAIL_IF(!isAllocated_alist(list))

    destruct_alist(list);
    TEST_FAIL_IF(isAllocated_alist(list))

    TEST_PASS
}

static bool test_arraylist_isSorted_alist(void) {
    char const unsorted[]       = { 'd', 'l', 'q', 'k', 'x', 'a', 'm', 'n' };
    char const sorted[]         = { 'a', 'd', 'k', 'l', 'm', 'n', 'q', 'x' };
    ArrayList unsortedList[1]   = { NOT_AN_ALIST };
    ArrayList sortedList[1]     = { NOT_AN_ALIST };

    construct_alist(unsortedList, 1, sizeof(unsorted));
    construct_alist(sortedList, 1, sizeof(sorted));

    TEST_FAIL_IF(!isSorted_alist(unsortedList, cmp_char))
    TEST_FAIL_IF(!isSorted_alist(sortedList, cmp_char))

    addElements_alist(unsortedList, unsorted, sizeof(unsorted));
    addElements_alist(sortedList, sorted, sizeof(sorted));

    TEST_FAIL_IF(isSorted_alist(unsortedList, cmp_char))
    TEST_FAIL_IF(!isSorted_alist(sortedList, cmp_char))

    destruct_alist(unsortedList);
    destruct_alist(sortedList);
    TEST_PASS
}

static bool test_arraylist_isValid_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    TEST_FAIL_IF(isValid_alist(list))

    construct_alist(list, 1, 1);
    TEST_FAIL_IF(!isValid_alist(list))

    destruct_alist(list);
    TEST_FAIL_IF(isValid_alist(list))

    TEST_PASS
}

static bool test_arraylist_lsearch_alist(void) {
    char const letters[]    = { 'd', 'l', 'q', 'k', 'x', 'a', 'm', 'n' };
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, 1, sizeof(letters));

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != sizeof(letters))

    addElements_alist(list, letters, sizeof(letters));

    TEST_FAIL_IF(list->len != sizeof(letters))
    TEST_FAIL_IF(list->cap != sizeof(letters))

    for (uint32_t i = 0; i < sizeof(letters); i++) {
        char* key = NULL;
        TEST_FAIL_IF(lsearch_alist((void**)&key, list, letters + i) != i)
        TEST_FAIL_IF(key == NULL)
        TEST_FAIL_IF(*key != letters[i])
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_qsort_alist(void) {
    char const unsorted[]       = { 'd', 'l', 'q', 'k', 'x', 'a', 'm', 'n' };
    char const sorted[]         = { 'a', 'd', 'k', 'l', 'm', 'n', 'q', 'x' };
    ArrayList unsortedList[1]   = { NOT_AN_ALIST };
    ArrayList sortedList[1]     = { NOT_AN_ALIST };

    construct_alist(unsortedList, 1, sizeof(unsorted));
    construct_alist(sortedList, 1, sizeof(sorted));

    TEST_FAIL_IF(!isSorted_alist(unsortedList, cmp_char))
    TEST_FAIL_IF(!isSorted_alist(sortedList, cmp_char))

    addElements_alist(unsortedList, unsorted, sizeof(unsorted));
    addElements_alist(sortedList, sorted, sizeof(sorted));

    TEST_FAIL_IF(isSorted_alist(unsortedList, cmp_char))
    TEST_FAIL_IF(!isSorted_alist(sortedList, cmp_char))

    qsort_alist(unsortedList, cmp_char);
    qsort_alist(sortedList, cmp_char);

    TEST_FAIL_IF(!isSorted_alist(unsortedList, cmp_char))
    TEST_FAIL_IF(!isSorted_alist(sortedList, cmp_char))
    TEST_FAIL_IF(strncmp(unsortedList->arr, sorted, sizeof(unsorted)) != 0)

    destruct_alist(unsortedList);
    destruct_alist(sortedList);
    TEST_PASS
}

static bool test_arraylist_removeLast_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addElements_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != nGrades)

    {
        int* const values = removeLast_alist(list, 4);
        for (uint32_t i = 0; i < 4; i++)
            TEST_FAIL_IF(values[i] != grades[i + 1])
    }

    TEST_FAIL_IF(list->len != 1)
    TEST_FAIL_IF(list->cap != nGrades)

    {
        int* const grade = removeLast_alist(list, 1);
        TEST_FAIL_IF(*grade != grades[0])
    }

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_reverse_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 6);

    reverse_alist(list);

    addElement_alist(list, "s");
    reverse_alist(list);

    TEST_FAIL_IF(strncmp(list->arr, "s", 1) != 0)

    addElements_alist(list, "pacer", 5);
    reverse_alist(list);

    TEST_FAIL_IF(strncmp(list->arr, "recaps", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_setDuplicate_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addElements_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 1024)

    for (uint32_t i = 2; i >= 1; i--)
        setDuplicate_alist(list, i - 1, i);

    TEST_FAIL_IF(strncmp(list->arr, "aab", 3) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_setDuplicates_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addElements_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 1024)

    setDuplicates_alist(list, 0, 1, 2);

    TEST_FAIL_IF(strncmp(list->arr, "aab", 3) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_setElement_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addZeros_alist(list, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    for (uint32_t i = 0; i < nGrades; i++) {
        int const* const grade = get_alist(list, i);
        setElement_alist(list, i, grades + i);
        TEST_FAIL_IF(*grade != grades[i])
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_setElements_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addZeros_alist(list, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    setElements_alist(list, 0, grades, nGrades);

    for (uint32_t i = 0; i < nGrades; i++) {
        int const* const grade = get_alist(list, i);
        TEST_FAIL_IF(*grade != grades[i])
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_setZero_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addElements_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    for (uint32_t i = 0; i < nGrades; i++) {
        int const* const grade = get_alist(list, i);
        TEST_FAIL_IF(*grade != grades[i])
        setZero_alist(list, i);
        TEST_FAIL_IF(*grade != 0)
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_setZeros_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(uint32_t);
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addElements_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
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

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_vconstruct_alist(size_t const nParameters, ...) {
    ArrayList list[1] = { NOT_AN_ALIST };
    va_list args;

    TEST_FAIL_IF(nParameters != 2)

    va_start(args, nParameters);
    vconstruct_alist(list, args);

    TEST_FAIL_IF(!isValid_alist(list))

    destruct_alist(list);
    TEST_PASS
}

