#ifndef PADKIT_TIMESTAMP_H
    #define PADKIT_TIMESTAMP_H

    #ifndef TS_FMT
        #define TS_FMT  "%F %T"
    #endif

    #ifndef TS_LEN
        #define TS_LEN  (19)
    #endif

    /* Generates an ISO 8601 timestamp for verbose/log outputs.
     * The timestamp is 'static'. Calls override previous timestamps. */
    char const* get_timestamp(void);
#endif
