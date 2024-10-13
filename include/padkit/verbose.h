#ifndef VERBOSE_H
    #define VERBOSE_H
    #include <stdarg.h>
    #include <stdbool.h>

    #ifndef VERBOSE_DEFAULT
        #define VERBOSE_DEFAULT (0)
    #endif

    extern bool verbose;

    int printf_verbose(char const* const restrict format, ...);

    int vprintf_verbose(char const* const restrict format, va_list args);
#endif
