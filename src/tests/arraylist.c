static int cmp_char(void const* a, void const* b);

static void test_arraylist(void);
static bool test_arraylist_add_alist(void);
static bool test_arraylist_addAll_alist(void);
static bool test_arraylist_addAllN_alist(void);
static bool test_arraylist_addDup_alist(void);
static bool test_arraylist_addDupFirst_alist(void);
static bool test_arraylist_addDupFirstN_alist(void);
static bool test_arraylist_addDupFirstSameN_alist(void);
static bool test_arraylist_addDupLast_alist(void);
static bool test_arraylist_addDupLastN_alist(void);
static bool test_arraylist_addDupLastSameN_alist(void);
static bool test_arraylist_addDupN_alist(void);
static bool test_arraylist_addDupSameN_alist(void);
static bool test_arraylist_addF_alist(void);
static bool test_arraylist_addIndeterminate_alist(void);
static bool test_arraylist_addIndeterminateN_alist(void);
static bool test_arraylist_addN_alist(void);
static bool test_arraylist_addSameN_alist(void);
static bool test_arraylist_addZeros_alist(void);
static bool test_arraylist_addZerosN_alist(void);
static bool test_arraylist_bsearch_alist(void);
static bool test_arraylist_concat_alist(void);
static bool test_arraylist_concatN_alist(void);
static bool test_arraylist_construct_alist(void);
static bool test_arraylist_constructEmpty_alist(void);
static bool test_arraylist_delete_alist(void);
static bool test_arraylist_deleteAll_alist(void);
static bool test_arraylist_deleteFirst_alist(void);
static bool test_arraylist_deleteFirstN_alist(void);
static bool test_arraylist_deleteLast_alist(void);
static bool test_arraylist_deleteLastN_alist(void);
static bool test_arraylist_deleteN_alist(void);
static bool test_arraylist_destruct_alist(void);
static bool test_arraylist_flush_alist(void);
static bool test_arraylist_get_alist(void);
static bool test_arraylist_getFirst_alist(void);
static bool test_arraylist_getFirstN_alist(void);
static bool test_arraylist_getLast_alist(void);
static bool test_arraylist_getLastN_alist(void);
static bool test_arraylist_getN_alist(void);
static bool test_arraylist_insert_alist(void);
static bool test_arraylist_insertDup_alist(void);
static bool test_arraylist_insertDupN_alist(void);
static bool test_arraylist_insertDupSameN_alist(void);
static bool test_arraylist_insertIndeterminate_alist(void);
static bool test_arraylist_insertIndeterminateN_alist(void);
static bool test_arraylist_insertN_alist(void);
static bool test_arraylist_insertSameN_alist(void);
static bool test_arraylist_insertZeros_alist(void);
static bool test_arraylist_insertZerosN_alist(void);
static bool test_arraylist_isAllocated_alist(void);
static bool test_arraylist_isSorted_alist(void);
static bool test_arraylist_isValid_alist(void);
static bool test_arraylist_lsearch_alist(void);
static bool test_arraylist_peek_alist(void);
static bool test_arraylist_peekBottom_alist(void);
static bool test_arraylist_peekBottomN_alist(void);
static bool test_arraylist_peekN_alist(void);
static bool test_arraylist_peekTop_alist(void);
static bool test_arraylist_peekTopN_alist(void);
static bool test_arraylist_pop_alist(void);
static bool test_arraylist_popBottom_alist(void);
static bool test_arraylist_popBottomN_alist(void);
static bool test_arraylist_popN_alist(void);
static bool test_arraylist_popTop_alist(void);
static bool test_arraylist_popTopN_alist(void);
static bool test_arraylist_push_alist(void);
static bool test_arraylist_pushBottom_alist(void);
static bool test_arraylist_pushBottomN_alist(void);
static bool test_arraylist_pushBottomSameN_alist(void);
static bool test_arraylist_pushIndeterminate_alist(void);
static bool test_arraylist_pushIndeterminateBottom_alist(void);
static bool test_arraylist_pushIndeterminateBottomN_alist(void);
static bool test_arraylist_pushIndeterminateN_alist(void);
static bool test_arraylist_pushIndeterminateTop_alist(void);
static bool test_arraylist_pushIndeterminateTopN_alist(void);
static bool test_arraylist_pushN_alist(void);
static bool test_arraylist_pushSameN_alist(void);
static bool test_arraylist_pushTop_alist(void);
static bool test_arraylist_pushTopN_alist(void);
static bool test_arraylist_pushTopSameN_alist(void);
static bool test_arraylist_pushZeros_alist(void);
static bool test_arraylist_pushZerosBottom_alist(void);
static bool test_arraylist_pushZerosBottomN_alist(void);
static bool test_arraylist_pushZerosN_alist(void);
static bool test_arraylist_pushZerosTop_alist(void);
static bool test_arraylist_pushZerosTopN_alist(void);
static bool test_arraylist_qsort_alist(void);
static bool test_arraylist_remove_alist(void);
static bool test_arraylist_removeAll_alist(void);
static bool test_arraylist_removeFirst_alist(void);
static bool test_arraylist_removeFirstN_alist(void);
static bool test_arraylist_removeLast_alist(void);
static bool test_arraylist_removeLastN_alist(void);
static bool test_arraylist_removeN_alist(void);
static bool test_arraylist_reverse_alist(void);
static bool test_arraylist_rotate_alist(void);
static bool test_arraylist_rotateDown_alist(void);
static bool test_arraylist_rotateDownN_alist(void);
static bool test_arraylist_rotateN_alist(void);
static bool test_arraylist_rotateUp_alist(void);
static bool test_arraylist_rotateUpN_alist(void);
static bool test_arraylist_set_alist(void);
static bool test_arraylist_setAll_alist(void);
static bool test_arraylist_setAllSame_alist(void);
static bool test_arraylist_setDup_alist(void);
static bool test_arraylist_setDupN_alist(void);
static bool test_arraylist_setDupSameN_alist(void);
static bool test_arraylist_setN_alist(void);
static bool test_arraylist_setSameN_alist(void);
static bool test_arraylist_setZeros_alist(void);
static bool test_arraylist_setZerosN_alist(void);
static bool test_arraylist_swap_alist(void);
static bool test_arraylist_swapN_alist(void);
static bool test_arraylist_vconstruct_alist(size_t const nParameters, ...);

