---
title: "Type inference"
teaching: 0
exercises: 0
questions:
- "Should I repeat again and again the obvious type of everything ?"
objectives:
- "Know about template type deduction, `auto` and `decltype`."
keypoints:
- "`auto` basically avoid you the error-prone typing of complex long type name."
- "A collateral benefit is that it is easier to modify some types repeated all over the code."
- "Yet, do not overuse `auto`, because the types contribute to the readability of the code."
---

{% include links.md %}

# Static typing and type inference

In C++, the developer must say the type of every piece of data which is handled, and the compiler will fiercely check that all your declarations are consistent. That is "static typing".

Yet, there are more and more situations where the compiler will infer the types from the context.  There are several benefits:
* it avoids to repeat redundant information, sometimes cumbersome and error-prone,
* it makes easier to replace a type with another, because only the explicit types require to be updated manually.

There is a drawback : when going above a threshold, which is rather subjective, you finally do not knowany more which variable has which type, and the code readability is damaged.

# Old school type inference for function templates

When one call a function template, the compiler will consider the arguments given to the function, and deduce the type parameters of the template. This is the first form of type inference introduced in C++. In the example below, the compiler will deduce that within `main`, for the call to `sum`, `Num` should deduced to be `int`.

~~~
#include <iostream>
#include <vector>

template< typename Num >
Num mean( const std::vector<Num> & col )
 {
  int sz = col.size() ;
  Num res = 0 ;
  for ( Num elem : col ) { res += elem ; }
  return res/sz ;
 }

int main()
 {
  std::vector<int> col = { 1, 2, 3, 4, 5 } ;
  std::cout << mean(col) << std::endl ;
 }
~~~
{: .language-cpp}

# Type inference for class templates

Type inference is now also available for classes. Below, notice how the compiler is able to deduce the type of `col` in `main`.

~~~
#include <iostream>
#include <vector>

template< typename Num >
Num mean( const std::vector<Num> & col )
 {
  int sz = col.size() ;
  Num res = 0 ;
  for ( Num elem : col ) { res += elem ; }
  return res/sz ;
 }

int main()
 {
  std::vector col = { 1, 2, 3, 4, 5 } ;
  std::cout << mean(col) << std::endl ;
 }
~~~
{: .language-cpp}

# New `auto` keyword, when initializing a variable

It is recommended to give an initial value to any variabe you declare. If the type of the variable is the same as the one of the initial value, do not repeat the type : use `auto` instead.

Rather than this:

~~~
#include <iostream>
#include <vector>

int main()
 {
  std::vector col = { 1, 2, 3, 4, 5 } ;
  
  int first = col[0] ;
  int sz = col.size() ; // bug ? unsigned to signed
  int sum = 0 ;
  for ( int elem : col ) { sum += elem ; }
  
  std::cout << "first: " << first <<std::endl ;
  std::cout << "mean: " << sum/sz << std::endl ;
 }
~~~
{: .language-cpp}

Write this:

~~~
#include <iostream>
#include <vector>

int main()
 {
  std::vector col = { 1, 2, 3, 4, 5 } ;
  
  auto first = col[0] ;
  auto sz = col.size() ;
  int sum = 0 ;
  for ( auto elem : col ) { sum += elem ; }
  
  std::cout << "first: " << first <<std::endl ;
  std::cout << "mean: " << sum/sz << std::endl ;
 }
~~~
{: .language-cpp}

In the latter, no risk to make an error with the type of `sz`, and if you change your collection from `std::vector<int>` to `std::vector<double>`, no need to change the declaration of `first` or `elem`.

Yet, what to do with `sum`, that we want to initiate with the value `0` (of type `int`), but that should be of the same type as `first` (possibly `double`) ?

# `decltype` keyword when initializing a new variable

If you do not have a valid initial value for your new variable, you can rely on  `decltype` to reuse the type of another variable.

~~~
#include <iostream>
#include <vector>

int main()
 {
  std::vector col = { 1, 2, 3, 4, 5 } ;
  
  auto first = col[0] ;
  auto sz = col.size() ;
  decltype(first) sum = 0 ;
  for ( auto elem : col ) { sum += elem ; }
  
  std::cout << "first: " << first <<std::endl ;
  std::cout << "mean: " << sum/sz << std::endl ;
 }
~~~
{: .language-cpp}

# `auto` remove any `const` or `&`

Be aware that `auto` gets rid of any `const` or `&` modifier to the type of the original value, which is what you expect in most of the cases. In the example below, we obviously do not want `res` to be of type `const int &`.

~~~
#include <iostream>
#include <vector>

template< typename Num >
Num accumulate( const std::vector<Num> & col, const Num & init )
 {
  auto res = init ;
  for ( auto elem : col ) { res += elem ; }
  return res ;
 }

int main()
 {
  std::vector col = { 1, 2, 3, 4, 5 } ;
  std::cout << accumulate(col,0) << std::endl ;
 }
~~~
{: .language-cpp}

# Willingly adding `const` and/or `&`

You sometimes should add `const` and/or `&` to the deduced type. For example, if you want to modifiy the elements of some collection. Below, notice the `auto & elem`.

~~~
#include <iostream>
#include <vector>

template< typename Num >
void scale( std::vector<Num> & col, Num factor )
 {
  for ( auto & elem : col ) { elem *= factor ; }
 }

int main()
 {
  std::vector col = { 1, 2, 3, 4, 5 } ;
  scale(col,2) ;
  auto first = col[0] ;
  std::cout << first << std::endl ;
 }
~~~
{: .language-cpp}

# `auto` as return type

The compiler can also deduce the return type of a function from the `return` instructions within the body of the function. This also works with several `return` isntructions, provided they all return a value of the same type.

~~~
#include <iostream>
#include <vector>

template< typename Num >
auto accumulate( const std::vector<Num> & col, Num init )
 {
  auto res = init ;
  for ( auto elem : col ) { res += elem ; }
  return res ;
 }

int main()
 {
  std::vector col = { 1, 2, 3, 4, 5 } ;
  std::cout << accumulate(col,0) << std::endl ;
 }
~~~
{: .language-cpp}

This only works if the declaration and the definition (body) of the function are in the same file, so this is mainly used for templates.

# Soon in C++20

Logically enough, C++20 introduce a simpler way to write template functions... with `auto` !
Below, there are two hidden type template parameters : one for `col`, one for `init`.

~~~
#include <iostream>
#include <vector>

auto accumulate( const auto & col, auto init )
 {
  auto res = init ;
  for ( auto elem : col ) { res += elem ; }
  return res ;
 }

int main()
 {
  std::vector col = { 1, 2, 3, 4, 5 } ;
  std::cout << accumulate(col,0) << std::endl ;
 }
~~~
{: .language-cpp}

Note: this simplified syntax implies some independance between all the template type parameters. There is no more clue that the type of `init` should be the same as the type ov the `col` elements. If you prefer to enforce such things, stay with the old `template` keyword.

