---
title: "Compound datatypes"
teaching: 0
exercises: 0
questions:
    - How do we combine existing types into new types that are greater than the
      sum of their parts?
    - What are classes, and how do we define and use them?
objectives:
    - Understand product types.
    - Understand the basics of classes.
keypoints:
    - Will follow
---

{% include links.md %}

## Introduction

In the course so far, we have seen that most computation in C++ is built up of
primitive datatypes like `int`, `float`, `double`, and `bool`. It is safe to say
that these types lie at the foundation of the definition of data, and of course
we cannot have useful computations without data. However, the power of types
does not end there. In fact, there is an entire field of computer science called
type theory which studies the power of types in computer programs. The
expressive power of types is truly extraordinary, although C++ only allows us a
small taste of it. Nevertheless, combining types into new types is still a key
part of C++, and you will need to master it in order to write code that is
performant and, perhaps more importantly, maintainable.

## Motivation

Let us start by reviewing an extraordinarily simple function, the function which
takes as its input a single integer, and returns the absolute value of that
integer. Since it takes an integer as its input, and returns an integer as its
output, the signature of this function is `int → int`. It can be defined as
follows in the C++ programming language:

~~~
int abs(int i) {
  return i >= 0 ? i : -i;
}
~~~
{: .language-cpp}

This function is perfectly sensible, and aside from the fact that there is a
well-tested `std::abs` method in the standard library, there is nothing wrong
with it. Let us now write a function with two integer arguments, representing a
position in a two-dimensional space, which calculates the Manhattan distance to
that point. The type of this function is `(int, int) → int`:

~~~
int manhattan(int x, int y) {
  return std::abs(x) + std::abs(y);
}
~~~
{: .language-cpp}

Once again, there is nothing really wrong with this function. You would find
code written like this in many production code-bases, but it does serve to
motivate the use of compound types. At the risk of seeming pedantic, we can
identify two distinct problems with this code. Firstly, this method of designing
methods risks exploding the number of arguments, which makes it harder to use
the function (because the user must do more typing), and it also makes it harder
to reason about the function (because there is more mental load on anyone
reading this code to keep track of all the arguments). Secondly, there is no
semantic information available in this code that indicates that the two
arguments of this function are linked in any way. A coordinate in our space is
only truly meaningful in conjunction with another one: by itself it is nothing
more than an integer. The function shown above relies on the understanding of
the user to provide two separate numbers that meaningfully combine to represent
a coordinate in our space, and the compiler does nothing to stop the user from
making mistakes by loading in non-related quantities:

~~~
int result = manhattan(grams_of_cheese_for_breakfast, number_of_cats_owned);
~~~
{: .language-cpp}

The example above is somewhat contrived, but we find more gripping examples of
the principles described all over high-energy physics code. Consider, for
example, a function that operates on a particle track state, which is described
as an *n*-tuple and an *n×n* covariance vector. Let's assume *n=5* for now:

~~~
double myfun(double x, double y, double eta, double phi, double qop, double[] cov) {
  ...
}
~~~
{: .language-cpp}

Defining such a function is tedious, and using it even more so. If this function
is commonly used, dozens of programmers will have to write out all six arguments
to this function thousands of times, and the large amount of typing these
programmers have to do is sure to attract more bugs. Indeed, someone might
switch around the η and φ arguments, which would be very difficult to debug. The
idea that having more code to write increases the number of bugs that appear in
that code is sometimes referred to the *surface area* of the code which bugs
can latch onto.

In the rest of this episode, we will see that we can group together the
parameters of the functions given into meaningful units which will make the code
easier to understand and easier to use. At the end of the episode, we will
understand how to write equivalent methods that look like this:

~~~
int manhattan(Point p) {
  return std::abs(p.x) + std::abs(p.y);
}

double myfun(TrackState ts) {
  ...
}
~~~
{: .language-cpp}

## Product types

The simplest, most common, and most useful type of compound data type is the
product type. These types are conveniently the solution to the problems
addressed in the previous paragraph. Recall that we wanted to write our
`manhattan` method to take a single `Point` type instead of two `int` values. To
achieve this, we will define a product type of two `int` values, which we do
using the `struct` keyword in C++:

