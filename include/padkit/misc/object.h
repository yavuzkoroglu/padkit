/*
 * An Object is a C struct that is constructable, destructable, allocatable, and validatable.
 * An ObjectInterface is a C struct that holds function pointers for the generic functions of an Object.
 *
 * Rationale: A generic C struct is sufficient to represent simple data structures, e.g., an integer pair.
 *   A C struct is complex if it has pointer members or it is larger than 8 bytes because, typically,
     the implementation will allocate pointer members or it is costlier to pass the structure as parameter
     than to pass a pointer to it, respectively. Four important properties appear to be common to every complex
     C struct:
 *      1) Constructablity: Initializability of a complex C struct given some initial parameters.
 *      2) Destructability: Freeing the memory allocated for the complex C struct and invalidating
        the complex C struct itself.
 *      3) Allocatability: If the complex C struct has pointer members, the ability to allocate these members.
 *      4) Validatability: The ability to distinguish valid and invalid instances of the complex C struct.
 *
 *   I use the ObjectInterface for every complex C struct even if some of the above properties result in trivial
     functions.
 */
#ifndef PADKIT_MISC_OBJECT_H
    #define PADKIT_MISC_OBJECT_H
    #include <stdarg.h>
    #include <stdbool.h>

    typedef struct ObjectInterfaceBody {
        /*
         * construct Convention: Give an Object[1] as parameter and use malloc() only to allocate members.
         */
        void    (*construct)    (void* const p_obj, ...);
        /*
         * destruct Convention: Use free() to deallocate members and assign NOT_A(N)_<OBJECT>.
         */
        void    (*destruct)     (void* const p_obj);
        /*
         * isAllocated Convention:
         *  => If the Object is NULL:
         *      + Return 0.
         *  => Else if the Object has NO allocatable members:
         *      + Return 1.
         *  => Else if ALL allocatable members are NONNULL:
         *      + Return 1.
         *  => Else
         *      + Return 0.
         */
        bool    (*isAllocated)  (void const* const p_obj);
        /*
         * isValid Conventions:
         *  1) Return 0 if isAllocated returns 0.
         *  2) Restrict checks to O(1) operations only.
         *  3) One kind of validness, many kinds of invalidness.
         *      + One if statement per kind of invalidness.
         *      + Return 1 only if the Object passes all invalidness checks.
         */
        bool    (*isValid)      (void const* const p_obj);
        /* vconstruct Convention:
         *  => Must be called by construct().
         */
        void    (*vconstruct)   (
            void* const p_obj,
            va_list args
        );
    } ObjectInterface;
#endif
