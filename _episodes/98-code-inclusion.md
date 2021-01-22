---
title: "Code inclusion"
teaching: 0
exercises: 0
questions:
- "How can I include code from an external file in my lesson"
objectives:
- "Include external code"
keypoints:
- "Put your code snippets in `_episodes/code/`"
- "There are three different ways to include code."
---

> ## Code includes
> Might be good for unit testing code snippets and for having syntax highlighting
> etc. when writing longer bits. Also great when you want to give students the
> opportunity to download the full files.
{: .callout}

This is a full include:

{% include includecpp filename='code/hello.cpp' highlight='cpp' %}

This is a partial include with line numbers

{% include includecpplines filename='code/hello.cpp' start=3 stop=6 %}

You can also include from a string to a string:

{% include includecppmethod filename='code/hello.cpp' startstring='main()' stopstring='}' %}

{% include links.md %}

