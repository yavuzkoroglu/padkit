/**
 * @file timestamp.h
 * @brief Formatted timestamps for verbose/log outputs.
 * @author Yavuz Koroglu
 */
#ifndef TIMESTAMP_H
    #define TIMESTAMP_H

    /**
     * @def TS_FMT
     *   The format string for the timestamp.
     */
    #ifndef TS_FMT
        #define TS_FMT  "%F %T"
    #endif

    /**
     * @def TS_LEN
     *   The length of a timestamp string.
     */
    #ifndef TS_LEN
        #define TS_LEN  (19)
    #endif

    /**
     * @brief Generates an ISO 8601 timestamp for verbose/log outputs.
     *
     * The timestamp is 'static'. Calls override previous timestamps.
     *
     * @return A ponter to a constant character.
     */
    char const* get_timestamp(void);
#endif
