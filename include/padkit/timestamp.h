/**
 * @file timestamp.h
 * @brief Formatted timestamps for verbose/log outputs.
 * @author Yavuz Koroglu
 */
#ifndef TIMESTAMP_H
    #define TIMESTAMP_H
    /**
     * @brief Generates a formatted timestamp for verbose/log outputs.
     *
     * The timestamp is 'static', so later calls overrides the previous timestamps.
     */
    char const* get_timestamp(void);
#endif
