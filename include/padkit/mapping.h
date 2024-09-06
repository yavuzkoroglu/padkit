#ifndef PADKIT_MAPPING_H
    #define PADKIT_MAPPING_H
    #include <stdbool.h>
    #include "padkit/invalid.h"

    #define NOT_A_MAPPING  ((Mapping){ 0, 0, INVALID_UINT32 })

    typedef struct MappingBody {
        uint_fast64_t   index;
        uint32_t        value;
        uint32_t        next_id;
    } Mapping;

    bool isValid_mppng(Mapping const mapping[static const 1]);
#endif