static int cmp_char(void const* a, void const* b) {
    return (*(char const*)a - *(char const*)b);
}

static void test_arraylist(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_arraylist_add_alist();
    allTestsPass &= test_arraylist_addAll_alist();
    allTestsPass &= test_arraylist_addAllN_alist();
    allTestsPass &= test_arraylist_addDup_alist();
    allTestsPass &= test_arraylist_addDupFirst_alist();
    allTestsPass &= test_arraylist_addDupFirstN_alist();
    allTestsPass &= test_arraylist_addDupFirstSameN_alist();
    allTestsPass &= test_arraylist_addDupLast_alist();
    allTestsPass &= test_arraylist_addDupLastN_alist();
    allTestsPass &= test_arraylist_addDupLastSameN_alist();
    allTestsPass &= test_arraylist_addDupN_alist();
    allTestsPass &= test_arraylist_addDupSameN_alist();
    allTestsPass &= test_arraylist_addF_alist();
    allTestsPass &= test_arraylist_addIndeterminate_alist();
    allTestsPass &= test_arraylist_addIndeterminateN_alist();
    allTestsPass &= test_arraylist_addN_alist();
    allTestsPass &= test_arraylist_addSameN_alist();
    allTestsPass &= test_arraylist_addZeros_alist();
    allTestsPass &= test_arraylist_addZerosN_alist();
    allTestsPass &= test_arraylist_bsearch_alist();
    allTestsPass &= test_arraylist_concat_alist();
    allTestsPass &= test_arraylist_concatN_alist();
    allTestsPass &= test_arraylist_construct_alist();
    allTestsPass &= test_arraylist_constructEmpty_alist();
    allTestsPass &= test_arraylist_delete_alist();
    allTestsPass &= test_arraylist_deleteAll_alist();
    allTestsPass &= test_arraylist_deleteFirst_alist();
    allTestsPass &= test_arraylist_deleteFirstN_alist();
    allTestsPass &= test_arraylist_deleteLast_alist();
    allTestsPass &= test_arraylist_deleteLastN_alist();
    allTestsPass &= test_arraylist_deleteN_alist();
    allTestsPass &= test_arraylist_destruct_alist();
    allTestsPass &= test_arraylist_flush_alist();
    allTestsPass &= test_arraylist_get_alist();
    allTestsPass &= test_arraylist_getFirst_alist();
    allTestsPass &= test_arraylist_getFirstN_alist();
    allTestsPass &= test_arraylist_getLast_alist();
    allTestsPass &= test_arraylist_getLastN_alist();
    allTestsPass &= test_arraylist_getN_alist();
    allTestsPass &= test_arraylist_insert_alist();
    allTestsPass &= test_arraylist_insertDup_alist();
    allTestsPass &= test_arraylist_insertDupN_alist();
    allTestsPass &= test_arraylist_insertDupSameN_alist();
    allTestsPass &= test_arraylist_insertIndeterminate_alist();
    allTestsPass &= test_arraylist_insertIndeterminateN_alist();
    allTestsPass &= test_arraylist_insertN_alist();
    allTestsPass &= test_arraylist_insertSameN_alist();
    allTestsPass &= test_arraylist_insertZeros_alist();
    allTestsPass &= test_arraylist_insertZerosN_alist();
    allTestsPass &= test_arraylist_isAllocated_alist();
    allTestsPass &= test_arraylist_isSorted_alist();
    allTestsPass &= test_arraylist_isValid_alist();
    allTestsPass &= test_arraylist_lsearch_alist();
    allTestsPass &= test_arraylist_peek_alist();
    allTestsPass &= test_arraylist_peekBottom_alist();
    allTestsPass &= test_arraylist_peekBottomN_alist();
    allTestsPass &= test_arraylist_peekN_alist();
    allTestsPass &= test_arraylist_peekTop_alist();
    allTestsPass &= test_arraylist_peekTopN_alist();
    allTestsPass &= test_arraylist_pop_alist();
    allTestsPass &= test_arraylist_popBottom_alist();
    allTestsPass &= test_arraylist_popBottomN_alist();
    allTestsPass &= test_arraylist_popN_alist();
    allTestsPass &= test_arraylist_popTop_alist();
    allTestsPass &= test_arraylist_popTopN_alist();
    allTestsPass &= test_arraylist_push_alist();
    allTestsPass &= test_arraylist_pushBottom_alist();
    allTestsPass &= test_arraylist_pushBottomN_alist();
    allTestsPass &= test_arraylist_pushBottomSameN_alist();
    allTestsPass &= test_arraylist_pushIndeterminate_alist();
    allTestsPass &= test_arraylist_pushIndeterminateBottom_alist();
    allTestsPass &= test_arraylist_pushIndeterminateBottomN_alist();
    allTestsPass &= test_arraylist_pushIndeterminateN_alist();
    allTestsPass &= test_arraylist_pushIndeterminateTop_alist();
    allTestsPass &= test_arraylist_pushIndeterminateTopN_alist();
    allTestsPass &= test_arraylist_pushN_alist();
    allTestsPass &= test_arraylist_pushSameN_alist();
    allTestsPass &= test_arraylist_pushTop_alist();
    allTestsPass &= test_arraylist_pushTopN_alist();
    allTestsPass &= test_arraylist_pushTopSameN_alist();
    allTestsPass &= test_arraylist_pushZeros_alist();
    allTestsPass &= test_arraylist_pushZerosBottom_alist();
    allTestsPass &= test_arraylist_pushZerosBottomN_alist();
    allTestsPass &= test_arraylist_pushZerosN_alist();
    allTestsPass &= test_arraylist_pushZerosTop_alist();
    allTestsPass &= test_arraylist_pushZerosTopN_alist();
    allTestsPass &= test_arraylist_qsort_alist();
    allTestsPass &= test_arraylist_remove_alist();
    allTestsPass &= test_arraylist_removeAll_alist();
    allTestsPass &= test_arraylist_removeFirst_alist();
    allTestsPass &= test_arraylist_removeFirstN_alist();
    allTestsPass &= test_arraylist_removeLast_alist();
    allTestsPass &= test_arraylist_removeLastN_alist();
    allTestsPass &= test_arraylist_removeN_alist();
    allTestsPass &= test_arraylist_reverse_alist();
    allTestsPass &= test_arraylist_rotate_alist();
    allTestsPass &= test_arraylist_rotateDown_alist();
    allTestsPass &= test_arraylist_rotateDownN_alist();
    allTestsPass &= test_arraylist_rotateN_alist();
    allTestsPass &= test_arraylist_rotateUp_alist();
    allTestsPass &= test_arraylist_rotateUpN_alist();
    allTestsPass &= test_arraylist_set_alist();
    allTestsPass &= test_arraylist_setAll_alist();
    allTestsPass &= test_arraylist_setAllSame_alist();
    allTestsPass &= test_arraylist_setDup_alist();
    allTestsPass &= test_arraylist_setDupN_alist();
    allTestsPass &= test_arraylist_setDupSameN_alist();
    allTestsPass &= test_arraylist_setN_alist();
    allTestsPass &= test_arraylist_setSameN_alist();
    allTestsPass &= test_arraylist_setZeros_alist();
    allTestsPass &= test_arraylist_setZerosN_alist();
    allTestsPass &= test_arraylist_swap_alist();
    allTestsPass &= test_arraylist_swapN_alist();
    allTestsPass &= test_arraylist_vconstruct_alist(2, sizeof(int), 1000000);

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_arraylist_add_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 5, 1);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1)

    add_alist(list, "Alice");
    add_alist(list, "Henry");
    add_alist(list, "Wendy");

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 4)
    TEST_FAIL_IF(strncmp(list->arr, "AliceHenryWendy", 15) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addAll_alist(void) {
    return test_arraylist_concat_alist();
}

static bool test_arraylist_addAllN_alist(void) {
    return test_arraylist_concatN_alist();
}

static bool test_arraylist_addDup_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 3);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 3)

    addN_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 3)

    addDup_alist(list, 0);
    addDup_alist(list, 3);
    addDup_alist(list, 4);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 6)
    TEST_FAIL_IF(strncmp(list->arr, "abcaaa", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addDupFirst_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 3);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 3)

    addN_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 3)

    REPEAT(3)
        addDupFirst_alist(list);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 6)
    TEST_FAIL_IF(strncmp(list->arr, "abcaaa", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addDupFirstN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 3);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 3)

    addN_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 3)

    addDupFirstN_alist(list, 3);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 6)
    TEST_FAIL_IF(strncmp(list->arr, "abcabc", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addDupFirstSameN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 3);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 3)

    addN_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 3)

    addDupFirstSameN_alist(list, 3);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 6)
    TEST_FAIL_IF(strncmp(list->arr, "abcaaa", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addDupLast_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 3);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 3)

    addN_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 3)

    REPEAT(3)
        addDupLast_alist(list);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 6)
    TEST_FAIL_IF(strncmp(list->arr, "abcccc", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addDupLastN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 3);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 3)

    addN_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 3)

    addDupLastN_alist(list, 3);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 6)
    TEST_FAIL_IF(strncmp(list->arr, "abcabc", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addDupLastSameN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 3);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 3)

    addN_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 3)

    addDupLastSameN_alist(list, 3);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 6)
    TEST_FAIL_IF(strncmp(list->arr, "abcccc", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addDupN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 3);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 3)

    addN_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 3)

    addDupN_alist(list, 1, 2);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 6)
    TEST_FAIL_IF(strncmp(list->arr, "abcbc", 5) != 0)

    destruct_alist(list);
    TEST_PASS
}

