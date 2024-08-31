- Home: [Table of Contents](..)

# A. Introduction

Formally, PADKIT is a collection of the following three components.

1. A detailed C setup guide for MacOS, Linux, and Windows.
2. A set of C conventions that adopt or reject C language features w.r.t. established C standards.
3. A C library that builds on top of only the standard C library.

I designed PADKIT to accommodate the needs of a general-purpose C program, in contrast to C code for specific domains like embedded systems, automotive software, operating system implementations, and more. PADKIT's main objective is the following.

> [!IMPORTANT]
> **PADKIT's objective:** To provide the general-purpose program coder with a platform-independent method to implement and share a small project with a long maintenance-free lifespan.

A platform-independent implementation method guarantees the software behavior to be the same across different operating systems and execution environments. A small project comprises as few dependencies as possible except the programming language's core libraries. A typical software project, if left unattended, often becomes unusable in time due to upgraded dependencies and changes in the execution environments. PADKIT aims to achieve the case that once the programmer ensures the correct behavior and finalizes the project, it has a long lifespan without any maintenance and changes.

[^1]: P. J. Landin, 1966. "The next 700 programming languages", Association for Computing Machinery (ACM), vol. 9, no. 3, p. 157-166, https://doi.org/10.1145/365230.365257 -- last accessed @ `[2024-08-31 21:15:43]`
[^2]: R. Chatley, A. Donaldson, and A. Mycroft, 2019. "The next 7000 programming languages", Computing and software science: State of the art and perspectives, p. 250-282, https://doi.org/10.1007/978-3-319-91908-9_15 -- last accessed @ `[2024-08-31 21:45:31]`

- Prev: [Abstract](../abstract)
- Next: [Using PADKIT](../using-padkit)

