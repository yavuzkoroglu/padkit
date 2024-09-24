include compile.mk

ifeq (${OS},Darwin)
DYNAMIC_LIB=lib/libpadkit.dylib
TESTS_OUT=bin/tests.out
else
ifeq (${OS},Linux)
DYNAMIC_LIB=lib/libpadkit.so
TESTS_OUT=bin/tests.out
else
DYNAMIC_LIB=lib/libpadkit.dll
TESTS_OUT=bin/tests.exe
endif
endif

OBJECTS=obj/padkit/arraylist.o          \
        obj/padkit/bitmatrix.o          \
        obj/padkit/hash.o               \
        obj/padkit/item.o               \
        obj/padkit/jsonparser.o         \
        obj/padkit/memalloc.o           \
        obj/padkit/overlap.o            \
        obj/padkit/prime.o              \
        obj/padkit/timestamp.o

SOURCES=src/padkit/arraylist.c          \
        src/padkit/bitmatrix.c          \
        src/padkit/hash.c               \
        src/padkit/item.c               \
        src/padkit/jsonparser.c         \
        src/padkit/memalloc.c           \
        src/padkit/overlap.c            \
        src/padkit/prime.c              \
        src/padkit/timestamp.c

TESTSRC=src/tests/arraylist.c           \
        src/tests/bitmatrix.c           \
        src/tests/graphmatrix.c         \
        src/tests/hash.c                \
        src/tests/item.c                \
        src/tests/jsonparser.c          \
        src/tests/memalloc.c            \
        src/tests/overlap.c             \
        src/tests/prime.c               \
        src/tests/timestamp.c

TEST_PARAM=-Isrc --coverage -fprofile-arcs -ftest-coverage src/tests.c lib/libpadkit.a

default: all

.FORCE:

.PHONY: .FORCE all clean cleancoverage default libs objects target tests version

${DYNAMIC_LIB}: .FORCE      \
    lib                     \
    ${SOURCES}              \
    ; ${COMPILE} ${DYNAMIC_LIB_FLAGS} -Iinclude ${SOURCES} -o ${DYNAMIC_LIB}

${TESTS_OUT}: .FORCE        \
    cleancoverage           \
    bin                     \
    include/padkit.h        \
    lib/libpadkit.a         \
    ${TESTSRC}              \
    src/tests.c             \
    ; ${COMPILE} -Iinclude ${TEST_PARAM} -o ${TESTS_OUT} && clear && ${TESTS_OUT}

all: include/padkit.h libs tests

bin: ; mkdir bin

clean: cleancoverage; rm -rf include/padkit.h obj bin lib html latex

cleancoverage: ; rm -rf *.gcno *.gcda *.gcov bin/*.gcno bin/*.gcda bin/*.gcov

include/padkit.h: .FORCE;                                                       @\
    echo '/**'                                               > include/padkit.h; \
    echo ' * @file padkit.h'                                >> include/padkit.h; \
    echo ' * @brief An automatically generated header.'     >> include/padkit.h; \
    echo ' * @author Yavuz Koroglu'                         >> include/padkit.h; \
    echo ' */'                                              >> include/padkit.h; \
    echo '#ifndef PADKIT_H'                                 >> include/padkit.h; \
    echo '    #define PADKIT_H'                             >> include/padkit.h; \
    echo '    #define PADKIT_VERSION "'${PADKIT_VERSION}'"' >> include/padkit.h; \
    echo '    #define PADKIT_TARGET  "'${PADKIT_TARGET}'"'  >> include/padkit.h; \
    echo '    #include "padkit/arraylist.h"'                >> include/padkit.h; \
    echo '    #include "padkit/bitmatrix.h"'                >> include/padkit.h; \
    echo '    #include "padkit/bliterals.h"'                >> include/padkit.h; \
    echo '    #include "padkit/error.h"'                    >> include/padkit.h; \
    echo '    #include "padkit/hash.h"'                     >> include/padkit.h; \
    echo '    #include "padkit/invalid.h"'                  >> include/padkit.h; \
    echo '    #include "padkit/item.h"'                     >> include/padkit.h; \
    echo '    #include "padkit/jsonparser.h"'               >> include/padkit.h; \
    echo '    #include "padkit/memalloc.h"'                 >> include/padkit.h; \
    echo '    #include "padkit/overlap.h"'                  >> include/padkit.h; \
    echo '    #include "padkit/preprocessor.h"'             >> include/padkit.h; \
    echo '    #include "padkit/prime.h"'                    >> include/padkit.h; \
    echo '    #include "padkit/repeat.h"'                   >> include/padkit.h; \
    echo '    #include "padkit/size.h"'                     >> include/padkit.h; \
    echo '    #include "padkit/timestamp.h"'                >> include/padkit.h; \
    echo '    #include "padkit/unused.h"'                   >> include/padkit.h; \
    echo '#endif'                                           >> include/padkit.h;

