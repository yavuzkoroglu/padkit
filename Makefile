CC=gcc
#CC=clang

#MODE=release
MODE=debug

#OS=Darwin
#OS=Linux
OS=$(shell uname)

STD=c99

VERSION_PADKIT_CUR=1.0
VERSION_PADKIT_COMPAT=1.0

ifeq (${OS},Darwin)
ARCH=$(shell uname -m)
ARCH_ARGS=-arch ${ARCH}
else
ARCH_ARGS=
endif

ifeq (${MODE},debug)
FLAGS=-std=${STD} -g
else
FLAGS=-std=${STD} -Ofast -DNDEBUG
endif

ifeq (${CC},clang)
SILENCED=                               \
    -Wno-poison-system-directories      \
    -Wno-declaration-after-statement    \
    -Wno-padded -Wno-unused-parameter   \
    -Wno-unknown-warning-option         \
    -Wno-unsafe-buffer-usage
ARGS=${ARCH_ARGS} ${FLAGS} -Weverything ${SILENCED} -Iinclude
else
SILENCED=                               \
    -Wno-unused-parameter               \
    -Wno-old-style-declaration          \
    -Wno-unknown-warning-option         \
    -Wno-nullability-completeness
ARGS=${ARCH_ARGS} ${FLAGS} -Wall -Wextra ${SILENCED} -Iinclude
endif

COMPILE=${CC} ${ARGS}

ifeq (${OS},Darwin)
DYNAMIC_LIB_FLAGS=                                      \
    -dynamiclib -current_version ${VERSION_PADKIT_CUR}  \
    -compatibility_version ${VERSION_PADKIT_COMPAT}     \
    -fvisibility="default"

DYNAMIC_LIB=lib/libpadkit.dylib
TESTS_OUT=bin/tests.out
else
ifeq (${OS},Linux)
DYNAMIC_LIB_FLAGS=-shared -fPIC
DYNAMIC_LIB=lib/libpadkit.so
TESTS_OUT=bin/tests.out
else
DYNAMIC_LIB_FLAGS=-shared
DYNAMIC_LIB=lib/libpadkit.dll
TESTS_OUT=bin/tests.exe
endif
endif

default: clean lib/libpadkit.a ${DYNAMIC_LIB}

.PHONY: all clean default objects tests

all: clean ${TESTS_OUT} lib/libpadkit.a ${DYNAMIC_LIB}

bin: ; mkdir bin

include/padkit.h: ;                                                         @\
    echo '/**'                                           > include/padkit.h; \
    echo ' * @file padkit.h'                            >> include/padkit.h; \
    echo ' * @brief An automatically generated header.' >> include/padkit.h; \
    echo ' * @author Yavuz Koroglu'                     >> include/padkit.h; \
    echo ' */'                                          >> include/padkit.h; \
    echo '#ifndef PADKIT_H'                             >> include/padkit.h; \
    echo '    #define PADKIT_H'                         >> include/padkit.h; \
    echo '    #include "padkit/bliterals.h"'            >> include/padkit.h; \
    echo '    #include "padkit/chunkset.h"'             >> include/padkit.h; \
    echo '    #include "padkit/chunktable.h"'           >> include/padkit.h; \
    echo '    #include "padkit/csv.h"'                  >> include/padkit.h; \
    echo '    #include "padkit/graphmatrix.h"'          >> include/padkit.h; \
    echo '    #include "padkit/hash.h"'                 >> include/padkit.h; \
    echo '    #include "padkit/map.h"'                  >> include/padkit.h; \
    echo '    #include "padkit/mapping.h"'              >> include/padkit.h; \
    echo '    #include "padkit/prime.h"'                >> include/padkit.h; \
    echo '    #include "padkit/reallocate.h"'           >> include/padkit.h; \
    echo '    #include "padkit/repeat.h"'               >> include/padkit.h; \
    echo '    #include "padkit/streq.h"'                >> include/padkit.h; \
    echo '    #include "padkit/timestamp.h"'            >> include/padkit.h; \
    echo '    #include "padkit/value.h"'                >> include/padkit.h; \
    echo '#endif'                                       >> include/padkit.h;

lib: ; mkdir lib