~~~
struct Point {
    int x;
    int y;
};
~~~
{: .language-cpp}

What this snippet of code achieves, is that it informs the compiler about the
existence of a new type called `Point`, which contains one integer called `x`
and another integer called `y`. Wherever we have an instance of this new type,
we can access the `x` and `y` values contained within to retrieve the
corresponding integers.

We can now start creating instances of our new type, in much the same way as we
create instances of primitive data types, although there is some special syntax
involved. The following code creates a `Point` object representing the
coordinates (5, 7). Note that this is not the only way to initialize and assign
values to data types, but we will return to this topic in the next paragraph.

~~~
Point p = {5, 7};
~~~
{: .language-cpp}

Accessing a member of our newly created point is equally simple. We use the
so-called member accessor operator, which is represented by a full stop (`.`) in
C++. For example, if we have our instance `p` defined above, the expression
`p.x` will give us the value of `x` inside that instance, and `p.y` will give us
the value of `y`. We can also insert new values into our instance using the same
syntax in addition to the assignment operator. For example, the following code
will update the `y` value of our instance to `9`:

~~~
p.y = 9;
~~~
{: .language-cpp}

To tie everything together, here is a minimal program which defines a product
type, initializes an instance of it, modifies one of the values, and then prints
the values contained within to the screen. The output of this program should be
`The point is: (5, 9)` (if it is not, please contact your nearest compiler
engineer).

~~~
#include <iostream>

struct Point {
    int x;
    int y;
};

int main(void) {
    Point p = {5, 7};

    p.y = 9;

    std::cout << "The point is: (" << p.x << ", " << p.y << ")" << std::endl;

    return 0;
}
~~~
{: .language-cpp}

As we have seen, defining and using product types is not too difficult! Most of
the syntax is reminiscent of the way we use primitive datatypes, but with some
extra member accessor operators thrown in. Now, let us discuss how we can
initialize values of our compound datatype, and how we can use them to solve the
problems we disucussed earlier.

> ## Why product types are called product types
>
> Each type represents a set of values it can contain. `int` corresponds to the
> set of integers between -2.1 billion and +2.1 billion, `uint` corresponds to
> the set of integers between 0 and 4.2 billion, `bool` corresponds to the set
> `{true, false}`, and `double` corresponds to a very strangely defined set of
> real numbers defined by the IEEE 754 standard. In any case, the set of values
> for each type is well-defined, even if it may be too large to usefully
> enumerate. When we create a product type of two types `a` and `b`, the set of
> values that type represents is exactly equal to the Cartesian *product* of the
> sets of values represented by `a` and `b`. This is why we often write this
> product type as `a×b`. The only primitive product type that we can enumerate
> in this short text bubble is `bool×bool`, which is represented by the set
> `{(true, true), (true, false), (false, true), (false, false)}`.
{: .discussion}

## Initializing compound types

Creating instances of our compound types is critical to our ability to use them.
Indeed, if we never produce any points, all the code that uses them will sit in
our code base looking pretty while it collects dust since it can never be used.
This paragraph will be somewhat more technical, and you do not necesserily need
to understand it to make good use of product types. However, it will give you a
better understanding of what is happening under the hood, and it will allow you
to reason more effectively about what is happening when the compiler compiles
certain statements and expressions.

So far, we have seen used syntax of the form `Point p = {5, 7};` to initialize
our instances. This is reminiscent of how we might initialize a primitive
datatype with an expression of the form `int a = 5;`. However, there are some
differences. In both cases, these statements are syntactic sugar, and the
compiler will *desugar* them to read the following:

~~~
// Point p = {5, 7};
Point p;
p = {5, 7};

// int a = 5;
int a;
a = 5;
~~~
{: .language-cpp}

