/**
 * @file arraylist.h
 * @brief Defines ArrayList and related functions.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_ARRAYLIST_H
    #define PADKIT_ARRAYLIST_H
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdio.h>

    /**
     * @def NOT_AN_ALIST
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
     *   isValid_alist(list)
     *   0 < n < SZ32_MAX
     *
     * ptr points to the first element to be added. If ptr is a null pointer, zeros will be added.
     * ptr must not overlap with list->array because reallocating list->array will invalidate ptr.
     * In that case, create a copy of the element(s) pointed by ptr, and then add that copy to the list.
     *
     * This function returns a pointer to the first element that is added to the ArrayList.
     *
     * @param[in,out] list A constant non-null pointer to an ArrayList.
     * @param[in]        n A constant 32-bit unsigned integer.
     * @param[in]      ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* add_alist(ArrayList list[static const 1], uint32_t const n, void const* const restrict ptr);

    /**
     * @brief Equivalent to add_alist(list, n, NULL).
     *
     * Preconditions:
     *   isValid_alist(list)
     *   0 < n < SZ32_MAX
     *
     * This function returns a pointer to the first element that is added to the ArrayList.
     *
     * @param[in,out] list A constant non-null pointer to an ArrayList.
     * @param[in]        n A constant 32-bit unsigned integer.
     *
     * @return A pointer to an object.
     */
    void* addZeros_alist(ArrayList list[static const 1], uint32_t const n);

    /**
     * @brief Performs a binary search on an ArrayList.
     *
     * Preconditions:
     *   isValid_alist(list)
     *   ptr is NOT a null pointer
     *   compar is NOT a null pointer
     *   isSorted_alist(list, compar)
     *
     * According to the C99 standard, which element is selected in case of duplicates is unspecified.
     * Returns INVALID_UINT32 if the element is not found.
     *
     * @param[out]   key A constant non-null pointer to an object pointer.
     * @param[in]   list A constant non-null pointer to a constant ArrayList.
     * @param[in]    ptr A constant pointer to an constant object.
     * @param[in] compar A function pointer that takes two pointers to constant objects and returns an integer.
     */
    uint32_t bsearch_alist(
        void* key[static const 1],
        ArrayList const list[static const 1],
        void const* const ptr,
        int (*compar)(void const*, void const*)
    );

    /**
     * @brief Concatenates a tail ArrayList to a head ArrayList.
     *
     * Preconditions:
     *   isValid_alist(head)
     *   isValid_alist(tail)
     *   head->sz_element * (size_t)head->size < SZSZ_MAX
     *   tail->sz_element * (size_t)tail->size < SZSZ_MAX
     *   head->array and tail->array does NOT overlap
     *
     * @param [in,out] head A constant restricted non-null pointer to an ArrayList.
     * @param [in]     tail A constant restricted non-null pointer to a constant ArrayList.
     */
    void concat_alist(ArrayList head[static const restrict 1], ArrayList const tail[static const restrict 1]);

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
     *   isValid_alist(list)
     *
     * @param[in,out] list A constant non-null pointer to an ArrayList.
     */
    void flush_alist(ArrayList list[static const 1]);

    /**
     * @brief Deallocates the contents of an ArrayList.
     *
     * Assigns NOT_AN_ALIST to the ArrayList.
     *
     * Preconditions:
     *   isValid_alist(list)
     *
     * @param[in,out] list A constant non-null pointer to an ArrayList.
     */
    void free_alist(ArrayList list[static const 1]);

    /**
     * @brief Gets an element from an ArrayList.
     *
     * Preconditions:
     *   isValid_alist(list)
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
     * @brief Checks if an ArrayList is sorted.
     *
     * Preconditions:
     *   isValid_alist(list)
     *   compar is NOT a null pointer
     *
     * @param[in]   list A constant non-null pointer to a constant ArrayList.
     * @param[in] compar A function pointer that takes two pointers to constant objects and returns an integer.
     *
     * @return A Boolean value.
     */
    bool isSorted_alist(ArrayList const list[static const 1], int (*compar)(void const*, void const*));

    /**
     * @brief Checks if an ArrayList is valid.
     *
     * @param[in] list A constant non-null pointer to a constant ArrayList.
     *
     * @return A Boolean value.
     */
    bool isValid_alist(ArrayList const list[static const 1]);

    /**
     * @brief Performs a linear search on an ArrayList.
     *
     * Preconditions:
     *   isValid_alist(list)
     *   list->sz_element * id < SZSZ_MAX
     *   list->sz_element * id does NOT overflow
     *   ptr is NOT a null pointer
     *
     * If the value pointed by ptr occurse more than once, the index of the leftmost element is returned.
     * Returns INVALID_UINT32 if the element is not found.
     *
     * @param[out]  key A constant non-null pointer to an object pointer.
     * @param[in]  list A constant non-null pointer to a constant ArrayList.
     * @param[in]   ptr A constant pointer to a constant object.
     *
     * @return A 32-bit unsigned integer.
     */
    uint32_t lsearch_alist(void* key[static const 1], ArrayList const list[static const 1], void const* const ptr);

    /**
     * @brief Sorts an ArrayList using the C standard library's QuickSort feature.
     *
     * Preconditions:
     *   isValid_alist(list)
     *   compar is NOT a null pointer
     *
     * @param[in,out]   list A constant non-null pointer to an ArrayList.
     * @param[in]     compar A function pointer that takes two pointers to constant objects and returns an integer.
     */
    void qsort_alist(ArrayList const list[static const 1], int (*compar)(void const*, void const*));

    /**
     * @brief Removes the last n elements of an ArrayList.
     *
     * Preconditions:
     *   isValid_alist(list)
     *   0 < n <= list->size
     *
     * @param[in,out] list A constant non-null pointer to an ArrayList.
     * @param[in]        n A constant 32-bit unsigned integer.
     */
    void removeLast_alist(ArrayList list[static const 1], uint32_t const n);

    /**
     * @brief Reverses the contents of an ArrayList.
     *
     * Preconditions:
     *   isValid_alist(list)
     *
     * @param[in,out] list A constant non-null pointer to an ArrayList.
     */
    void reverse_alist(ArrayList list[static const 1]);

    /**
     * @brief Sets n elements in the ArrayList.
     *
     * Preconditions:
     *   isValid_alist(list)
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
     * This function returns a pointer to the first element in the ArrayList that is set.
     *
     * @param[in,out]    list A constant non-null pointer to an ArrayList.
     * @param[in]     startId A constant 32-bit unsigned integer.
     * @param[in]           n A constant 32-bit unsigned integer.
     * @param[in]         ptr A constant restricted pointer to a constant object.
     *
     * @return A pointer to an object.
     */
    void* set_alist(
        ArrayList list[static const 1],
        uint32_t const startId,
        uint32_t const n,
        void const* const restrict ptr
    );

    /**
     * @brief Equivalent to set_alist(list, startId, n, NULL).
     *
     * Preconditions:
     *   isValid_alist(list)
     *   startId < list->size
     *   0 < n <= list->size - startId
     *
     * startId is the index of the first element to be set.
     *
     * This function returns a pointer to the first element in the ArrayList that is set.
     *
     * @param[in,out]    list A constant non-null pointer to an ArrayList.
     * @param[in]     startId A constant 32-bit unsigned integer.
     * @param[in]           n A constant 32-bit unsigned integer.
     *
     * @return A pointer to an object.
     */
    void* setZeros_alist(ArrayList list[static const 1], uint32_t const startId, uint32_t const n);
#endif
