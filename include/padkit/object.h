#ifndef PADKIT_OBJECT_H
    #define PADKIT_OBJECT_H
    #include <stdarg.h>
    #include <stdbool.h>

    typedef struct ObjectInterfaceBody {
        void    (*construct)    (void* const p_obj, ...);
        void    (*destruct)     (void* const p_obj);
        bool    (*isAllocated)  (void const* const p_obj);
        bool    (*isValid)      (void const* const p_obj);
        void    (*vconstruct)   (
            void* const p_obj,
            va_list args
        );
    } ObjectInterface;
#endif
