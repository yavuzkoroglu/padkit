/**
 * @file object.h
 * @brief Typedef for <tt>Object</tt>.
 * @author Yavuz KÖROĞLU
 *
 * An \c Object is a C struct that is constructable, destructable, allocatable, and validatable.
 * An ObjectInterface is a C struct that holds function pointers for the generic functions of an <tt>Object</tt>.
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

    /**
     * @brief An \c Object is a C struct that is constructable, destructable, allocatable, and validatable.
     *
     * This interface operates on the following conventions:
     *
     * \c construct Convention: Give an <tt>Object[1]</tt> as parameter and use <tt>malloc()</tt> only to allocate members.
     *
     * \c destruct Convention: Use <tt>free()</tt> to deallocate members and assign <tt>NOT_A(N)_<OBJECT></tt>.
     *
     * \c isAllocated Convention:
     *  => If the \c Object is NULL:
     *      + Return <tt>0</tt>.
     *  => Else if the \c Object has NO allocatable members:
     *      + Return <tt>1</tt>.
     *  => Else if ALL allocatable members are NONNULL:
     *      + Return <tt>1</tt>.
     *  => Else
     *      + Return <tt>0</tt>.
     *
     * \c isValid Conventions:
     *  1) Return 0 if <tt>isAllocated()</tt> returns <tt>0</tt>.
     *  2) Restrict checks to O(1) operations only.
     *  3) One kind of validness, many kinds of invalidness.
     *      + One if statement per kind of invalidness.
     *      + Return 1 only if the \c Object passes all invalidness checks.
     *
     * \c vconstruct Convention:
     *  => Must be called by <tt>construct()</tt>.
     */
    typedef struct ObjectInterfaceBody {
        void    (*construct)    (void* const p_obj, ...);
        void    (*destruct)     (void* const p_obj);
        bool    (*isAllocated)  (void const* const p_obj);
        bool    (*isValid)      (void const* const p_obj);
        void    (*vconstruct)   (void* const p_obj, va_list args);
    } ObjectInterface;
#endif
