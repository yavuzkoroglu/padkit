/**
 * @file debug.h
 * @brief Defines some useful debugging and error macros.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_DEBUG_H
    #define PADKIT_DEBUG_H
    #include <stdio.h>
    #include <stdlib.h>

    /**
     * @def DEBUG_ASSERT_NDEBUG_EXECUTE
     *   In debug mode, asserts the result of bool_stmt. Otherwise, executes bool_stmt and discards the result.
     */
    #define DEBUG_ASSERT_NDEBUG_EXECUTE(bool_stmt)                      \
        DEBUG_ASSERT(bool_stmt)                                         \
        NDEBUG_EXECUTE(bool_stmt)

    /**
     * @def DEBUG_ABORT_UNLESS_NDEBUG_EXECUTE
     *   In debug mode, aborts unless bool_stmt. Otherwise, executes bool_stmt and discards the result.
     */
    #define DEBUG_ABORT_UNLESS_NDEBUG_EXECUTE(bool_stmt)                \
        DEBUG_ABORT_UNLESS(bool_stmt)                                   \
        NDEBUG_EXECUTE(bool_stmt)

    /**
     * @def TERMINATE_ABORT
     *   Terminates program execution via abort().
     */
    #define TERMINATE_ABORT {                                           \
        DEBUG_MSG("Abort in %s::%s():%d", __FILE__, __func__, __LINE__) \
        NDEBUG_MSG("Abort")                                             \
        abort();                                                        \
    }

    /**
     * @def TERMINATE_ABORT_MSG
     *   Prints an abort message and then terminates program execution via abort().
     */
    #define TERMINATE_ABORT_MSG(...) {                                  \
        fprintf(stderr, __VA_ARGS__);                                   \
        fputs("\n", stderr);                                            \
        TERMINATE_ABORT                                                 \
    }

    /**
     * @def TERMINATE_ERROR
     *   Terminates program execution via exit(EXIT_FAILURE).
     */
    #define TERMINATE_ERROR {                                           \
        DEBUG_MSG("Error in %s::%s():%d", __FILE__, __func__, __LINE__) \
        NDEBUG_MSG("Error")                                             \
        exit(EXIT_FAILURE);                                             \
    }

    /**
     * @def TERMINATE_ERROR_MSG
     *   Prints an error message and then terminates program execution via exit(EXIT_FAILURE).
     */
    #define TERMINATE_ERROR_MSG(...) {                                  \
        fprintf(stderr, __VA_ARGS__);                                   \
        fputs("\n", stderr);                                            \
        TERMINATE_ERROR                                                 \
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
    /**
     * @def NDEBUG_MSG
     *   In ndebug mode, prints a given message.
     */
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

    /**
     * @def MALLOC_ERROR
     *   The default error raised in case of a MALLOC error.
     */
    #define MALLOC_ERROR    TERMINATE_ERROR_MSG("%s", "Error Because => MALLOC_ERROR")

    /**
     * @def CALLOC_ERROR
     *   The default error raised in case of a CALLOC error.
     */
    #define CALLOC_ERROR    TERMINATE_ERROR_MSG("%s", "Error Because => CALLOC_ERROR")

    /**
     * @def REALLOC_ERROR
     *   The default error raised in case of a REALLOC error.
     */
    #define REALLOC_ERROR   TERMINATE_ERROR_MSG("%s", "Error Because => REALLOC_ERROR")

    /**
     * @def RECALLOC_ERROR
     *   The default error raised in case of a RECALLOC error.
     */
    #define RECALLOC_ERROR  TERMINATE_ERROR_MSG("%s", "Error Because => RECALLOC_ERROR")
#endif
