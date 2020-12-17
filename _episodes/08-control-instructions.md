---
title: "Control Instructions"
teaching: 20
exercises: 10
questions:
- "How do I execute certain lines of code but not others?"
- "How do I reuse code and execute it many times?"
objectives:
- "Understand the syntax of conditional statements (if-else, switch, ? operator) and loops (for, while, do-while)."
- "Understand how conditionals and loops may stop early or skip over lines (break, continue, return, default)."
keypoints:
- "Control instructions make your code powerful and versatile."
- "You may need to test your program against different inputs for some code blocks to execute."
---

## What are Control Instructions

Control instructions are a core component of an imperative programming language.  An imperative programming language is one in which algorithms are described as a sequence of commands to be executed by the computer.  Sometimes, the program specifies that certain commands are only executed conditionally, dependent on the result of other commands.  C++, C, and python are all examples of imperative languages, and they all feature some form of the same types of control instructions.

Are there languages without control instructions?  Yes!  For example, Haskell is a pure functional language in which control more or less tackled by defining piece-wise functions that will execute different mathematical statements conditional on the argument.

## If Statements

An example of a block of code using the `if` and `else` reserved words is shown below.

~~~
if (condition1) {
    Instructions1;
}
else if (condition2) {
    Instructions2;
}
else {
    Instructions3;
}
~~~
{: .language-cpp}

The `else` and `else if` blocks are optional, and an arbitrary number of `else if` blocks may appear after the `if` code block.  The braces may be omitted when the instruction is one line, as our instructions are; however, the parenthesis are mandatory.  When the computer executes this portion of a program, only one of the three instructions will be executed, dependent on whether conditions 1 or 2 are satisfied.

A practical example of using `if-else` statements is the following block of code.  Read carefully and understand which lines will execute for a given input value a.

~~~
int collatz(int a) {
    if (a<=0) {
        std::cout << "Not supported" << std::endl;
        return 0;
    } else if (a == 1) {
        return 1;
    } else if (a%2 == 0) {
        return collatz(a/2);
    } else {
        return collatz(3*a+1);
    }    
}
~~~
{: .language-cpp}

## Conditional Operator

The syntax for the conditional operator is shown in the code block below.

~~~
test ? expression1 : expression2;
~~~
{: .language-cpp}

If the statement test is true, then `expression1` is evaluated and its result is returned; otherwise, `expression2` is evaluated and its result is returned.

The conditional operator `?` allows some conditional statements, namely when a *return value* is conditional, to be condensed into more compact syntax.  In the `collatz` function above, the result of the `if` statement was simply to return a different value.  We can write this block of code in one line with the conditional operator.

~~~
int collatz(int a) {
    return a==1 ? 1 : collatz(a%2 ? 3*a+1 : a/2);
}
~~~
{: .language-cpp}

We made use of the conditional operator twice: to check if `a` is precisely 1 and if `a` is even.  You might think after reading this line of code that the explicit `if-else` clauses are easier to understand, and you would be right.  The conditional operator should not be abused, meaning they should only be used when the effect is obvious and they are not nested.

## Switch Statements

`switch` statements provide a similar functionality to `if` and `else` but they are different in a subtle way that causes bugs for many users: **the cases are entry points, not independent pieces**.  Let's look at an example to understand this point.

~~~
switch (identifier) {
    case c1 : instructions1; break;
    case c2 : instructions2; break;
    case c3 : instructions3; break;
    ...
    default : instructiond; break;
}
~~~
{: .language-cpp}

In this block of code, if `identifier` equals `c1` then `instructions1` executes and then the `break` statement prevents any of the other instructions from executing.  The code executes similarly if `identifier` equals `c2` or `c3`.  If we omit the `break` after `instructions1` then `instructions2` will also execute when `identifier` equals `c1`.  This brings us back to the point mentioned before, which bears repeating: **the cases are entry points, not independent pieces**.  The `break` is not mandatory, but omitting it can lead to frustrating debugging sessions.  For your own benefit, **do not make use of non-breaking cases**.  Finally, the `default` instruction executes if `identifier` is not equal to any of the provided cases.

Typically switch statements use an `enum`, `int` or `char` as the `identifier`.  Here is an example of how to use `enum` and `switch` to create a very readable conditional statement.

