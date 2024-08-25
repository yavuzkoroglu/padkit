#CC=gcc
CC=clang

#OS=Darwin
#OS=Linux
OS=$(shell uname)

#MODE=release
MODE=debug

PADKIT_VERSION=1.2
PADKIT_TARGET=c23

# -std=c23 adopts the older c2x standard. Only -std=gnu23 allows some of the c23 features.
STD=gnu23

ifeq (${OS},Darwin)
DYNAMIC_LIB_FLAGS=-dynamiclib -fvisibility="default"
ARCH=$(shell uname -m)
ARCH_ARGS=-arch ${ARCH}
else
ARCH_ARGS=
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
SILENCED=-Wno-unsafe-buffer-usage -Wno-pre-c23-compat -Wno-gnu-binary-literal
ARGS=${ARCH_ARGS} ${FLAGS} -Iinclude -Weverything ${SILENCED}
else
SILENCED=
ARGS=${ARCH_ARGS} ${FLAGS} -Iinclude -Wall -Wextra ${SILENCED}
endif

COMPILE=${CC} ${ARGS}
