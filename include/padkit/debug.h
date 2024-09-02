#ifndef PADKIT_DEBUG_H
    #define PADKIT_DEBUG_H
    #include <stdio.h>
    #include <stdlib.h>

    #define DEBUG_ASSERT_NDEBUG_EXECUTE(bool_stmt)                      \
        DEBUG_ASSERT(bool_stmt)                                         \
        NDEBUG_EXECUTE(bool_stmt)

    #define DEBUG_ABORT_UNLESS_NDEBUG_EXECUTE(bool_stmt)                \
        DEBUG_ABORT_UNLESS(bool_stmt)                                   \
        NDEBUG_EXECUTE(bool_stmt)

    #define TERMINATE_ABORT {                                           \
        DEBUG_MSG("Abort in %s::%s():%d", __FILE__, __func__, __LINE__) \
        NDEBUG_MSG("Abort")                                             \
        abort();                                                        \
    }

    #define TERMINATE_ABORT_MSG(...) {                                  \
        fprintf(stderr, __VA_ARGS__);                                   \
        fputs("\n", stderr);                                            \
        TERMINATE_ABORT                                                 \
    }

    #define TERMINATE_ERROR {                                           \
        DEBUG_MSG("Error in %s::%s():%d", __FILE__, __func__, __LINE__) \
        NDEBUG_MSG("Error")                                             \
        exit(EXIT_FAILURE);                                             \
    }

    #define TERMINATE_ERROR_MSG(...) {                                  \
        fprintf(stderr, __VA_ARGS__);                                   \
        fputs("\n", stderr);                                            \
        TERMINATE_ERROR                                                 \
    }

    #ifndef NDEBUG
        #define DEBUG_ABORT_IF(condition)                               \
            if(condition)                                               \
                TERMINATE_ABORT_MSG(                                    \
                    "Abort Because => (%s)",                            \
                    #condition                                          \
                )

        #define DEBUG_ABORT_UNLESS(condition)                           \
            if(!(condition))                                            \
                TERMINATE_ABORT_MSG(                                    \
                    "Abort Because => !(%s)",                           \
                    #condition                                          \
                )

        #define DEBUG_ASSERT(condition)                                 \
            if(!(condition))                                            \
                TERMINATE_ERROR_MSG(                                    \
                    "Failed Assertion => (%s)",                         \
                    #condition                                          \
                )

        #define DEBUG_ERROR_IF(condition)                               \
            if(condition)                                               \
                TERMINATE_ERROR_MSG(                                    \
                    "Error Because => (%s)",                            \
                    #condition                                          \
                )

        #define DEBUG_EXECUTE(statement) statement;
        #define NDEBUG_EXECUTE(statement)

        #define DEBUG_MSG(...) {                                        \
            fprintf(stderr, __VA_ARGS__);                               \
            fputs("\n", stderr);                                        \
        }
        #define NDEBUG_MSG(...)
    #else
        #define DEBUG_ABORT_IF(condition)
        #define DEBUG_ABORT_UNLESS(condition)
        #define DEBUG_ASSERT(condition)
        #define DEBUG_ERROR_IF(condition)
        #define DEBUG_EXECUTE(statement)
        #define NDEBUG_EXECUTE(statement) statement;
        #define DEBUG_MSG(...)
        #define NDEBUG_MSG(...) {                                       \
            fprintf(stderr, __VA_ARGS__);                               \
            fputs("\n", stderr);                                        \
        }
    #endif

    #define MALLOC_ERROR    TERMINATE_ERROR_MSG("%s", "Error Because => MALLOC_ERROR")
    #define CALLOC_ERROR    TERMINATE_ERROR_MSG("%s", "Error Because => CALLOC_ERROR")
    #define REALLOC_ERROR   TERMINATE_ERROR_MSG("%s", "Error Because => REALLOC_ERROR")
    #define RECALLOC_ERROR  TERMINATE_ERROR_MSG("%s", "Error Because => RECALLOC_ERROR")
#endif
