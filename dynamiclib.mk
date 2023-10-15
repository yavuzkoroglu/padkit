include os.mk

ifeq (${OS},Darwin)
include version.mk
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