Here, the *initialization* of our values has been split into an explicit
*declaration* and an *assignment*. But what exactly is the meaning of the
declaration statement `Point p;`? In fact, what is the meaning of `int a;`? It
is here that we first encounter the concept of *constructors*. A constructor is
a recipe for creating an instance of a type, and one of the fundamental
differences between primitive data types and compound data types is that the
former don't have constructors while the latter do. When we write `int a;`, we
instruct the compiler to reserve enough memory for us to store an integer, and
we will be able to use the name `a` later to conveniently reference that memory.
When declaring an integer or any other primitive data type, the compiler does
absolutely nothing to prepare that memory for use - that happens only when we
assign a value to it later.

> ## Declaring instances without initializing them
>
> Try declaring an integer type without any initialization, and then print the
> value of that integer to the screen. Before you execute your program, what do
> you think will happen? And why? Now run your program and see what happens. Did
> that match your intuition? If not, why not?
{: .challenge}

When we declare an instance of a compound data type, however, the compiler will
implicitly add code to prepare that instance for use: the constructor. The
compiler has helpfully created an implicit default constructor for us, saving us
the hassle of writing our own. We will see later how we can influence the
compiler's decision making process when designing default constructors, and we
will also learn how to create our own constructors.

Constructors are usually called using a syntax reminiscent of function calls,
and this will become important later when we create constructors that have
multiple arguments. However, we do not need to provide the usual function call
parentheses for the default constructor (and, in fact, we are not *allowed* to
provide them, as the meaning of this is ambiguous). Here are a few more ways to
declare, initialize, and assign compound data types:

~~~
// Default constructor:
Point a;

// Default constructor with two assignments:
Point b;
b.x = 5;
b.y = 7;

// Default constructor with one assignment:
Point c;
c.y = 7;

// Initialization with empty initializer list:
Point d {};

// Initialization with non-empty initializer list:
Point e {5, 7};

// Initialization with named initializer list:
Point f {.x=5, .y=7};

// Initialization with partial named initializer list:
Point g {.y=7};

// Assignment with initializer list:
Point h;
h = {.x=5, .y=7};
~~~
{: .language-cpp}

> ## Try out different ways of declaring and initializing types
>
> Copy the different declarations and initializations into a C++ file and print
> values of the points to the screen. Can you predict what each one will contain
> before running the program? Then run the program and verify your intuition. If
> you got it wrong, don't fret: even experienced C++ programmers get tripped up
> by the many way to initialize values.
{: .challenge}

### Default member values

So far, we have relied on the compiler to generate a default constructor for us.
This is very helpful, because it saves us the work of defining one. However, it
also leaves many of the design choices up to the compiler. For example, the
compiler will not try to initialize any of the integer values in our structure.
Luckily, we can exert some control over the default constructor without having
to define the whole thing. The most common way to do this is by specifying
default values for members. Consider the following C++ code:

~~~
struct Point {
    int x = 5;
    int y = 10;
};
~~~
{: .language-cpp}

This code instructs the compiler to initialize the value of `x` to five, and the
value of `y` to ten. The compiler will incorporate our wishes into the default
constructor, and it will implicitly insert code that sets these values anywhere
that we construct a `Point` instance. It is also possible to specify default
values for some members while omitting them for others. For example, the
following complete program will always give a value of ten for the `y`
coordinate, while the `x` will be unitialized, and its value will therefore be
undefined.

~~~
#include <iostream>

struct Point {
    int x;
    int y = 10;
};

int main(void) {
    Point p;

    std::cout << "The point is: (" << p.x << ", " << p.y << ")" << std::endl;

    return 0;
}
~~~
{: .language-cpp}

## Passing around compound types

Now that we know how to define, declare, initialize, and assign our custom
compound data types, we can finally return to our lamentations about passing
structured data to objects. You will be happy to learn that there is nothing
special about compound types when it comes to defining functions that take them
as arguments, or when passing them into those functions. Indeed, with the
knowledge we have already, extending our functions to use compound data types is
trivial:

~~~
#include <iostream>

struct Point {
    int x;
    int y;
};

int manhattan(Point p) {
  return std::abs(p.x) + std::abs(p.y);
}

int main(void) {
    Point p = {-11, 17};

    std::cout << "The Manhattan distance is: " << manhattan(p) << std::endl;

    return 0;
}
~~~
{: .language-cpp}

