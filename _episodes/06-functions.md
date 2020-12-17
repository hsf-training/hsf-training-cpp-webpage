---
title: "Functions (UNDER WORK)"
teaching: 10
exercises: 0
questions:
- "How to define a function ?"
- "What are the different ways to pass input arguments ?"
- "What are the different ways to get back the results ?"
objectives:
- "Know about ordinary C++ functions."
- "Know about references and const references."
- "Know about RVO and structured bindings."
keypoints:
- "Const references avoid the cost of the copy for input arguments."
- "You should not be afraid any more of returning big results."
---

{% include links.md %}

# Different examples of input arguments and output results

## With return type

~~~
int square(int a) {
  return a*a;
}
~~~
{: .language-cpp}

## Multiple parameters

~~~
int mult(int a, int b) {
  return a*b;
 }
~~~
{: .language-cpp}

## No parameter

~~~
void hello() {
  std::cout << "Hello World" << std::endl;
}
~~~
{: .language-cpp}

## No return

~~~
void log(char* msg) {
  std::cout << msg << std::endl;
}
~~~
{: .language-cpp}

# Different ways to exchange arguments

## By value

Each time the function is called, the value given as argument is duplicated within the function. If the function modify the argument, only the internal copy is modified, not the original (which is often what we want). The duplication may take time when the input argument is big.

~~~
{% include includelines filename='code/06-arg-by-value.cpp' start=3 stop=16 %}
~~~
{: .language-cpp}

## By reference

If you want the function to modify the original value, you must declare the argument as a reference (postfix with `&`). 

~~~
{% include includelines filename='code/06-arg-by-reference.cpp' start=3 stop=8 %}
~~~
{: .language-cpp}

## By constant reference

If you do want the function to modify the original value, but you would like to avoid the cost of the copy, you can declare the argument as a constant reference (prefix with `const` and postfix with `&`). 

~~~
{% include includelines filename='code/06-arg-by-const-reference.cpp' start=9 stop=16 %}
~~~
{: .language-cpp}

This pratice is not worth for small builtin types such as `int`, `double`, or the standard libray iterators, which are usually passed by value.

# Different ways to return results

## By value... and only by value !

We have seen that one can pass a variable as reference to a function, and the function modify it : it was the old way to proceed when you have several results, or big ones you want to avoid to duplicate.

Nowadays, whenever you can, simply return the result by value, as would do a methematical function.

~~~
{% include includelines filename='code/06-return-by-value.cpp' start=3 stop=9 %}
~~~
{: .language-cpp}

Do not be afraid of returning a big value, object, array, etc. Most of the time, if not all the time, the compiler will avoid the copy and drectly write the reslt in the external receiving variable.

NEVER return a reference, unless you are a C++ great master !

