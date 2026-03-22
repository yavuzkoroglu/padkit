/**
 * @file preprocessor.h
 * @brief Commonly used preprocessor macros for stringization and concatenation.
 * @author Yavuz KÖROĞLU
 */
#ifndef PADKIT_MISC_PREPROCESSOR_H
    #define PADKIT_MISC_PREPROCESSOR_H

    #define MKSTR(x)    #x
    #define STR(x)      MKSTR(x)

    #define MKCAT(x,y)  x##y
    #define CAT(x,y)    MKCAT(x,y)
#endif
