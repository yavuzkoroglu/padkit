- Home: [Table of Contents](..)

# A. Introduction

PADKIT comprises the following components.

1. A detailed and up-to-date C setup guide for MacOS, Linux, and Windows.
2. A set of C concepts; i.e., conventions, utilities, macros, functions, and structures for general-purpose C programs.
3. A C library that builds on top of only the standard C library.

I designed PADKIT to accommodate the needs of a general-purpose C program, in contrast to C code for specific domains, such as embedded systems, automotive software, operating system implementations, and more. PADKIT's primary objective is as follows.

> [!IMPORTANT]
> **PADKIT's objective:** To provide the general-purpose program coder with a platform-independent method to implement and share a small project with a long maintenance-free lifespan.

A platform-independent implementation method ensures behavioral consistency across platforms (operating systems, execution environments, etc.). A small project comprises as few dependencies as possible except the programming language's core libraries. A typical software project, if left unattended, often becomes unusable in time due to upgraded dependencies and changes in the execution environments. Once the programmer ensures correct behavior and finalizes the project using PADKIT, the program should ideally require only minimal maintenance for an extended period.

The number of programming languages steadily grow. Researchers even predict the direction of the growth of programming languages in the near future [^1][^2].

[^1]: P. J. Landin, 1966. "The next 700 programming languages", Association for Computing Machinery (ACM), vol. 9, no. 3, p. 157-166, https://doi.org/10.1145/365230.365257 -- last accessed @ `[2024-08-31 21:15:43]`
[^2]: R. Chatley, A. Donaldson, and A. Mycroft, 2019. "The next 7000 programming languages", Computing and software science: State of the art and perspectives, p. 250-282, https://doi.org/10.1007/978-3-319-91908-9_15 -- last accessed @ `[2024-08-31 21:45:31]`

- Prev: [Abstract](../abstract)
- Next: [Why C?](why-c)

