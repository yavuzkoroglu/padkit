#ifndef PADKIT_UNUSED_H
    #define PADKIT_UNUSED_H

    /* https://stackoverflow.com/questions/3599160/how-can-i-suppress-unused-parameter-warnings-in-c#3599170 */
    #define MAYBE_UNUSED(...)   (void)(__VA_ARGS__);
#endif
