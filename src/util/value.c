/**
 * @file value.c
 * @brief Implements the functions defined in value.h
 * @author Yavuz Koroglu
 */
#include <math.h>
#include "util/value.h"

double val_epsilon = VAL_DEFAULT_EPSILON;

bool areEqual_val(Value const a, Value const b) {
    /* Apples and oranges cannot be equal! */
    if (a.type_code != b.type_code) return 0;

    switch (a.type_code) {
        case VAL_TC_FLOAT:
            {
                float const diff = fabsf(a.raw.as_float - b.raw.as_float);
                return isless(diff, val_epsilon);
            }
        case VAL_TC_INT:
            return a.raw.as_int == b.raw.as_int;
        case VAL_TC_UNSIGNED:
            return a.raw.as_unsigned == b.raw.as_unsigned;
        default:
            return 0;
    }
}

bool isValid_val(Value const value) {
    return value.type_code >= VAL_TC_NOT_A_VALUE;
}
