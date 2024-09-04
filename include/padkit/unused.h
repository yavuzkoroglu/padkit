#ifndef PADKIT_UNUSED_H
    #define PADKIT_UNUSED_H

    /* https://stackoverflow.com/questions/3599160/how-can-i-suppress-unused-parameter-warnings-in-c */
    /* #define MAYBE_UNUSED(x) (void)(x); */
    /* #define MAYBE_UNUSED(x) switch ((long long)&(x)) {default: break;} */
    #define MAYBE_UNUSED(x) if (&(x) == 0) {}
#endif