lib/libpadkit.a: lib objects; ar -rcs lib/libpadkit.a obj/padkit/*.o

${DYNAMIC_LIB}: lib; ${COMPILE} ${DYNAMIC_LIB_FLAGS} src/padkit/*.c -o ${DYNAMIC_LIB}

obj: ; mkdir obj

obj/padkit: obj ; mkdir obj/padkit

obj/padkit/chunk.o: obj/padkit          \
    include/padkit/chunk.h              \
    include/padkit/debug.h              \
    include/padkit/reallocate.h         \
    src/padkit/chunk.c                  \
    ; ${COMPILE} src/padkit/chunk.c -c -o obj/padkit/chunk.o

obj/padkit/chunkset.o: obj/padkit       \
    include/padkit/chunk.h              \
    include/padkit/chunkset.h           \
    include/padkit/debug.h              \
    include/padkit/hash.h               \
    include/padkit/prime.h              \
    include/padkit/reallocate.h         \
    include/padkit/streq.h              \
    src/padkit/chunkset.c               \
    ; ${COMPILE} src/padkit/chunkset.c -c -o obj/padkit/chunkset.o

obj/padkit/chunktable.o: obj/padkit     \
    include/padkit/chunk.h              \
    include/padkit/chunktable.h         \
    include/padkit/debug.h              \
    include/padkit/hash.h               \
    include/padkit/prime.h              \
    include/padkit/reallocate.h         \
    include/padkit/streq.h              \
    src/padkit/chunktable.c             \
    ; ${COMPILE} src/padkit/chunktable.c -c -o obj/padkit/chunktable.o

obj/padkit/graphmatrix.o: obj/padkit    \
    include/padkit/bliterals.h          \
    include/padkit/debug.h              \
    include/padkit/graphmatrix.h        \
    src/padkit/graphmatrix.c            \
    ; ${COMPILE} src/padkit/graphmatrix.c -c -o obj/padkit/graphmatrix.o

obj/padkit/hash.o: obj/padkit           \
    include/padkit/debug.h              \
    include/padkit/hash.h               \
    src/padkit/hash.c                   \
    ; ${COMPILE} src/padkit/hash.c -c -o obj/padkit/hash.o

obj/padkit/map.o: obj/padkit            \
    include/padkit/debug.h              \
    include/padkit/map.h                \
    include/padkit/mapping.h            \
    include/padkit/reallocate.h         \
    include/padkit/value.h              \
    src/padkit/map.c                    \
    ; ${COMPILE} src/padkit/map.c -c -o obj/padkit/map.o

obj/padkit/prime.o: obj/padkit          \
    include/padkit/debug.h              \
    include/padkit/prime.h              \
    src/padkit/prime.c                  \
    ; ${COMPILE} src/padkit/prime.c -c -o obj/padkit/prime.o

obj/padkit/reallocate.o: obj/padkit     \
    include/padkit/debug.h              \
    include/padkit/reallocate.h         \
    src/padkit/reallocate.c             \
    ; ${COMPILE} src/padkit/reallocate.c -c -o obj/padkit/reallocate.o

obj/padkit/streq.o: obj/padkit          \
    include/padkit/debug.h              \
    include/padkit/streq.h              \
    src/padkit/streq.c                  \
    ; ${COMPILE} src/padkit/streq.c -c -o obj/padkit/streq.o

obj/padkit/timestamp.o: obj/padkit      \
    include/padkit/timestamp.h          \
    src/padkit/timestamp.c              \
    ; ${COMPILE} src/padkit/timestamp.c -c -o obj/padkit/timestamp.o

obj/padkit/value.o: obj/padkit          \
    include/padkit/value.h              \
    src/padkit/value.c                  \
    ; ${COMPILE} src/padkit/value.c -c -o obj/padkit/value.o

${TESTS_OUT}:        \
    bin              \
    include/padkit.h \
    src/tests.c      \
    ; ${COMPILE} --coverage -fprofile-arcs -ftest-coverage src/padkit/*.c src/tests.c -o ${TESTS_OUT}

clean: ; rm -rf include/padkit.h obj/* bin/* lib/* *.gcno *.gcda *.gcov

objects:                        \
    obj/padkit/chunk.o          \
    obj/padkit/chunkset.o       \
    obj/padkit/chunktable.o     \
    obj/padkit/graphmatrix.o    \
    obj/padkit/hash.o           \
    obj/padkit/map.o            \
    obj/padkit/prime.o          \
    obj/padkit/reallocate.o     \
    obj/padkit/streq.o          \
    obj/padkit/timestamp.o      \
    obj/padkit/value.o

tests: ${TESTS_OUT}
