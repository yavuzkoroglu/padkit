/**
 * @file map.c
 * @brief Implements the functions defined in map.h
 * @see Map
 * @author Yavuz Koroglu
 */
#include <stdio.h>
#include <string.h>
#include "padkit/map.h"
#include "padkit/reallocate.h"

uint32_t binarySearchLeftmostKey_map(Map const* const map, uint32_t const key_id) {
    #ifndef NDEBUG
        if (!isValid_map(map)) return 0xFFFFFFFF;
    #endif
    uint32_t l = 0;
    uint32_t r = map->size;
    for (uint32_t id = r >> 1; l < r; id = (l + r) >> 1) {
        if (map->mappings[id].key_id < key_id) {
            l = id + 1;
        } else {
            r = id;
        }
    }
    return l;
}

uint32_t binarySearchRightmostKey_map(Map const* const map, uint32_t const key_id) {
    #ifndef NDEBUG
        if (!isValid_map(map)) return 0xFFFFFFFF;
    #endif
    uint32_t l = 0;
    uint32_t r = map->size;
    for (uint32_t id = r >> 1; l < r; id = (l + r) >> 1) {
        if (map->mappings[id].key_id > key_id) {
            r = id;
        } else {
            l = id + 1;
        }
    }
    return r - 1;
}

#ifndef NDEBUG
bool
#else
void
#endif
constructEmpty_map(Map* map, uint32_t const initial_cap) {
    #ifndef NDEBUG
        if (map == NULL)               return 0;
        if (initial_cap == 0)          return 0;
        if (initial_cap == 0xFFFFFFFF) return 0;
    #endif

    map->size = 0;
    map->cap  = initial_cap;

    map->mappings = malloc(initial_cap * sizeof(Mapping));

    #ifndef NDEBUG
        if (map->mappings == NULL) return 0;
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
deleteLast_map(Map* const map) {
    #ifndef NDEBUG
        if (!isValid_map(map)) return 0;
        if (map->size == 0)    return 0;
    #endif
    map->size--;
    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
flush_map(Map* const map) {
    #ifndef NDEBUG
        if (!isValid_map(map)) return 0;
    #endif
    map->size = 0;
    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
free_map(Map* const map) {
    #ifndef NDEBUG
        if (!isValid_map(map)) return 0;
    #endif
    free(map->mappings);
    #ifndef NDEBUG
        return 1;
    #endif
}

#ifndef NDEBUG
bool
#else
void
#endif
insert_map(Map* const map, uint32_t const key_id, Value const value) {
    #ifndef NDEBUG
        if (!isValid_map(map)) return 0;
    #endif

    REALLOC_IF_NECESSARY(Mapping,map->mappings,uint32_t,map->cap,map->size,return 0;)

    /* Selection Sort on already sorted list, O(n) worst case. */
    uint32_t const id = linearSearchBackwardKey_map(map, map->size - 1, key_id) + 1;

    memmove(
        map->mappings + id + 1, map->mappings + id,
        (size_t)(map->size++ - id) * sizeof(Mapping)
    );
    map->mappings[id] = (Mapping){ key_id, value };

    #ifndef NDEBUG
        return 1;
    #endif
}

bool isValid_map(Map const* const map) {
    return map != NULL            &&
           map->cap != 0          &&
           map->cap != 0xFFFFFFFF &&
           map->size <= map->cap  &&
           map->mappings != NULL;
}

uint32_t linearSearchBackward_map(
    Map const* const map, uint32_t const search_start_id,
    uint32_t const key_id, Value const value
) {
    #ifndef NDEBUG
        if (!isValid_map(map))            return 0xFFFFFFFF;
        if (search_start_id >= map->size) return 0xFFFFFFFF;
    #endif

    uint32_t id = search_start_id;
    while (
        id != 0xFFFFFFFF && (
            map->mappings[id].key_id > key_id || (
                map->mappings[id].key_id == key_id &&
                !areEqual_val(map->mappings[id].value, value)
            )
        )
    ) id--;
    return id;
}

uint32_t linearSearchBackwardKey_map(
    Map const* const map, uint32_t const search_start_id, uint32_t const key_id
) {
    #ifndef NDEBUG
        if (!isValid_map(map))            return 0xFFFFFFFF;
        if (search_start_id >= map->size) return 0xFFFFFFFF;
    #endif

    uint32_t id = search_start_id;
    while (id != 0xFFFFFFFF && map->mappings[id].key_id > key_id)
        id--;
    return id;
}

uint32_t linearSearchBackwardValue_map(
    Map const* const map, uint32_t const search_start_id, Value const value
) {
    #ifndef NDEBUG
        if (!isValid_map(map))            return 0xFFFFFFFF;
        if (search_start_id >= map->size) return 0xFFFFFFFF;
    #endif

    uint32_t id = search_start_id;
    while (id != 0xFFFFFFFF && !areEqual_val(map->mappings[id].value, value))
        id--;
    return id;
}

uint32_t linearSearchForward_map(
    Map const* const map, uint32_t const search_start_id,
    uint32_t const key_id, Value const value
) {
    #ifndef NDEBUG
        if (!isValid_map(map))            return 0xFFFFFFFF;
        if (search_start_id >= map->size) return 0xFFFFFFFF;
    #endif

    uint32_t id = search_start_id;
    while (
        id != map->size && (
            map->mappings[id].key_id < key_id || (
                map->mappings[id].key_id == key_id &&
                !areEqual_val(map->mappings[id].value, value)
            )
        )
    ) id++;
    return id;
}

uint32_t linearSearchForwardKey_map(
    Map const* const map, uint32_t const search_start_id, uint32_t const key_id
) {
    #ifndef NDEBUG
        if (!isValid_map(map))            return 0xFFFFFFFF;
        if (search_start_id >= map->size) return 0xFFFFFFFF;
    #endif

    uint32_t id = search_start_id;
    while (id != 0xFFFFFFFF && map->mappings[id].key_id < key_id) id++;
    return id;
}

uint32_t linearSearchForwardValue_map(
    Map const* const map, uint32_t const search_start_id, Value const value
) {
    #ifndef NDEBUG
        if (!isValid_map(map))            return 0xFFFFFFFF;
        if (search_start_id >= map->size) return 0xFFFFFFFF;
    #endif

    uint32_t id = search_start_id;
    while (id != 0xFFFFFFFF && !areEqual_val(map->mappings[id].value, value)) id++;
    return id;
}
