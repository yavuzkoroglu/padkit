#ifndef PADKIT_PREPROCESSOR_H
    #define PADKIT_PREPROCESSOR_H

    #define MKSTR(x)            #x
    #define STR(x)              MKSTR(x)

    #define MKCAT(x,y)          x##y
    #define CAT(x,y)            MKCAT(x,y)
#endif
