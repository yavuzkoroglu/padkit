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
        obj/padkit/memalloc.o           \
        obj/padkit/overlap.o            \
        obj/padkit/stack.o              \
        obj/padkit/timestamp.o

SOURCES=src/padkit/arraylist.c          \
        src/padkit/memalloc.c           \
        src/padkit/overlap.c            \
        src/padkit/stack.c              \
        src/padkit/timestamp.c          \

TEST_PARAM=--coverage -fprofile-arcs -ftest-coverage

default: all

.PHONY: all clean default documentation libs objects target tests version

${DYNAMIC_LIB}: lib                     \
                ${SOURCES}              \
                ; ${COMPILE} ${DYNAMIC_LIB_FLAGS} -Iinclude ${SOURCES} -o ${DYNAMIC_LIB}

${TESTS_OUT}:   bin                     \
                include/padkit.h        \
                ${SOURCES}              \
                src/tests.c             \
                ; ${COMPILE} -Iinclude ${TEST_PARAM} ${SOURCES} src/tests.c -o ${TESTS_OUT}

all: clean libs tests

bin: ; mkdir bin

clean: ; rm -rf include/padkit.h obj/* bin/* lib/* *.gcno *.gcda *.gcov html latex

documentation: ; doxygen

include/padkit.h: ;                                                             @\
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
    echo '    #include "padkit/debug.h"'                    >> include/padkit.h; \
    echo '    #include "padkit/invalid.h"'                  >> include/padkit.h; \
    echo '    #include "padkit/memalloc.h"'                 >> include/padkit.h; \
    echo '    #include "padkit/overlap.h"'                  >> include/padkit.h; \
    echo '    #include "padkit/size.h"'                     >> include/padkit.h; \
    echo '    #include "padkit/stack.h"'                    >> include/padkit.h; \
    echo '    #include "padkit/timestamp.h"'                >> include/padkit.h; \
    echo '#endif'                                           >> include/padkit.h;

lib: ; mkdir lib

lib/libpadkit.a: lib objects; ar -rcs lib/libpadkit.a ${OBJECTS}

libs: lib/libpadkit.a ${DYNAMIC_LIB}

obj: ; mkdir obj

obj/padkit: obj ; mkdir obj/padkit

obj/padkit/arraylist.o: obj/padkit      \
    include/padkit/arraylist.h          \
    include/padkit/debug.h              \
    include/padkit/memalloc.h           \
    include/padkit/overlap.h            \
    include/padkit/size.h               \
    src/padkit/arraylist.c              \
    ; ${COMPILE} -Iinclude src/padkit/arraylist.c -c -o obj/padkit/arraylist.o

obj/padkit/memalloc.o: obj/padkit       \
    include/padkit/debug.h              \
    include/padkit/memalloc.h           \
    include/padkit/size.h               \
    src/padkit/memalloc.c               \
    ; ${COMPILE} -Iinclude src/padkit/memalloc.c -c -o obj/padkit/memalloc.o

obj/padkit/overlap.o: obj/padkit        \
    src/padkit/overlap.c                \
    ; ${COMPILE} -Iinclude src/padkit/overlap.c -c -o obj/padkit/overlap.o

obj/padkit/stack.o: obj/padkit          \
    include/padkit/arraylist.h          \
    include/padkit/debug.h              \
    include/padkit/memalloc.h           \
    include/padkit/overlap.h            \
    include/padkit/size.h               \
    include/padkit/stack.h              \
    src/padkit/stack.c                  \
    ; ${COMPILE} -Iinclude src/padkit/stack.c -c -o obj/padkit/stack.o

obj/padkit/timestamp.o: obj/padkit      \
    include/padkit/debug.h              \
    include/padkit/timestamp.h          \
    src/padkit/timestamp.c              \
    ; ${COMPILE} -Iinclude src/padkit/timestamp.c -c -o obj/padkit/timestamp.o

objects: ${OBJECTS}

target: ; @echo ${PADKIT_TARGET}

tests: ${TESTS_OUT}

version: ; @echo ${PADKIT_VERSION}