/* TBI */
static bool test_arraylist_addDupSameN_alist(void) {
    TEST_PASS
}

/* TBI */
static bool test_arraylist_addF_alist(void) {
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

static bool test_arraylist_addIndeterminateN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 1);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1)

    addIndeterminateN_alist(list, 5);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 8)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 5, 1);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1)

    addN_alist(list, "AliceHenryWendy", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 4)
    TEST_FAIL_IF(strncmp(list->arr, "AliceHenryWendy", 15) != 0)

    destruct_alist(list);
    TEST_PASS
}

/* TBI */
static bool test_arraylist_addSameN_alist(void) {
    TEST_PASS
}

static bool test_arraylist_addZeros_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 8);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 8)

    REPEAT(8)
        addZeros_alist(list);

    TEST_FAIL_IF(list->len != 8)
    TEST_FAIL_IF(list->cap != 8)

    {
        int const* const p_lastValue    = getLast_alist(list);
        int const* p_value              = getFirst_alist(list);
        while (p_value <= p_lastValue) {
            TEST_FAIL_IF(*p_value != 0)
            p_value++;
        }
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_addZerosN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 8);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 8)

    addZerosN_alist(list, 8);

    TEST_FAIL_IF(list->len != 8)
    TEST_FAIL_IF(list->cap != 8)

    {
        int const* const p_lastValue    = getLast_alist(list);
        int const* p_value              = getFirst_alist(list);
        while (p_value <= p_lastValue) {
            TEST_FAIL_IF(*p_value != 0)
            p_value++;
        }
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

    addN_alist(list, letters, sizeof(letters));

    TEST_FAIL_IF(list->len != sizeof(letters))
    TEST_FAIL_IF(list->cap != sizeof(letters))

    for (uint32_t i = 0; i < sizeof(letters); i++) {
        char* p_key = NULL;
        TEST_FAIL_IF(bsearch_alist((void**)&p_key, list, letters + i, cmp_char) != i)
        TEST_FAIL_IF(p_key == NULL)
        TEST_FAIL_IF(*p_key != letters[i])
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

    addN_alist(tail, "abc", 3);

    concat_alist(head, tail);

    TEST_FAIL_IF(head->len != 3)
    TEST_FAIL_IF(tail->len != 3)

    TEST_FAIL_IF(head->cap != 5)
    TEST_FAIL_IF(tail->cap != 5)

    addN_alist(tail, "def", 3);

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

/* TBI */
static bool test_arraylist_concatN_alist(void) {
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

/* TBI */
static bool test_arraylist_delete_alist(void) {
    TEST_PASS
}

/* TBI */
static bool test_arraylist_deleteAll_alist(void) {
    TEST_PASS
}

/* TBI */
static bool test_arraylist_deleteFirst_alist(void) {
    TEST_PASS
}

/* TBI */
static bool test_arraylist_deleteFirstN_alist(void) {
    TEST_PASS
}

/* TBI */
static bool test_arraylist_deleteLast_alist(void) {
    TEST_PASS
}

/* TBI */
static bool test_arraylist_deleteLastN_alist(void) {
    TEST_PASS
}

/* TBI */
static bool test_arraylist_deleteN_alist(void) {
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

    addZerosN_alist(list, 5);

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
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

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
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[0] != *(int*)getFirst_alist(list))

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_getFirstN_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[0] != *(int*)getFirstN_alist(list, nGrades))

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_getLast_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[nGrades - 1] != *(int*)getLast_alist(list))

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_getLastN_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[0] != *(int*)getLastN_alist(list, nGrades))

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_getN_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    for (uint32_t i = 0; i < list->len; i++) {
        int const* const grade = getN_alist(list, i, list->len - i);
        TEST_FAIL_IF(*grade != grades[i])
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_insert_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addN_alist(list, "aefgh", 5);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 1024)

    insert_alist(list, 1, "b");
    insert_alist(list, 2, "c");
    insert_alist(list, 3, "d");

    TEST_FAIL_IF(list->len != 8)
    TEST_FAIL_IF(list->cap != 1024)
    TEST_FAIL_IF(strncmp(list->arr, "abcdefgh", 8) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_insertDup_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addN_alist(list, "abcde", 5);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 1024)

    insertDup_alist(list, 4, 0);
    insertDup_alist(list, 3, 1);

    TEST_FAIL_IF(list->len != 7)
    TEST_FAIL_IF(list->cap != 1024)
    TEST_FAIL_IF(strncmp(list->arr, "abcbdae", 7) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_insertDupN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addN_alist(list, "abcde", 5);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 1024)

    insertDupN_alist(list, 3, 1, 3);

    TEST_FAIL_IF(list->len != 8)
    TEST_FAIL_IF(list->cap != 1024)
    TEST_FAIL_IF(strncmp(list->arr, "abcbcdde", 8) != 0)

    destruct_alist(list);
    TEST_PASS
}

