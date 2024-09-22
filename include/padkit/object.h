#ifndef PADKIT_OBJECT_H
    #define PADKIT_OBJECT_H
    #include <stdarg.h>
    #include <stdbool.h>

    typedef struct ObjectInterfaceBody {
        void    (*construct)    (void* const, ...);
        void    (*destruct)     (void* const);
        bool    (*isAllocated)  (void const* const);
        bool    (*isValid)      (void const* const);
        void    (*vconstruct)   (void* const, va_list);
    } ObjectInterface;
#endif
