#CC=gcc
CC=clang

#OS=Darwin
#OS=Linux
OS=$(shell uname)

#MODE=release
MODE=debug

PADKIT_VERSION=2.0
PADKIT_TARGET=C99

STD=c99

ifeq (${OS},Darwin)
DYNAMIC_LIB_FLAGS=-dynamiclib -fvisibility="default"
ARCH=$(shell uname -m)
ARCH_ARGS=-arch ${ARCH}
else
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

CCNAME=$(findstring clang,${CC})

ifeq (${CCNAME},clang)
ifeq (${OS},Darwin)
ARGS=${ARCH_ARGS} ${FLAGS} -Weverything -Werror -Wno-unsafe-buffer-usage
else
ARGS=${FLAGS} -Weverything -Werror -Wno-unsafe-buffer-usage
endif
else
ifeq (${OS},Darwin)
ARGS=${ARCH_ARGS} ${FLAGS} -Wall -Wextra -Werror
else
ARGS=${FLAGS} -Wall -Wextra -Werror
endif
endif

COMPILE=${CC} ${ARGS}
