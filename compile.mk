#CC=gcc
CC=clang

#OS=Darwin
#OS=Linux
OS=$(shell uname)

#MODE=release
MODE=debug

STD=gnu23

PADKIT_VERSION=1.1beta

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