/* TBI */
static bool test_arraylist_insertDupSameN_alist(void) {
    TEST_PASS
}

static bool test_arraylist_insertIndeterminate_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addN_alist(list, "aefgh", 5);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 1024)

    memcpy(insertIndeterminate_alist(list, 1), "b", 1);
    memcpy(insertIndeterminate_alist(list, 2), "c", 1);
    memcpy(insertIndeterminate_alist(list, 3), "d", 1);

    TEST_FAIL_IF(list->len != 8)
    TEST_FAIL_IF(list->cap != 1024)
    TEST_FAIL_IF(strncmp(list->arr, "abcdefgh", 8) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_insertIndeterminateN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addN_alist(list, "aefgh", 5);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 1024)

    memcpy(insertIndeterminateN_alist(list, 1, 3), "bcd", 3);

    TEST_FAIL_IF(list->len != 8)
    TEST_FAIL_IF(list->cap != 1024)
    TEST_FAIL_IF(strncmp(list->arr, "abcdefgh", 8) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_insertN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addN_alist(list, "aefgh", 5);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 1024)

    insertN_alist(list, 1, "bcd", 3);

    TEST_FAIL_IF(list->len != 8)
    TEST_FAIL_IF(list->cap != 1024)
    TEST_FAIL_IF(strncmp(list->arr, "abcdefgh", 8) != 0)

    destruct_alist(list);
    TEST_PASS
}

/* TBI */
static bool test_arraylist_insertSameN_alist(void) {
    TEST_PASS
}

