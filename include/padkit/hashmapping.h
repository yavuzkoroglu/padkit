#ifndef PADKIT_HASHMAPPING_H
    #define PADKIT_HASHMAPPING_H
    #include <stdbool.h>
    #include "padkit/invalid.h"

    #define NOT_A_HASH_MAPPING  ((HashMapping){ 0, 0, INVALID_UINT32 })

    typedef struct HashMappingBody {
        uint_fast64_t   hashValue;
        uint32_t        mappedValue;
        uint32_t        nextId;
    } HashMapping;

    bool isValid_hmpng(HashMapping const mapping[static const 1]);
#endif
