/**
 * @file map.c
 * @brief Implements the functions defined in map.h
 * @see Map
 * @author Yavuz Koroglu
 */
#include <stdio.h>
#include <string.h>
#include "padkit/debug.h"
#include "padkit/map.h"
#include "padkit/memalloc.h"
#include "padkit/reallocate.h"

uint32_t binarySearchLeftmostKey_map(Map const map[static const 1], uint32_t const key_id) {
    DEBUG_ASSERT(isValid_map(map))
    {
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
}

uint32_t binarySearchRightmostKey_map(Map const map[static const 1], uint32_t const key_id) {
    DEBUG_ASSERT(isValid_map(map))
    {
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
}

void constructEmpty_map(Map map[static const 1], uint32_t const initial_cap) {
    DEBUG_ASSERT(initial_cap > 0)
    DEBUG_ASSERT(initial_cap < INT32_MAX)

    map->size = 0;
    map->cap  = initial_cap;

    map->mappings = mem_alloc((size_t)initial_cap * sizeof(Mapping));
}

void deleteLast_map(Map map[static const 1]) {
    DEBUG_ASSERT(isValid_map(map))
    DEBUG_ERROR_IF(map->size == 0)

    map->size--;
}

void flush_map(Map map[static const 1]) {
    DEBUG_ASSERT(isValid_map(map))
    map->size = 0;
}

void free_map(Map map[static const 1]) {
    DEBUG_ABORT_UNLESS(isValid_map(map))

    free(map->mappings);
    map[0] = NOT_A_MAP;
}

void insert_map(Map map[static const 1], uint32_t const key_id, Value const value) {
    DEBUG_ASSERT(isValid_map(map))

    REALLOC_IF_NECESSARY(Mapping, map->mappings, uint32_t, map->cap, map->size)

    {
        /* Selection Sort on already sorted list, O(n) worst case. */
        uint32_t const id = linearSearchBackwardKey_map(map, map->size - 1, key_id) + 1;

        memmove(
            map->mappings + id + 1, map->mappings + id,
            (size_t)(map->size++ - id) * sizeof(Mapping)
        );
        map->mappings[id] = (Mapping){ key_id, value };
    }
}

bool isValid_map(Map const map[static const 1]) {
    if (map->cap == 0)          return 0;
    if (map->cap >= INT32_MAX)  return 0;
    if (map->size > map->cap)   return 0;
    if (map->mappings == NULL)  return 0;

    return 1;
}

uint32_t linearSearchBackward_map(
    Map const map[static const 1], uint32_t const search_start_id,
    uint32_t const key_id, Value const value
) {
    DEBUG_ASSERT(isValid_map(map))

    if (map->size == 0) return UINT32_MAX;

    DEBUG_ASSERT(search_start_id < map->size)

    {
        uint32_t id = search_start_id;
        while (
            id != UINT32_MAX && (
                map->mappings[id].key_id > key_id || (
                    map->mappings[id].key_id == key_id &&
                    !areEqual_val(map->mappings[id].value, value)
                )
            )
        ) id--;
        return id;
    }
}

uint32_t linearSearchBackwardKey_map(
    Map const map[static const 1], uint32_t const search_start_id, uint32_t const key_id
) {
    DEBUG_ASSERT(isValid_map(map))

    if (map->size == 0) return UINT32_MAX;

    DEBUG_ASSERT(search_start_id < map->size)

    {
        uint32_t id = search_start_id;
        while (id != UINT32_MAX && map->mappings[id].key_id > key_id)
            id--;
        return id;
    }
}

uint32_t linearSearchBackwardValue_map(
    Map const map[static const 1], uint32_t const search_start_id, Value const value
) {
    DEBUG_ASSERT(isValid_map(map))

    if (map->size == 0) return UINT32_MAX;

    DEBUG_ASSERT(search_start_id < map->size)

    {
        uint32_t id = search_start_id;
        while (id != UINT32_MAX && !areEqual_val(map->mappings[id].value, value))
            id--;
        return id;
    }
}

uint32_t linearSearchForward_map(
    Map const map[static const 1], uint32_t const search_start_id,
    uint32_t const key_id, Value const value
) {
    DEBUG_ASSERT(isValid_map(map))

    if (map->size == 0) {
        return UINT32_MAX;
    } else {
        uint32_t id = search_start_id;
        while (
            id < map->size && (
                map->mappings[id].key_id < key_id || (
                    map->mappings[id].key_id == key_id &&
                    !areEqual_val(map->mappings[id].value, value)
                )
            )
        ) id++;
        return id;
    }
}

uint32_t linearSearchForwardKey_map(
    Map const map[static const 1], uint32_t const search_start_id, uint32_t const key_id
) {
    DEBUG_ASSERT(isValid_map(map))

    if (map->size == 0) {
        return UINT32_MAX;
    } else {
        uint32_t id = search_start_id;
        while (id < map->size && map->mappings[id].key_id < key_id) id++;
        return id;
    }
}

uint32_t linearSearchForwardValue_map(
    Map const map[static const 1], uint32_t const search_start_id, Value const value
) {
    DEBUG_ASSERT(isValid_map(map))

    if (map->size == 0) {
        return UINT32_MAX;
    } else {
        uint32_t id = search_start_id;
        while (id < map->size && !areEqual_val(map->mappings[id].value, value)) id++;
        return id;
    }
}
