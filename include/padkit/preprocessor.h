#ifndef PADKIT_PREPROCESSOR_H
    #define PADKIT_PREPROCESSOR_H

    #define MKSTR(x)            #x
    #define STR(x)              MKSTR(x)

    #define MKCAT(x,y)          x##y
    #define CAT(x,y)            MKCAT(x,y)

    /* https://stackoverflow.com/questions/3599160/how-can-i-suppress-unused-parameter-warnings-in-c#3599170 */
    #define MAYBE_UNUSED(...)   (void)(__VA_ARGS__);
#endif
