# PADKIT: Portable Application Development KIT for C 

# Abstract

Portable Application (App.) Development (Dev.) KIT (PADKIT) is a library of C macros, structs, and functions designed to support the average command-line program developer. C is a popular language among embedded, automotive, and operating system (OS) software developers. For this reason, C has many features that accommodate the low-level needs of these developers. However, for the same reason, C has many confusing features for an average command-line programmer. An excess abundance of C standards, conventions, and principles designed for domain-specific use cases makes it almost impossible to decide on a consistent way of implementing an average command-line program. After forcing myself to implement many ambitious projects solely in C, I have developed a set of best practices, conventions, and principles to write a modern command-line program. I implemented PADKIT using these guidelines. In this documentation, I provide examples to demonstrate the usefulness of PADKIT. I also provide all the design details of PADKIT and the rationale behind them. My main aim is not to promote C as the single most dominant programming language but to propose a novel set of ideas that could change how to approach coding. I believe that if C remains widespread as it is, PADKIT will one day become an essential swiss-knife for the average coder. 

# Table of Contents

- [A. Straight to Business](#a-straight-to-business)
    - [A1. Prerequisites](#a1-prerequisites)
        - [A1i. A Terminal-Supporting Platform](#a1i-a-terminal-supporting-platform)
        - [A1ii. A Text Editor](#a1ii-a-text-editor)
        - [A1iii. A Standard-Conforming C Compilation Environment](#a1iii-a-standard-conforming-c-compilation-environment)
    - [A2. Compile PADKIT](#a2-compile-padkit)
    - [A3. Examples](#a3-examples)
- [B. Introduction](#b-introduction)
- [Acknowledgment](#acknowledgment) 
- [References](#references)

# A. Straight to Business

This chapter comprises three sections. First, the prerequisites necessary to build and use PADKIT. Then, the steps to build the PADKIT C99 and C23 branches in MacOS, Linux, and Windows platforms. Finally, some examples to demonstrate how to practically use PADKIT.

## A1. Prerequisites

To use PADKIT, you only need three things:

1. A terminal-supporting platform (MacOS, Linux, or Windows),
2. A text editor, and
3. A standard-conforming C compilation environment.

> [!TIP]
> If you have all these three things, you can skip to Section **[A2. Compile PADKIT](#a2-compile-padkit)**.

### A1i. A Terminal-Supporting Platform

A terminal environment is a command-line interface (CLI) with which a user interacts. A terminal environment comprises a shell and a window. A terminal window is about aesthetics. So, choosing a terminal window is purely a matter of taste. On the other hand, shell selection is about functionality and has real consequences for the user. A shell is a computer program that exposes OS services to the user or other[^7]. Having a standard shell allows the average coder to use almost the same features across different OS platforms.

> [!IMPORTANT]
> For the average coder, the best shell is the most universal shell.

The reasoning behind the above tip is simple. An average coder is neither interested in small differences between different shell implementations (e.g. between `bash`[^4] and `zsh`[^5]) nor bound to shell features that target a specific OS (e.g. `powershell`[^6]). The average coder's shell should be as much cross-platform as possible. Ideally, the shell should be available in MacOS, Linux, and Windows. Therefore, I deduce that the average coder should prefer `bash`[^4], especially the most commonly available versions of it. Now, I will describe how to use `bash`[^4] in MacOS, Linux, and Windows. I use Ubuntu 22.04.4 LTS for Linux examples but feel free to adapt the examples to your preferred Linux distribution.

> [!TIP]
> If you have `bash`, and familiar with it, you may skip to Section **[A1ii. A Text Editor](#a1ii-a-text-editor)**.

#### MacOS

1. Open the `Terminal.app`. You can use *Spotlight* to locate your application as below.

![figures/sections/a1i/macos/spotlight.png](figures/sections/a1i/macos/spotlight.png)

2. Now, you need to see a terminal window as below. Notice that the title gives away the fact that the shell is `zsh`[^5].

![figures/sections/a1i/macos/terminalwindow.png](figures/sections/a1i/macos/terminalwindow.png)

3. Type `bash` and press Enter to start a bash session. The string `bash-3.2` indicates the shell version.

![figures/sections/a1i/macos/bash.png](figures/sections/a1i/macos/bash.png)

#### Linux

1. Open the `Terminal`. On Ubuntu 22.04.4 LTS, it is possible to locate it using the *Show Applications* menu.

![figures/sections/a1i/linux/showapps.png](figures/sections/a1i/linux/showapps.png)

2. The default shell in Linux is `bash`[^4]. You can check the bash version by typing `bash --version` and pressing Enter.

![figures/sections/a1i/linux/bash.png](figures/sections/a1i/linux/bash.png)

#### Windows

1. Install `MSYS2`[^8].

2. Open `MSYS2`.

3. You can check the bash version by typing `bash --version` and pressing Enter.

![figures/sections/a1i/windows/bash.png](figures/sections/a1i/windows/bash.png)

### A1ii. A Text Editor

A text editor is necessary to write code. Text editors, like terminals, comprise a text window and text features. The average coder must carefully select the text editor, according to the text features.

> [!IMPORTANT]
> A good text editor must NOT do the coding for the average coder.

Many powerful integrated development environments (IDEs) supposedly facilitate "coding" by automatically generating code snippets and performing automatic code completion. At first glance, you might think that these text features are designed to help the average coder. In fact, they are more useful for the advanced coder and potentially harmful for the average coder. The average coder may not know many features of a programming language, especially in the case of a low-level language, like C. The automatic coding experience produces working code at the expense of the learning experience, i.e., the average coder learns to rely on the IDE too much instead of learning the fine details of the programming language. Then, the best practice is to start by avoiding IDEs, using a simple text editor. When the coder feels that he/she comprehends every line of his/her code, i.e., can describe what that line does with its every caveat, then he/she may consider upgrading to an IDE.

#### Avoid These Text Features

1. Automatic code generation
2. Automatic code completion
3. Automatic code repair

> [!IMPORTANT]
> A good text editor must facilitate code reviewing and refactoring.

The average coder must accept the fact that the first version of a code block is almost never going to be the final version. Most code blocks change many times as the software under implementation evolves. Identifying and modyfing lines of code may become a routine and cumbersome task for the coder. Hence, the coder must seek a text editor that facilitates these operations.

#### Seek These Text Features

1. Syntax highlighting
2. Easily cut and paste multiple words and lines
3. Search and replace features, preferably with regular expression support
4. A right margin or a guide line that indicate a code line consists more than, e.g. 120 characters.
5. Automatic indentation
6. Line numbering
7. Bracket matching and highlighting

#### Example Text Editors

GUI-based text editors are intuitive and easy-to-learn. GEdit[^1] could be a good place to start as it is available for all OSs (MacOS, Linux, and Windows).

> [!TIP]
> Did you know that you could also use a terminal-based text editor? Nano[^9], Vim[^10], and Emacs[^11] are good examples. They are harder to learn but provide much better code reviewing/refactoring features. I personally use Nano but also envy Vim and Emacs users.

## A2. Compile PADKIT

The next step is to compile PADKIT. You already have a terminal with a `bash`[^4] shell but three more tools are essentials:

1. `git`[^12] distributed version control system,
2. `make`[^13] , and
3. `gcc`[^2] or `clang`[^3] C compiler.

### A2i. Debug Build for PADKIT-C23

### A2ii. Build Parameters

# Acknowledgment

I wish to start by stating that not one word of this documentation would have been written, if not for my wife, Dilara, and her unwavering support.

I used UTM to try PADKIT on both Linux and Windows. It would have been very hard to test all OSs without UTM.

# References

[^1]: The GNOME Project, "gedit", https://gedit-technology.github.io/apps/gedit/ -- last accessed @ `[2024-08-24 09:08:21]`
[^2]: Free Software Foundation Inc., "GCC, the GNU compiler collection", https://gcc.gnu.org -- last accessed @ `[2024-08-23 09:24:15]`
[^3]: LLVM Foundation, "Clang: a C language family frontend for LLVM", https://clang.llvm.org -- last accessed @ `[2024-08-23 01:17:09]`
[^4]: Free Software Foundation Inc., "GNU bourne again shell", https://www.gnu.org/software/bash/ -- last accessed @ `[2024-08-23 20:34:13]`
[^5]: P. Falstad, "Z shell", https://zsh.sourceforge.io/ -- last accessed @ `[2024-08-23 20:38:44]`
[^6]: Microsoft, "PowerShell", https://learn.microsoft.com/en-us/powershell/ -- last accessed @ `[2024-08-23 20:38:44]`
[^7]: "Shell (computing)", https://en.wikipedia.org/wiki/Shell_(computing) -- last accessed @ `[2024-08-23 21:41:54]`
[^8]: "MSYS2 software distribution and building platform for windows", https://www.msys2.org -- last accessed @ `[2024-08-23 23:25:48]`
[^9]: Free Software Foundation Inc., "The GNU nano", https://nano-editor.org/ -- last accessed @ `[2024-08-24 09:13:27]`
[^10]: "Vim - the ubiquitous text editor", https://www.vim.org -- last accessed @ `[2024-08-24 09:16:12]`
[^11]: Free Software Foundation Inc., "GNU Emacs - an extensible, customizable, free/libre text editor -- and more", https://www.gnu.org/software/emacs/ -- last accessed @ `[2024-08-24 09:17:50]`
[^12]: https://git-scm.com -- last accessed @ `[2024-08-24 19:22:09]`
[^13]: Free Software Foundation Inc., "GNU Make", https://www.gnu.org/software/make/#documentation -- last accessed @ `[2024-08-24 19:24:36]`
