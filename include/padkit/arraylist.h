/**
 * @file arraylist.h
 * @brief Defines ArrayList and related functions.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_ARRAYLIST_H
    #define PADKIT_ARRAYLIST_H
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <stdint.h>

    /**
     * @def NOT_AN_A_LIST
     *   A special ArrayList that cannot pass the isValid_alist() test.
     */
    #define NOT_AN_ALIST                    ((ArrayList){ 0, 0, 0, NULL })

    /**
     * @def ALIST_RECOMMENDED_INITIAL_CAP
     *   This capacity should work nicely in most situations.
     */
    #define ALIST_RECOMMENDED_INITIAL_CAP   (BUFSIZ)

    /**
     * @struct ArrayList
     * @brief An array of objects.
     *
     * @var ArrayList::sz_element
     *   The size of one element in the ArrayList, in bytes.
     * @var ArrayList::cap
     *   The maximum number of elements the ArrayList can hold.
     * @var ArrayList::size
     *   The number of elements in the ArrayList.
     * @var ArrayList::array
     *   A pointer to the first element in the ArrayList.
     */
    typedef struct ArrayListBody {
        size_t      sz_element;
        uint32_t    cap;
        uint32_t    size;
        char*       array;
    } ArrayList;

    /**
     * @brief Adds n elements to an ArrayList.
     *
     * Preconditions:
     *   isValid_list(list)
     *   0 < n < SZ32_MAX
     *
     * ptr points to the first element to be added. If ptr is a null pointer, zeros will be added.
     * ptr must not overlap with list->array because reallocating list->array will invalidate ptr.
     * In that case, create a copy of the element(s) pointed by ptr, and then add that copy to the list.
     *
     * @param[in,out] list A constant non-null pointer to an ArrayList.
     * @param[in]        n A constant 32-bit unsigned integer.
     * @param[in]      ptr A constant restricted pointer to a constant object.
     */
    void add_alist(ArrayList list[static const 1], uint32_t const n, void const* const restrict ptr);

    /**
     * @brief Equivalent to add_alist(list, n, NULL).
     *
     * Preconditions:
     *   isValid_list(list)
     *   0 < n < SZ32_MAX
     *
     * @param[in,out] list A constant non-null pointer to an ArrayList.
     * @param[in]        n A constant 32-bit unsigned integer.
     */
    void addZeros_alist(ArrayList list[static const 1], uint32_t const n);

    /**
     * @brief Constructs an empty ArrayList.
     *
     * Preconditions:
     *   0 < sz_element < SZSZ_MAX
     *   0 < initial_cap < SZ32_MAX
     *   (sz_element * initial_cap) does NOT overflow
     *
     * @param[in,out]        list A constant non-null pointer to an ArrayList.
     * @param[in]      sz_element A constant size.
     * @param[in]     initial_cap A constant 32-bit unsigned integer.
     */
    void constructEmpty_alist(
        ArrayList list[static const 1],
        size_t const sz_element,
        uint32_t const initial_cap
    );

    /**
     * @brief Empties an ArrayList.
     *
     * Preconditions:
     *   isValid_list(list)
     *
     * @param[in,out] list A constant non-null pointer to an ArrayList.
     */
    void flush_alist(ArrayList list[static const 1]);

    /**
     * @brief Deallocates memory for an ArrayList.
     *
     * Assigns NOT_AN_ALIST to the ArrayList.
     *
     * Preconditions:
     *   isValid_list(list)
     *
     * @param[in,out] list A constant non-null pointer to an ArrayList.
     */
    void free_alist(ArrayList list[static const 1]);

    /**
     * @brief Gets an element from an ArrayList.
     *
     * Preconditions:
     *   isValid_list(list)
     *   id < list->size
     *   list->sz_element * id < SZSZ_MAX
     *   list->sz_element * id does NOT overflow
     *
     * @param[in] list A constant non-null pointer to a constant ArrayList.
     * @param[in]   id A constant 32-bit unsigned integer.
     *
     * @return A pointer to an object.
     */
    void* get_alist(ArrayList const list[static const 1], uint32_t const id);

    /**
     * @brief Checks if an ArrayList is valid.
     *
     * @param[in] list A constant non-null pointer to a constant ArrayList.
     *
     * @return A Boolean value.
     */
    bool isValid_alist(ArrayList const list[static const 1]);

    /**
     * @brief Reallocates the array of an ArrayList and updates the ArrayList's capacity.
     *
     * Preconditions:
     *   isValid_list(list)
     *   list->cap < new_cap < SZ32_MAX
     *   list->sz_element * new_cap < SZ32_MAX
     *   list->sz_element * new_cap does NOT overflow
     *
     * @param[in,out]    list A constant non-null pointer to an ArrayList.
     * @param[in]     new_cap A constant 32-bit unsigned integer.
     */
    void realloc_alist(ArrayList list[static const 1], uint32_t const new_cap);

    /**
     * @brief Sets n elements in the ArrayList.
     *
     * Preconditions:
     *   isValid_list(list)
     *   startId < list->size
     *   0 < n <= list->size - startId
     *   list->sz_element * n < SZSZ_MAX
     *   list->sz_element * n does NOT overflow.
     *
     * ptr points to the first element to be set. If ptr is a null pointer, the targets will be set to zeros.
     * ptr must not overlap with list->array + startId because memcpy() would cause UB.
     * In that case, create a copy of the element(s) pointed by ptr.
     *
     * startId is the index of the first element to be set.
     *
     * @param[in,out]    list A constant non-null pointer to an ArrayList.
     * @param[in]     startId A constant 32-bit unsigned integer.
     * @param[in]           n A constant 32-bit unsigned integer.
     * @param[in]         ptr A constant restricted pointer to a constant object.
     */
    void set_alist(
        ArrayList list[static const 1],
        uint32_t const startId,
        uint32_t const n,
        void const* const restrict ptr
    );

    /**
     * @brief Equivalent to set_alist(list, startId, n, NULL).
     *
     * Preconditions:
     *   isValid_list(list)
     *   startId < list->size
     *   0 < n <= list->size - startId
     *
     * startId is the index of the first element to be set.
     *
     * @param[in,out]    list A constant non-null pointer to an ArrayList.
     * @param[in]     startId A constant 32-bit unsigned integer.
     * @param[in]           n A constant 32-bit unsigned integer.
     */
    void setZeros_alist(ArrayList list[static const 1], uint32_t const startId, uint32_t const n);
#endif

