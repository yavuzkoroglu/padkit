/**
 * @file preprocessor.h
 * @brief Defines some preprocessor tricks.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_PREPROCESSOR_H
    #define PADKIT_PREPROCESSOR_H

    /**
     * @def MKSTR(x)
     *   Constructs a string literal from x.
     */
    #define MKSTR(x)    #x

    /**
     * @def STR(x)
     *   Performs macro replacement on x, then constructs a string literal from the replacement.
     */
    #define STR(x)      MKSTR(x)

    /**
     * @def MKCAT(x,y)
     *   Concatenates x and y.
     */
    #define MKCAT(x,y)  x##y

    /**
     * @def CAT(x,y)
     *   Performs macro replacement on x and y, then concatenates them.
     */
    #define CAT(x,y)    MKCAT(x,y)
#endif