Take a moment to appreciate how compound datatypes allow us to write elegant
code. Firstly, all the arguments to the `manhattan` function are now grouped
together into a single sensible unit. Secondly, it is immediately clear to the
user what the meaning is of these values (indeed, the type is named `Point`, and
not `HeightAndWeight`) - we have encoded additional semantic information into
the function signature using our types. Thirdly, the number of arguments to the
function is reduced, giving both the user and the function author less work to
do.

> ## Be careful with large types
>
> When you pass arguments to functions, the compiler will copy the data from the
> call site to the callee. This is not usually a problem with primitive data
> types as they are generally small. In most implementations, the largest
> primitive data type will be eight bytes. However, compound datatypes are not
> limited in their size, and one could feasibly define a compound data type that
> occupy tens of thousands of bytes. In such cases, passing the instance by
> value, as it the default, can incur large performance penalties. In such cases
> it is wise to use references, which we will cover later.
{: .discussion}

## Classes

As boring as historical introductions to programming languages usually are,
please bear with us just once. When C++ was first being developed in Denmark in
the 1979, the language was not called *"C++"*, but rather *"C with Classes"*.
Indeed, classes are one of the most fundamental features of C++, and they are
the *raison d'être* for the entire programming language. Classes allow us to
take simple types like the structs we have seen earlier, and augment them with
special functions that operate on them.

> ## Classes and structs are (almost) the same
>
> The existence of the `struct` keyword in C++ is a vestige of C, and it must be
> said that classes and structs are almost the same thing in C++. However, we
> have chosen to denote simple product types with `struct` as this is more in
> line with how the keyword is used in C. Perhaps this will help you if you ever
> have the misfortune of reading C code; you will know that C structs are much
> less powerful than classes in C++.
{: .callout}

### Motivation

The motivation behind classes is a strict superset of the motivation behind
simple structs. Everything that motivates structs also motivates classes, but
classes give us a few more desirable properties, mainly encapsulation and the
ability to enforce invariants about our code.

#### Encapsulation

When we talked about structures, we mentioned the value of grouping information
together into senbible units that we can operate on. We noted that this provides
valuable semantics for human readers of the code. But we can go one step further
and *hide* information from the user if they don't need to see it. Indeed, when
you define a class, you *cannot* access the values stored inside it by default!
This might seem like a ridiculous at first, but there are some extremely
enticing benefits to this practice, which we call encapsulation. If you've ever
driven a car, you will be familiar with using the steering wheel, the gas and
brake pedals, and perhaps the stick shift. What you do not encounter during your
daily commute is the incredibly complex machinery that happens under the hood of
your car. The car designer has cleverly hidden the inner workings of the car
from you, encapsulating the stuff you don't need to know about under the bonnet,
and exposed only a simple interface for steering and accelerating to you. This
is the same idea that *drives* the desire for encapsulation in software.

Let us return to the example of a point in two-dimensional space that we used
earlier. Before, we used a Cartesian coordinate system, representing the point
in space as an *x*-coordinate and a *y*-coordinate. However, the Cartesian
system is not our only choice, and we could opt for a polar coordinate system
instead, where we represent points using an angle and a distance from the
center. These two approaches can be used to represent the same points, but the
implementations are different. The benefit of encapsulation in this case is that
we can hide the internal implementation of our class from the user, and expose
methods to retrieve the coordinates in either a polar system or a Cartesian
system. The implementation of this class can either have Cartesian coordinates
or polar coordinates on the inside, and the user doesn't have to care, because
they will interact only with the interface we expose. This also allows us to
freely change the implementation if the need comes up, without the user
noticing. If we changed up the coordinate system in our earlier `Point` struct,
we would have many angry users at our office within hours!

#### Invariants

