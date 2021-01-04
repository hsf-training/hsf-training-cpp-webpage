---
title: "References"
teaching: 10
exercises: 0
questions:
  - "How do we use references in C++?"
objectives:
  - "Understand C++ references."
  - "Know about references and const references."
  - "Be aware of return value optimization and structured bindings."
keypoints:
  - "Coming up."
---

{% include links.md %}

## Introduction

When we order items from online retailers, we are required to give them our
residential address so they ship the items to us. We send them a trivially small
amount of information so they can identify our homes and then operate on them
(in this case by shipping stuff to them). In C++, we pass around information
too: between functions for example. Take the following code as an example:

~~~
int double(int i) {
    return i * 2;
};
~~~
{: .language-cpp}

When the function `double` is called, we are instructing the computer to copy
(barring compiler optimisations) an integer to a new location, operate on it,
and then copy the result back to where we came to. This data movement is faily
fundamental to the concept of function calls in C++ as well as other languages.
We usually refer to this as *pass-by-value*, as a value is passed to the
function in its entirety. Let's consider a new example:

~~~
struct Behemoth {
    int vals[1000000];
};

int double_first(Behemoth i) {
    return i.vals[0] * 2;
}
~~~
{: .language-cpp}

When we call our new `double_first` function, we are once again passing some
data by value, and the computer will copy the data to the function that needs
it. In this case, however, our data is very large! On most (but certainly not
all) modern machines, an integer is four bytes, so in our first example we only
had to copy four bytes into the `double` function and then four bytes back as
the return value. In this second example, our structure is four *million* bytes
in size! At that point, we're spending so much time and effort copying
information that the performance of our program will decrease *dramatically*. It
is the C++ equivalent of ordering something online and then moving your *entire
house* to the retailer's warehouse! It's ruthlessly inefficient. Thankfully, C++
gives us a way to refer to large objects efficiently. In this chapter, we will
learn more about so-called *references*.

## Basic references

Virtually all data we work with in C++ lives somewhere in our memory, which is a
large adressable space which we can index numerically. The obvious real-world
analogue are street adresses, where we might have a house at address 12, and
then the next house at address 13 (or 14). The idea of a reference is to store
data not directly, but rather as a small numeric value which points us to where
in memory we can find the value we need. Creating references in C++ is easy, and
not restricted to function calls:

~~~
#include <iostream>

int main(void) {
    // Create a new integer with value 5.
    int a = 5;

    // Create a reference b that points to a.
    int & b = a;

    // This prints 5!
    std::cout << b << std::endl;

    return 0;
};
~~~
{: .language-cpp}

The ampersand (`&`) is the common syntax for denoting references. Appending this
symbol to the end of a type essentially transforms it into a new type. In this
case, we go from the type *integer* to the type *reference to an integer*. We
can create references to virtually all types, and since references refer to a
location in memory rather than a value in itself, updating the value a reference
refers to will alter the value we can read from that reference, too:

~~~
#include <iostream>

int main(void) {
    int a = 5;
    int & b = a;

    // Note we are not directly changing b!
    a = 7;

    // This prints 7!
    std::cout << b << std::endl;

    return 0;
};
~~~
{: .language-cpp}

The reverse is also true; if we change a reference, then the value it points to
is also changed:

~~~
#include <iostream>

int main(void) {
    int a = 5;
    int & b = a;

    // Note we are not directly changing a!
    b = 9;

    // This prints 9!
    std::cout << b << std::endl;

    return 0;
};
~~~
{: .language-cpp}

This *spooky action at a distance* of data may be a surprising idea at first,
and depending on the school of programming you subscribe to it may be rather
disturbing, but we will come to talk about uses of this property later, as well
as how we can avoid it using const references. First, we will talk about the two
fundamental properties of references; their transparency, their non-nullability,
and their non-reseatability.

### Transparency

A wonderfully comfortable property of references is that they are transparent,
which is to say that they behave just like non-reference values. You can
subscript them like normal values, you can call member functions on them like
with normal values, and you can access their data members as normal with the `.`
operator. This is in contrast to pointers where you need to use the dereference
(`*`) or dereferencing accessor (`->`) operators. In most cases, code that works
syntactically with normal values can be adapted to use references without too
much hassle.

### Non-nullability

In C++, references must always point to something. This fact is either
profoundly confusing if you are familiar with C pointers, or completely sensible
if you're not. In C, as well as C++, there is the concept of a null pointer,
which points to some special location at the very start of the memory space to
indicate that the pointer doesn't point at anything. This is not possible with
references, and a reference always points to something. The following is invalid
C++:

~~~
void f(void) {
    int & a;
}
~~~
{: .language-cpp}

The compiler will complain at you that the reference is not initialized, which
is illegal. It is a malformed program.

### Non-reseatability

It is also impossible to change where a reference points. Once a reference is
created, it points to a specific location in memory, and you can never make it
point anywhere else. This is another comforting property, but it is important to
note that it does not mean that the value we point at cannot change. Recall from
our introduction that we were, in fact, making changes to a reference.

~~~
void f(void) {
    // This integer lives at 0x7ffcdbbde5dc
    int a = 5;

    // This integer lives at 0x7ffcdbbde5d8
    int b = 7;

    // This integer reference lives at 0x7ffcdbbde5d4, points to 0x7ffcdbbde5dc
    int & c = a;

    // This integer reference lives at 0x7ffcdbbde5d0, points to 0x7ffcdbbde5dc
    int & d = a;

    // After this, c still lives at 0x7ffcdbbde5d4
    // And c still points to 0x7ffcdbbde5dc
    // But the value at 0x7ffcdbbde5dc has been updated to 8.
    c = 8;
};
~~~
{: .language-cpp}

