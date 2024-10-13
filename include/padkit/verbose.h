#ifndef VERBOSE_H
    #define VERBOSE_H
    #include <stdbool.h>

    #ifndef VERBOSE_DEFAULT
        #define VERBOSE_DEFAULT (0)
    #endif

    extern bool verbose;

    int printf_verbose(char const* const restrict format, ...);
#endif
