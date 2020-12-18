---
title: "Templates (UNDER WORK)"
teaching: 10
exercises: 0
questions:
- "How to factorize common code, when only the types and sizes are changing ?"
objectives:
- "Know about basic templates syntax and mechanisms."
keypoints:
- "There are function, struct and class templates."
- "Parameters can be types or integers known at the compile time."
- "Beware of code bloat."
- "Before C++20, there is no simple way to define constraints on the allowed values for parameters."
---

{% include links.md %}

# General idea

Sometimes, several chunk of codes differs only about some types involved, or about some integral values which are known at compilation, such as the fixed size of some arrays. The C++ `template` mechanism is way to factorize such similar functions or classes, declaring the types and fixed integers as parameters. Wherever they will be used afterwards, one will have to specify each time the parameters to be concretely used.

One can see the template mechanism as a improved preprocessor macro, under the full control of the compiler. It can also be seen as an automated copy-and-paste. Beware of this : you may rather simply and unconsciously instanciate (i.e; duplicate) your template items with many different paramters, and feed the so-called "code bloat".

# Function templates

# Struct and class templates

~~~
{% include_relative code/TypeInference/noauto-variables.cpp %}
~~~
{: .language-cpp}
