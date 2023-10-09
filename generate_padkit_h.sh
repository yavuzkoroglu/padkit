#!/usr/bin/env bash
echo '/**
 * @file padkit.h
 * @brief An automatically generated header which includes all padkit headers.
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_H
    #define PADKIT_H' > include/padkit.h
for header in $(ls include/padkit)
do
    if   [ "${header}" = "chunk.h" ]; then :;
    elif [ "${header}" = "debug.h" ]; then :;
    else
        echo "    #include \"padkit/${header}\"" >> include/padkit.h
    fi
done
echo '#endif' >> include/padkit.h
