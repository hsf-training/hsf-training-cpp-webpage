---
title: "Templates"
teaching: 10
exercises: 10
questions:
- "How to factorize the code of similar functions and classes, where only few types and sizes are changing ?"
objectives:
- "Know about basic template features."
keypoints:
- "There are function and class templates."
- "Template parameters can be types or integers known at the compile time."
- "This is all managed at compile time."
- "All the code must stay in header files."
- "Beware of code bloat."
- "Specialization enable to handle special parameter values, but also imply some hassle, especially when mixing templates with inheritance or implicit conversions."
- "Before C++20, there is no simple way to define constraints on the allowed values for template parameters."
---

{% include links.md %}


# Templates

## Template definition

Sometimes, several chunk of codes differs only about some *types* involved, or about some *integral values which are known at compilation time*, such as the fixed size of some arrays. The C++ `template` feature is a way to factorize the code of those similar functions or classes, declaring the types and fixed integers as additional parameters. Let's see an example of function template, and an example of class template :

~~~
template<typename  T>
T abs( T val ) {
  const T ZERO = 0 ;
  if ( val > ZERO ) { return val ; }
  else { return (-val) ; }
}

template<typename  T, int sz>
class Vector {
  public:
    T data[sz] ;
};
~~~
{: .language-cpp}

## Template use

Wherever one call such template, he must clarify the lacking types and values. The compilation of the resulting *template instance* is finalized on-the-fly:

~~~
Vector<int,2> v = { 2*2*2, -3*3 } ;
std::cout << abs<int>(v.data[0]) << std::endl ;
std::cout << abs<int>(v.data[1]) << std::endl ;
~~~
{: .language-cpp}

Especially for function templates, the compiler is sometimes able to infer the lacking types from the values given as arguments to the function call, and one do not need to explicit them:

~~~
Vector<int,2> v = { 2*2*2, -3*3 } ;
std::cout << abs(v.data[0]) << std::endl ; // T is infered to be int
std::cout << abs(v.data[1]) << std::endl ; // T is infered to be int
~~~
{: .language-cpp}

## Alias template

The keyword `using`, which can define an alias name for any type, can also receive some template parameters. The two containers defined below are perfectly equivalent:

~~~
template<int sz>
using VectorDouble = Vector<double,sz> ;

VectorDouble<10> v1 ;
Vector<double,10> v2 ;
~~~
{: .language-cpp}

## Beware of code bloat

A template body cannot be compiled separately once for all : *it must stay entirely in the header file* where you declare the template item, and it will be somehow duplicated and substituted with the parameter values, wherever you use it.

Beware of this : you may rather simply and unconsciously instanciate (i.e. duplicate) your template items with many different parameters, trigger many copies and feed the so-called "code bloat". For each line below, there will be a different class generated, and they may be additionally duplicated in any body file where such lines appear:

~~~
Vector<int,2> v1 ;
Vector<int,3> v2 ;
Vector<double,10> v3 ;
Vector<double,20> v4 ;
Vector<double,30> v5 ;
.....
~~~
{: .language-cpp}

> ## Exercise
> 
> Consider the following example:
>
> ~~~
> #include <iostream>
> 
> template<typename  T, int sz>
> class Vector {
>   public:
>     T data[sz] ;
> };
> 
> template<int sz>
> using VectorDouble = Vector<double,sz> ;
> 
> template<typename T>
> using Vector3 = Vector<T,3> ;
> 
> // COMPLETE HERE
> 
> int main() {
>   Vector3<int> v1 = { 6*7, 3*14, 2*21 } ;
>   VectorDouble<2> v2 = { 3.14, 1.62};
>   display(v1) ;
>   display(v2) ;
> }
> ~~~
> {: .language-cpp}
> 
> Instructions:
> 1. add the lacking `display()` function, which print the values of the input `Vector` onto `std::cout`, one after the other,
> 2. the expected output is:
> 
> ~~~
> 42 42 42
> 3.14 1.62
> ~~~
> {: .language-bash}
{: .challenge}

> ## Solution
> 
> ~~~
> #include <iostream>
> 
> template<typename  T, int sz>
> class Vector {
>   public:
>     T data[sz] ;
> };
> 
> template<int sz>
> using VectorDouble = Vector<double,sz> ;
> 
> template<typename T>
> using Vector3 = Vector<T,3> ;
> 
> template<typename  T, int sz>
> void display( const Vector<T,sz> & v ) {
>   for ( int i = 0 ; i < sz ; ++i ) {
>     std::cout << v.data[i] << ' ' ;
>   }
>   std::cout << std::endl ;
> };
> 
> int main() {
>   Vector3<int> v1 = { 6*7, 3*14, 2*21 } ;
>   VectorDouble<2> v2 = { 3.14, 1.62};
>   display(v1) ;
>   display(v2) ;
> }
> ~~~
> {: .language-cpp}
{: .solution}


# Specialization

One can define a specific implementation for some specific values of a template parameter. This is called a *specialization*.

## Function template specialization

Below, we give a general implementation for `equal`, and a specialized one for `double`:

