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
> Currently the code snippets live in `_includes/code/` (using a subfolder of the
> `_includes` folder makes it a bit easier for Jekyll).
{: .callout}

This is a full include:

~~~
{% include code/scripts.py %}
~~~
{: .language-python}


This is a partial include with line numbers base on the solution found [here](https://hblok.net/blog/posts/2016/10/23/jekyll-include-partial-snippets-of-code/),
but it doesn't have the carpentry style

{% highlight python %}
{% include includelines filename='code/scripts.py' start=8 count=2 %}
{% endhighlight %}

This is a carpentry style include, but it has issues with blank lines which I am
not able to understand just yet.

```python
{% include includelines filename='code/scripts.py' start=8 count=2 %}
```

> ## Disabling all of this
> If we decide against using partial includes as above or find a better solution
> please remove `includelines` and `includemethods` from the `_includes`
> directory.
{: .callout}

{% include links.md %}

