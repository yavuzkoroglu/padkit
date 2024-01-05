/**
 * @file debug.h
 * @brief Defines some useful debugging macros.
 * @author Yavuz Koroglu
 */
#ifndef DEBUG_H
    #define DEBUG_H
    #include <stdio.h>
    #include <stdlib.h>

    #define DEBUG_ASSERT_NDEBUG_EXECUTE(bool_stmt) \
        DEBUG_ASSERT(bool_stmt) NDEBUG_EXECUTE(bool_stmt)

    #define DEBUG_ABORT_UNLESS_NDEBUG_EXECUTE(bool_stmt) \
        DEBUG_ABORT_UNLESS(bool_stmt) NDEBUG_EXECUTE(bool_stmt)

    #define TERMINATE_ABORT                     \
        fprintf(                                \
            stderr, "Abort in %s::%s():%d\n",   \
            __FILE__, __func__, __LINE__        \
        );                                      \
        abort()

    #define TERMINATE_ABORT_MSG(...)            \
        fprintf(stderr, __VA_ARGS__);           \
        fputs("\n", stderr);                    \
        TERMINATE_ABORT

    #define TERMINATE_ERROR                     \
        fprintf(                                \
            stderr, "Error in %s::%s():%d\n",   \
            __FILE__, __func__, __LINE__        \
        );                                      \
        exit(EXIT_FAILURE)

    #define TERMINATE_ERROR_MSG(...)            \
        fprintf(stderr, __VA_ARGS__);           \
        fputs("\n", stderr);                    \
        TERMINATE_ERROR

    #ifndef NDEBUG
        #define DEBUG_ABORT_IF(condition)       \
            if(condition) {                     \
                TERMINATE_ABORT_MSG(            \
                    "Abort Because => (%s)",    \
                    #condition                  \
                );                              \
             }

        #define DEBUG_ABORT_UNLESS(condition)   \
            if(!(condition)) {                  \
                TERMINATE_ABORT_MSG(            \
                    "Abort Because => !(%s)",   \
                    #condition                  \
                );                              \
             }

        #define DEBUG_ASSERT(condition)         \
            if(!(condition)) {                  \
                TERMINATE_ERROR_MSG(            \
                    "Failed Assertion => (%s)", \
                    #condition                  \
                );                              \
            }

        #define DEBUG_ERROR_IF(condition)       \
            if(condition) {                     \
                TERMINATE_ERROR_MSG(            \
                    "Error Because => (%s)",    \
                    #condition                  \
                );                              \
            }

        #define DEBUG_EXECUTE(statement) statement;
        #define NDEBUG_EXECUTE(statement)
    #else
        #define DEBUG_ABORT_IF(condition)
        #define DEBUG_ASSERT(condition)
        #define DEBUG_ERROR_IF(condition)
        #define DEBUG_EXECUTE(statement)
        #define NDEBUG_EXECUTE(statement) statement;
    #endif
#endif
