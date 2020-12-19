---
title: "Classes"
teaching: 0
exercises: 0
questions:
    - What are classes, how do they differ from structs, and how do we build
      them?
objectives:
    - Understand how to define and implement classes.
    - Understand how encapsulation and invariants can improve our code.
keypoints:
    - Will follow
---

{% include links.md %}

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
