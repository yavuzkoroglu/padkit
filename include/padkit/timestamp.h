/**
 * @file timestamp.h
 * @brief Formatted timestamps for verbose/log outputs.
 * @author Yavuz Koroglu
 */
#ifndef TIMESTAMP_H
    #define TIMESTAMP_H
    /**
     * @brief Generates an ISO 8601 timestamp for verbose/log outputs.
     *
     * The timestamp is 'static'. Calls override previous timestamps.
     */
    char const* get_timestamp(void);
#endif
