#ifndef NONNULL_H
    #define NONNULL_H

    #define NONNULL(type, x)    NONNULL_N(type, x, 1)
    #define NONNULL_N(type, x)  type x[static const 1]
