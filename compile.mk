include cc.mk
include os.mk
include mode.mk
include std.mk

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