Imagine we have our points in a Cartesian coordinate system, and we want our
class to represent points on the unit circle. That is to say, the distance from
the origin should always be one. The requirement that the length of our vector
should always be one is called an *invariant*, and the ability to enforce such
invariants is both a continuation of encapsulation as well as another desirable
property of classes. Imagine if we wanted to enforce this unit requirement on
the point struct we defined before: anyone can freely set the values inside that
struct, and there is nothing stopping them from inserting values that do not
have unit length! Our invariant could be broken almost immediately unless our
programmers took great care to only ever insert the right values! By enforcing
our invariants at the class level, we help the user protect themselves against
bugs.

In the coming few paragraphs, we will demonstrate how we can implement the
encapsulation described above, as well as these invariants.

### Defining classes

Let us now create our first class. We'll once again use the point example we
gave above, in which we have two coordinates in space, but we'll use doubles
this time, to change things up:

~~~
class Point {
    double x;
    double y;
};
~~~
{: .language-cpp}

If you're squinting your eyes, trying to spot the difference between the structs
we defined earlier and this class (except for the fact that we used a different
keyword), don't worry: the syntax is virtually the same!

### Access control

Recall that, by default, members of a class are not accessible from the outside
by default in order to facilitate encapsulation. To see this in action, consider
the following complete C++ program which will **not** compile:

~~~
#include <iostream>

class Point {
    double x;
    double y;
};

int main(void) {
    Point p;
    std::cout << p.x << ", " << p.y << std::endl;
    return 0;
}
~~~
{: .language-cpp}

If you were to try to compile this code, the compiler would show you an error.
The `x` and `y` members of the `Point` class are hidden to the outside world by
default: they are *private*. Only functions inside the class (which we will
cover in the next paragraph) are able to access them. In general, this is a
great property to have, as it encourages encapsulation. However, there are some
scenarios where you absolutely must access a member from the outside world. In
such cases, we can use *access* modifiers. Two common access modifiers are
`private` and `public`. The public access modifier allows anyone to access the
member, and breaks encapsulation. There is also the `protected` modifier, which
we do not yet have the ability to understand, and as such we will skip over it
for now. The following code compiles by making the data members public:

~~~
#include <iostream>

class Point {
public:
    double x;
    double y;
};

int main(void) {
    Point p;
    std::cout << p.x << ", " << p.y << std::endl;
    return 0;
}
~~~
{: .language-cpp}

As a general rule of thumb, you should use the strictest access modifier you can
get away with (that is to say, `private` over `protected` over `public`). Try
to expose data using public functions rather than public data members, and only
make data members public if you absolutely do not have a choice.

### Member functions

A useful feature of classes is that they can contain methods. Methods are
functions which only operate on an instance of the class on which it is defined.
Let's add some methods to our `Point` class:

~~~
#include <iostream>

class Point {
public:
    double getX() {
        return x;
    }
    double getY() {
        return y;
    }
    void setCartesian(double xn, double yn) {
        x = xn;
        y = yn;
    }
private:
    double x;
    double y;
};

int main(void) {
    Point p;
    p.setCartesian(5.0, 9.0);
    std::cout << p.getX() << ", " << p.getY() << std::endl;
    return 0;
}
~~~
{: .language-cpp}

There is a lot to say about this code! First of all, it might seem a little
verbose, especially compared to the code we had when the data members were
public. This is true! For now, it seems like we have added a lot of unnecessary
code for little gain, but we will benefit from the encapsulation later.

Secondly, note that we can still access the data members of the class from the
outside using the `getX` and `getY` methods, but only indirectly. This is
possible because these methods are public even though the data members are
private. Since the `getX` and `getY` methods are defined in the class, they can
access private members. Note how this means the class still has full agency on
how it handles calls to that function. This alternative implementation always
writes the number `42.0` to the coordinates, regardless of what the user
requests. This is not particularly useful, of course, but demonstrates that the
class designer is in control of what happens, and is free to inforce invariants
if they please.

~~~
class Point {
    ...
    void setCartesian(double xn, double yn) {
        x = 42.0;
        y = 42.0;
    }
    ...
};
~~~
{: .language-cpp}

Finally, we should take note of the fact that the methods defined in the class
only work on instances of that class. The following code would not compile, for
example:

~~~
double a = 5.0;
a.getX();
~~~
{: .language-cpp}

