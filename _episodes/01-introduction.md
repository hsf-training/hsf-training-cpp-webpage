---
title: "Introduction"
teaching: 10
exercises: 0
questions:
- "What is C++?"
- "When is C++ the right language?"
- "How do I get started in C++?"
objectives:
- "Understand the problem domain where C++ is the best solution."
- "Be able to compile and run a simple C++ *hello, world* program."
keypoints:
- "C++ is a compiled language, source code is translated by the compiler to machine specific binaries."
- "Well written C++ can achieve very high performance."
- "Using the compiler on the command line I can simple and run a simple C++ program."
---
## Welcome

Welcome to the HSF training module on C++ fundamentals. This module will walk
you through the core concepts of *modern* C++ and give you a good grounding
in the key ideas and syntax that you will need to follow more advanced
modules in the overall HSF C++ course.

## Why the C++ Language

The C++ language [has been around for a long
time](https://en.wikipedia.org/wiki/C%2B%2B) (since the 1980s). Yet, despite
it's age C++ is still a very popular language. That's because it has an
excellent combination of lower-level features that help to get extremely high
performance from modern computing hardware and higher level features that help
to abstract the logical structure of the code and manage the overall design
coherently. In particular, C++ is an extremely popular language for data
intensive sciences (physics, astronomy, chemistry and engineering). C++ is also
used (with some extensions) for programming devices like GPUs and is the
language used for many of the high-performance modules in other languages like
Python.

All of this makes C++ an excellent language to learn for people who need to
of get maximum performance for their code. And that's why we wrote this
course!

> ## C++ in this course
> 
> Over it's lifetime C++ has evolved a lot from the original versions that
> provided some extensions on top of the C programming language and it has been
> though numerous revisions and extensions (you might see these referred to as
> C++98, C++11, C++14, etc.). In this course we'll consider all of these old
> revisions uninteresting for the modern student and we'll dive right in to
> teaching you modern C++ programming and best practice.
>
> However, to be precise, here we shall base the course on the C++17 standard. 
> Occasionally we may point out places where this standard differs significantly
> from earlier versions, but this is really only to help you where you might
> have to look at older code.
{: .discussion}

## Getting started with C++

### Compiler

The essential ingredient for working with C++ is a program called a *compiler*.
Written C++ *source code* describes what we want our program to do, but it isn't
yet in a form that the CPU can do anything with. The compiler makes the translation
from one form to another for us and it outputs *binary code* that our
computer can then execute.


> ## A compiler for this course
>
> We assume that you have a modern C++ compiler available on your system - either
> the GNU g++ compiler or the LLVM clang++ compilers will do the job very nicely
> as long as you have g++ version 8 or higher, or clang++ version 5 or higher.
{: .discussion}

### Editor

Our first job when writing or adapting C++ code will be to work with the source
files. That requires us to use a *text editor*. There are a bewildering array
of editors available depending on which system you are using. There's also
a strong subjective element here as well as people can have personal preferences
for their editor.

As a programmer a good editor will help hugely when it understands C++ as a
language - many helpful features and syntax checks can be performed as you
write your code and they will make you much more productive. The most advanced
editors are actually part of an IDE suite (Integrated Development Environment)
that will also include full integration with the compiler and the debugger.
However, setting up these is beyond the scope of this tutorial.

> ## An editor for this course
>
> We can recommend highly the
> [Microsoft VS Code](https://code.visualstudio.com/) editor
> for being easy to use, very functional and being available on
> most platforms (OS X, Windows, Linux).
{: .discussion}

### My first C++ program

Alright, let's get started then... using your editor let's write the
canonical starting program in C++, the venerable *hello, world*.

~~~
{% include_relative code/hello.cpp %}
~~~
{: .language-cpp}

Don't worry about the pieces of the code here that you don't understand yet - by the end of the module
you'll know them all.

Save this file as `hello.cpp`.

Now, open a terminal on your system and let's compile this program and run it:

~~~
$ g++ -std=c++17 hello.cpp -o hello
$ ./hello
hello, world
$
~~~
{: .language-bash}

If you managed to get that to work then you have successfully started your journey
as a C++ programmer. Well done!

Now let's go on to look more systematically at some of the things that make up
the C++ programing language.

## C++ Resources

Here are some useful resources for C++ programmers:

| Resource | Link | Description |
|----------|------|-------------|
| Cpp Reference | <https://en.cppreference.com/w/> | Essential reference to the C++ standard and standard library |
| C++ Standards | <https://isocpp.org/> | The C++ Standards Organisaion, but in itself a great source of resources about C++ |

{% include links.md %}
