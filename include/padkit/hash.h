#ifndef PADKIT_HASH_H
    #define PADKIT_HASH_H
    #include <stddef.h>
    #include <stdint.h>

    uint32_t hash32_str(char const str[static 1], size_t n);

    uint64_t hash64_str(char const str[static 1], size_t n);
#endif
