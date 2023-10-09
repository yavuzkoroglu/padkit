/**
 * @file reallocate.h
 * @brief Defines a safe REALLOCATE macro accompanied with a _reallocate() function.
 */
#ifndef REALLOCATE_H
    #define REALLOCATE_H
    #include <stdbool.h>
    #include "padkit/debug.h"

    #ifndef NDEBUG
        #define REALLOC_ERROR TERMINATE_ERROR_MSG("%s", "Error Because => REALLOCATE_ERROR")
        #define RECALLOC_ERROR TERMINATE_ERROR_MSG("%s", "Error Because => RECALLOC_ERROR")

        #define REALLOC_IF_NECESSARY(obj_t, obj, obj_cap_t, obj_cap, obj_sz, err)           \
            if (obj_cap <= (obj_cap_t)(obj_sz)) {                                           \
                if (REALLOCATE(obj, obj_cap, ((obj_cap_t)(obj_sz)) * 2, obj_t) == NULL) err \
                obj_cap = ((obj_cap_t)(obj_sz)) * 2;                                        \
            }

        #define RECALLOC_IF_NECESSARY(obj_t, obj, obj_cap_t, obj_cap, obj_sz, err)          \
            if (obj_cap <= (obj_cap_t)(obj_sz)) {                                           \
                if (RECALLOC(obj, obj_cap, ((obj_cap_t)(obj_sz)) * 2, obj_t) == NULL) err   \
                obj_cap = ((obj_cap_t)(obj_sz)) * 2;                                        \
            }
    #else
        #define REALLOC_IF_NECESSARY(obj_t, obj, obj_cap_t, obj_cap, obj_sz, err)           \
            if (obj_cap <= (obj_cap_t)(obj_sz)) {                                           \
                REALLOCATE(obj, obj_cap, ((obj_cap_t)(obj_sz)) * 2, obj_t);                 \
                obj_cap = ((obj_cap_t)(obj_sz)) * 2;                                        \
            }

        #define RECALLOC_IF_NECESSARY(obj_t, obj, obj_cap_t, obj_cap, obj_sz, err)          \
            if (obj_cap <= (obj_cap_t)(obj_sz)) {                                           \
                RECALLOC(obj, obj_cap, ((obj_cap_t)(obj_sz)) * 2, obj_t);                   \
                obj_cap = ((obj_cap_t)(obj_sz)) * 2;                                        \
            }
    #endif

    #define REALLOCATE(ptr, old_n, new_n, type) \
        reallocate((void**)&(ptr), (size_t)(old_n), (size_t)new_n, sizeof(type))

    #define RECALLOC(ptr, old_n, new_n, type) \
        recalloc((void**)&(ptr), (size_t)(old_n), (size_t)new_n, sizeof(type))

    /**
     * @brief A reallocator that uses realloc().
     * @param ptrptr A pointer to the pointer to be reallocated.
     * @param old_element_count The old element count.
     * @param new_element_count The new element count.
     * @param element_size Size of one element in bytes.
     */
    void* reallocate(
        void** ptrptr, size_t const old_element_count,
        size_t const new_element_count, size_t const element_size
    );

    /**
     * @brief A reallocator that uses calloc() & memcpy() instead of realloc().
     * @param ptrptr A pointer to the pointer to be reallocated.
     * @param old_element_count The old element count.
     * @param new_element_count The new element count.
     * @param element_size Size of one element in bytes.
     */
    void* recalloc(
        void** ptrptr, size_t const old_element_count,
        size_t const new_element_count, size_t const element_size
    );
#endif
