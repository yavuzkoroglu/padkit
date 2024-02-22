/**
 * @file debug.h
 * @brief Defines some useful debugging macros.
 * @author Yavuz Koroglu
 */
#ifndef DEBUG_H
    #define DEBUG_H
    #include <stdio.h>
    #include <stdlib.h>

    /**
     * @def DEBUG_ASSERT_NDEBUG_EXECUTE
     *   In debug mode, it executes bool_stmt and asserts that the result is nonzero. In ndebug mode, it just executes the bool_stmt, discarding the result.
     */
    #define DEBUG_ASSERT_NDEBUG_EXECUTE(bool_stmt) \
        DEBUG_ASSERT(bool_stmt) NDEBUG_EXECUTE(bool_stmt)

    /**
     * @def DEBUG_ABORT_UNLESS_NDEBUG_EXECUTE
     *   In debug mode, it executes bool_stmt and aborts if the result is zero. In ndebug mode, it just executes the bool_stmt, discarding the result.
     */
    #define DEBUG_ABORT_UNLESS_NDEBUG_EXECUTE(bool_stmt) \
        DEBUG_ABORT_UNLESS(bool_stmt) NDEBUG_EXECUTE(bool_stmt)

    /**
     * @def TERMINATE_ABORT
     *   Terminates program execution via abort().
     */
    #define TERMINATE_ABORT {                   \
        fprintf(                                \
            stderr, "Abort in %s::%s():%d\n",   \
            __FILE__, __func__, __LINE__        \
        );                                      \
        abort();                                \
    }

    /**
     * @def TERMINATE_ABORT_MSG
     *   Prints an abort message and then terminates program execution via abort().
     */
    #define TERMINATE_ABORT_MSG(...) {          \
        fprintf(stderr, __VA_ARGS__);           \
        fputs("\n", stderr);                    \
        TERMINATE_ABORT                         \
    }

    /**
     * @def TERMINATE_ERROR
     *   Terminates program execution via exit(EXIT_FAILURE).
     */
    #define TERMINATE_ERROR {                   \
        fprintf(                                \
            stderr, "Error in %s::%s():%d\n",   \
            __FILE__, __func__, __LINE__        \
        );                                      \
        exit(EXIT_FAILURE);                     \
    }

    /**
     * @def TERMINATE_ERROR_MSG
     *   Prints an error message and then terminates program execution via exit(EXIT_FAILURE).
     */
    #define TERMINATE_ERROR_MSG(...) {          \
        fprintf(stderr, __VA_ARGS__);           \
        fputs("\n", stderr);                    \
        TERMINATE_ERROR                         \
    }

    /**
     * @def DEBUG_ABORT_IF
     *   In debug mode, aborts program execution if condition is true.
     */
    /**
     * @def DEBUG_ABORT_UNLESS
     *   In debug mode, aborts program execution if condition is false.
     */
    /**
     * @def DEBUG_ASSERT
     *   In debug mode, raises an error if condition is false.
     */
    /**
     * @def DEBUG_ERROR_IF
     *   In debug mode, raises an error if condition is true.
     */
    /**
     * @def DEBUG_EXECUTE
     *   In debug mode, executes statement.
     */
    /**
     * @def NDEBUG_EXECUTE
     *   In ndebug mode, executes statement.
     */
    /**
     * @def DEBUG_MSG
     *   In debug mode, prints a given message.
     */
    #ifndef NDEBUG
        #define DEBUG_ABORT_IF(condition)       \
            if(condition)                       \
                TERMINATE_ABORT_MSG(            \
                    "Abort Because => (%s)",    \
                    #condition                  \
                )

        #define DEBUG_ABORT_UNLESS(condition)   \
            if(!(condition))                    \
                TERMINATE_ABORT_MSG(            \
                    "Abort Because => !(%s)",   \
                    #condition                  \
                )

        #define DEBUG_ASSERT(condition)         \
            if(!(condition))                    \
                TERMINATE_ERROR_MSG(            \
                    "Failed Assertion => (%s)", \
                    #condition                  \
                )

        #define DEBUG_ERROR_IF(condition)       \
            if(condition)                       \
                TERMINATE_ERROR_MSG(            \
                    "Error Because => (%s)",    \
                    #condition                  \
                )

        #define DEBUG_EXECUTE(statement) statement;
        #define NDEBUG_EXECUTE(statement)

        #define DEBUG_MSG(...) {                \
            fprintf(stderr, __VA_ARGS__);       \
            fputs("\n", stderr);                \
        }
    #else
        #define DEBUG_ABORT_IF(condition)
        #define DEBUG_ASSERT(condition)
        #define DEBUG_ERROR_IF(condition)
        #define DEBUG_EXECUTE(statement)
        #define NDEBUG_EXECUTE(statement) statement;
        #define DEBUG_MSG(...)
    #endif
#endif