~~~
template<typename  T>
T abs( T val ) {
  const T ZERO = 0 ;
  if ( val > ZERO ) { return val ; }
  else { return (-val) ; }
}

template<typename T>
bool equal( T v1, T v2 ) {
  return (v1==v2) ;
}

template<>
bool equal( double v1, double v2 ) {
  const double EPSILON = 1e-13 ;
  return (abs(v1-v2)<EPSILON) ;
}
~~~
{: .language-cpp}

From the point of view of the client code, this is a single template with some special cases. Try the code below, with or without the specialization:

~~~
int main() {
  double val = 1.0, tenth = val/10, sum = 0.0 ;
  for ( int i = 0 ; i<10 ; ++i ) { 
    sum += tenth ;
  }
  if (equal(val,sum)) {
    std::cout<<"1. == 1./10 + 1./10 + ..." ;
  }
  else {
    std::cout<<"1. != 1./10 + 1./10 + ..." ;
  }
}
~~~
{: .language-cpp}

## Class template specialization & traits

The same kind of specialization can be applied to class templates, with an important *surprising characteristic* : one is completely allowed to change the public interface of the class !

Sometimes, it even makes sense to define a default template class which is empty, and only its specialization will provide some content. This usually called `traits`, and is used to *externally extend some existing types with new attributes*.

In this example, we extend `float` and `double` with a new constant `EPSILON` :

~~~
#include <iostream>

template<typename T>
class Traits {};

template<>
class Traits<float> {
  public:
    static constexpr float EPSILON = 1e-6;
};

template<>
class Traits<double> {
  public:
    static constexpr double EPSILON = 1e-13;
};

int main() {
  std::cout << Traits<float>::EPSILON << std::endl;
  std::cout << Traits<double>::EPSILON << std::endl;
}
~~~
{: .language-cpp}

Writing `Traits<int>::EPSILON` would be invalid, because the general implemetation of `Traits` does not include any `EPSILON` constant. This behavior may be what we want : asking the `EPSILON` for `int` does not make sense in this design, and we are happy that the compiler will complain.

## Variable templates

C++ has been given recently the ability to define *variable templates*, i.e. variables whose type is a template parameter. This is typically used to define a constant with a varying precision:

~~~
#include <iostream>
#include <cmath>

template<typename T>
T constexpr PI = std::acos(-T(1)) ;

int main() {
  // 3 . 14159 26535 89793 23846
  std::cout.precision(20) ;
  std::cout<< PI<int> <<"\n";
  std::cout<< PI<float> <<"\n";
  std::cout<< PI<double> <<"\n";
  std::cout<< PI<long double> <<"\n";
}
~~~
{: .language-cpp}

 When combined with specialization, this offers another way to define a value depending on the type:

~~~
#include <iostream>

template<typename T>
const T EPSILON =0;

template<>
const float EPSILON<float> = 1e-6;

template<>
const double EPSILON<double> = 1e-13;

int main() {
  std::cout << EPSILON<int> << std::endl;
  std::cout << EPSILON<float> << std::endl;
  std::cout << EPSILON<double> << std::endl;
}
~~~
{: .language-cpp}

As compared with the previous example, this is a lot more simple, from the syntax point of view. But the expression `EPSILON<T>` is valid for any `T`, for example `int`, and one must give a default value to the default non-specialized implementation of the variable template (here `0`).

> ## Exercise
> 
> In the program below, if one replace `double` with `float`, the value `1.0` is not any more equivalent to the sum of ten values `0.1`, because the `EPSILON` value (`1.e-13`) is too small for `float` precision. 
> 
> ~~~
> #include <iostream>
> 
> template<typename  T>
> T abs( T val ) {
>   const T ZERO = 0 ;
>   if ( val > ZERO ) { return val ; }
>   else { return (-val) ; }
> }
> 
> template<typename T>
> bool equal( T v1, T v2 ) {
>   return (v1==v2) ;
> }
> 
> // COMPLETE HERE: EPSILON definition for float and double
> 
> // REPLACE BELOW: the single specialization with two
> // specializations, one for float, and the other for double
> 
> using real = double ;
> 
> template<>
> bool equal( real v1, real v2 ) {
>   const real EPSILON = 1e-13 ;
>   return (abs(v1-v2)<EPSILON<double>) ;
> }
> 
> // REPLACE BELOW: real by float, so to validate
> // that the equality is now true also for float
> 
> int main() {
>   real val = 1.0, tenth = val/10, sum = 0.0 ;
>   for ( int i = 0 ; i<10 ; ++i ) { 
>     sum += tenth ;
>   }
>   if (equal(val,sum)) {
>     std::cout<<"1. == 1./10 + 1./10 + ..." ;
>   }
>   else {
>     std::cout<<"1. != 1./10 + 1./10 + ..." ;
>   }
> }
> ~~~
> {: .language-cpp}
> 
> Instructions:
> 1. replace `real`, and check the result,
> 2. inject into the program a definition of `EPSILON` which would be `1e-13` for `double` computation, and `1e-6` for `float` computation,
> 3. specialize the function `equal` both for `double` and `float`, using the previous definitions,
> 4. check, when using `float` numbers in `main()`, that `1.0` is now equivalent to the sum of ten values `0.1`.
{: .challenge}

