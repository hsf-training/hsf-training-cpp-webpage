---
title: "Code inclusion"
teaching: 0
exercises: 0
questions:
- "How can I include code from an external file in my lesson"
objectives:
- "Include external code"
keypoints:
- "Put your code snippets in `_includes/code/`"
- "You can use `{% include path %}` to include an external file at any point"
- "Partial includes are a bit trickier unfortunately."
---

> ## Code includes
> Might be good for unit testing code snippets and for having syntax highlighting
> etc. when writing longer bits. Also great when you want to give students the
> opportunity to download the full files.
{: .callout}

This is a full include:

{% include includecpp filename='code/hello.cpp' highlight='cpp' %}

This is a partial include with line numbers

{% include includecpplines filename='code/hello.cpp' start=4 stop=7 %}

You can also include from a string to a string:

{% include includecppmethod filename='code/hello.cpp' startstring='main()' stopstring='}' %}

> ## Disabling all of this
> If we decide against using partial includes as above or find a better solution
> please remove `includelines` and `includemethods` from the `_includes`
> directory.
{: .callout}

{% include links.md %}

