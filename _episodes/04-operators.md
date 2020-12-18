---
title: "Basic C++ operators"
teaching: 10
exercises: 0
questions:
- "What is specific in basic C++ operators ?"
objectives:
- "Know about basic C++ operators specificities."
keypoints:
- "Be careful with increment operators, which have a left-side and a right-side version."
- "Prefer using explicit parentheses over relying on complex precedence rules."
- "There is no predefined power operator."
---

{% include links.md %}

# Binary & Assignment Operators

~~~
int i = 1 + 4 - 2 ; // 3
i *= 3; // 9
i /= 2; // 4
i = 23 % i; // modulo => 3
~~~
{: .language-cpp}

# Increment / Decrement

~~~
int i = 0; i++; // i = 1
int j = ++i;    // i = 2, j = 2
int k = i++;    // i = 3, k = 2
int l = --i;    // i = 2, l = 2
int m = i--;    // i = 1, m = 2
~~~
{: .language-cpp}

Be careful with those operators !

# Bitwise and Assignment Operators

~~~
int i = 0xee & 0x55;  // 0x44
i |= 0xee;            // 0xee
i ^= 0x55;            // 0xbb
int j = ~0xee;        // 0xffffff
int k = 0x1f << 3;    // 0x78
int l = 0x1f >> 2;    // 0x7
~~~
{: .language-cpp}

# Boolean Operators

~~~
bool a = true;
bool b = false;
bool c = a && b;    // false
bool d = a || b;    // true
bool e = !d;        // false
~~~
{: .language-cpp}

# Comparison Operators

~~~
bool a = (3 == 3);  // true
bool b = (3 != 3);  // false
bool c = (4 < 4);   // false
bool d = (4 <= 4);  // true
bool e = (4 > 4);   // false
bool f = (4 >= 4);  // true
~~~
{: .language-cpp}

# Precedences

~~~
c &= 1+(++b)|(a--)*4%5^7; // ???
~~~
{: .language-cpp}

Do not rely on complex precedence rules ! Use parenthesis.

