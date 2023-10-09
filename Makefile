VERSION_PADKIT_CUR=1.0
VERSION_PADKIT_COMPAT=1.0

SILENCED=-Wno-poison-system-directories -Wno-declaration-after-statement -Wno-padded -Wno-unused-parameter -Wno-unsafe-buffer-usage
CCARGS=-std=c99 -Weverything ${SILENCED}
CC=clang ${CCARGS}
# CCARGS=-std=c99 -Wall -Wextra
# CC=gcc-13

COVARGS=--coverage -fprofile-arcs -ftest-coverage
PADKIT_C=src/padkit/*.c
TESTS_C=src/tests/*.c
INCS=-Iinclude
LIBS=-lm
DEBUGFLAGS=-g
RELEASEFLAGS=-Ofast -DNDEBUG

DYLIBFLAGS=-dynamiclib -current_version ${VERSION_PADKIT_CUR} -compatibility_version ${VERSION_PADKIT_COMPAT} -fvisibility="default"

DYLIB_RELEASE_LIB=lib/padkit.${VERSION_PADKIT_CUR}.dylib
DYLIB_DEBUG_LIB=lib/padkit_debug.${VERSION_PADKIT_CUR}.dylib

TEST_RELEASE_OUT=bin/tests_release.out
TEST_DEBUG_OUT=bin/tests_debug.out

dylibrelease: padkit_h; \
    ${CC} ${DYLIBFLAGS} ${RELEASEFLAGS} ${INCS} ${LIBS} ${PADKIT_C} -o ${DYLIB_RELEASE_LIB}

bin: ; \
    mkdir bin

documentation: padkit_h; \
    doxygen

dylib: dylibrelease dylibdebug

dylibdebug: padkit_h; \
    ${CC} ${DYLIBFLAGS} ${DEBUGFLAGS} ${INCS} ${LIBS} ${PADKIT_C} -o ${DYLIB_DEBUG_LIB}

lib: ; \
    mkdir lib

padkit_h: ; ./generate_padkit_h.sh

tests: padkit_h; \
    ${CC} ${COVARGS} ${RELEASEFLAGS} ${INCS} ${LIBS} ${PADKIT_C} ${TESTS_C} -o ${TEST_RELEASE_OUT}; \
    ${CC} ${COVARGS} ${DEBUGFLAGS}   ${INCS} ${LIBS} ${PADKIT_C} ${TESTS_C} -o ${TEST_DEBUG_OUT}

clean: ; \
    rm -rf include/padkit.h *.gcno *.gcda *.gcov bin/* lib/* html latex
