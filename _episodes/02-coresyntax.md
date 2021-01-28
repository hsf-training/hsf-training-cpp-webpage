---
title: "Core Syntax and Types"
teaching: 10
exercises: 10
questions:
- "What are the basic syntactical elements of C++"
- "What are C++ types and which basic types exist"
objectives:
- "Learn to 'read' basic C++ code"
- "Understand basic types and the distinction to other types"
keypoints:
- "Introdution into basic syntactical concepts of C++"
- "Definition and explanation of the most basic C++ types"
---

{% include links.md %}

## Comments

Let's start with the most important in C++, i.e. comments.

~~~
// simple comment for integer declaration
int i;

/* multiline comment
 * in case we need to say more
 */
double d;

/**
 * Best choice : doxygen compatible comments
 * \fn bool isOdd(int i)
 * \brief checks whether i is odd
 * \param i input
 * \return true if i is odd, otherwise false
 */
bool isOdd(int i);
~~~
{: .language-cpp}

There are various ways of commenting the code.

  - If the comment is only on a single line it needs to start with double forward slash `//`.
  - If the comment spans multiple lines it needs to start with slash-star `/*` and end with star-slash `*/` (The star in the second line of the multi-line comment is just for beautification and can be omitted).
  - The last example denotes a specific syntax which is used by external tools [doxygen](https://www.doxygen.nl/index.html) tool for creating code documentation and is used widely by C++ developers. Those comments look similar to multi-line comments with the difference that they start with a slash-double-star `/**`.

Comments are removed from the source code by the compiler during the translation process into machine code.


## Basic Syntax

Let's start with the standard programming "hello world" example in C++

~~~
#include <iostream>

// This is a function
void print(int i) {
  std::cout << "Hello World " << i << std::endl;
}

int main(int argc, char** argv) {
  int n = 3;
  for (int i = 0; i < n; i++) {
    print(i);
  }
  return 0;
}
~~~
{: .language-cpp}

The code block above contains already several key ingredients of C++ syntax.

Right at the top you can see the `#include` statement which will include more code which is necessary to compile the example below. Here the included file is inbetween angular braces `<>` which denotes standard headers, in our case the `iostream` file. Another possibility is to include files between double quotes (e.g. `"MyHeader.h"`).

The next text line contains a single line comment we discussed above.

The rest of the code contains two functions `print` and `main`. Each of the functions has a return value (e.g. main returns an `int` type) and arguments (e.g. `argc` and `argv` of type `int` and `char**`).

The main function in addition is a special function, in the sense that this is the entry point for the executable to run and every C++ executable can only contain one `main` function.

The code that is executed within a function is contained between an opening and closing curly brace, e.g. the `std::cout << ... ` statement in the print function.

Compling the above code in a file `helloworld.cpp` and running the executable, yields

~~~
~ % vi helloworld.cpp
~ % g++ helloworld.cpp -o hello
~ % ./hello
Hello World 0
Hello World 1
Hello World 2
~ %
~~~
{: .language-bash}


## Basic Types

~~~
bool b = true;                  // boolean, true or false

char c = 'a';                   // 8 bits ASCII character
char* s = "a C string";         // array of chars ended by \0
std::string t = "a C++ string"; // class provided by the STL

char c = -3;                    // 8 bits signed integer
signed char c = -3;             // 8 bits signed integer
unsigned char c = 4;            // 8 bits unsigned integer

short int s = -444;             // 16 bits signed integer
unsigned short s = 444;         // 16 bits unsigned integer
short s = -444;                 // int is optional

int i = -123456;                // 32 bits signed integer
unsigned int i = 1234567;       // 32 bits signed integer

long l=0L;                      // 32 or 64 bits (ptr size)
unsigned long l = 0UL;          // 32 or 64 bits (ptr size)

long long ll = 0LL;             // 64 bits unsigned integer
unsigned long long l = 0ULL;    // 64 bits unsigned integer

float f = 1.23f;                // 32 (23+7+1) bits float
double d = 1.23E34;             // 64 (52+11+1) bits float
~~~
{: .language-cpp}

The code snippet above denotes the most basic C++ types, also called fundamental types.

The variable in the first line is of type boolean (`bool`). The value for this type can only be `true` or `false`.

The next block denotes character variables. The `char` type can hold any ASCII character. The first line in this block of type char contains a single character. Note the single parenthesis to contain the value. The second line denotes a pointer to char (we will learn about pointers (`*`) in a later section) and can contain multiple characters. While `char*`` is also used in C the `std::string` type is a more powerful C++ object and can also contain multiple characters. Note that both values are surrounded by double parenthesis.

`char` is also an 8 bit signed integer (see third block). The string `signed` can be omitted in the declaration so the first and the second line are syntactically the same. The third line in this block though denotes the unsigned version of the char type (so has 8 bits for the value).

The `signed` string can be omitted for any of the basic types.

The next block denotes integer types which are 16 bits long (`short int`) and again exist in signed (15 bits for the value, 1 bit for the sign) and unsigned (16 bit value) versions.

The 32 bit version of the integer value is called `int` and again exists in signed and unsigned versions.

The next longer integer type is called `long int` and depending on the architecture holds 32 or 64 bit values. While the `long long int` type guarantees to hold a 64 bit integer type.

For `short`, `long` and `long long` integer types the string `int` can be omitted.

The last two types are floating point types. `float` fits into 32 bits with 23 bits of mantissa, 7 bits for the exponent and 1 bit for the sign. `double` takes 64 bits with 52 bits mantissa, 11 bits exponent and 1 bit for the sign.


### Guaranteed Length Arithmetic Types

~~~
#include <cstdint>

int8_t c = -3;       // 8 bits, replaces char
uint8_t c = 4;       // 8 bits, replaces unsigned char

int16_t s = -444;    // 16 bits, replaces short
uint16_t s = 444;    // 16 bits, replaces unsigned short

int32_t s = -0674;   // 32 bits, replaces int
uint32_t s = 0674;   // 32 bits, replaces unsigned int

int64_t s = -0x1bc;  // 64 bits, replaces long long
uint64_t s = 0x1bc;  // 64 bits, replaces unsigned long long
~~~
{: .language-cpp}

In case you want to be sure about the size of your arithmetic types, you can include the `<cstdint>` header and use the type names of the code snippet above.
