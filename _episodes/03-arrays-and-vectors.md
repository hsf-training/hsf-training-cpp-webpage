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
- "For vectors, data elements can be added and removed, as well as updated."
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
> will access the third element, but will fail (throwing an exception - more on them latter) if the
> third element wasn't valid.
>
> If you needed to know the number of elements in an array, this code will return that value to you:
>
> `four_vector.size()`
{: .callout}

> ## EXERCISE FOR ARRAYS HERE
>
> Blah blah blah
{: .challenge}

## Variable Size Containers: Vectors

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
- Accessing the elements of a vector uses the same `[]` notation as arrays.
  - Vectors also have the methods `front()` and `back()` that access the start and the end
  of the container.
- The size of the vector is returned by `size()`, just like it was for an array.

Compiling and running the code produces the expected results:

~~~
$ g++ --std=c++17 -Wall vector-basic.cpp -o vector-basic
$ ./vector-basic
This n-vector has time component -10
This n-vector now has time component 7.5
The first element of the vector is 3 and the last is 7.5
The vector size is 4
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
with the second `insert` that adding values from this starting point
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
> Formally in C++ the vector `v.begin()` method returns what is called
> an *iterator* that can be used to identify a position inside a container.
> Adding and subtracting then moves the access point up and down the
> vector, respectively, e.g.,
>
> `auto second_element = v.begin()+1`
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
> Note that `v.end()` is used a lot in C++ and returns the position in the
> container *one step beyond the last valid value*. (Thus in loops the comparison is always
> *less than*: `still_valid < v.end()`.)
{: .callout}

> ## EXERCISE FOR VECTORS HERE
>
> Blah blah blah
{: .challenge}

#### Deleting

If you want to delete the final element of the vector the `pop_back()` method will
do this. Note this method returns nothing, i.e., it's a `void` function in C++.

~~~
{% include_relative code/03-arrays-and-vectors/vector-pop-back.cpp %}
~~~
{: .language-cpp}

~~~
$ g++ --std=c++17 -Wall vector-pop-back.cpp -o vector-pop-back
$ ./vector-pop-back
After pop the last vector element is -2 and the size is 2
~~~
{: .language-bash}

And to delete an arbitrary position, use the iterator position that we
saw above with `erase()`.

~~~
{% include_relative code/03-arrays-and-vectors/vector-erase.cpp %}
~~~
{: .language-cpp}

~~~
$ g++ --std=c++17 -Wall vector-erase.cpp -o vector-erase
$ ./vector-erase
After single erase the third vector element is -4 and the size is 4
After a block erase the vector size is 2
~~~
{: .language-bash}

Here we illustrated two ways to use `erase`, first with a single element
and then with a range where all the elements between the starting
point and *before* the end point are removed.

If you want to delete all of the current entries in a vector then use
the `clear()` method:

~~~
{% include_relative code/03-arrays-and-vectors/vector-clear.cpp %}
~~~
{: .language-cpp}

~~~
$ g++ --std=c++17 -Wall vector-clear.cpp -o vector-clear
$ ./vector-clear
Vector initial size is 5
After a clear() the vector size is 0
~~~
{: .language-bash}

> ## EXERCISE FOR VECTORS EXTENSION HERE
>
> Blah blah blah
{: .challenge}
> ## How vector storage works in C++
>
> It's useful to know they way in which a vector works in C++ so you understand
> how to use it most effectively. Vectors are guaranteed in C++ to occupy
> contiguous memory, which means that processing a vector's elements one
> after another is usually rather efficient on modern CPUs.
>
> However, that does mean that if elements are inserted at the beginning or
> in the middle of a vector then all the elements after it have to be moved,
> which is slower. The advice is always try to fill up vectors at the end!
>
> As a vector's size is mutable the library will usually allocate some more space
> for the vector elements than are currently used. If there is spare space in the
> underlying allocation then `push_back()` will be very quick. However, when the
> underlying storage is exhausted the library has to reallocate memory in order
> to add a new element. Roughly this process is:
>
> 1. Call to `push_back()`
> 2. Realise that the current storage if full.
> 3. Allocate a new, larger, storage block.
> 4. Copy each element in turn from the old block to the new one.
> 5. Add the final, new, element.
> 6. Free the old storage.
>
> This is slow, and gets slower as the vector grows in size. To offset this
> problem, use the `reserve(N)` method of a vector that will tell the library
> to pre-allocate enough space for `N` elements in advance. e.g.,
>
> `vector<double> v;`
> `v.reserve(1000000);`
> `for (unsigned int i=0; i<1000000; ++i) v.push_back(i);`
>
> will avoid a lot of unnecessary reallocations and copying compared to the same
> code without the `reserve()` call.
{: .callout}

{% include links.md %}
