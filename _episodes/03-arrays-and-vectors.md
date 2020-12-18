---
title: "Arrays and Vectors"
teaching: 20
exercises: 20
questions:
- "How can I create collections of things in C++"
- "How can I get and set values in a collection?"
- "If I don't know the size of the collection in advance, what do I do?"
objectives:
- "Understand static arrays of objects in C++ for creating collections."
- "Know how to use the standard library vector to create variable sized collections."
- "Be able to access members of the collection and update, insert and delete values."
keypoints:
- "C++ can assign fixed sized collections as arrays."
- "C++ can manage variable sized collections as vectors of objects."
---

## N.B.

I feel after having written this episode that it would be very useful to have covered
`for` loops at this point, even just to be able to write an example where one
can loop over the container.

It's also appropriate to introduce container iteration loops alongside containers.

Also, any iterator type really, really should be handled with `auto`...

## Introduction

We saw previously how to create variables that represented the basic types
of C++. However, usually in scientific and data intensive problems we need
to deal a huge amount of data and these are usually grouped into collections
of numbers rather than being created and accessed one by one (which would be
incredibly tedious!).

## Fixed Size Containers: Arrays

In C++ we have the possibility to create arrays of the basic types (well, we'll see
later this can be extended to virtually any object in C++). Here's a simple
example:

~~~
{% include_relative code/03-arrays-and-vectors/array-basic.cpp %}
~~~
{: .language-cpp}

What do we see here?

First, arrays in modern C++ are part of the standard library
and first we need to tell the compiler we want to use that
functionality by including the header file `array`.

Second, we define an array in C++ using a syntax like this:

`array<TYPE, NUMBER>`

This is actually an example of what's called a *template* in C++, which
we'll study in more detail later, but in this simple example it's pretty
clear how to use it passing these two arguments in.

We're also showing you a way to initialise multiple value objects like arrays
using a standard C++ syntax called *uniform initialization*: `{a, b, c, ... }`.

Third, data in the array is accessed using the `[n]` notation *where
`n` counts from 0*. So an array of size `N` has elements `0`, `1`,
`2`, `...`, `N-1`.

When we compile and run we get:

~~~
$ g++ -std=c++17 array-basic.cpp -o array-basic
$ ./array-basic
This 4-vector has time component -10
This 4-vector now has time component 7.5
$
~~~
{: .language-bash}

Note that arrays are always a fixed size in C++.

> ## Array indexes
>
> As we saw, array indexes run from `0` to `N-1` for an array of size `N`.
> If you accidentally try to access a value outside of this range then
> the results are *undefined behavior* - you're program might crash,
> or worse it might silently just produce wrong answers. So this is 
> something to be very careful of.
>
> Arrays also support an access method called `at` which will check that
> a valid data element is being accessed:
>
> `four_vector.at(3)`
> 
> will access the third element.
>
> If you needed to know the number of elements in an array, this code will return that value to you:
>
> `four_vector.size()`
{: .callout}

> ## EXERCISE FOR ARRAYS HERE
>
> Blah blah blah
{: .challenge}

## Fixed Size Containers: Vectors

Arrays are great to use when the data size is known up-front. However, in many cases
we might not know how large a container we need at the beginning. In this case
C++ comes to our aid with a *variable sized container type* called a *vector*.

One can use a vector in much the same way as an array:

~~~
{% include_relative code/03-arrays-and-vectors/vector-basic.cpp %}
~~~
{: .language-cpp}

This looks very like our array code above and one of the nice things about these C++
*containers* is that they are used in very similar ways!

- Instead of including the `array` header, this time we use `vector`.
- When we define our vector we don't need to give the size, as this is mutable.
  - In this case, we initialised the vector with 4 elements the size of the vector *is* 4.
- Accessing the elements of a vector uses the same `[]` notation as arrays

Compiling and running the code produces the expected results:

~~~
$ g++ --std=c++17 -Wall vector-basic.cpp -o vector-basic
$ ./vector-basic
This n-vector has time component -10
This n-vector now has time component 7.5
$
~~~
{: .language-bash}

### Adding and Deleting Elements from Vectors

#### Adding

To add a new element to a vector there is a the `push_back()` method:

~~~
{% include_relative code/03-arrays-and-vectors/vector-push-back.cpp %}
~~~
{: .language-cpp}

The example shows that the `push_back()` extends the container by one element, adding the argument
to as the last value.

~~~
$ g++ --std=c++17 -Wall vector-push-back.cpp -o vector-push-back
$ ./vector-push-back
Vector elements are 1.5 and 2.7 and the size is 2
Vector now has 3 elements; and the last value is 3.9
~~~
{: .language-bash}

If you need to add an element to an arbitrary position in a vector then you can use the 
`insert()` method:

~~~
{% include_relative code/03-arrays-and-vectors/vector-insert.cpp %}
~~~
{: .language-cpp}

Here we used the method `begin()` to get the start of the vector and you can see
with the second insert that adding and subtracting values from this starting point
work as you would expect (`begin()+3`, for example, is the 4th element position).

~~~
$ g++ --std=c++17 -Wall vector-insert.cpp -o vector-insert
$ ./vector-insert
The first vector element is 100 and the size is 4
The second vector element is 200 and the size is 5
~~~
{: .language-bash}

> ## Iterator arithmetic
>
> Formally in C++ the `vector<TYPE>.begin()` method returns what is called
> an *iterator* that can be used to identify a position inside a container.
> Adding and subtracting then moves the access point up and down the
> vector, respectively, e.g.,
>
> `auto second = v.begin()+1`
>
> Just be careful that you don't try to insert into an invalid place in the
> vector as bad things will happen, i.e., inserting into a location *before
> the beginning* of the vector or inserting into a place more than *one
> step beyond* the end. Inserting right at the end is valid and makes
> `insert()` behave like `push_back()`:
>
> `v.insert(v.end(), VALUE)`
>
> behaves the same as
>
> `v.push_back(VALUE)`
>
> Note that `vector<TYPE>.end()` is used a lot in C++ and returns the position in the
> container *one step beyond the last valid value*. (Thus in loops the comparison is always
> *less than*: `still_valid < v.end()`.)
{: .callout}

#### Deleting



> ## How vector storage works in C++
>
> It's useful to know they way in which a vector works in C++ so you understand
> how to use it most effectively...
{: .callout}

{% include links.md %}
