/**
 * @file streq.h
 * @brief Defines string comparison functions and macros.
 * @author Yavuz Koroglu
 */
#ifndef STREQ_H
    #define STREQ_H
    #include <stdbool.h>
    #include <stddef.h>
    #include <string.h>

    /**
     * @def STR_EQ_CONST
     *   Compares any string to a string literal or char[].
     */
    #define STR_EQ_CONST(str,strconst) str_eq_n(str,strconst,sizeof(strconst)-1)

    /**
     * @def STR_CONTAINS_CONST
     *   Checks if str contains a string literal or char[].
     *   DO NOT DO THIS! EVIL!!! ==> STR_CONTAINS_CONST(some_str,"")
     */
    #define STR_CONTAINS_CONST(str,strconst) str_eq_n(str,strconst,sizeof(strconst)-2)

    /**
     * @brief Compares two memory blocks of n bytes.
     * @param a First memory block.
     * @param b Second memory block.
     * @param n The number of bytes.
     */
    bool mem_eq_n(char const* a, char const* b, size_t n);

    /**
     * @brief Compares two strings.
     * @param a The first string.
     * @param b The second string.
     */
    bool str_eq(char const* a, char const* b);

    /**
     * @brief Compares two strings up to n + 1 characters.
     * @param a The first string.
     * @param b The second string.
     * @param n The maximum number of characters to compare.
     */
    bool str_eq_n(char const* a, char const* b, size_t n);

    /**
     * @brief Wrapper for the strcmp() function to be used by bsearch().
     * @param s1 The first string.
     * @param s2 The second string.
     */
    int strcmp_as_comparator(void const* s1, void const* s2);
#endif