lib: ; mkdir lib

lib/libpadkit.a: .FORCE lib objects; ar -rcs lib/libpadkit.a ${OBJECTS}

libs: lib/libpadkit.a ${DYNAMIC_LIB}

obj: ; mkdir obj

obj/padkit: obj ; mkdir obj/padkit

obj/padkit/arraylist.o: .FORCE          \
    obj/padkit                          \
    include/padkit/arraylist.h          \
    include/padkit/error.h              \
    include/padkit/invalid.h            \
    include/padkit/memalloc.h           \
    include/padkit/overlap.h            \
    include/padkit/size.h               \
    include/padkit/unused.h             \
    src/padkit/arraylist.c              \
    ; ${COMPILE} -Iinclude src/padkit/arraylist.c -c -o obj/padkit/arraylist.o

obj/padkit/bitmatrix.o: .FORCE          \
    obj/padkit                          \
    include/padkit/bitmatrix.h          \
    include/padkit/error.h              \
    include/padkit/memalloc.h           \
    include/padkit/size.h               \
    src/padkit/bitmatrix.c              \
    ; ${COMPILE} -Iinclude src/padkit/bitmatrix.c -c -o obj/padkit/bitmatrix.o

obj/padkit/item.o: .FORCE               \
    obj/padkit                          \
    include/padkit/hash.h               \
    include/padkit/item.h               \
    include/padkit/size.h               \
    src/padkit/item.c                   \
    ; ${COMPILE} -Iinclude src/padkit/item.c -c -o obj/padkit/item.o

obj/padkit/hash.o: .FORCE               \
    obj/padkit                          \
    include/padkit/hash.h               \
    src/padkit/hash.c                   \
    ; ${COMPILE} -Iinclude src/padkit/hash.c -c -o obj/padkit/hash.o

obj/padkit/jsonparser.o: .FORCE         \
    obj/padkit                          \
    include/padkit/error.h              \
    include/padkit/jsonparser.h         \
    include/padkit/memalloc.h           \
    include/padkit/size.h               \
    include/padkit/unused.h             \
    src/padkit/jsonparser.c             \
    ; ${COMPILE} -Iinclude src/padkit/jsonparser.c -c -o obj/padkit/jsonparser.o

obj/padkit/memalloc.o: .FORCE           \
    obj/padkit                          \
    include/padkit/error.h              \
    include/padkit/memalloc.h           \
    include/padkit/size.h               \
    src/padkit/memalloc.c               \
    ; ${COMPILE} -Iinclude src/padkit/memalloc.c -c -o obj/padkit/memalloc.o

obj/padkit/overlap.o: .FORCE            \
    obj/padkit                          \
    include/padkit/overlap.h            \
    include/padkit/size.h               \
    src/padkit/overlap.c                \
    ; ${COMPILE} -Iinclude src/padkit/overlap.c -c -o obj/padkit/overlap.o

obj/padkit/prime.o: .FORCE              \
    obj/padkit                          \
    include/padkit/prime.h              \
    src/padkit/prime.c                  \
    ; ${COMPILE} -Iinclude src/padkit/prime.c -c -o obj/padkit/prime.o

obj/padkit/timestamp.o: .FORCE          \
    obj/padkit                          \
    include/padkit/timestamp.h          \
    src/padkit/timestamp.c              \
    ; ${COMPILE} -Iinclude src/padkit/timestamp.c -c -o obj/padkit/timestamp.o

objects: ${OBJECTS}

target: ; @echo ${PADKIT_TARGET}

tests: ${TESTS_OUT}

version: ; @echo ${PADKIT_VERSION}