## Using references as function arguments

A common use of references is as function arguments. Recall that we were trying
to pass a very large data structure to a function earlier, and the cost of
copying that data was prohibitive. References allow us to *pass-by-reference*
instead of *pass-by-value*, which allows us to use even the largest data
structures as function arguments without worrying about performance. On most
modern systems, a reference is eight bytes in size, even to very large data
structures. Here is an updated example where we pass a very large data structure
to a function:

~~~
#include <iostream>

struct Behemoth {
    int vals[1000000];
};

int double_first(Behemoth & i) {
    return i.vals[0] * 2;
}

int main(void) {
    Behemoth b;

    int r = double_first(b);

    std::cout << r << std::endl;

    return 0;
}
~~~
{: .language-cpp}

When this code is executed, an eight-byte reference will be passed to the
`double_first` function, and the function will retrieve the data is needs itself
without any unnecessary copying. If you would like to examine the performance
difference between the two methods, try the following fully formed program:

~~~
#include <iostream>
#include <chrono>

struct Behemoth {
    int vals[1000000];
};

int double_pbv(Behemoth i) {
    return i.vals[0] * 2;
}

int double_pbr(Behemoth & i) {
    return i.vals[0] * 2;
}

int main(void) {
    Behemoth b;
    b.vals[0] = 10;

    auto t1 = std::chrono::high_resolution_clock::now();
    int r1 = double_pbv(b);
    auto t2 = std::chrono::high_resolution_clock::now();
    int r2 = double_pbr(b);
    auto t3 = std::chrono::high_resolution_clock::now();

    auto nano_pbv = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    auto nano_pbr = std::chrono::duration_cast<std::chrono::nanoseconds>(t3 - t2).count();

    std::cout << "Pass by val found " << r1 << " and took " << nano_pbv << "ns." << std::endl;
    std::cout << "Pass by ref found " << r1 << " and took " << nano_pbr << "ns." << std::endl;

    return 0;
}
~~~
{: .language-cpp}

You do not need to spend much time trying to understand what this code is doing,
but the difference in time should be significant! On my testing machine, the
pass-by-value implementation took roughly eight million nanoseconds (or eight
milliseconds) while the pass-by-reference implementation took roughly one
hundred nanoseconds!

## Const references

The *action at a distance effect* described at the beginning of this episode is
not always what we want. Sometimes we want to ensure that we a value cannot be
changed through a reference. In such cases, we can use const references which
block any attempt to modify the value they point at. Making const references
is trivial:

~~~
int main(void) {
    int a = 5;
    const int & b = a;
    return 0;
}
~~~
{: .language-cpp}

In this case, we can use the reference `b` only to read, not write. The
following code is malformed and will not compile:

~~~
int main(void) {
    int a = 5;
    const int & b = a;

    b = 7;

    return 0;
}
~~~
{: .language-cpp}

Note that we can create const references to non-const values! Essentially, we
are creating a read-only view of otherwise mutable data. This can have some
potentially unexpected effects:

~~~
#include <iostream>

int main(void) {
    int a = 5;
    const int & b = a;

    std::cout << b << std::endl;

    a = 7;

    std::cout << b << std::endl;

    return 0;
}
~~~
{: .language-cpp}

In this case, the value pointed at by our const reference changes between two
read accesses. This is usually not a problem in well-designed problems, but you
should be aware that it can happen, and having a constant reference to some data
does not mean that data will never change.

## Using references as output variables

One rather unfortunate use of references which stems from older and mostly
deprecated C++ programming practices is the use of references as so-called
*output variables*. It used be to be common practice to pass references to
functions with the intention of having the function write to them without
reading from them. These arguments were commonly called output parameters.
Sometimes arguments are used both as input and output, in which case they are
referred to as input-output arguments. The following function is an example of
output parameters in use:

~~~
void sincos(double in, double & sin, double & cos) {
    sin = std::sin(in);
    cos = std::cos(in);
}
~~~
{: .language-cpp}

Because this method takes two of its arguments as references, it can influence
the outside world without actually returning anything. Here is an example of
us using this method:

~~~
int main(void) {
    double sin, cos;
    sincos(0.3 * 3.1415, sin, cos);
    std::cout << sin << ", " << cos << std::endl;
    return 0;
}
~~~
{: .language-cpp}

Here, the `main` method is relying on the fact that `sincos` modifies the values
of `sin` and `cos`. Otherwise, it would be printing uninitialized values.

In general, usage of output variables should be avoided as much as possible in
modern C++. The compiler does a much better job optimizing code which returns
using the standard return interface, it makes the code more referentially
transparent, and it makes the code clearer to programmers.

## Memory safety

The fact that a reference is always bound to something (by way of their
non-nullability) is a great boon for memory safety, but it is not impossible for
a reference to point to invalid memory. The power of references is that, within
the scope of well-written code using only references, this doesn't really
happen. The main risk is receiving invalid references from outside or, in
multi-threaded programs, having another thread free some memory your references
are pointing too. In these cases, you can safely point fingers at someone else
and be reasonably assured that your code is not at fault. Still, be aware that
code using references can still suffer from, for example segmentation faults!

## Knowing more

References are an extremely important part of C++, and they form the foundation
for a lot of what we do in the language. However, references are also an
incredibly complex topic. We have just scratched the surface in this episode,
and it is designed to give you basic working knowledge to read and write code
that uses references. There is much more to learn about references, including
*lvalue references*, *rvalue references*, reference reduction rules, special
rules for const references, and much more. If you continue programming in C++,
you will gradually learn more and more about these topics.