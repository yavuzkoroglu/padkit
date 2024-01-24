# PADKIT: Portable App. Dev. KIT for C 

## How to Build

1. `git clone https://github.com/yavuzkoroglu/padkit.git`
2. `cd padkit`
3. `make`

The above steps should produce

1. The libraries in `lib/` and
2. The automatically generated headers in `include/`.

## Tested Environments (v1.1beta)

| Date (ISO 8601) |                  OS |                   `uname -sm` |     Compiler |
|----------------:|--------------------:|------------------------------:|-------------:|
|      2024-01-24 |   macOS Sonoma 14.3 |                  Darwin arm64 | clang 17.0.6 |
|      2024-01-24 |   macOS Sonoma 14.3 |                  Darwin arm64 |   gcc 13.2.0 |
|      2023-12-11 | macOS Sonoma 14.2.1 |                  Darwin arm64 | clang 17.0.6 |
|      2023-12-11 |   macOS Sonoma 14.2 |                  Darwin arm64 | clang 17.0.6 |
|      2023-12-11 | macOS Sonoma 14.1.2 |                  Darwin arm64 | clang 17.0.6 |
|      2023-11-30 | macOS Sonoma 14.1.1 |                  Darwin arm64 | clang 17.0.6 |
|      2023-11-05 |   macOS Sonoma 14.0 |                  Darwin arm64 | clang 17.0.4 |
|      2023-10-18 |   macOS Sonoma 14.0 |                  Darwin arm64 | clang 17.0.3 |
|      2023-10-14 |   macOS Sonoma 14.0 |                  Darwin arm64 | clang 17.0.2 |
|      2023-10-14 |   macOS Sonoma 14.0 |                  Darwin arm64 |   gcc 13.2.0 |
|      2023-10-14 |   macOS Sonoma 14.0 |                 Darwin x86_64 | clang 17.0.2 |
|      2023-10-14 |   macOS Sonoma 14.0 |                 Darwin x86_64 |   gcc 13.2.0 |
|      2023-10-14 |  Ubuntu 22.04.3 LTS |                 Linux aarch64 | clang 14.0.0 |
|      2023-10-14 |  Ubuntu 22.04.3 LTS |                 Linux aarch64 |   gcc 11.4.0 |
|      2023-10-14 |  Ubuntu 22.04.3 LTS |                  Linux x86_64 | clang 14.0.0 |
|      2023-10-14 |  Ubuntu 22.04.3 LTS |                  Linux x86_64 |   gcc 11.4.0 |
|      2023-10-14 | Windows 10 Pro 22H2 | MINGW64\_NT-10.0-19045 x86_64 | clang 11.0.0 |
|      2023-10-14 | Windows 10 Pro 22H2 | MINGW64\_NT-10.0-19045 x86_64 |   gcc 13.1.0 |

## Changes v1.0 -> v1.1beta

* Added `include/padkit/jsonparser.h` and `src/padkit/jsonparser.c`.
* External scripts now can import the `${COMPILE}` command in the `Makefile`.
* In `src/padkit/timestamp.c`, timestamps now conform to ISO 8601.
* Removed `extern Chunk strings[1];` and `void free_strings(void)` from `Chunk`.
* Solved a bug in `src/padkit/streq.c::str_eq_n()`.
* Slight code corrections in `src/padkit/hash.c`.
