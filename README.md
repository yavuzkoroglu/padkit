# PADKIT: Portable App. Dev. KIT for C99

## How to Build

1. `git clone -b C99 https://github.com/yavuzkoroglu/padkit.git padkit-C99`
2. `cd padkit-C99`
3. `make`

The above steps should produce

1. The libraries in `lib/` and
2. The automatically generated headers in `include/`.

## Tested Environments (v2.0)

| Date (ISO 8601) |                  OS |                   `uname -sm` |     Compiler |
|----------------:|--------------------:|------------------------------:|-------------:|
|      2024-08-22 | macOS Sonoma 14.6.1 |                  Darwin arm64 | clang 18.1.8 |
|      2024-08-22 | macOS Sonoma 14.6.1 |                  Darwin arm64 |   gcc 14.2.0 |
|      2024-08-22 |  Ubuntu 22.04.4 LTS |                 Linux aarch64 | clang 18.1.8 |
|      2024-08-22 |  Ubuntu 22.04.4 LTS |                 Linux aarch64 |   gcc 14.2.0 |

## Changes 

### Changes v1.1 -> v2.0

* Most of the codebase is completely rewritten.
* Splitted into two branches, **C99** and **C23**.

<!--
* Added `include/padkit/linkedlist.h` and `src/padkit/linkedlist.c`,
* Added `include/padkit/size.h` for extra size limit macros.
* Added `include/padkit/invalid.h` for invalid integer macros.
* Removed `include/padkit/reallocate.h`. Transfered the functionality to `include/padkit/memalloc.h`
* Added `include/padkit/arraylist.h` and `src/padkit/arraylist.c`,
* Added overlapping pointer checks to `Chunk`, `CircularBuffer`, and `Stack` in debug mode.
* Resolved several bugs in `JSONParser`.
* Added `include/padkit/overlap.h` and `src/padkit/overlap.c`, to debug restricted pointer overlapping issues.
* Added `include/padkit/memalloc.h` and `src/padkit/memalloc.c`, along with corresponding tests.
* Major overhaul. Replaced `#ifndef NDEBUG` clauses with `include/padkit/debug.h` routines.
* Replaced all macros in `include/padkit/circbuff.h` with struct and functions.
* Replaced all macros in `include/padkit/stack.h` with struct and functions.
* `REALLOC_IF_NECESSARY` ceased to take an `err` parameter.
* `include/padkit/reallocate.h` does NOT include `include/padkit/debug.h`
* Added `include/padkit/circbuff.h` and a `test_circbuff()` function to `src/tests.c`.
* Added `include/padkit/stack.h` and a `test_stack()` function to `src/tests.c`.
* Added `include/padkit/preprocessor.h` that implements preprocessor tricks.

### Changes v1.0 -> v1.1

* Silenced some warning messages for `clang` and `gcc` in `compile.mk`.
* `GraphMatrix` objects now allocate bits in 64-bit blocks instead of 8-bit blocks.
* Updated `include/padkit/reallocate.h`.
* Corrected `NOT_A_JSON_PARSER` in `include/padkit/jsonparser.h`.
* Encapsulated debug messages within extra code blocks in `include/padkit/debug.h`.
* Added `CTblConstIterator` and related functions.
* Added `include/padkit/jsonparser.h` and `src/padkit/jsonparser.c`.
* External scripts now can import the `${COMPILE}` command in the `Makefile`.
* In `src/padkit/timestamp.c`, timestamps now conform to ISO 8601.
* Removed `extern Chunk strings[1];` and `void free_strings(void)` from `Chunk`.
* Solved a bug in `src/padkit/streq.c::str_eq_n()`.
* Slight code corrections in `src/padkit/hash.c`.
-->
