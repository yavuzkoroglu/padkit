/**
 * @file timestamp.h
 * @brief Facilities to generate ISO 8601 timestamps for verbose/log outputs.
 * @author Yavuz KÖROĞLU
 */
#ifndef PADKIT_MISC_TIMESTAMP_H
    #define PADKIT_MISC_TIMESTAMP_H

    #ifndef TS_FMT
        /**
         * @brief The timestamp format string.
         * @warning An equivalent format, <tt>"%F %T"</tt>, does NOT work with some compilers in Windows.
         */
        #define TS_FMT "%Y-%m-%d %H:%M:%S"
    #endif

    #ifndef TS_LEN
        /**
         * @brief The length of a timestamp string in bytes.
         */
        #define TS_LEN (19)
    #endif

    /**
     * @brief Generates an ISO 8601 timestamp for verbose/log outputs.
     * @returns A pointer to a constant string that holds the timestamp.
     * @important The pointed timestamp string is a <tt>static</tt> variable.
     * @warning Due to <tt>static</tt> storage, every <tt>getTS()</tt> call overrides previous timestamps.
     */
    char const* getTS(void);
#endif
