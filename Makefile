VERSION_SRCMETRICS=0.0.2
DEFINES=-DVERSION_SRCMETRICS=\"${VERSION_SRCMETRICS}\" -DUNIT_COUNT_GUESS=1024 -DFN_COUNT_GUESS=16384 -DSTMT_COUNT_GUESS=524288 -DLABEL_COUNT_GUESS=1024 -DCALL_COUNT_GUESS=1024 -DELEMENT_LEN_GUESS=16

CCARGS=-arch x86_64 -std=c99 ${DEFINES} -Weverything
CC=clang
# CCARGS=-arch x86_64 -std=c99 ${DEFINES} -Wall -Wextra
# CC=gcc-13

COVARGS=${DEBUGFLAGS} --coverage -fprofile-arcs -ftest-coverage
CFILES=src/util/*.c src/languages/*.c src/srcmetrics/*.c src/srcmetrics/metrics/*.c
INCLUDES=-Iinclude
LIBS=-L/usr/local/lib
LIBRARIES=${LIBS} -lsrcml -lsrcsax -lm
DEBUGFLAGS=-g
SRCMETRICS=src/srcmetrics.c
EXEC=bin/srcmetrics
ALWAYSSILENCED=-Wno-poison-system-directories -Wno-declaration-after-statement -Wno-padded -Wno-unused-parameter -Wno-unsafe-buffer-usage
SILENCEDWARNINGS=${ALWAYSSILENCED}
COVERAGE=${CC} ${ALWAYSSILENCED} ${COVARGS} ${CCARGS} ${DEBUGFLAGS} ${INCLUDES} ${LIBRARIES}
DEBUG=${CC} ${ALWAYSSILENCED} ${CCARGS} ${DEBUGFLAGS} ${INCLUDES} ${LIBRARIES} ${CFILES}

compile: ; \
    ${CC} ${CCARGS} -DNDEBUG ${SILENCEDWARNINGS} ${INCLUDES} ${LIBRARIES} ${CFILES} ${SRCMETRICS} -o ${EXEC}

compiledebug: ; \
    ${CC} ${CCARGS} -g -DNDEBUG ${SILENCEDWARNINGS} ${INCLUDES} ${LIBRARIES} ${CFILES} ${SRCMETRICS} -o ${EXEC}

release: clean bin compile documentation

releasedebug: clean bin compiledebug documentation

documentation: ; @\
    doxygen

coverage: clean bin; @\
    ${COVERAGE} ${SRCMETRICS} -o ${EXEC}

debug: clean bin; \
    ${DEBUG} ${SRCMETRICS} -o ${EXEC}

bin: ; @\
    mkdir bin

tests: test230619 test230718

test230619: clean bin; @\
    ${COVERAGE} tests/test230619.c -o bin/test230619.out

test230718: clean bin; @\
    ${COVERAGE} src/util/chunk.c src/util/reallocate.c tests/test230718.c -o bin/test230718.out

test230807: clean bin; @\
    ${COVERAGE} src/util/chunk.c src/util/chunkset.c src/util/hash.c src/util/prime.c src/util/reallocate.c src/util/streq.c src/util/chunktable.c tests/test230807.c -o bin/test230807.out

clean: ; @\
    rm -rf *.gcno *.gcda *.gcov bin/* html latex
