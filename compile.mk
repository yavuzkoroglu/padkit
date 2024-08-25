#CC=gcc
CC=clang

#OS=Darwin
#OS=Linux
OS=$(shell uname)

#MODE=release
MODE=debug

PADKIT_VERSION=1.2
PADKIT_TARGET=c99

STD=${PADKIT_TARGET}

ifeq (${OS},Darwin)
DYNAMIC_LIB_FLAGS=-dynamiclib -fvisibility="default"
ARCH=$(shell uname -m)
ARCH_ARGS=-arch ${ARCH}
STDLIBS=
else
ARCH_ARGS=
STDLIBS=
ifeq (${OS},Linux)
DYNAMIC_LIB_FLAGS=-shared -fPIC
else
DYNAMIC_LIB_FLAGS=-shared
endif
endif

ifeq (${MODE},debug)
FLAGS=-std=${STD} -g
else
FLAGS=-std=${STD} -Ofast -DNDEBUG
endif

ifeq (${CC},clang)
SILENCED=-Wno-unsafe-buffer-usage -Wno-unused-parameter
ARGS=${ARCH_ARGS} ${FLAGS} -Weverything ${SILENCED} -Iinclude ${STDLIBS}
else
SILENCED=-Wno-unused-parameter
ARGS=${ARCH_ARGS} ${FLAGS} -Wall -Wextra ${SILENCED} -Iinclude ${STDLIBS}
endif

COMPILE=${CC} ${ARGS}
