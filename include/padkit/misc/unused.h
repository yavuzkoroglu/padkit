/**
 * @file unused.h
 * @brief A macro for variables that may be unused.
 * @author Yavuz KÖROĞLU
 * @see https://stackoverflow.com/questions/3599160/how-can-i-suppress-unused-parameter-warnings-in-c
 */
#ifndef PADKIT_MISC_UNUSED_H
    #define PADKIT_MISC_UNUSED_H

    /**
     * @brief Suppresses unused variable warnings for a given variable name.
     * @param x A variable name.
     * @warning If the compiler does NOT support void-casts, you may need to use an alternative.
     *
     * Alternative 1: <tt>#define MAYBE_UNUSED(x) switch ((long long)&(x)) {default: break;}</tt>
     * Alternative 2: <tt>#define MAYBE_UNUSED(x) if (&(x) == 0) {}</tt>
     */
    #define MAYBE_UNUSED(x) (void)(x);
#endif
