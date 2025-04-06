#ifndef PADKIT_INTFN_H
    #define PADKIT_INTFN_H
    #include <stdbool.h>
    #include <stdint.h>

    #define ABS_I8(a)   ((uint8_t)(((a) > 0) ? (a) : (-a)))
    #define ABS_I16(a) ((uint16_t)(((a) > 0) ? (a) : (-a)))
    #define ABS_I32(a) ((uint32_t)(((a) > 0) ? (a) : (-a)))
    #define ABS_I64(a) ((uint64_t)(((a) > 0) ? (a) : (-a)))
    #define MAX_I(a,b) (((a) > (b)) ? (a) : (b))
    #define MIN_I(a,b) (((a) < (b)) ? (a) : (b))

       int8_t  add_i8(  int8_t const a,   int8_t const b, bool* const p_overflow);
      int16_t add_i16( int16_t const a,  int16_t const b, bool* const p_overflow);
      int32_t add_i32( int32_t const a,  int32_t const b, bool* const p_overflow);
      int64_t add_i64( int64_t const a,  int64_t const b, bool* const p_overflow);
      uint8_t  add_u8( uint8_t const a,  uint8_t const b, bool* const p_overflow);
     uint16_t add_u16(uint16_t const a, uint16_t const b, bool* const p_overflow);
     uint32_t add_u32(uint32_t const a, uint32_t const b, bool* const p_overflow);
     uint64_t add_u64(uint64_t const a, uint64_t const b, bool* const p_overflow);
     uint8_t  add_ui8( uint8_t const a,   int8_t const b, bool* const p_overflow);
    uint16_t add_ui16(uint16_t const a,  int16_t const b, bool* const p_overflow);
    uint32_t add_ui32(uint32_t const a,  int32_t const b, bool* const p_overflow);
    uint64_t add_ui64(uint64_t const a,  int64_t const b, bool* const p_overflow);
      int8_t  add_iu8(  int8_t const a,  uint8_t const b, bool* const p_overflow);
     int16_t add_iu16( int16_t const a, uint16_t const b, bool* const p_overflow);
     int32_t add_iu32( int32_t const a, uint32_t const b, bool* const p_overflow);
     int64_t add_iu64( int64_t const a, uint64_t const b, bool* const p_overflow);

    uint32_t gcd_u32(uint32_t const a, uint32_t const b);
    uint32_t lcm_u32(uint32_t const a, uint32_t const b, bool* const p_overflow);

    bool isPrime(uint32_t const odd_x);

    uint32_t nextPrime(uint32_t const x);
#endif