~~~
enum Lang { FRENCH, GERMAN, ENGLISH, OTHER};
...
switch (language) { // language is one of the elements of the Lang enum
    case FRENCH:
        printf("Bonjour");
	break;
    case GERMAN:
        printf("Guten tag");
	break;
    case ENGLISH:
        printf("Good morning");
	break;
    default:
        printf("I do not speak your language");
	break;
}
~~~
{: .language-cpp}

### The [[fallthrough]] Attribute

For expert users, the `[[fallthrough]]` attribute will suppress the compiler warnings produced by non-broken cases, for example:

~~~
switch (c) {
    case 'a':
        f();
	[[fallthrough]];  // Warning suppressed when this line is added
    case 'c':
        h();
}
~~~
{: .language-cpp}

However, remember that we recommend using `break` anyways.

### Init Statements for if and switch

If an object is needed within the blocks of an `if-else` statement, or the cases of a `switch` statement, one option is to instantiate the object on a separate line as shown below:

~~~
Value val = GetValue();
if (condition(val)) {
    // on success ...
}
else {
   // on failure ...
}
~~~
{: .language-cpp}

However, we can condense this statement and declare the object `val` in the local scope of the conditional statement by use of an init-statement.  (By local in scope we mean that `val` will be avaliable only within the `if` and `else` blocks, not in the next lines of code).

~~~
if (Value val = GetValue(); condition(val)) {
    // on success ...
}
else {
    // on failure ...
}
~~~
{: .language-cpp}

> ## Challenge
> What will happen if we try to compile and run the following program?
> ~~~
> int a = 3;
> switch (a) {
>     case 1: printf("a == 1");
>     case 3: printf("a == 3");
>     case 4: printf("a == 4");
>     default: printf("a is not 1, 3, or 4");
> }
> ~~~
> {: .language-cpp}
> 
> > ## Solution
> > When we compile the code, we will see a warning for each of the non-terminated cases.  When we run the code, we will see three printouts, saying that a is 3, a is 4, and a is not 1, 3, or 4.
> {: .solution}
{: .challenge}

## For Loops

At this point, we switch gears in the middle of a rather long lesson.  Up until now we focused on how to tell the computer to execute one line of code instead of an alternative.  Loops will allow the same lines of code to be executed repeatedly.  The first loop we examine will be the `for` loop.

~~~
for (initializations; conditions; increments) {
    instructions;
}
~~~
{: .language-cpp}

The initializations may include declarations (i.e. `size_t i = 0`).  Multiple initializations or increments are comma separated.  As with previous conditional statements, the braces are optional if the instructions are only a single line of code.  A practical example using multiple initializations and increments is shown below.

~~~
for (int i = 0, j = 0; i < 10; i++, j = i*i) {
    std::cout << i << "^2 is " << j << "\n";
}
~~~
{: .language-cpp}

This will print out ten lines, starting with `0^2 is 0` and ending with `9^2 is 81`.  To keep code readable, make sure your foor loop statement (including initializations, conditions, and increments) fits in 1-3 lines.

### Range Based for Loops

~~~
for (type iteration_variable : container) {
    // body using iteration_variable
}
~~~
{: .language-cpp}

Range based loops make iterating over many containers extremely easy, including arrays and `std::vector`s.  Many standard library objects support range based loops, and you can even write your own objects to be compatible with this syntax.  An example code using this syntax is:

~~~
int v[4] = {1,2,3,4};
int sum = 0;
for (int a : v) { sum += a; }
~~~
{: .language-cpp}

This syntax saves us the hassel of declaring some intermediate variable to index the array position; rather, we cut straight to the contents of the array.

## While Loops

Another way to repeatedly execute code is the `while` loop.  The syntax is as follows:

~~~
// while loop
while (condition) {
    instructions;
}

// or a do-while loop
do {
    instructions;
} while (condition);
~~~
{: .language-cpp}

The `while` loop repeatedly executes the `instructions` until the `condition` is false.  The `do-while` variant will be sure to execute the instructions at least once, and then starts checking whether the condition is true or false.  A practical example of the while loop, which again computes the `collatz` function, is as follows.

~~~
while (n != 1)
    if (0 == n%2) n /= 2;
    else n = 3 * n + 1;
~~~
{: .language-cpp}

Note that the `if-else` clause here still counts as being "one line" of code, and the braces are omitted.

**Be careful with while loops!**  While loops can cause infinite repeated execution if the condition is not properly defined.  It is also possible to have infinite repeated execution in `for` loops, but a less common problem.

