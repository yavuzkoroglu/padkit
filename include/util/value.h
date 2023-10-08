/**
 * @file value.h
 * @brief Defines Value.
 * @author Yavuz Koroglu
 * @see Pair
 */
#ifndef VALUE_H
    #define VALUE_H
    #include <stdbool.h>
    #include <stdint.h>

    typedef union value_t_body {
        float    as_float;
        int32_t  as_int;
        uint32_t as_unsigned;
    } value_t;

    #define VAL_DEFAULT_EPSILON 0.0001220703125
    extern double val_epsilon;

    #define VAL_TC_FLOAT        0U
    #define VAL_TC_INT          1U
    #define VAL_TC_UNSIGNED     2U
    #define VAL_TC_NOT_A_VALUE  3U

    #define VAL_F_FLOAT         "%.2lf"
    #define VAL_F_INT           "%d"
    #define VAL_F_UNSIGNED      "%u"

    #define NOT_A_VALUE       ((Value){ (value_t){ .as_unsigned = 0U  }, VAL_TC_NOT_A_VALUE })
    #define VAL_FLOAT(val)    ((Value){ (value_t){ .as_float    = val }, VAL_TC_FLOAT       })
    #define VAL_INT(val)      ((Value){ (value_t){ .as_int      = val }, VAL_TC_INT         })
    #define VAL_UNSIGNED(val) ((Value){ (value_t){ .as_unsigned = val }, VAL_TC_UNSIGNED    })

    /**
     * @struct Value
     * @brief A Value could be one of several types.
     *
     * @var Value::value
     *   The value.
     * @var Value::type_code
     *   Type-code of the value.
     */
    typedef struct ValueBody {
        value_t  raw;
        uint32_t type_code;
    } Value;

    /**
     * @brief Checks if two Values are equal.
     * @param a The first Value.
     * @param b The second Value.
     */
    bool areEqual_val(Value const a, Value const b);

    /**
     * @brief Checks if a Value is valid.
     * @param value The Value.
     */
    bool isValid_val(Value const value);
#endif
