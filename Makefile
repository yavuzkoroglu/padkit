VERSION_PADKIT_CURRENT=1.0
VERSION_PADKIT_COMPATIBILITY=1.0

CCARGS=-std=c99 -Weverything
CC=clang
# CCARGS=-std=c99 -Wall -Wextra
# CC=gcc-13

COVARGS=${DEBUGFLAGS} --coverage -fprofile-arcs -ftest-coverage
UTILFILES=src/util/*.c
INCLUDES=-Iinclude
LIBRARIES=-lm
DEBUGFLAGS=-g
RELEASEFLAGS=-Ofast -DNDEBUG

DYLIBFLAGS=-dynamiclib -current_version ${VERSION_PADKIT_CURRENT} -compatibility_version ${VERSION_PADKIT_COMPATIBILITY} -fvisibility="default"

DYLIB_RELEASE_OUT=lib/padkit.${VERSION_PADKIT_CURRENT}.dylib
DYLIB_DEBUG_OUT=lib/padkitdebug.${VERSION_PADKIT_CURRENT}.dylib

ALWAYSSILENCED=-Wno-poison-system-directories -Wno-declaration-after-statement -Wno-padded -Wno-unused-parameter -Wno-unsafe-buffer-usage

dylib: ; \
    ${CC} ${DYLIBFLAGS} ${RELEASEFLAGS} ${ALWAYSSILENCED} ${INCLUDES} ${LIBRARIES} -o ${DYLIB_RELEASE_OUT}; \
    ${CC} ${DYLIBFLAGS} ${DEBUGFLAGS} ${ALWAYSSILENCED} ${INCLUDES} ${LIBRARIES} -o ${DYLIB_DEBUG_OUT}      \

documentation: ; \
    doxygen

bin: ; \
    mkdir bin

lib: ; \
    mkdir lib

tests: dylib
    

clean: ; \
    rm -rf *.gcno *.gcda *.gcov bin/* lib/* html latex