> ## Challenge
> What will happen when	we try to compile and execute the following program?
> ~~~
> int a = 0;
> do
>     a-=10;
>     std::cout << a << std::endl;
> while (a != 0);
> ~~~
> {: .language-cpp}
> > ## Solution
> > This code will not compile.  The `do` clause must have braces before the `while` when multiple statements are present.  If we did fix this issue by adding braces, it might appear at first glance like the code in the brances would not execute because our variable `a` is initialized to not meet the condition `a != 0`.  However, because the `do` causes the code to execute once before checking the condition, the first number printed will be -10 and then this loop will repeat infinitely, continuing to subtract 10 from `a`.
> {: .solution}
{: .challenge}


## Commands

Various commands halt execution of a conditional statement or function to differing degrees.  The main culprits are:
* A `continue` statment prevents and further execution *of that iteration*, but the loop is allowed to keep executing the next iteration.
* We have already seen how the `break` command interacts with a `switch` block by preventing further execution.  It has a similar effect on loops as well.  When in a loop, if a `break` statement is executed the loop immediately terminates, but the function is allowed to keep executing.
* A `return` statment not only breaks out of the loop, but breaks out of the current function as well, and possibly returns a value (if the return type of the function is not `void`).

An example of using these commands within a loop to compute the `collatz` function is shown.

~~~
while (1) { // naively, the loop will never finish (unless a break or return is reached)
    if (n == 1) break;
    if (0 == n%2) {
        std::cout << n << "\n";
	n /= 2;
	continue;
    }
    n = 3 * n + 1; // will not execute unless n is odd
}
~~~
{: .language-cpp}

> ## Challenge
> The while loop we just provided is vulnerable to infinite execution.  Can you come up with an integer value of n that will cause infinite execution?
>
> > ## Solution
> > The most apparent example is if `n` is zero.  In this case, on every iteration of the loop we keep dividing `n` by 2, which doesn't change its value.  There is also a possible loop for negative integers, for instance -2 will be divided by 2 on the first loop to set `n=-1` and then on the second loop n will be set back to -2.  If you found a positive integer solution, [go claim your $500.](https://en.wikipedia.org/wiki/Collatz_conjecture#:~:text=He%20also%20offered%20US$500%20for%20its%20solution)
> {: .solution}
{: .challenge}

> ## Challenge
> What will happen when we try to compile and execute the following program?
> ~~~
> int a = 10;
> for (;;) {
>     std::cout << a << std::endl;
>     a--;
>     if (a == 0) break;
> }
> ~~~
> {: .language-cpp}
> > ## Solution
> > The program compiles and runs, printing integers from 10 descending to 1.  The 3 expressions in a `for` loop are *optional*.  Usually, we do want them there because the syntax is much clearer, for example we could write the same program in a single line as:
> > ~~~
> > for (int a = 10; a != 0; --a) std::cout << a << std::endl;
> > ~~~
> > {: .language-cpp}
> > However, both programs will produce the same output.  Note that if you omit the termination condition in a for loop you risk running into an infinitely repeating loop.
> {: .solution}
{: .challenge}

> ## Challenge
> One of your colleagues writes the following function and called it several times to test it.  The function is designed to return the maximum of three floating point values.
> ~~~
> float max(float a, float b, float c) {
>     if (a < b) {
>         if (b > c) return b;
>         else return c;
>     } else if (b > c) return b;
>     else return a;
> }
>
> std::cout << max(0, 1, 2) << std::endl;
> std::cout << max(0, 2, 1) << std::endl;
> std::cout << max(1, 2, 0) << std::endl;
> ~~~
> {: .language-cpp}
> Your collaborator tells you that they are sure the function works because they tested it and no matter what order they put the numbers in, it always found that the max was 2.
> 
>
> Are they correct?  Or are there other cases you should test before being so sure?
> 
> > ## Solution
> > You should test a few more cases.  The bare minimum should be to test the function enough so that each line executes, and in the test cases provided `a` is always less than `b` so the line `else return a;` is never executed.  When using control flow with much larger blocks of code, it becomes dangerous to push code to some shared repository if it has not been tested.
> >
> > Further, if `c > a > b`, then the function erroneously returns `a`, not `c`.  With control instructions different parts of the program are executed, so you must be careful when testing the program to cover all parts of the input phase space.
> {: .solution}
{: .challenge}
