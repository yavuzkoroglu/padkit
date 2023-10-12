#ARCH=arm64
ARCH=x86_64

# win => ?
# linux => ?
# macos => Darwin
OS=$(shell uname)

VERSION_PADKIT_CUR=1.0
VERSION_PADKIT_COMPAT=1.0

CLANG_SILENCED=                         \
    -Wno-poison-system-directories      \
    -Wno-declaration-after-statement    \
    -Wno-padded -Wno-unused-parameter   \
    -Wno-unsafe-buffer-usage

CLANG_ARGS=-arch ${ARCH} -std=c99 -Weverything ${CLANG_SILENCED}
CLANG=clang ${CLANG_ARGS}

GCCARGS=-arch ${ARCH} -std=c99 -Wall -Wextra
GCC=gcc ${GCC_ARGS}

#CC=${GCC}
CC=${CLANG}

INCS=-Iinclude
PADKIT_C=src/padkit/*.c
TESTS_C=src/tests.c

COVERAGE=--coverage -fprofile-arcs -ftest-coverage

DEBUGFLAGS=-g
RELEASEFLAGS=-Ofast -DNDEBUG

ifeq (${OS},Darwin)
LIBFLAGS=-dynamiclib -current_version ${VERSION_PADKIT_CUR} -compatibility_version ${VERSION_PADKIT_COMPAT} -fvisibility="default"

RELEASE_LIB=lib/padkit.${VERSION_PADKIT_CUR}.dylib
DEBUG_LIB=lib/padkit_debug.${VERSION_PADKIT_CUR}.dylib

TEST_RELEASE_OUT=bin/tests_release.out
TEST_DEBUG_OUT=bin/tests_debug.out
endif

default: lib

debugtests: bin clean padkit_h; ${CC} ${COVERAGE} ${DEBUGFLAGS} ${INCS} ${PADKIT_C} ${TESTS_C} -o ${TEST_DEBUG_OUT}

all: clean lib tests documentation

bin: ; mkdir bin

clean: ; rm -rf include/padkit.h coverage.info *.gcno *.gcda *.gcov bin/* lib/* html latex

documentation: padkit_h; doxygen

libdebug: padkit_h; ${CC} ${LIBFLAGS} ${DEBUGFLAGS} ${INCS} ${PADKIT_C} -o ${DEBUG_LIB}

librelease: padkit_h; ${CC} ${LIBFLAGS} ${RELEASEFLAGS} ${INCS} ${PADKIT_C} -o ${RELEASE_LIB}

lib: libdebug librelease

padkit_h: ; @ ./generate_padkit_h.sh

releasetests: bin clean padkit_h; ${CC} ${COVERAGE} ${RELEASEFLAGS} ${INCS} ${PADKIT_C} ${TESTS_C} -o ${TEST_RELEASE_OUT}

tests: debugtests releasetests
