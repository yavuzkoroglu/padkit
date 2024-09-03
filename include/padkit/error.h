#ifdef TERMINATE_ABORT
    #undef TERMINATE_ABORT
#endif
#ifdef TERMINATE_ERROR
    #undef TERMINATE_ERROR
#endif

#ifndef NDEBUG
    #define TERMINATE_ABORT {                                                       \
        fprintf(stderr, "Abort in %s::%s():%d\n", __FILE__, __func__, __LINE__);    \
        abort();                                                                    \
    }

    #define TERMINATE_ERROR {                                                       \
        fprintf(stderr, "Error in %s::%s():%d\n", __FILE__, __func__, __LINE__);    \
        exit(EXIT_FAILURE);                                                         \
    }
#else
    #define TERMINATE_ABORT {                                                       \
        fputs("Abort\n", stderr);                                                   \
        abort();                                                                    \
    }

    #define TERMINATE_ERROR {                                                       \
        fputs("Error\n", stderr);                                                   \
        exit(EXIT_FAILURE);                                                         \
    }
#endif

#ifndef PADKIT_ERROR_H
    #define PADKIT_ERROR_H
    #include <stdio.h>
    #include <stdlib.h>

    #define TERMINATE_ABORT_MSG(...) {                                              \
        fprintf(stderr, __VA_ARGS__);                                               \
        fputs("\n", stderr);                                                        \
        TERMINATE_ABORT                                                             \
    }

    #define TERMINATE_ERROR_MSG(...) {                                              \
        fprintf(stderr, __VA_ARGS__);                                               \
        fputs("\n", stderr);                                                        \
        TERMINATE_ERROR                                                             \
    }
#endif