static bool test_arraylist_insertZeros_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addN_alist(list, "aefgh", 5);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 1024)

    REPEAT(3)
        insertZeros_alist(list, 1);

    TEST_FAIL_IF(list->len != 8)
    TEST_FAIL_IF(list->cap != 1024)
    TEST_FAIL_IF(memcmp(list->arr, "a\0\0\0efgh", 8) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_insertZerosN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addN_alist(list, "aefgh", 5);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != 1024)

    insertZerosN_alist(list, 1, 3);

    TEST_FAIL_IF(list->len != 8)
    TEST_FAIL_IF(list->cap != 1024)
    TEST_FAIL_IF(memcmp(list->arr, "a\0\0\0efgh", 8) != 0)

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

    addN_alist(unsortedList, unsorted, sizeof(unsorted));
    addN_alist(sortedList, sorted, sizeof(sorted));

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

    addN_alist(list, letters, sizeof(letters));

    TEST_FAIL_IF(list->len != sizeof(letters))
    TEST_FAIL_IF(list->cap != sizeof(letters))

    for (uint32_t i = 0; i < sizeof(letters); i++) {
        char* p_key = NULL;
        TEST_FAIL_IF(lsearch_alist((void**)&p_key, list, letters + i) != i)
        TEST_FAIL_IF(p_key == NULL)
        TEST_FAIL_IF(*p_key != letters[i])
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_peek_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[nGrades - 1] != *(int*)peek_alist(list))

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_peekBottom_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[0] != *(int*)peekBottom_alist(list))

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_peekBottomN_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[0] != *(int*)peekBottomN_alist(list, nGrades))

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_peekN_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[0] != *(int*)peekN_alist(list, nGrades))

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_peekTop_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[nGrades - 1] != *(int*)peekTop_alist(list))

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_peekTopN_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    TEST_FAIL_IF(grades[0] != *(int*)peekTopN_alist(list, nGrades))

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pop_alist(void) {
    int const sorted[]  = { 5, 12, 36, 42, 54, 73, 82 };
    uint32_t const n    = sizeof(sorted) / sizeof(int);
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), n);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != n)

    pushN_alist(list, sorted, n);

    for (uint32_t i = n - 1; list->len > 0; i--)
        TEST_FAIL_IF(*(int*)pop_alist(list) != sorted[i])

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_popBottom_alist(void) {
    int const sorted[]  = { 5, 12, 36, 42, 54, 73, 82 };
    uint32_t const n    = sizeof(sorted) / sizeof(int);
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), n);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != n)

    pushN_alist(list, sorted, n);

    for (uint32_t i = 0; list->len > 0; i++)
        TEST_FAIL_IF(*(int*)popBottom_alist(list) != sorted[i])

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_popBottomN_alist(void) {
    int const sorted[]  = { 5, 12, 36, 42, 54, 73, 82 };
    uint32_t const n    = sizeof(sorted) / sizeof(int);
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), n);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != n)

    pushN_alist(list, sorted, n);

    TEST_FAIL_IF(memcmp(popBottomN_alist(list, 3), sorted, 3 * sizeof(int)) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_popN_alist(void) {
    int const sorted[]  = { 5, 12, 36, 42, 54, 73, 82 };
    uint32_t const n    = sizeof(sorted) / sizeof(int);
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), n);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != n)

    pushN_alist(list, sorted, n);

    TEST_FAIL_IF(memcmp(popN_alist(list, 3), sorted + n - 3, 3 * sizeof(int)) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_popTop_alist(void) {
    int const sorted[]  = { 5, 12, 36, 42, 54, 73, 82 };
    uint32_t const n    = sizeof(sorted) / sizeof(int);
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), n);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != n)

    pushN_alist(list, sorted, n);

    for (uint32_t i = n - 1; list->len > 0; i--)
        TEST_FAIL_IF(*(int*)popTop_alist(list) != sorted[i])

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_popTopN_alist(void) {
    int const sorted[]  = { 5, 12, 36, 42, 54, 73, 82 };
    uint32_t const n    = sizeof(sorted) / sizeof(int);
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), n);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != n)

    pushN_alist(list, sorted, n);

    TEST_FAIL_IF(memcmp(popTopN_alist(list, 3), sorted + n - 3, 3 * sizeof(int)) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_push_alist(void) {
    char const word[]               = "recaps";
    uint32_t const n                = sizeof(word) - 1;
    char const* const p_lastLetter  = word + n - 1;
    ArrayList list[1]   = { NOT_AN_ALIST };
    ArrayList rlist[1]  = { NOT_AN_ALIST };
    construct_alist(list, 1, n);
    construct_alist(rlist, 1, n);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != n)
    TEST_FAIL_IF(rlist->len != 0)
    TEST_FAIL_IF(rlist->cap != n)

    for (char const* p_letter = word; p_letter <= p_lastLetter; p_letter++)
        push_alist(list, p_letter);

    TEST_FAIL_IF(list->len != n)
    TEST_FAIL_IF(list->cap != n)
    TEST_FAIL_IF(strncmp(list->arr, word, n) != 0)

    while (list->len > 0) {
        char* const p_letter = pop_alist(list);
        push_alist(rlist, p_letter);
    }

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != n)
    TEST_FAIL_IF(rlist->len != n)
    TEST_FAIL_IF(rlist->cap != n)
    TEST_FAIL_IF(strncmp(rlist->arr, "spacer", n) != 0)

    destruct_alist(list);
    destruct_alist(rlist);
    TEST_PASS
}

static bool test_arraylist_pushBottom_alist(void) {
    char const word[]               = "recaps";
    uint32_t const n                = sizeof(word) - 1;
    char const* const p_lastLetter  = word + n - 1;
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, 1, n);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != n)

    for (char const* p_letter = word; p_letter <= p_lastLetter; p_letter++)
        pushBottom_alist(list, p_letter);

    TEST_FAIL_IF(list->len != n)
    TEST_FAIL_IF(list->cap != n)
    TEST_FAIL_IF(strncmp(list->arr, "spacer", n) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pushBottomN_alist(void) {
    char const word[]               = "space";
    uint32_t const n                = sizeof(word) - 1;
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, 1, n);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != n)

    pushBottomN_alist(list, "r", 1);
    pushBottomN_alist(list, "space", n);

    TEST_FAIL_IF(list->len != n + 1)
    TEST_FAIL_IF(list->cap != n << 1)
    TEST_FAIL_IF(strncmp(list->arr, "spacer", n + 1) != 0)

    destruct_alist(list);
    TEST_PASS
}

