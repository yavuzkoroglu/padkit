static void test_prime(void);
static bool test_prime_isPrime(void);
static bool test_prime_nextPrime(void);

static void test_prime(void) {
    bool allTestsPass = 1;

    allTestsPass &= test_prime_isPrime();
    allTestsPass &= test_prime_nextPrime();

    if (allTestsPass) TESTS_PASS_MESSAGE
}

static bool test_prime_isPrime(void) {
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

static bool test_prime_nextPrime(void) {
    TEST_PASS
}
