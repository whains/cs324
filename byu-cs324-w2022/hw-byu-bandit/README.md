# BYU Bandit

The purpose of this assignment is to familiarize you with working in a shell
environment, including redirection, pipelining, backgrounding, and more.  Read
the entire assignment before beginning!


# Preparation

NOTE: Throughout this exercise, you _must_ run the `ssh` command from the BYU
CS network, or the exercises will not work. To accomplish this, you may either
log on to a BYU CS lab workstation directly or log on remotely via SSH using
the following command:

```
ssh username@schizo.cs.byu.edu
```
(Replace "username" with your actual CS username)


# Instructions

Follow these steps:

 1. Use the SSH program to log in remotely to the computer imaal.byu.edu with
    username `bandit0` and password `bandit0`:

    ```
    $ ssh bandit0@imaal.byu.edu
    ```

 2. Follow the instructions in the file `readme` to get the password for Level
    1 (hint: use `cat` to get started).

 3. Close out your session to log out of imaal.byu.edu (`ctrl`+`d` or `exit`).

 4. Use SSH to again log in to imaal.byu.edu, this time with username `bandit1`
    and the password you obtained for Level 1.

 5. Repeat steps 2 through 4 through Level 10, such that you can log in to
    imaal.byu.edu successfully as the `bandit10` user.

For each level, except Level 8 (i.e., as a the `bandit7` user), you need to use
a combination of input/output redirection and/or pipelining, such that you can
get a single pipeline command (i.e., a "one-liner") to output just the password
for the next level, on a single line.  In some cases, the pipeline might just
contain a single command (example: learning the password for Level 1).  For
most cases, however, more than one command is required.  For example, consider
the following pipeline:

```
grep bar somefile.txt | awk '{ print $8 }' | base64 -d
```

Note that three commands were used in the example pipeline above: `grep`,
`awk`, and `base64`.  The output (stdout) of `grep` was connected to the input
(stdin) of the `awk` command, and the output (stdout) of `awk` was connected to
the stdin of the `base64` command.  There was no further command in the
pipeline, so `base64`'s output simply goes to the console.

When learning the password for Level 8 (i.e., as the `bandit7` user), the
suspend/resume does not need to be done as part of the "one-liner".  Those
require keystrokes after the program has been executed.  Just use the single
command.


# Submission Format

As you go, create a file `bandit.txt` that has the following format:

```
Level 0:
PASSWORD1
PIPELINE1
Level 1:
PASSWORD2
PIPELINE2
...
```

`PASSWORD1` represents the password for Level 1, and `PIPELINE1` is the actual
pipeline of commands (i.e., "one-liner") you used to get that password while
logged in as `bandit0`, etc.  For example:

```
Level 0:
0G3wlqW6MYydw4jQJb99pW8+uISjbJhe
foo
Level 1:
xJJHpfRpbE7F2cAt8+V9HLEoZEzZqvi+
grep bar somefile.txt | awk '{ print $8 }' | base64 -d
...
```

Note that following the format above is important, as it will allow your
assignment to be graded automatically.

Again, the pipeline for Level 8 does not require any more than what was used to
_start_ the command; you do not need to include what you did to suspend and
resume.


# Automated Testing

For your convenience, a script is also provided for automated testing.  This is
not a replacement for manual testing but can be used as a sanity check.  You
can use it by simply running the following:

```
./SshTester.py bandit.txt
```


# Helps

## Useful Commands

Here are some commands that you might use to help you:

 - `awk`
 - `base64`
 - `cat`
 - `curl`
 - `cut`
 - `dig`
 - `grep`
 - `gzip`
 - `head`
 - `md5sum`
 - `sha1sum`
 - `sort`
 - `tar`
 - `uniq`


## Building a Pipeline Incrementally

You might feel overwhelmed with the "pipeline" aspect of this assignment.  To
help you out, build the pipeline gradually.  For example, in the above example,
run just the following to see what the output is:

```
grep bar somefile.txt
```

Then run:

```
grep bar somefile.txt | awk ' { print $8 }'
```

Finally, when that is working, run the whole thing:

```
grep bar somefile.txt | awk '{ print $8 }' | base64 -d
```


## Other Helps

 - Use the man pages to learn about a command, as they are the primary
   documentation!  You can also find helpful examples on the Web.
 - Where a pipelined command begins with a command that can receive input from
   stdin, and the initial input is a file, one way of doing it is to use `<` to
   open the file and send it to the stdin of the first command.
 - To suspend the pipeline currently running in the foreground, use `ctrl`+`z`.
   Use `fg` to resume.  For more information, See the sections on
   `REDIRECTION`, `Pipelines` (under `SHELL GRAMMAR`), and `JOB CONTROL` in the
   `bash` man page.
 - You can duplicate stderr output on stdout by using `2>&1`.
 - You can redirect stderr output to `/dev/null` by adding `2> /dev/null` to
   the end of a command.
 - The `awk` command is pretty extensive and indeed includes a whole language.
   However, one of the common uses is to print a single space-delimited field
   from every line.  For example, a simple `awk` script to print out just the
   second (space-delimited) field of text from every line, the following
   command would work:
   ```
   awk '{ print $2 }'
   ```
 - `dig` and `curl` and are commands used to issue a request to a Domain Name
   System (DNS) server and HyperText Transfer Protocol (HTTP) server,
   respectively.  You can try them out with different domain names, types, or
   URLs, to see how they work, but you shouldn't need to do anything fancy with
   them for this assignment.  You will find the `+short` option useful for
   `dig`.


# Submission

Upload `bandit.txt` to the assignment page on LearningSuite.
