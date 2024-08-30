# PADKIT: Portable App. Dev. KIT for C23

## How to Build

1. `git clone -b C23 https://github.com/yavuzkoroglu/padkit.git padkit-C23`
2. `cd padkit`
3. `make`

## Tested Environments (v1.2)

| Date (ISO 8601) |                  OS |                   `uname -sm` |     Compiler |
|----------------:|--------------------:|------------------------------:|-------------:|
|      2024-08-22 | macOS Sonoma 14.6.1 |                  Darwin arm64 | clang 18.1.8 |
|      2024-08-22 | macOS Sonoma 14.6.1 |                  Darwin arm64 |   gcc 14.2.0 |
|      2024-08-22 |  Ubuntu 22.04.4 LTS |                 Linux aarch64 | clang 18.1.8 |
|      2024-08-22 |  Ubuntu 22.04.4 LTS |                 Linux aarch64 |   gcc 14.2.0 |

## Compiler Confusion

It turns out that the compiler option `-std=c23` conforms to [ISO/IEC 9899:202x (C2x), N2310, November 2018](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2310.pdf) rather than [ISO/IEC 9899:2023 (C23), Working Draft, N3096, April 2024](https://www.open-std.org/JTC1/SC22/WG14/www/docs/n3096.pdf). So, keywords such as `constexpr` are still not available in both `gcc-14.2.0` and `clang-18.1.8`.

## Features

From PADKIT's perspective, all the standard C features fall into four categories:

1. Adopted,
2. Rejected,
3. Promised, and
4. Usable.

### A. Adopted Features

#### A1. Binary Literals

PADKIT uses binary literals, e.g. `0b11111111'11111111'11111111'11110110`, which is equivalent to `UINT32_C(-10)`.

PADKIT's binary literals conform to the [ISO/IEC 9899:2023 (C23), Working Draft, April 2024](https://www.open-std.org/JTC1/SC22/WG14/www/docs/n3096.pdf), Section 6.4.4.1, p. 57-59.

PADKIT-C99 uses its own `include/padkit/bliterals.h`, which defines every binary literal from `B_00000000` to `B_11111111` as macros.

#### A2. `bool` Keyword

According to [ISO/IEC 9899:TC3 (C99), Committee Draft, September 2007](https://www.open-std.org/JTC1/SC22/WG14/www/docs/n1256.pdf), 

#### A3. `[[maybe_unsued]]` Keyword

#### A4. `restrict` Keyword

According to [ISO/IEC 9899:TC3 (C99), Committee Draft, September 2007](https://www.open-std.org/JTC1/SC22/WG14/www/docs/n1256.pdf)

#### A5. `static` Keyword in Array Parameters of Function Declarators

According to [ISO/IEC 9899:TC3 (C99), Committee Draft, September 2007](https://www.open-std.org/JTC1/SC22/WG14/www/docs/n1256.pdf), Section 6.7.5.3, p. 119, item 7, the `static` keyword ensures that a function parameter is a non-null pointer to at least `n` elements, e.g.:

```
void setPassword(char const password[static const 9]);
```

The above function declaration signals that the parameter `password` is a constant non-null pointer to at least nine constant characters. The old-style declaration, e.g.:

```
void setPassword(char const* const password);
```

could require the code to explicitly check if `password` is a null pointer. Also, `password + 7` could be an invalid pointer.

**WARNING**: It is still possible to call such a function with a null pointer. It is the job of the *caller* to check if the given parameter conforms to the function declaration.

### B. Rejected Features

#### B1. `auto` Keyword (Type Inference)

#### B2. `false` and `true` Keywords

#### B3. Checked Integer Arithmetic

#### B3. Flexible Array Members

#### B4. Generic-Type Macros

#### B5. Inline Functions

#### B6. Trigraphs

#### B7. Variable-Length Arrays (VLAs)

### C. Promised Features

#### C1. `constexpr` Keyword

### D. Usable Features

The C standard employs many more features that PADKIT simply does NOT use, yet. More details:

 - [ISO/IEC 9899:1990 (C90), published by ANSI, August 1992](https://web.archive.org/web/20200909074736if_/https://www.pdf-archive.com/2014/10/02/ansi-iso-9899-1990-1/ansi-iso-9899-1990-1.pdf)
 - [ISO/IEC 9899:TC3 (C99), Committee Draft, N1256, September 2007](https://www.open-std.org/JTC1/SC22/WG14/www/docs/n1256.pdf)
 - [ISO/IEC 9899:2011 (C1x), Committee Draft, N1570, April 2011](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)
 - [ISO/IEC 9899:202x (C2x), N2310, November 2018](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2310.pdf) 
 - [ISO/IEC 9899:2023 (C23), Working Draft, N3096, April 2024](https://www.open-std.org/JTC1/SC22/WG14/www/docs/n3096.pdf)
 - [ISO/IEC 9899:202y (C2y), Working Draft, N3301](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3301.pdf)
 
## Version History
