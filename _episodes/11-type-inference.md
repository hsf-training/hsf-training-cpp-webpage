---
title: "Type inference"
teaching: 10
exercises: 0
questions:
- "Should I repeat again and again the obvious type of everything ?"
objectives:
- "Know about `auto` and `decltype`."
keypoints:
- "The new keyword `auto` avoid you the error-prone typing of complex long type names."
- "A collateral benefit is that the code is more generic."
- "Yet, do not overuse `auto`, because the types contribute to the readability of the code."
---

{% include links.md %}

# Static typing and type inference

In C++, the developer must say the type of every piece of data which is handled, and the compiler will fiercely check that all your declarations are consistent. That is "static typing".

Yet, there are more and more situations where you can ask the compiler to infer the types from the context.  There are several benefits:
* it avoids to repeat redundant information, sometimes cumbersome and error-prone,
* it makes easier to replace a type with another, because only the explicit types require to be updated manually.

There is a drawback : when going above a threshold, which is *rather subjective*, you do not know any more which variable pertains to which type, and the code readability is damaged.

# Old school type inference for function templates

When one call a function template, the compiler will consider the arguments given to the function, and can deduce the type parameters of the template. This is the first form of type inference introduced in C++. In the example below, the compiler will deduce that within `main`, for the call to `sum`, `Num` should deduced to be `int`.

{% include includecpp filename='code/TypeInference/function-template-inference.cpp' highlight='cpp' %}

# Type inference for class templates

Type inference is now also available for classes. Below, notice how the compiler is able to deduce the type of `col` in `main`.

{% include includecpp filename='code/TypeInference/class-template-inference.cpp' highlight='cpp' %}

# New `auto` keyword, when initializing a variable

It is recommended to give an initial value to any variabe you declare. If the type of the variable is the same as the one of the initial value, do not repeat the type : use `auto` instead.

Rather than this:

{% include includecpp filename='code/TypeInference/noauto-variables.cpp' highlight='cpp' %}

Write this:

{% include includecpp filename='code/TypeInference/auto-variables.cpp' highlight='cpp' %}

In the latter, no risk to make an error with the type of `sz`, and if you change your array from integers to doubles, no need to change the declaration of `first` or `elem`.

Yet, what to do with `sum`, which we want to initiate with the value `0` (of type `int`), but that should be of the same type as `first` (possibly `double`) ?

# New `decltype` keyword

If you do not have a valid initial value for your new variable, you can rely on  `decltype` to reuse the type of another variable.

{% include includecpp filename='code/TypeInference/decltype-variables.cpp' highlight='cpp' %}

# Keyword `auto` remove any `const` or `&`

Be aware that `auto` gets rid of any `const` or `&` modifier to the type of the original value, which is what you expect in most of the cases. In the example below, we obviously do not want `res` to be of type `const int &`.

{% include includecpp filename='code/TypeInference/remove-modifiers.cpp' highlight='cpp' %}

If you want to preserve the possible `const` and/or `&` from the initial value, use `decltype` instead of `auto`.

# Willingly adding `const` and/or `&`

On the contrary, you must sometimes add `const` and/or `&` to a deduced type which lacks those modifiers. For example, if you want to modify the elements of some collection. In the example below, notice the `auto & elem`.

{% include includecpp filename='code/TypeInference/add-modifiers.cpp' highlight='cpp' %}

# Keyword `auto` as a return type

The compiler can also deduce the return type of a function from the `return` instructions within the body of the function. This also works with several `return` instructions, provided they all return a value of the same type.

{% include includecpp filename='code/TypeInference/auto-return.cpp' highlight='cpp' %}

> This only works if the declaration and the definition (body) of the function are in the same file
> (i.e. inline or template functions).
{: .callout}

# Soon in C++20 : `auto` for function arguments

Logically enough, we should be able, soon, to use `auto` for function arguments.... Actually, this is hiding templates, and as above, it only works for functions which have their declaration and description in the same file.

{% include includecpp filename='code/TypeInference/auto-arguments.cpp' highlight='cpp' %}

If you look at the final implementation of `accumulate` above, you will probably agree that too much `auto` makes the code probably more generic, but also less readable.
