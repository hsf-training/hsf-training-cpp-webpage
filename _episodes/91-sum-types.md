---
title: "Sum types"
teaching: 0
exercises: 0
questions:
    - How do sum types differ from product types?
objectives:
    - Understand sum types.
keypoints:
    - Will follow
---

{% include links.md %}

## Sum types

Although they are much less common than product types, sum types are another
important family of types. A sum type represents a *choice* between two types
instead of the *combination* of two types represented by a product. For example,
the sum type of a boolean and an unsigned integer (`uint+bool`) represents
exactly one value in the set `{true, false, 0, 1, .., 4294967295}`. This type
can be written in C++ using the following syntax, which we call C-style unions:

~~~
union IntBool {
    bool b;
    uint i;
};
~~~
{: .language-cpp}

This type is simulatenously a boolean and an unsigned integer, and without
external bookkeeping it is impossible to know which state it is currently in.
There is a comparison to be made to quantum mechanics, although collapsing a
wave form does not cause undefined behaviour (the root of all evil). To
understand what happens inside a union, consider the following complete C++
program:

~~~
#include <iostream>
#include <bitset>

union IntBool {
    bool b;
    uint i;
};

int main(void) {
    IntBool v;
    v.i = 1234567;
    std::cout << "i1 = " << std::bitset<32>(v.i) << " (" << v.i  << ")" << std::endl;
    v.b = true;
    std::cout << "i2 = " << std::bitset<32>(v.i) << " (" << v.i  << ")" << std::endl;
    return 0;
}
~~~
{: .language-cpp}

This program will set the integer member of the union to the value `1234567` and
then print it, along with the binary representation of that number. If you
execute this program, you will see that the first print correctly indicates the
value `1234567`, and the binary representation
`00000000000100101101011010000111`. Next, the program sets the boolean member of
the union to true, and then it prints the integer member again. However, because
the integer member and the boolean member occupy the same memory, setting the
boolean value has *modified* the integer member, and we see that the new value
is `1234433`, with binary representation `00000000000100101101011000000001`.

~~~
00000000 00010010 11010110 10000111
00000000 00010010 11010110 00000001
~~~

Notice how the only bits that have changed are the bottom eight. On the machine
that we tested this on, the size of a byte is one byte (eight bits), and as such
the operation `v.b = true;` has assigned the bits `00000001` to that byte, also
changing the integer member in the process.

> ## C-style unions are not type safe
>
> C-style unions are not type safe, and the use of such unions is very
> dangerous. In modern C++, **it is virtually always a bad idea to use unions
> like this**, and one should always use the type-safe sum types defined in the
> standard library. This snippet of code is included purely for educational
> purposes to help you understand the concept of sum types.
{: .callout}

Reading this, you may think sum types are a fundamentally bad idea, but they are
not. To truly appreciate them, we must split the *semantics* of unions from
their *implementation*. The semantics of unions are, as we will see, extremely
useful, but the C-style implementation is thoroughly lacking. We will see
examples of type-safe sum types later.

If we discard any notion of implementation and look at sum types from a
sufficiently abstract point of view, it is immediately clear how useful they
are. For example, consider a classic division function:

~~~
int divide(int n, int d) {
    return n / d;
}
~~~
{: .language-cpp}

This function is not safe. If the value of `d` is zero, and then we are diving
by zero. This will crash our program. But how do we make our function safe? We
can return some default value in the case that `d` is zero, as follows:

~~~
int divide(int n, int d) {
    if (d == 0) {
        return -1;
    }

    return n / d;
}
~~~
{: .language-cpp}

But this is also a bad idea, because there is now no way to differentiate
between the function returning `-1` to indicate a division by zero versus a
division which legitimately returns `-1`. C++ provides an exception mechanism
which can be used to handle these errors, but it is ham-fisted and very
uncomfortable to use. The ideal solution is to use a sum type:

~~~
int+Error divide(int n, int d) {
    if (d == 0) {
        return Error{DivByZero};
    }

    return n / d;
}
~~~
{: .language-cpp}

Although this is not quite valid C++ syntax, this serves to demonstrate the
value of sum types. The error values exist completely outside the realm of
legitmate return values, but they are easily distinguished. At the same time,
both the integer return values as well as the error state exist within the same
type, so the program type checks without error. One could also imagine a program
which divides two numbers and returns an integer value if the denominator
devides the numerator, and a double otherwise. Or one could represent optional
value of type `a` using the sum type `a+void`.

Let us return now to the real world, and consider implementation. If we don't
care about space or performance, we can represent any sum type as a product
type, just by storing one additional value to represent which of the summed
types is currently represented by the instance. However, the size of a struct is
equal to the sum of the sizes of all its members, while the size of a union is
equal to the size of the biggest of its members. A struct containing members of
sizes 50, 100, 100, 20, 4, and 8 bytes will total 282 bytes, while a union of
the same types will be only 100 bytes in size. Memory is the only valid reason
to overlap values in a union like C does, but unfortunately memory is often of
critical importance, and thus we overlap. This is where the horrible behaviour
we saw above come from. Remember, though, that this is an implementation detail
of the union keyword in C++, and it is possible to get the full semantic power
of sum types without having to result to such terrible implementation tricks.

## Sum types in the standard library

In C++, product types are well represented by structs and unions, but sum types
are not type safe by default. Luckily, the standard library provides some useful
type-safe sum types, and we will cover two of them now.

### `std::optional`

The `std::optional` type represents the sum type of a given type and the void
type (also called the unit type in more enlightened languages). You can use this
type when you want to support cases where you are not sure your value will
actually be populated. Here is the division example from earlier, but in a way
that actually compiles as C++:

~~~
#include <optional>
#include <iostream>

std::optional<int> divide(int n, int d) {
    if (d == 0) {
        // Return a "nothing" value.
        return {};
    }

    return n / d;
}

int main(void) {
    std::optional<int> r1 = divide(9, 3);
    std::optional<int> r2 = divide(9, 0);

    if (r1) {
        std::cout << "Result 1: " << r1.value() << std::endl;
    } else {
        std::cout << "Result 1: INVALID!" << std::endl;
    }

    if (r2) {
        std::cout << "Result 2: " << r2.value() << std::endl;
    } else {
        std::cout << "Result 2: INVALID!" << std::endl;
    }

    return 0;
}
~~~
{: .language-cpp}

### `std::variant`

Secondly, there is `std::variant`, which represents a sum type of an arbitrary
number of types. We won't go into detail about using `std::variant` here,
because it is far harder to use than the other three types shown here. In fact,
many C++ developers consider `std::variant` a failure of the standard committee,
and it is often given as an negative example of the ever-increasing complexity
of C++. Still, it is good to be aware of its existence, and to know what it
represents should you encounter it while reading existing code.