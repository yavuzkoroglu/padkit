# PADKIT: Portable Application Development KIT for C 

# Abstract

Portable Application (App.) Development (Dev.) KIT (PADKIT) is a library of C macros, structs, and functions designed to support the average command-line program developer. C is a popular language among embedded, automotive, and operating system (OS) software developers. For this reason, C has many features that accommodate the low-level needs of these developers. However, for the same reason, C has many confusing features for an average command-line programmer. An excess abundance of C standards, conventions, and principles designed for domain-specific use cases makes it almost impossible to decide on a consistent way of implementing an average command-line program. After forcing myself to implement many ambitious projects solely in C, I have developed a set of best practices, conventions, and principles to write a modern command-line program. I implemented PADKIT using these guidelines. In this documentation, I provide examples to demonstrate the usefulness of PADKIT. I also provide all the design details of PADKIT and the rationale behind them. My main aim is not to promote C as the single most dominant programming language but to propose a novel set of ideas that could change how to approach coding. I believe that if C remains widespread as it is, PADKIT will one day become an essential swiss-knife for the average coder. 

# Table of Contents

- [A. Straight to Business](#a-straight-to-business)
	- [A1. Prerequisites](#a1-prerequisites)
		- [A1i. A Terminal-Supporting Platform](#a1i-a-terminal-supporting-platform)
		- [A1ii. A Text Editor](#a1ii-a-text-editor)
		- [A1iii. A Standard-Conforming C Compilation Environment](#a1iii-a-standard-conforming-c-compilation-environment)
	- [A2. How to Build](#a2-how-to-build)
 		- [A2i. Debug Build for PADKIT-C23](#a2i-debug-build-for-padkit-c23)
        - [A2ii. Build Parameters](#a2ii-build-parameters)
	- [A3. Examples](#a3-examples)
- [B. Introduction](#b-introduction)
- C. 
- [References](#references)

# A. Straight to Business

This chapter comprises three sections. First, the prerequisites necessary to build and use PADKIT. Then, the steps to build the PADKIT C99 and C23 branches in MacOS, Linux, and Windows platforms. Finally, some examples to demonstrate how to practically use PADKIT.

## A1. Prerequisites

To use PADKIT, you only need three things:

1. A Terminal-Supporting Platform (MacOS, Linux, or Windows)
2. Text Editor (e.g. nano, or Notepad++[^1] )
3. Standard-Conforming C Compilation Environment (`gcc`[^2], `llvm-clang`[^3], etc.)

> [!NOTE]
> If you have all these three things, you can skip to Section **[A2. How to Build](#a2-how-to-build)**.

### A1i. A Terminal-Supporting Platform

A terminal environment is a command-line interface (CLI) with which a user interacts. A terminal environment comprises a shell and a window. A terminal window is about aesthetics. So, choosing a terminal window is purely a matter of taste. On the other hand, shell selection is about functionality and has real consequences for the user.

> [!TIP]
> The best shell is the most universal shell.

> [!NOTE]
> If you have a terminal, and know how to use it, you can skip to Section **[A1ii. A Text Editor](#a1ii-a-text-editor)**.

## A2. How to Build 

### A2i. Debug Build for PADKIT-C23

```
git clone -b C23 https://github.com/yavuzkoroglu/padkit.git 
cd padkit
make -e MODE=debug
```

### A2ii. Build Parameters

### References

[^1]: D. Ho, "Nodepad++", https://notepad-plus-plus.org/downloads/ -- last accessed @ `[2024-08-23 01:17:09]`
[^2]: Free Software Foundation Inc., "GCC, the GNU Compiler Collection" https://gcc.gnu.org -- last accessed @ `[2024-08-23 09:24:15]`
[^3]: LLVM Foundation, "Clang: a C language family frontend for LLVM", https://clang.llvm.org -- last accessed @ `[2024-08-23 01:17:09]`
