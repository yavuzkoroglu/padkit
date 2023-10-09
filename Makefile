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

TEST_RELEASE_OUT=bin/tests.out
TEST_DEBUG_OUT=bin/tests.out

default: dylibrelease

all: clean dylib tests documentation

bin: ; mkdir bin

clean: ; rm -rf include/padkit.h *.gcno *.gcda *.gcov bin/* lib/* html latex

debugtests: bin clean padkit_h; ${CC} ${COVARGS} ${RELEASEFLAGS} ${INCS} ${LIBS} ${PADKIT_C} ${TESTS_C} -o ${TEST_RELEASE_OUT}

documentation: padkit_h; doxygen

dylib: dylibrelease dylibdebug

dylibdebug: lib padkit_h; ${CC} ${DYLIBFLAGS} ${DEBUGFLAGS} ${INCS} ${LIBS} ${PADKIT_C} -o ${DYLIB_DEBUG_LIB}

dylibrelease: lib padkit_h; ${CC} ${DYLIBFLAGS} ${RELEASEFLAGS} ${INCS} ${LIBS} ${PADKIT_C} -o ${DYLIB_RELEASE_LIB}

lib: ; mkdir lib

padkit_h: ; @ ./generate_padkit_h.sh

releasetests: bin clean padkit_h; ${CC} ${COVARGS} ${DEBUGFLAGS} ${INCS} ${LIBS} ${PADKIT_C} ${TESTS_C} -o ${TEST_DEBUG_OUT}
