static void test_stack(void);
static bool test_stack_constructEmpty_stack(void);
static bool test_stack_flush_stack(void);
static bool test_stack_free_stack(void);
static bool test_stack_isValid_stack(void);
static bool test_stack_peek_stack(void);
static bool test_stack_peekBottom_stack(void);
static bool test_stack_peekTop_stack(void);
static bool test_stack_pop_stack(void);
static bool test_stack_popBottom_stack(void);
static bool test_stack_popTop_stack(void);
static bool test_stack_push_stack(void);
static bool test_stack_pushBottom_stack(void);
static bool test_stack_pushIndeterminate_stack(void);
static bool test_stack_pushIndeterminateBottom_stack(void);
static bool test_stack_pushIndeterminateTop_stack(void);
static bool test_stack_pushTop_stack(void);
static bool test_stack_pushZeros_stack(void);
static bool test_stack_pushZerosBottom_stack(void);
static bool test_stack_pushZerosTop_stack(void);
static bool test_stack_rotate_stack(void);
static bool test_stack_rotateDown_stack(void);
static bool test_stack_rotateUp_stack(void);

static void test_stack(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_stack_constructEmpty_stack();
    allTestsPass &= test_stack_flush_stack();
    allTestsPass &= test_stack_free_stack();
    allTestsPass &= test_stack_isValid_stack();
    allTestsPass &= test_stack_peek_stack();
    allTestsPass &= test_stack_peekBottom_stack();
    allTestsPass &= test_stack_peekTop_stack();
    allTestsPass &= test_stack_pop_stack();
    allTestsPass &= test_stack_popBottom_stack();
    allTestsPass &= test_stack_popTop_stack();
    allTestsPass &= test_stack_push_stack();
    allTestsPass &= test_stack_pushBottom_stack();
    allTestsPass &= test_stack_pushIndeterminate_stack();
    allTestsPass &= test_stack_pushIndeterminateBottom_stack();
    allTestsPass &= test_stack_pushIndeterminateTop_stack();
    allTestsPass &= test_stack_pushTop_stack();
    allTestsPass &= test_stack_pushZeros_stack();
    allTestsPass &= test_stack_pushZerosBottom_stack();
    allTestsPass &= test_stack_pushZerosTop_stack();
    allTestsPass &= test_stack_rotate_stack();
    allTestsPass &= test_stack_rotateDown_stack();
    allTestsPass &= test_stack_rotateUp_stack();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_stack_constructEmpty_stack(void) {
    Stack stack[2] = { NOT_A_STACK, NOT_A_STACK };
    constructEmpty_stack(stack, sizeof(int), 1);
    constructEmpty_stack(stack + 1, sizeof(int), SZ32_MAX - 1);

    TEST_FAIL_IF(!isValid_stack(stack))
    TEST_FAIL_IF(!isValid_stack(stack + 1))

    free_stack(stack);
    free_stack(stack + 1);
    TEST_PASS
}

static bool test_stack_flush_stack(void) {
    Stack stack[1] = { NOT_A_STACK };
    constructEmpty_stack(stack, sizeof(int), 5);

    TEST_FAIL_IF(stack->size != 0)
    TEST_FAIL_IF(stack->cap != 5)

    flush_stack(stack);

    TEST_FAIL_IF(stack->size != 0)
    TEST_FAIL_IF(stack->cap != 5)

    pushZeros_stack(stack, 5);

    TEST_FAIL_IF(stack->size != 5)
    TEST_FAIL_IF(stack->cap != 5)

    flush_stack(stack);

    TEST_FAIL_IF(stack->size != 0)
    TEST_FAIL_IF(stack->cap != 5)

    free_stack(stack);
    TEST_PASS
}

static bool test_stack_free_stack(void) {
    Stack stack[1] = { NOT_A_STACK };
    constructEmpty_stack(stack, sizeof(int), SZ32_MAX - 1);
    free_stack(stack);
    TEST_PASS
}

static bool test_stack_isValid_stack(void) {
    Stack stack[1] = { NOT_A_STACK };
    TEST_FAIL_IF(isValid_stack(stack))

    constructEmpty_stack(stack, 1, 1);
    TEST_FAIL_IF(!isValid_stack(stack))

    free_stack(stack);
    TEST_FAIL_IF(isValid_stack(stack))

    TEST_PASS
}

static bool test_stack_peek_stack(void) {
    Stack stack[1] = { NOT_A_STACK };
    constructEmpty_stack(stack, sizeof(int), 4);

    pushZeros_stack(stack, 3);
    TEST_FAIL_IF(peek_stack(stack) != stack->array + 2 * sizeof(int))

    free_stack(stack);
    TEST_PASS
}

static bool test_stack_peekBottom_stack(void) {
    Stack stack[1] = { NOT_A_STACK };
    constructEmpty_stack(stack, sizeof(int), 4);

    pushZeros_stack(stack, 3);
    TEST_FAIL_IF(peekBottom_stack(stack) != stack->array)

    free_stack(stack);
    TEST_PASS
}

static bool test_stack_peekTop_stack(void) {
    Stack stack[1] = { NOT_A_STACK };
    constructEmpty_stack(stack, sizeof(int), 4);

    pushZeros_stack(stack, 3);
    TEST_FAIL_IF(peekTop_stack(stack) != stack->array + 2 * sizeof(int))

    free_stack(stack);
    TEST_PASS
}

static bool test_stack_pop_stack(void) {
    int const celsius[] = { 12, 16, 31, 42, -5, -18, -12 };
    size_t const nItems = sizeof(celsius) / sizeof(int);
    constructEmpty_stack(stack, sizeof(int), nItems);

    push_stack(stack, nItems, celsius);

    {
        int const* const negativeTemps = pop_stack(stack, 3);
        TEST_FAIL_IF(negativeTemps[0] != -5)
        TEST_FAIL_IF(negativeTemps[1] != -18)
        TEST_FAIL_IF(negativeTemps[2] != -12)
    }

    free_stack(stack);
    TEST_PASS
}

static bool test_stack_popBottom_stack(void) {
    int const celsius[] = { 12, 16, 31, 42, -5, -18, -12 };
    size_t const nItems = sizeof(celsius) / sizeof(int);
    constructEmpty_stack(stack, sizeof(int), nItems);

    push_stack(stack, nItems, celsius);

    {
        int const* const positiveTemps = popBottom_stack(stack, 4);
        TEST_FAIL_IF(positiveTemps[0] != 12)
        TEST_FAIL_IF(positiveTemps[1] != 16)
        TEST_FAIL_IF(positiveTemps[2] != 31)
        TEST_FAIL_IF(positiveTemps[3] != 42)
    }

    free_stack(stack);
    TEST_PASS
}

static bool test_stack_popTop_stack(void) {
    int* negativeTemps  = NULL;
    int const celsius[] = { 12, 16, 31, 42, -5, -18, -12 };
    size_t const nItems = sizeof(celsius) / sizeof(int);
    constructEmpty_stack(stack, sizeof(int), nItems);

    push_stack(stack, nItems, celsius);

    {
        int const* const negativeTemps = popTop_stack(stack, 3);
        TEST_FAIL_IF(negativeTemps[0] != -5)
        TEST_FAIL_IF(negativeTemps[1] != -18)
        TEST_FAIL_IF(negativeTemps[2] != -12)
    }

    free_stack(stack);
    TEST_PASS
}

static bool test_stack_push_stack(void) {
    TEST_PASS
}

static bool test_stack_pushBottom_stack(void) {
    TEST_PASS
}

static bool test_stack_pushIndeterminate_stack(void) {
    TEST_PASS
}

static bool test_stack_pushIndeterminateBottom_stack(void) {
    TEST_PASS
}

static bool test_stack_pushIndeterminateTop_stack(void) {
    TEST_PASS
}

static bool test_stack_pushTop_stack(void) {
    TEST_PASS
}

static bool test_stack_pushZeros_stack(void) {
    TEST_PASS
}

static bool test_stack_pushZerosBottom_stack(void) {
    TEST_PASS
}

static bool test_stack_pushZerosTop_stack(void) {
    TEST_PASS
}

static bool test_stack_rotate_stack(void) {
    TEST_PASS
}

static bool test_stack_rotateDown_stack(void) {
    TEST_PASS
}

static bool test_stack_rotateUp_stack(void) {
    TEST_PASS
}