/* TBI */
static bool test_arraylist_pushBottomSameN_alist(void) {
    TEST_PASS
}

static bool test_arraylist_pushIndeterminate_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, 1, 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    memcpy(pushIndeterminate_alist(list), "s", 1);
    memcpy(pushIndeterminate_alist(list), "p", 1);
    memcpy(pushIndeterminate_alist(list), "a", 1);
    memcpy(pushIndeterminate_alist(list), "c", 1);
    memcpy(pushIndeterminate_alist(list), "e", 1);
    memcpy(pushIndeterminate_alist(list), "r", 1);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 8)
    TEST_FAIL_IF(strncmp(list->arr, "spacer", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pushIndeterminateBottom_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, 1, 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    memcpy(pushIndeterminateBottom_alist(list), "s", 1);
    memcpy(pushIndeterminateBottom_alist(list), "p", 1);
    memcpy(pushIndeterminateBottom_alist(list), "a", 1);
    memcpy(pushIndeterminateBottom_alist(list), "c", 1);
    memcpy(pushIndeterminateBottom_alist(list), "e", 1);
    memcpy(pushIndeterminateBottom_alist(list), "r", 1);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 8)
    TEST_FAIL_IF(strncmp(list->arr, "recaps", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pushIndeterminateBottomN_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, 1, 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    memcpy(pushIndeterminateBottomN_alist(list, 5), "pacer", 5);
    memcpy(pushIndeterminateBottomN_alist(list, 1), "s", 1);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 8)
    TEST_FAIL_IF(strncmp(list->arr, "spacer", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pushIndeterminateN_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, 1, 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    memcpy(pushIndeterminateN_alist(list, 5), "space", 5);
    memcpy(pushIndeterminateN_alist(list, 1), "r", 1);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 8)
    TEST_FAIL_IF(strncmp(list->arr, "spacer", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pushIndeterminateTop_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, 1, 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    memcpy(pushIndeterminateTop_alist(list), "s", 1);
    memcpy(pushIndeterminateTop_alist(list), "p", 1);
    memcpy(pushIndeterminateTop_alist(list), "a", 1);
    memcpy(pushIndeterminateTop_alist(list), "c", 1);
    memcpy(pushIndeterminateTop_alist(list), "e", 1);
    memcpy(pushIndeterminateTop_alist(list), "r", 1);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 8)
    TEST_FAIL_IF(strncmp(list->arr, "spacer", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pushIndeterminateTopN_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, 1, 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    memcpy(pushIndeterminateTopN_alist(list, 5), "space", 5);
    memcpy(pushIndeterminateTopN_alist(list, 1), "r", 1);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 8)
    TEST_FAIL_IF(strncmp(list->arr, "spacer", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pushN_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, 1, 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    pushN_alist(list, "space", 5);
    pushN_alist(list, "r", 1);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 8)
    TEST_FAIL_IF(strncmp(list->arr, "spacer", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

/* TBI */
static bool test_arraylist_pushSameN_alist(void) {
    TEST_PASS
}

static bool test_arraylist_pushTop_alist(void) {
    char const word[]               = "recaps";
    uint32_t const n                = sizeof(word) - 1;
    char const* const p_lastLetter  = word + n - 1;
    ArrayList list[1]   = { NOT_AN_ALIST };
    ArrayList rlist[1]  = { NOT_AN_ALIST };
    construct_alist(list, 1, n);
    construct_alist(rlist, 1, n);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != n)
    TEST_FAIL_IF(rlist->len != 0)
    TEST_FAIL_IF(rlist->cap != n)

    for (char const* p_letter = word; p_letter <= p_lastLetter; p_letter++)
        pushTop_alist(list, p_letter);

    TEST_FAIL_IF(list->len != n)
    TEST_FAIL_IF(list->cap != n)
    TEST_FAIL_IF(strncmp(list->arr, word, n) != 0)

    while (list->len > 0) {
        char* const p_letter = popTop_alist(list);
        pushTop_alist(rlist, p_letter);
    }

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != n)
    TEST_FAIL_IF(rlist->len != n)
    TEST_FAIL_IF(rlist->cap != n)
    TEST_FAIL_IF(strncmp(rlist->arr, "spacer", n) != 0)

    destruct_alist(list);
    destruct_alist(rlist);
    TEST_PASS
}

static bool test_arraylist_pushTopN_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, 1, 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    pushTopN_alist(list, "space", 5);
    pushTopN_alist(list, "r", 1);

    TEST_FAIL_IF(list->len != 6)
    TEST_FAIL_IF(list->cap != 8)
    TEST_FAIL_IF(strncmp(list->arr, "spacer", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

/* TBI */
static bool test_arraylist_pushTopSameN_alist(void) {
    TEST_PASS
}

static bool test_arraylist_pushZeros_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    REPEAT(3)
        pushZeros_alist(list);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 4)

    {
        int const* const p_last = getLast_alist(list);
        int const* p_value      = getFirst_alist(list);
        while (p_value <= p_last) {
            TEST_FAIL_IF(*p_value != 0)
            p_value++;
        }
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pushZerosBottom_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    REPEAT(3)
        pushZerosBottom_alist(list);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 4)

    {
        int const* const p_last = getLast_alist(list);
        int const* p_value      = getFirst_alist(list);
        while (p_value <= p_last) {
            TEST_FAIL_IF(*p_value != 0)
            p_value++;
        }
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pushZerosBottomN_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    pushZerosBottomN_alist(list, 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 4)

    {
        int const* const p_last = getLast_alist(list);
        int const* p_value      = getFirst_alist(list);
        while (p_value <= p_last) {
            TEST_FAIL_IF(*p_value != 0)
            p_value++;
        }
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pushZerosN_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    pushZerosN_alist(list, 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 4)

    {
        int const* const p_last = getLast_alist(list);
        int const* p_value      = getFirst_alist(list);
        while (p_value <= p_last) {
            TEST_FAIL_IF(*p_value != 0)
            p_value++;
        }
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pushZerosTop_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    REPEAT(3)
        pushZerosTop_alist(list);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 4)

    {
        int const* const p_last = getLast_alist(list);
        int const* p_value      = getFirst_alist(list);
        while (p_value <= p_last) {
            TEST_FAIL_IF(*p_value != 0)
            p_value++;
        }
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_pushZerosTopN_alist(void) {
    ArrayList list[1]   = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), 2);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 2)

    pushZerosTopN_alist(list, 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 4)

    {
        int const* const p_last = getLast_alist(list);
        int const* p_value      = getFirst_alist(list);
        while (p_value <= p_last) {
            TEST_FAIL_IF(*p_value != 0)
            p_value++;
        }
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

    addN_alist(unsortedList, unsorted, sizeof(unsorted));
    addN_alist(sortedList, sorted, sizeof(sorted));

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

static bool test_arraylist_remove_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 7);

    addN_alist(list, "abefgcd", 7);

    TEST_FAIL_IF(strncmp(list->arr, "abefgcd", list->len) != 0)

    TEST_FAIL_IF(strncmp(remove_alist(list, 2), "e", 1) != 0)
    TEST_FAIL_IF(strncmp(remove_alist(list, 2), "f", 1) != 0)
    TEST_FAIL_IF(strncmp(remove_alist(list, 2), "g", 1) != 0)

    TEST_FAIL_IF(list->len != 4)
    TEST_FAIL_IF(strncmp(list->arr, "abcd", list->len) != 0)

    TEST_FAIL_IF(strncmp(remove_alist(list, 1), "b", 1) != 0)
    TEST_FAIL_IF(strncmp(remove_alist(list, 1), "c", 1) != 0)
    TEST_FAIL_IF(strncmp(remove_alist(list, 1), "d", 1) != 0)

    TEST_FAIL_IF(list->len != 1)
    TEST_FAIL_IF(strncmp(list->arr, "a", list->len) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_removeAll_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 7);

    addN_alist(list, "abefgcd", 7);

    TEST_FAIL_IF(strncmp(list->arr, "abefgcd", list->len) != 0)
    TEST_FAIL_IF(strncmp(removeAll_alist(list), "abefgcd", 7) != 0)
    TEST_FAIL_IF(list->len != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_removeFirst_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != nGrades)

    for (uint32_t i = 0; i < nGrades - 1; i++) {
        int* const value = removeFirst_alist(list);
        TEST_FAIL_IF(*value != grades[i])
    }

    TEST_FAIL_IF(list->len != 1)
    TEST_FAIL_IF(list->cap != nGrades << 1)

    {
        int* const grade = removeFirst_alist(list);
        TEST_FAIL_IF(*grade != grades[nGrades - 1])
    }

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades << 1)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_removeFirstN_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != 5)
    TEST_FAIL_IF(list->cap != nGrades)

    {
        int* const values = removeFirstN_alist(list, nGrades - 1);
        for (uint32_t i = 0; i < nGrades - 1; i++)
            TEST_FAIL_IF(values[i] != grades[i])
    }

    TEST_FAIL_IF(list->len != 1)
    TEST_FAIL_IF(list->cap != nGrades << 1)

    {
        int* const grade = removeFirstN_alist(list, 1);
        TEST_FAIL_IF(*grade != grades[nGrades - 1])
    }

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades << 1)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_removeLast_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    for (uint32_t i = nGrades - 1; i >= 1; i--) {
        int* const grade = removeLast_alist(list);
        TEST_FAIL_IF(*grade != grades[i])
    }

    TEST_FAIL_IF(list->len != 1)
    TEST_FAIL_IF(list->cap != nGrades)

    {
        int* const grade = removeLast_alist(list);
        TEST_FAIL_IF(*grade != grades[0])
    }

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_removeLastN_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1]       = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    {
        int* const values = removeLastN_alist(list, nGrades - 1);
        for (uint32_t i = 0; i < nGrades - 1; i++)
            TEST_FAIL_IF(values[i] != grades[i + 1])
    }

    TEST_FAIL_IF(list->len != 1)
    TEST_FAIL_IF(list->cap != nGrades)

    {
        int* const grade = removeLastN_alist(list, 1);
        TEST_FAIL_IF(*grade != grades[0])
    }

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_removeN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 7);

    addN_alist(list, "abefgcd", 7);

    TEST_FAIL_IF(strncmp(list->arr, "abefgcd", list->len) != 0)

    TEST_FAIL_IF(strncmp(removeN_alist(list, 2, 3), "efg", 3) != 0)

    TEST_FAIL_IF(list->len != 4)
    TEST_FAIL_IF(strncmp(list->arr, "abcd", list->len) != 0)

    TEST_FAIL_IF(strncmp(removeN_alist(list, 1, 3), "bcd", 3) != 0)

    TEST_FAIL_IF(list->len != 1)
    TEST_FAIL_IF(strncmp(list->arr, "a", list->len) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_reverse_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 6);

    reverse_alist(list);

    add_alist(list, "s");
    reverse_alist(list);

    TEST_FAIL_IF(strncmp(list->arr, "s", 1) != 0)

    addN_alist(list, "pacer", 5);
    reverse_alist(list);

    TEST_FAIL_IF(strncmp(list->arr, "recaps", 6) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_rotate_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 6);

    addN_alist(list, "tars", 4);

    REPEAT(3)
        rotate_alist(list);

    TEST_FAIL_IF(strncmp(list->arr, "star", 4) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_rotateDown_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 6);

    addN_alist(list, "tars", 4);

    REPEAT(3)
        rotateDown_alist(list);

    TEST_FAIL_IF(strncmp(list->arr, "star", 4) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_rotateDownN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 6);

    addN_alist(list, "tars", 4);

    rotateDownN_alist(list, 3);

    TEST_FAIL_IF(strncmp(list->arr, "star", 4) != 0)

    rotateDownN_alist(list, 9);

    TEST_FAIL_IF(strncmp(list->arr, "tars", 4) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_rotateN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 6);

    addN_alist(list, "tars", 4);

    rotateN_alist(list, 3);

    TEST_FAIL_IF(strncmp(list->arr, "star", 4) != 0)

    rotateN_alist(list, 9);

    TEST_FAIL_IF(strncmp(list->arr, "tars", 4) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_rotateUp_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 6);

    addN_alist(list, "star", 4);

    REPEAT(3)
        rotateUp_alist(list);

    TEST_FAIL_IF(strncmp(list->arr, "tars", 4) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_rotateUpN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 6);

    addN_alist(list, "tars", 4);

    rotateUpN_alist(list, 9);

    TEST_FAIL_IF(strncmp(list->arr, "star", 4) != 0)

    rotateUpN_alist(list, 3);

    TEST_FAIL_IF(strncmp(list->arr, "tars", 4) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_set_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addZerosN_alist(list, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    for (uint32_t i = 0; i < nGrades; i++) {
        int const* const grade = get_alist(list, i);
        set_alist(list, i, grades + i);
        TEST_FAIL_IF(*grade != grades[i])
    }

    destruct_alist(list);
    TEST_PASS
}

/* TBI */
static bool test_arraylist_setAll_alist(void) {
    TEST_PASS
}

/* TBI */
static bool test_arraylist_setAllSame_alist(void) {
    TEST_PASS
}

static bool test_arraylist_setDup_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addN_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 1024)

    for (uint32_t i = 2; i >= 1; i--)
        setDup_alist(list, i, i - 1);

    TEST_FAIL_IF(strncmp(list->arr, "aab", 3) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_setDupN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addN_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 1024)

    setDupN_alist(list, 1, 0, 2);

    TEST_FAIL_IF(strncmp(list->arr, "aab", 3) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_setDupSameN_alist(void) {
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, 1024);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != 1024)

    addN_alist(list, "abc", 3);

    TEST_FAIL_IF(list->len != 3)
    TEST_FAIL_IF(list->cap != 1024)

    setDupSameN_alist(list, 1, 0, 2);

    TEST_FAIL_IF(strncmp(list->arr, "aaa", 3) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_setN_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addZerosN_alist(list, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    setN_alist(list, 0, grades, nGrades);

    for (uint32_t i = 0; i < nGrades; i++) {
        int const* const grade = get_alist(list, i);
        TEST_FAIL_IF(*grade != grades[i])
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_setSameN_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addZerosN_alist(list, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    setSameN_alist(list, 0, grades, nGrades);

    for (uint32_t i = 0; i < nGrades; i++) {
        int const* const grade = get_alist(list, i);
        TEST_FAIL_IF(*grade != grades[0])
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_setZeros_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    for (uint32_t i = 0; i < nGrades; i++) {
        int const* const grade = get_alist(list, i);
        TEST_FAIL_IF(*grade != grades[i])
        setZeros_alist(list, i);
        TEST_FAIL_IF(*grade != 0)
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_setZerosN_alist(void) {
    int const grades[]      = { 92, 84, 76, 22, 45 };
    uint32_t const nGrades  = sizeof(grades) / sizeof(int);
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, sizeof(int), nGrades);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != nGrades)

    addN_alist(list, grades, nGrades);

    TEST_FAIL_IF(list->len != nGrades)
    TEST_FAIL_IF(list->cap != nGrades)

    for (uint32_t i = 0; i < nGrades; i++) {
        int const* const grade = get_alist(list, i);
        TEST_FAIL_IF(*grade != grades[i])
    }

    setZerosN_alist(list, 0, nGrades);

    for (uint32_t i = 0; i < nGrades; i++) {
        int const* const grade = get_alist(list, i);
        TEST_FAIL_IF(*grade != 0)
    }

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_swap_alist(void) {
    char const word[]       = "ward";
    uint32_t const word_len = sizeof(word) - 1;
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, word_len);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != word_len)

    addN_alist(list, word, word_len);

    swap_alist(list, 0, 3);
    swap_alist(list, 1, 2);

    TEST_FAIL_IF(strncmp(list->arr, "draw", 4) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_swapN_alist(void) {
    char const word[]       = "ward";
    uint32_t const word_len = sizeof(word) - 1;
    ArrayList list[1] = { NOT_AN_ALIST };
    construct_alist(list, 1, word_len);

    TEST_FAIL_IF(list->len != 0)
    TEST_FAIL_IF(list->cap != word_len)

    addN_alist(list, word, word_len);

    swapN_alist(list, 0, 2, 2);
    swapN_alist(list, 0, 1, 1);
    swapN_alist(list, 2, 3, 1);

    TEST_FAIL_IF(strncmp(list->arr, "draw", 4) != 0)

    destruct_alist(list);
    TEST_PASS
}

static bool test_arraylist_vconstruct_alist(size_t const nParameters, ...) {
    ArrayList list[1] = { NOT_AN_ALIST };
    va_list args;

    assert(nParameters == 2);

    va_start(args, nParameters);
    vconstruct_alist(list, args);

    TEST_FAIL_IF(!isValid_alist(list))

    destruct_alist(list);
    TEST_PASS
}

