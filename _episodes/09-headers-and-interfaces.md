---
title: "Headers and Interfaces"
teaching: 10
exercises: 0
questions:
- "What is an interface?"
- "Why separate some of the code into header files?"
objectives:
- "Understand the difference between header and implementation files"
- "Comprehend code using preprocessor directives"
keypoints:
- "Preprocessor directives are useful for making compile-time decisions"
- "By separating header files and implementation files we can program to interfaces, not implementations."
---

## Headers and Interfaces

An *interface* describes functionality without providing any implementation.  An *interface* is defined in a *header file*, which has a different extension (usually `.hpp` or just `.h`) than the implementation file (which will usually be `.cpp` or `.cc`).

In a header file `hello.hpp`, you may see a function declaration *with no implementation* such as:
~~~
void printHello();
~~~
{: .language-cpp}

And then used in another file `myfile.cpp`:
~~~
#include "hello.hpp"
int main() {
    printHello();
}
~~~
{: .language-cpp}

But how does the computer know what to execute when it gets to the `printHello()` statement?  When we compile, we must include an implementation file (or link against a library) that implements the function.

But why do we do this?  Why not just keep all the code in one file?  There are several answers to this question, but here are a few of them:
* Yes, for this example with one line of code a header does seem contrived.  Header files become an absolute necessity when you introduce multiple functions or classes.
* When recompiling a large project, if the interface is kept the same but the implementation changes, the compilation process can be sped up significantly.
* One of the mantras of object-oriented programming is **program to interfaces, not implementations**.  This is a deep concept we are only touching on at a surface level for now, so don't worry if it seems a little confusing at the moment.  The idea is that as you continue to add functionality to a large code project, it is easier to work with the abstraction of the function or class and not depend on the nuts and bolts of its implementation.

## Preprocessor Directives

Preprocessor directives use the `#` character.  These lines are not statements, and thus do not need a semicolon to terminate the line.  Rather, they are terminated by a newline character, similar to single line comments `// like this`.

~~~
// file inclusion
#include "hello.cpp"

// macro defines a constant
#define MY_GOLDEN_NUMBER 1746

// compile time decision
#ifdef USE64BITS
typedef uint64_t myint;
#else
typedef uint32_t myint;
#endif
~~~
{: .language-cpp}

The `#define` directive will effectively replace all instances of the token `MY_GOLDEN_NUMBER` with `1746` before compiling.  The `#ifdef`, `#else` and `#endif` allow the compiler to check whether the identifier `USE64BITS` is defined and conditionally declare a typedef depending on the desired size of an integer in this architecture.

Preprocessor directives are used in only restricted cases, namely
* Including header files
* Hardcoding constants
* Portability to 32 or 64 bit architectures

You might also see preprocessor directives in header files to prevent the compiler from reading a header file twice and compilaing that the function `printHello` is declared twice, as in this example:

~~~
#ifndef PRINT_HELLO_HPP
#define PRINT_HELLO_HPP

void printHello();

#endif
~~~
{: .language-cpp}

This uses directives to define the `PRINT_HELLO_HPP` identifier only once and prevent passing the header file to the compiler twice if it is included by many files in a large code project.