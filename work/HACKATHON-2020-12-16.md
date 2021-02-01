# Hackathon 2020-12-16

These notes are sourced from the original
[hackathon Google doc](https://docs.google.com/document/d/1M0knOEK0HGHwYuaFCMj3lyKtD9wVgc3ODF0u3MGcGfY/edit).

## \[Porting module\] C++

*Top level summary…* at least of what Graeme, David, Stefan and Stephen
have been doing on Wednesday.

-   We decided that we would try to port the first day of Sebastien
    Ponce’s C++ course into the carpentry format. This is a learning
    experience for us all (of how the carpentry templates work and
    what you can do with them)

    -   We see this as dividing into about 10 “episodes” following the
        original structure of SP’s material

    -   Please use the who’s working on what document:
        [<u>https://docs.google.com/spreadsheets/d/18mzGGaaDPQaLX8PnrCD3h775PFABCZRyctFgC88ZC80/edit?usp=sharing</u>](https://docs.google.com/spreadsheets/d/18mzGGaaDPQaLX8PnrCD3h775PFABCZRyctFgC88ZC80/edit?usp=sharing)
        so that different people are not simultaneously editing the
        same material…

    -   Zoom for times when we want to discuss strategy...
        [<u>https://cern.zoom.us/j/99841855307?pwd=Y0RSUGM1STUxTXJIcTRueTU0Zm5udz09</u>](https://cern.zoom.us/j/99841855307?pwd=Y0RSUGM1STUxTXJIcTRueTU0Zm5udz09)

    -   GitHub with the freshly cloned lesson, just waiting for your
        content...:
        [<u>https://github.com/hsf-training/hsf-training-cpp-webpage</u>](https://github.com/hsf-training/hsf-training-cpp-webpage)

    -   Some discussion topics that we touched on (so we don’t forget
        them):

        -   At what point do we introduce CMake?

            -   Dive in right away, even if people don’t really know
                what’s happening

            -   Make CMake a prerequisite

            -   Start with command line, but introduce CMake as soon as
                we go over 1 source file scope

        -   Do not dwell on C++ history, we just start from C++17

        -   Start with the standard library as a given and don’t
            introduce it as a second way of doing things

        -   Are pointers introduced too early? They are quite a tricky
            topic and not needed at the beginning

            -   This also goes hand in hand with C++ memory management
                (could this even be a separate module?)

    -   Once you’ve done some work on the module, please commit the code
        (right now we’re at such an early stage that direct commits to
        the gh-pages branch are fine!)

    -   Send a short message to mattermost telling people what you did

<!-- -->

-   Matternost:
    [<u>https://mattermost.web.cern.ch/awesome-ws/channels/c-module</u>](https://mattermost.web.cern.ch/awesome-ws/channels/c-module)

    -   Can be used for chat on this C++ material or for anyone else’s
        project

-   Interested people:

    -   Kevin Nelson (emphasis on OO)

    -   Graeme Stewart

    -   David Chamont - translation of Sebastien course to
        carpentries(-like?) format, and start debating a new module
        “Scientific C++20 for Pythonists” (details below).

    -   Sam Meehan - translation of Sebastien course to SWC format

    -   Stefan Roiser - understand Carpentries and how to make it
        sustainable on the long-term

-   This is about thinking how to improve the HSF C++ training and how
    to bring it in a sustainable format, e.g. carpentry style module

    -   Starting here -
        [<u>https://docs.google.com/document/d/1dBRtqI0qeux3O-oV-NRxUTQTdusiSnh3fko2N\_ZnF4A/edit\#</u>](https://docs.google.com/document/d/1dBRtqI0qeux3O-oV-NRxUTQTdusiSnh3fko2N_ZnF4A/edit#)

    -   We need to think about how to have some sort of a single test
        program that can be threaded through each lesson

-   Kevin Nelson: After C++ students learn the basics (control
    flow/classes/inheritance/etc) they often overlook the software
    design paradigms. I’m interested in developing a module (perhaps a
    second course in C++, after the so-called introductory material)
    that focuses on studying design patterns and the “first
    principles” of object-oriented software development. To me C++ is
    a natural vehicle for this because it is more explicit than
    python, making the design principles manifest more concretely.
    Students would come away with an understanding of how to write
    code adhering to general principles (maximization of code reuse,
    encapsulation, abstraction, programming to interfaces not
    implementations, etc) in C++ but also in any other OO language.

-   Graeme Stewart: given the limited time we have should we work on a
    “C++ Core Ideas” module here?

    -   This also makes me wonder if this is really 3-4 courses that
        form an aggregate of C++ programming… (what follows is only a
        brain dump, don’t take it too seriously)

        -   C++ Core Ideas

        -   C++ Object Orientation

        -   C++ Templates

        -   C++ Tools (debuggers, profilers)

        -   C++ Design Patterns

        -   C++ and Python

-   David Chamont: you may also have

    -   C++ Functional programming (std::tuple, std::optional, ranges…)

    -   C++ Concurrent programming (std::thread, std::mutex, …)

    -   And I have a full bunch of other things ;)

### Who was working on which episode during the hackathon...

| Rough planning document for who would work on which "episode" for the core C++ |  |  |  |
|--------------------------------------------------------------------------------|---------|---------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  |                                                                                                                                                                                                  |
| Section                                                                        | Episode | Person  | Notes                                                                                                                                                                                            |
| Introduction                                                                   | 1       | Graeme  | DONE First version committed - I have an open question to self if we would like to have an annotated version of the hello-world code and compile; also we need a set of resource links somewhere |
| Core Syntax and Types                                                          | 2       | Stefan  |                                                                                                                                                                                                  |
| Arrays and Pointers                                                            | 3       | Graeme  | Dial back on pointers (they are an advanced topic) and add vectors as a variable length container                                                                                                |
| Operators                                                                      | 4       | David   | DONE. Raw set of examples, as in the original. Almost no text.                                                                                                                                   |
| Compound data types                                                            | 5       | Stephen | DONE. David: I like the functional flavor :)                                                                                                                                                     |
| Functions                                                                      | 6       | David   | DONE. David: I remove pointers stuff, to be used in another dedicated lesson, I think. I added some "return" stuff.                                                                              |
| References                                                                     | 7       | Stephen | DONE.                                                                                                                                                                                            |
| Control instructions                                                           | 8       | Kevin   | DONE                                                                                                                                                                                             |
| Headers and interfaces                                                         | 9       | Kevin   | DONE. No "exercises" yet, if others have ideas, please let me know                                                                                                                               |
| Templates                                                                      | 10      | David   |                                                                                                                                                                                                  |
| Type inference                                                                 | 11      | David   | DONE. I did extend Sebastian slides, which I found really to short for this topic.                                                                                                               |


## \[Talk about a new module\] Scientific C++20 for Pythonists

-   Interested people:

    -   David Chamont

    -   Graeme Stewart

-   David Chamont:

    -   We currently focus on a C++ course which helps raise the C++
        programmers from their ancient C++ practices to the new modern
        C++ syntax and standard library. I think that soon, those
        ancient C++ programmers will be raised, or definitively
        reluctant to be raised. The new community to focus on will be
        mostly made of young pythonists.

    -   Also, in the midterm, C++20 will be mainstream, and I think we
        should start soon to prepare some new course where we only
        teach C++20, not detailing any more the multiple and subtle
        differences between C++98, 03, 11, 14, 17… as we tend to do as
        experts.

    -   That’s why I suggest to plan this new course : C++20 only,
        targeted at pythonists.

    -   Also, since we are not in a hurry for this new course, we may
        try to investigate how we could produce some sort of
        “self-learning” module, and/or tend towards something
        MOOC-like...

    -   **During this hackathon, I just want to collect interested
        people, and perhaps talk a little about the ideas written
        above and topics below. I do not want to hijack the C++
        volunteers who want to participate to the porting of Sebastien
        Ponce course (I am one of them !).**

-   Ideas of course topics

    -   Python variables =&gt; C++ values, references, pointers, right
        value references, …

    -   Python garbage collector =&gt; C++ stack, heap, new, delete,
        RAII, smart pointers, allocators, ...

    -   Python dynamic duck typing =&gt; C++ static typing and type
        inference…

    -   Python modules =&gt; C++ modules

    -   Python tuples, list, maps =&gt; C++ array, valarray, vector,
        list, map, set, unordered, span, ranges, ...

    -   Python numbers =&gt; C++ char, short, int, long, long long,
        float, double, long double, ...

    -   Numpy/Scipy =&gt; C++ what ? mdspan ? Eigen ?

    -   Pandas =&gt; C++ what ?

-   Graeme

    -   So this is really nice as an idea, but I am wondering is it so
        different from the C++ course above, with some appropriate
        filtering and decorations? We definitely are teaching that to
        beginners… and I think most of them do know Python.

    -   Do we also want to give people help to understand older codes in
        HEP? If so, we can’t completely ignore old styles of doing
        things (maybe in “breakout” sections we can have sections a la
        “And in older code you might see…”)

        -   But this might only really apply to some more advanced
            topics…

-   David

    -   Yes to all Graeme remarks above. This could be an evolution of
        the current course under work.

    -   I just advocate for two strong changes of perspective in the
        near future :

        -   We reorganize, starting from Python premises

        -   We teach C++20 first, and older C++ as optional details. A
            good example is templates : teach first using \`auto\` as
            argument type, and explain afterwards the gory details of
            old syntax \`template blablabla\`.

    -   For the short-term, let’s assume C++17 is the standard, and
        translate Sebastian stuff,
