# `man` Hunt

This set of exercises is intended to familiarize you with `man`, which is the
gateway to the official documentation of programs, system calls, library calls,
and operating system features _for your running system_.


## Setup

Log in to one of the BYU CS machines using `ssh`:

```bash
ssh username@schizo.cs.byu.edu
```
(substitute `username` with your actual username)

Run the following:

```bash
man man
```

Running this command opens a "pager" (i.e., a file viewer) that displays the
contents of the manual page for the program `man`.  With the default pager
(`less`), the following keys are helpful for navigation:

 - `h`: launch the built-in help
 - `j` or down arrow: go down one line (mneumonic: the crook of the j points
   downward)
 - `k` or up arrow: go up one line
 - `ctrl`+`f` or page down: go down one screen (i.e., page down)
 - `ctrl`+`b` or page up: go up one screen (i.e., page up)
 - `/`, `<pattern>`, `Enter`: search for `<pattern>`
 - `n`: go to the next instance of the pattern previously searched for
 - `?`: go to the previous instance of the pattern previously searched for
 - `q`: quit

Now read through the man page for `man`, especially the sections on "SYNOPSIS",
"DESCRIPTION", "EXAMPLES", "OVERVIEW", and "OPTIONS".  And look closely at the
`-f` and `-k` options, which will be useful in the next section.


## Questions

Using only the `man` command, answer the following questions.  To answer each
question, you will need to call `man` with certain arguments and options and
either inspect the output or read parts of (or search within) the man page that
is opened.  

 1. What are the numbers associated with the manual sections for executable
    programs, system calls, and library calls, respectively?
 2. Which section number(s) contain a man page for `open`?
 3. What three `#include` lines should be included to use the `open()` system
    call?
 4. Which section number(s) contain a man page for `socket`?
 5. Which `socket` option "Returns a value indicating whether or not this
    socket has been marked to accept connections with listen(2)"?
 6. How many man pages (in any section) contain keyword references to
    `getaddrinfo`?
 8. According to the "DESCRIPTION" section of the man page for `string`, the
    functions described in that man page are used to perform operations on
    strings that are ________________. (fill in the blank)
 8. What is the return value of `strcmp()` if the value of its first argument
    (i.e., `s1`) is greater than the value of its second argument (i.e., `s2`)?
