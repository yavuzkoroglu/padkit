/**
 * @file error.h
 * @brief Error macros.
 * @author Yavuz KÖROĞLU
 * @important Redefines <tt>TERMINATE_ABORT</tt> and <tt>TERMINATE_ERROR</tt> at every inclusion.
 */

#ifdef TERMINATE_ABORT
    #undef TERMINATE_ABORT
#endif
#ifdef TERMINATE_ERROR
    #undef TERMINATE_ERROR
#endif

/**
 * @def TERMINATE_ABORT
 * @brief Prints a message and calls <tt>abort()</tt>.
 * @important The message is more verbose if <tt>NDEBUG</tt> is NOT defined.
 */
/**
 * @def TERMINATE_ERROR
 * @brief Prints a message and calls <tt>exit(EXIT_FAILURE)</tt>
 * @important The message is more verbose if <tt>NDEBUG</tt> is NOT defined.
 */
#ifndef NDEBUG
    #define TERMINATE_ABORT {                                                       \
        fprintf(                                                                    \
            stderr, "Abort in %.*s::%.*s():%d\n",                                   \
            (int)sizeof(__FILE__), __FILE__,                                        \
            (int)sizeof(__func__), __func__,                                        \
            __LINE__                                                                \
        );                                                                          \
        abort();                                                                    \
    }

    #define TERMINATE_ERROR {                                                       \
        fprintf(                                                                    \
            stderr, "Error in %.*s::%.*s():%d\n",                                   \
            (int)sizeof(__FILE__), __FILE__,                                        \
            (int)sizeof(__func__), __func__,                                        \
            __LINE__                                                                \
        );                                                                          \
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

#ifndef PADKIT_MISC_ERROR_H
    #define PADKIT_MISC_ERROR_H
    #include <stdio.h>
    #include <stdlib.h>

    /**
     * @brief Prints a custom message on top of the standard, and invokes <tt>TERMINATE_ABORT</tt>.
     */
    #define TERMINATE_ABORT_MSG(...) {                                              \
        fprintf(stderr, __VA_ARGS__);                                               \
        fputs("\n", stderr);                                                        \
        TERMINATE_ABORT                                                             \
    }

    /**
     * @brief Prints a custom message on top of the standard, and invokes <tt>TERMINATE_ERROR</tt>.
     */
    #define TERMINATE_ERROR_MSG(...) {                                              \
        fprintf(stderr, __VA_ARGS__);                                               \
        fputs("\n", stderr);                                                        \
        TERMINATE_ERROR                                                             \
    }
#endif
