- Home: [Table of Contents](../..)

# A2. Why a Standard?

Programming language standardization is one of the earliest activities of information technology [^1].

> [!IMPORTANT]
> The main benefit of programming language standardization is **portability**; whether the program under development switches developers or operating systems, the code remains unambiguous to the most minute detail.

On the other hand, **over-standardization** can harm the utility of a programming language; taking away the developer's ability to implement a program by drowning the developer. ISO/IEC 9899:TC3 [^2], or C99 in short, is the standard I developed PADKIT on. However, C99 is not the final standard for a command-line program developer. The POSIX.1-XXXX family of standards build on top of C standards. If standardization is so beneficial, why not adopt a POSIX standard?

> [!WARNING]
> What if I want to use the latest standard, POSIX.1-2024, but keep using the C99 standard despite the fact that POSIX.1-2024 relies on the newer C17 standard?

> [!WARNING]
> What about the costs involved in keeping PADKIT updated with respect to such a big standard as POSIX?

In short, reasonable people will agree that there has to be a limit to standardization, especially considering the development of general-purpose programs. Then, the question is about where the limit should be. I decided to stick to the C99 standard only to keep the number of constraints on PADKIT concise.

[^1]: Robert H. Follett and Jean E. Sammet. 2003. Programming language standards. Encyclopedia of Computer Science. John Wiley and Sons Ltd., GBR, 1466–1470. URL: [https://dl.acm.org/doi/abs/10.5555/1074100.1074734](https://dl.acm.org/doi/abs/10.5555/1074100.1074734)
[^2]: ISO/IEC 9899:TC3, C99, [https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf)

- Prev: [Why C?](../why-c)
- Next: [Why C99?](../why-c99)