Now, let us unlock the full magic of encapsulation. In the following code, we
will completely redesign the internals of the class to use polar coordinates
instead of Cartesian coordinates. Take note of the fact that the user code (in
the `main` function) is identical between the two examples! This is how well we
can hide implementation: the user need not care *at all* about the insides of
the class.

~~~
#include <iostream>
#include <cmath>

class Point {
public:
    double getX() {
        return r * std::cos(phi);
    }
    double getY() {
        return r * std::sin(phi);
    }
    void setCartesian(double xn, double yn) {
        phi = std::atan2(yn, xn);
        r = std::hypot(yn, xn);
    }
private:
    double phi;
    double r;
};

int main(void) {
    Point p;
    p.setCartesian(5.0, 9.0);
    std::cout << p.getX() << ", " << p.getY() << std::endl;
    return 0;
}
~~~
{: .language-cpp}

Information hiding (encapsulation) is *the* core concept of object-oriented
programming, and of C++. It allows us to build modular code, and it allows us to
abstract ugly class internals away from the user. This is the jaw-dropping power
of encapsulation, and it is why you should focus on making your software as
encapsulated as possible.

Finally, let's quickly cover invariants. We will change our Point class to use
Cartesian coordinates again, like it was before, but we will not enforce that
the distance from the center of the coordinate space must always be one. That is
to say, the `setCartesian` method should fail if we try to set it to a point not
on the unit circle.

~~~
#include <iostream>
#include <cmath>

class Point {
public:
    double getX() {
        return x;
    }
    double getY() {
        return y;
    }
    bool setCartesian(double xn, double yn) {
        if (std::abs(1.0 - std::hypot(yn, xn)) < 0.0001) {
            x = xn;
            y = yn;
            return true;
        } else {
            return false;
        }
    }
private:
    double x;
    double y;
};

int main(void) {
    Point p;

    bool r1 = p.setCartesian(0.866025404, 0.5);
    std::cout << "Attempt 1 " << (r1 ? "succeeded" : "failed") << std::endl;

    bool r2 = p.setCartesian(6.0, 0.0);
    std::cout << "Attempt 2 " << (r2 ? "succeeded" : "failed") << std::endl;

    std::cout << "Point is (" << p.getX() << ", " << p.getY() << ")" << std::endl;
    return 0;
}
~~~
{: .language-cpp}

This time, we have altered the `setCartesian` method to check whether the given
point is on the unit circle. If it is, the values are updated as normal, and a
`true` value is returned to indicate success. If the point is not on the unit
circle, the values are *not* updated and `false` is returned to indicate
failure. Hopefully, this example demonstrates succinctly how classes allow us to
enforce invariants: try as the user might, the object will never lie off the
unit circle. Both the user and the developer can rest assured that whichever
values are inside this class, that requirement will always hold...

### Constructors

...or will it? There is one last weakness in our plan, and the following bit of
code reveals it:

~~~
int main(void) {
    Point p;
    std::cout << "Point is (" << p.getX() << ", " << p.getY() << ")" << std::endl;
    return 0;
}
~~~
{: .language-cpp}

When I ran this code, the result was `(7.89628e-317, 3.03428e-86)`, which is
clearly not on the unit circle! Due to the way our objects are initialized,
there is still a chance that we might end up with a point that is not on the
unit circle. This weakens our invariant tremendously, but thankfully there is a
way around it: constructors. We learned earlier that constructors are a way for
us to control the initialization of our class. Currently, we are using a
compiler-generated default constructor which does not know about our invariants,
but we can write our own constructor that does:

~~~
#include <iostream>
#include <cmath>

class Point {
public:
    Point() {
        x = 1.0;
        y = 0.0;
    }
    double getX() {
        return x;
    }
    double getY() {
        return y;
    }
    bool setCartesian(double xn, double yn) {
        if (std::abs(1.0 - std::hypot(yn, xn)) < 0.0001) {
            x = xn;
            y = yn;
            return true;
        } else {
            return false;
        }
    }
private:
    double x;
    double y;
};

