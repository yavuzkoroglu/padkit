/**
 * @file csv.h
 * @brief Defines some CSV related macros.
 * @author Yavuz Koroglu
 */
#ifndef CSV_H
    #define CSV_H

    /**
     * @def CSV_INITIAL_DELIMETER
     *   Initially, let the csv_delimeter value be equal to this constant.
     */
    #define CSV_INITIAL_DELIMETER ","
    extern char const* csv_delimeter;

    /**
     * @def CSV_INITIAL_ROW_END
     *   Initially, let the csv_row_end value be equal to this constant.
     */
    #define CSV_INITIAL_ROW_END "\n"
    extern char const* csv_row_end;
#endif
