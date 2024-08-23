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

    /**
     * @def VAL_DEFAULT_EPSILON
     *   The minimum value difference that is non-negligible in computation.
     */
    #define VAL_DEFAULT_EPSILON (0.0001220703125)
    extern double val_epsilon;

    /**
     * @def VAL_TC_FLOAT
     *   The typecode for float.
     */
    #define VAL_TC_FLOAT        (0U)

    /**
     * @def VAL_TC_INT
     *   The typecode for int.
     */
    #define VAL_TC_INT          (1U)

    /**
     * @def VAL_TC_UNSIGNED
     *   The typecode for unsigned.
     */
    #define VAL_TC_UNSIGNED     (2U)

    /**
     * @def VAL_TC_NOT_A_VALUE
     *   The typecode for invalid values.
     */
    #define VAL_TC_NOT_A_VALUE  (3U)

    /**
     * @def VAL_F_FLOAT
     *   The format string for float values.
     */
    #define VAL_F_FLOAT         "%.2lf"

    /**
     * @def VAL_F_INT
     *   The format string for int values.
     */
    #define VAL_F_INT           "%d"

    /**
     * @def VAL_F_UNSIGNED
     *   The format string for unsigned values.
     */
    #define VAL_F_UNSIGNED      "%u"

    /**
     * @def NOT_A_VALUE
     *   A special Value denoting a NOT-Value. This value cannot pass the isValid_val() test.
     */
    #define NOT_A_VALUE       ((Value){ (value_t){ .as_unsigned = 0U  }, VAL_TC_NOT_A_VALUE })

    /**
     * @def VAL_FLOAT
     *   Constructs a float Value that is equal to val.
     */
    #define VAL_FLOAT(val)    ((Value){ (value_t){ .as_float    = val }, VAL_TC_FLOAT       })

    /**
     * @def VAL_INT
     *   Constructs an int Value that is equal to val.
     */
    #define VAL_INT(val)      ((Value){ (value_t){ .as_int      = val }, VAL_TC_INT         })

    /**
     * @def VAL_UNSIGNED
     *   Constructs an unsigned Value that is equal to val.
     */
    #define VAL_UNSIGNED(val) ((Value){ (value_t){ .as_unsigned = val }, VAL_TC_UNSIGNED    })

    /**
     * @struct Value
     * @brief A Value could be one of several types.
     *
     * @var Value::raw
     *   The raw value.
     * @var Value::type_code
     *   Type-code of the value.
     */
    typedef struct ValueBody {
        value_t  raw;
        uint32_t type_code;
    } Value;

    /**
     * @brief Checks if two Values are equal.
     *
     * @param[in] a A constant Value.
     * @param[in] b A constant Value.
     *
     * @return A Boolean value.
     */
    bool areEqual_val(Value const a, Value const b);

    /**
     * @brief Checks if a Value is valid.
     *
     * @param[in] value A constant Value.
     *
     * @return A Boolean value.
     */
    bool isValid_val(Value const value);
#endif
