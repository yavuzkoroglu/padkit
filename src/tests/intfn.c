static void test_intfn(void);
static bool test_intfn_isPrime(void);
static bool test_intfn_nextPrime(void);

static void test_intfn(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_intfn_isPrime();
    allTestsPass &= test_intfn_nextPrime();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_intfn_isPrime(void) {
    TEST_FAIL_IF(!isPrime(3))
    TEST_FAIL_IF(!isPrime(5))
    TEST_FAIL_IF(!isPrime(7))
    TEST_FAIL_IF(isPrime(9))
    TEST_FAIL_IF(!isPrime(8191))
    TEST_FAIL_IF(isPrime(65535))
    TEST_FAIL_IF(!isPrime(1589663))
    TEST_FAIL_IF(!isPrime(69149681))
    TEST_FAIL_IF(isPrime(69149683))
    TEST_FAIL_IF(!isPrime(2147483647))
    TEST_FAIL_IF(isPrime(UINT32_MAX))

    TEST_PASS
}

static bool test_intfn_nextPrime(void) {
    uint32_t primes[] = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23 };

    for (uint32_t i = 1; i < sizeof(primes) / sizeof(uint32_t); i++)
        TEST_FAIL_IF(primes[i] != nextPrime(primes[i-1]))

    TEST_PASS
}
