/**
 * @file streq.h
 * @brief Defines string comparison functions and macros.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_STREQ_H
    #define PADKIT_STREQ_H
    #include <stdbool.h>
    #include <stddef.h>

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
     *
     * @param[in] a A non-null pointer to at least one constant character.
     * @param[in] b A non-null pointer to at least one constant character.
     * @param[in] n A size.
     *
     * @return A Boolean value.
     */
    bool mem_eq_n(char const a[static 1], char const b[static 1], size_t n);

    /**
     * @brief Compares two strings.
     *
     * @param[in] a A non-null pointer to at least one constant character.
     * @param[in] b A non-null pointer to at least one constant character.
     *
     * @return A Boolean value.
     */
    bool str_eq(char const a[static 1], char const b[static 1]);

    /**
     * @brief Compares two strings up to n + 1 characters.
     *
     * @param[in] a A non-null pointer to at least one constant character.
     * @param[in] b A non-null pointer to at least one constant character.
     * @param[in] n A size.
     *
     * @return A Boolean value.
     */
    bool str_eq_n(char const a[static 1], char const b[static 1], size_t n);

    /**
     * @brief Wrapper for the strcmp() function to be used by bsearch().
     *
     * @param[in]   needle A pointer to a constant object.
     * @param[in] haystack A pointer to a constant object.
     *
     * @return An integer.
     */
    int strcmp_as_comparator(void const* needle, void const* haystack);
#endif

