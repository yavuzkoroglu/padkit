#CC=gcc
CC=clang

#OS=Darwin
#OS=Linux
OS=$(shell uname)

#MODE=release
MODE=debug

PADKIT_VERSION=1.1beta

STD=c99

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
SILENCED=                               \
    -Wno-poison-system-directories      \
    -Wno-declaration-after-statement    \
    -Wno-padded -Wno-unused-parameter   \
    -Wno-unknown-warning-option         \
    -Wno-missing-noreturn               \
    -Wno-implicit-fallthrough           \
    -Wno-unsafe-buffer-usage            \
    -Wno-disabled-macro-expansion       \
    -Wno-switch-default
ARGS=${ARCH_ARGS} ${FLAGS} -Weverything ${SILENCED} -Iinclude ${STDLIBS}
else
SILENCED=                               \
    -Wno-unused-parameter               \
    -Wno-old-style-declaration          \
    -Wno-unknown-warning-option         \
    -Wno-missing-noreturn               \
    -Wno-implicit-fallthrough           \
    -Wno-nullability-completeness       \
    -Wno-disabled-macro-expansion       \
    -Wno-switch-default
ARGS=${ARCH_ARGS} ${FLAGS} -Wall -Wextra ${SILENCED} -Iinclude ${STDLIBS}
endif

COMPILE=${CC} ${ARGS}