> ## Solution
> 
> ~~~
> #include <iostream>
> 
> template<typename  T>
> T abs( T val ) {
>   const T ZERO = 0 ;
>   if ( val > ZERO ) { return val ; }
>   else { return (-val) ; }
> }
> 
> template<typename T>
> const T EPSILON =0;
> 
> template<>
> const float EPSILON<float> = 1e-6;
> 
> template<>
> const double EPSILON<double> = 1e-13;
> 
> template<typename T>
> bool equal( T v1, T v2 ) {
>   return (v1==v2) ;
> }
> 
> template<>
> bool equal( float v1, float v2 ) {
>   return (abs(v1-v2)<EPSILON<float>) ;
> }
> 
> template<>
> bool equal( double v1, double v2 ) {
>   return (abs(v1-v2)<EPSILON<double>) ;
> }
> 
> int main() {
>   float val = 1.0, tenth = val/10, sum = 0.0 ;
>   for ( int i = 0 ; i<10 ; ++i ) { 
>     sum += tenth ;
>   }
>   if (equal(val,sum)) {
>     std::cout<<"1. == 1./10 + 1./10 + ..." ;
>   }
>   else {
>     std::cout<<"1. != 1./10 + 1./10 + ..." ;
>   }
> }
> ~~~
> {: .language-cpp}
{: .solution}

# Few hassles

In real code, you mix templates with other C++ features, and the compiler sometimes fails to understand what you obviously mean... 

## Implicit conversions

Because they belong to different stages of the compilation process, the compiler cannot both infer a type parameter and apply an implicit conversion. Locate the implicit conversion in this program:

~~~
#include <iostream>

class Vector2 {
  public:
    double x, y ;
};

void display( Vector2 v ) {
  std::cout << v.x << '/' << v.y << std::endl ;
}

int main() {
  display({ 2*2*2, -3*3 }) ;
}
~~~
{: .language-cpp}

In this example, one cannot simply transform `double` into a template parameter, or the compiler will not known how to compile `display({ 2*2*2, -3*3 })`:

~~~
#include <iostream>

template<typename  T>
class Vector2 {
  public:
    T x, y;
};

template<typename  T>
void display( Vector2<T> v ) {
  std::cout << v.x << '/' << v.y << std::endl;
}

int main() {
  display({ 2*2*2, -3*3 });
}
~~~
{: .language-cpp}

In such a situation, the developer must *help* the compiler with an explicit conversion:

~~~
int main() {
  display(Vector2<int>{ 2*2*2, -3*3 });
}
~~~
{: .language-cpp}

## Nested dependent types

The compiler will refuse to compile the following code:

~~~
template<typename Container>
void inspect( Container & container )
 {
  Container::iterator * x ; // DOES NOT COMPILE !
  //...
 }
~~~
{: .language-cpp}

Actually, the compiler does not know yet if `iterator` is some `Container` nested type, or some static member variable. By default, it is assuming the latter (strange choice !), and  `Container::iterator * x` is seen as the multiplication of `Container::iterator` and `x`, which does not exist...

The fact that `Container::iterator` is expected to be a type can be specified with the keyword `typename`:

~~~
template<typename Container>
void inspect( Container & container )
 {
  typename Container::iterator * x ;
  //...
 }
~~~
{: .language-cpp}

Surprisingly enough, the compiler will also refuse to compile the following code:

~~~
template<typename Val>
void inspect( std::vector<Val> & container )
 {
  std::vector<Val>::iterator * x ; // DOES NOT COMPILE!
  //...
 }
~~~
{: .language-cpp}

Well, `std::vector` is known, but what if there exists a nasty specialization for a certain value of `Val`,
which changes the meaning of `std::vector<Val>::iterator`? Remember: when specializing a class, one can freely modify the class interface ! Again, the use of `typename` will appease the compiler.

## Inheritance

When a class inherits from a class template, the compiler suspects some possible nasty specialization, and *does not apply the inheritance as is* !

~~~
template<typename Val>
struct MyContainer
 {
  int size() { return 0 ; } ;
 } ;  

template<typename Val>
struct MyExtendedContainer : public MyContainer<Val>
 {
  int extended_size()
   { return size() + 1 ; }  // DOES NOT COMPILE!
 } ;
~~~
{: .language-cpp}

Three ways permit to restore the expected inheritance:
1. making the attribute visible with a help of instruction using: `... using MyContainer<Val>::size ; ...`,
2. calling the attribute with a pointer this: `... return this->size() ...`,
3. prefixing the attribute by the class name: `... return MyContainer<Val>::size() ...`.

The last approach should be avoided, because it inhibits possibly virtual methods.


# Yet, templates are a killing feature for library developers

Despites a tricky syntax and well-know drawbacks, templates are a key feature for C++ expressivity and performance. Perhaps you will never write yours, but certainly you will use more and more of them, provided by expert libraries. In C++20, the new *concepts features* will make templates even more pervasive. **Get ready !**
