# PADKIT: Portable App. Dev. KIT for C 

## How to Use

You may download a suitable prebuilt release or build the source code from scratch.

## How to Build

1. `git clone https://github.com/yavuzkoroglu/padkit.git`
2. `cd padkit`
3. `make`

The above steps should produce

1. The libraries in `lib/` and
2. The automatically generated headers in `include/`.

## Tested Environments

|  # |                  OS |                   `uname -sm` |     Compiler |
|---:|--------------------:|------------------------------:|-------------:|
|  1 |   macOS Sonoma 14.0 |                  Darwin arm64 | clang 17.0.2 |
|  2 |   macOS Sonoma 14.0 |                  Darwin arm64 |   gcc 13.2.0 |
|  3 |   macOS Sonoma 14.0 |                 Darwin x86_64 | clang 17.0.2 |
|  4 |   macOS Sonoma 14.0 |                 Darwin x86_64 |   gcc 13.2.0 |
|  5 |  Ubuntu 22.04.3 LTS |                 Linux aarch64 | clang 14.0.0 |
|  6 |  Ubuntu 22.04.3 LTS |                 Linux aarch64 |   gcc 11.4.0 |
|  7 |  Ubuntu 22.04.3 LTS |                  Linux x86_64 | clang 14.0.0 |
|  8 |  Ubuntu 22.04.3 LTS |                  Linux x86_64 |   gcc 11.4.0 |
|  9 | Windows 10 Pro 22H2 | MINGW64\_NT-10.0-19045 x86_64 | clang 11.0.0 |
| 10 | Windows 10 Pro 22H2 | MINGW64\_NT-10.0-19045 x86_64 |   gcc 13.1.0 |