int main(void) {
    Point p;
    std::cout << "Point is (" << p.getX() << ", " << p.getY() << ")" << std::endl;
    return 0;
}
~~~
{: .language-cpp}

The constructor is defined just like a member method, but it does not have a
return type and its name is equal to the class name. Here, we have defined the
zero-argument constructor (which is the one used in `main`) to initialize the
point to `(1.0, 0.0)`, which of course is on the unit circle. This way, we are
guaranteed that our invariant will hold from the moment the object is created.
An alternative syntax for this constructor is the following:

~~~
Point() : x(1.0), y(0.0) {
}
~~~
{: .language-cpp}

Finally, let's create a constructor which takes two arguments representing a
pair of polar coordinates, and initializes the instance with those coordinates.
The code might look something like this:

~~~
Point(double phi, double r): x(std::cos(phi)), y(std::sin(phi)) {
}
~~~
{: .language-cpp}

Note that we can throw away the value for *r*, since we want to have points on
the unit circle only. Discarding the value for *r* essentially scales our vector
to length 1 anyway. A full example that calls this new constructor is given
here. It gives us the point `(0.125465, 0.992098)`, and once again we are
guaranteed that any point we can create now lies on the unit circle. The
invariant holds.

~~~
#include <iostream>
#include <cmath>

class Point {
public:
    Point() : x(1.0), y(0.0) {
    }
    Point(double phi, double r): x(std::cos(phi)), y(std::sin(phi)) {
    }
    double getX() {
        return x;
    }
    double getY() {
        return y;
    }
    bool setCartesian(double xn, double yn) {
        if (std::abs(1.0 - std::hypot(yn, xn)) < 0.0001) {
            x = xn;
            y = yn;
            return true;
        } else {
            return false;
        }
    }
private:
    double x;
    double y;
};

int main(void) {
    Point p(1.445, 6);
    std::cout << "Point is (" << p.getX() << ", " << p.getY() << ")" << std::endl;
    return 0;
}
~~~
{: .language-cpp}

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

## Product and sum types in the standard library

In C++, product types are well represented by structs and unions, but sum types
are not type safe by default. Luckily, the standard library provides some useful
implementations of both, and we will cover four of them in this section. Note
that all these types can accept non-primitive types without question, so you
should feel free to experiment with them using more complex types.

### `std::pair`

Firstly, the `std::pair` class represents a 2-tuple (or a couple), which is a
product type between two types. In C++, `std::pair<A, B>` is the product type
`A×B`. Using this type saves you the hassle of defining your own custom data
type. Here is a minimal program showcasing the `pair` type:

~~~
#include <utility>
#include <iostream>

int main(void) {
    std::pair<int, double> v {5, 11.73};
    v.first = 8;
    std::cout << "Integer part: " << v.first << ", double part: " << v.second << std::endl;
    return 0;
}
~~~
{: .language-cpp}

### `std::tuple`

Secondly, `std::tuple` generalizes the concept of `std::pair` to an arbitrary
number of types. Whereas a pair has exactly two types, a tuple can have however
many you want. Here is a program that does the same thing as above, but with
an integer, a double, a boolean, and a float.

~~~
#include <tuple>
#include <iostream>

int main(void) {
    std::tuple<int, double, bool, float> v {5, 11.73, true, -5.81};
    std::get<0>(v) = 8;
    std::get<2>(v) = false;
    std::cout << "Integer part: " << std::get<0>(v) << std::endl;
    std::cout << "Double  part: " << std::get<1>(v) << std::endl;
    std::cout << "Boolean part: " << std::get<2>(v) << std::endl;
    std::cout << "Float   part: " << std::get<3>(v) << std::endl;
    return 0;
}
~~~
{: .language-cpp}

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

Finally, there is `std::variant`, which represents a sum type of an arbitrary
number of types. We won't go into detail about using `std::variant` here,
because it is far harder to use than the other three types shown here. In fact,
many C++ developers consider `std::variant` a failure of the standard committee,
and it is often given as an negative example of the ever-increasing complexity
of C++. Still, it is good to be aware of its existence, and to know what it
represents should you encounter it while reading existing code.