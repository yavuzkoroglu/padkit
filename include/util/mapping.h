/**
 * @file mapping.h
 * @brief Defines Mapping, which is a logical pairing between some key index and a value.
 * @author Yavuz Koroglu
 * @see Value
 */
#ifndef MAPPING_H
    #define MAPPING_H
    #include "util/value.h"

    /**
     * @struct Mapping
     * @brief An index-value pairing.
     *
     * @var Mapping::key_id
     *   The key index.
     * @var Mapping::value
     *   The value.
     */
    typedef struct MappingBody {
        uint32_t key_id;
        Value    value;
    } Mapping;
#endif
