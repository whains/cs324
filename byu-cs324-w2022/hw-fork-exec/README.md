# `fork` and `exec`

The purpose of this assignment is to give you hands-on experience with
`fork()`, `exec()`, and `pipe()` system calls, by walking you through various
iterative exercises and examining the resulting output.  Read the entire
assignment before beginning!


# Preparation

 1. Read the following in preparation for this assignment:
    - Sections 8.2 - 8.4 and 10.8 - 10.10 in the book
    - The man pages for the following system calls:
      - `fork`
      - `execve`
      - `pipe`
      - `dup2`

 2. Run `make` to build two executables: `fork` and `exec`.  These are programs
    that illustrate the system calls `fork()` and `exec()`.

 3. Start a tmux session.  Create two panes, such that the window looks like
    this:

    ```
    ----------------------------
    |  command   |   system    |
    | execution  |  analysis   |
    |            |             |
    ----------------------------
    ```

 4. You will be doing a writeup on this assignment. Call your writeup
    `forkexec.txt`. Make sure you answer any questions/provide outputs as
    stated in the *bolded* questions/statements (there should be 20 in all).


# Part 1: `exec()` Overview

Open `exec.c`, and look at what it does.  Then answer the following questions.
Note that you will be _testing_ the behavior of `exec.c` in Part 2, so you will
want to consider these questions as you go through that part.

 1. *Briefly describe its behavior.*

 2. *Under what condition(s) will the final `printf()` statement get executed?*


# Part 2: `exec()` Experimentation

In the next steps, you will be using the `ps` command to examine how a process
associated with the `exec` program changes over time. Because of this, you will
want to read all of problems 3 through 6 before you start.

 3. In the left ("command execution") pane of your tmux window, run the `exec`
    program, passing `/bin/cat` as the first command-line argument. *Show your
    terminal commands and the output.*

 4. In the right ("system analysis") pane of your tmux window, run the `ps`
    command, first during the initial 30-second `sleep()` call, then again after
    the first 30 seconds is over, but before the end of the program.

    Use the `-p` and `-o` options when you run `ps` so that, respectively:

    - only the process with the PID output by `exec` is shown
    - the `ps` output is formatted to have the following fields:
      - `user`: the username of the user running the process
      - `pid`: the process ID of the process
      - `ppid`: the process ID of the parent process
      - `state`: the state of the process, e.g., "Running", "Sleep", "Zombie"
      - `ucmd`: the command executed

    Use the man page for `ps` for more on how to use these options.

    *Show your terminal commands and the output.*

 5. *Which fields are the same in the output of the two `ps` commands? Which
    have changed?  Briefly explain.*
    
    (You can use `ctrl`+`d` to signal end of file (EOF), so the program will
    run to completion)

 6. Run the `exec` program again, but this time using a non-existent program
    (e.g., `/does-not-exist`) as an argument.  *Show the output, and briefly
    explain what happened.*

Now would be a good time to review questions 1 and 2, both to confirm or update
your answers and to check your understanding.


# Part 3: `fork()` Overview

Open `fork.c`, and look at what it does.  Then answer the following questions.
Note that you will be _testing_ the behavior of `fork.c` in Part 4, so you will
want to consider these questions as you go through that part.

 7. *Briefly describe its behavior.*

 8. *Which sections (i.e., of "A", "B", "C", and "D") are run by the parent
    process and, which are run by the child process?*


# Part 4: `fork()` Experimentation

In the next few steps, you will be using the `ps` command to examine how the
process(es) associated with the `fork` program change over time. Because of
this, you will want to read all of problems 9 through 15 before you start.

 9. In the left pane of your tmux window, run the `fork` program.  In the right
    pane, run the `ps` command, first during the initial 30-second `sleep()`
    call, then again after "Section B done sleeping" is printed.

    Use the `-p`, `-o`, and `--forest` options when you run `ps` so that,
    respectively:

    - only the processes with the PIDs output by `fork` are shown
    - the `ps` output is formatted to have the following fields:
      - `user`: the username of the user running the process
      - `pid`: the process ID of the process
      - `ppid`: the process ID of the parent process
      - `state`: the state of the process, e.g., "Running", "Sleep", "Zombie"
      - `ucmd`: the command executed
    - the process ancestry is illustrated

    Use the man page for `ps` for more on how to use these options.

    *Show the two `ps` commands you used, each followed by its respective
    output.*

 10. *What is different between the output of the two `ps` commands?  Briefly
     explain.*
    
 11. If you were to run the `fork` and `ps` commands from #9 again at the same
     times as you did before, *what special line of code could you add to
     `fork.c` to eliminate the process with state "Z" from the output of the
     second `ps` command? Where would this line most appropriately go?*

     Add that line to `fork.c`, and re-`make` (note: you may also need to add a
     few `#include` statements at the top of the file for it to compile and run
     properly--see the man page for the function to learn which to include).
     Then re-`make`.

 12. Follow the instructions from #9 again to verify your answer from #11.

     *Show the two `ps` commands you used, each followed by its respective
     output.*

 13. *What is different between the output of the two `ps` commands?  Briefly
     explain.*
    
 14. Modify `fork.c` according to the following:

     - Comment out the line of code you added in #11, until a later part of the
       assignment.
     - Replace the single call to `sleep()` in Section B with two 30-second
       `sleep()` calls, back-to-back.
     - Replace the two back-to-back calls to `sleep()` in Section C with a
       single 30-second `sleep()` call.

     Re-`make`, then run `fork` in the left pane of your tmux window.  In the
     right pane, run the `ps` command with the same options as in #9, first
     during the initial 30-second sleep call, then again after "Section C done
     sleeping" is printed.

     *Show the two `ps` commands, each followed by its respective output.*

 15. *What is different between the output of the two `ps` commands?  Briefly
     explain.*
    
You can now close the right pane in tmux.  Further commands will only use a
single pane.

Now would be a good time to review questions 7 and 8, both to confirm or update
your answers and to check your understanding.


# Part 5: File Descriptor Inheritance and File Description Sharing

In this section, you will learn hands-on how file descriptors are inherited by
child processes, and how two different processes with descriptors referencing
the same system-wide file description can write to the same open file.

 16. Modify `fork.c` according to the following:

     - Un-comment the line you added in #11.
     - Comment out _all_ calls to `sleep()`.
     - Comment out _all_ `printf()` calls that print "...done sleeping".
     - Before the call to `fork()`, open the file `fork-output.txt` for writing
       (see the man page for `fopen`).
       - Write "BEFORE FORK\n" to the file before the call to `fork()`.
       - Write "SECTION A\n" to the file in section A. Do the same for sections
	 B, C, and D (but replacing the "A" with "B", "C", and "D",
	 respectively). After each call to `fprintf()` that you use to print
	 these statements, flush the file using `fflush()`;  otherwise, you
	 might find that the strings are written in an unexpected order, due to
         buffering.

     Re-`make` and run the newly recompiled `fork`. *Using `cat`, show the
     contents of the `fork-output.txt` file you created.*

 17. Analyze the file contents, and *briefly describe what you observe about
     the parent and child processes writing to the file.*


# Part 6: Pipes

In this section, you will learn how pipes are created and used to communicate
between different processes.

 18. Modify `fork.c` according to the following:

     - Prior to the call to `fork()`, open a pipe (see the man page for
       `pipe()`).
     - In section B:
       - Close the file descriptor corresponding to the _read_ end of the pipe
         (see the man pages for `pipe()` and `close()`).
       - Create a file stream using the file descriptor corresponding to the
         _write_ end of the pipe (see the man page for `fdopen()`).  Make sure
         it is opened for _writing_.
       - Write "hello from Section B\n" to the newly opened stream (see the man
         page for `fputs()`).
     - In section C:
       - Close the file descriptor corresponding to the _write_ end of the
         pipe (see the man pages for `pipe()` and `close()`).
       - Create a file stream using the file descriptor corresponding to the
         _read_ end of the pipe (see the man page for `fdopen()`).  Make sure
         it is opened for _reading_.
       - Read a single line from the newly opened file stream (see the man page
         for `fgets()`).
       - Print the line retrieved from `fgets()` to stdout.

     Re-`make` and run the newly recompiled `fork`.  *Show the output of your
     program.*


# Part 7: Combining `fork()` and `exec()`

In this section, you will learn hands-on how file descriptors are inherited by
child processes and maintained after a call to `exec`.

 19. Modify `fork.c` according to the following:

     - Copy the contents of the `main()` function in `exec.c` into `fork.c` in
       such a way that the _child_ process created with the call to `fork()`
       runs the `execve()` call with the first command-line argument passed to
       `fork`. The contents you paste should immediately precede the `exit(0)`
       statement called by the child process.
     - Comment out _all_ remaining calls to `sleep()`.

     Re-`make` and execute the following:

     ```
     echo foobar | ./fork /bin/cat
     ```

     *Show the output from running the above pipeline.*


# Part 8: File Descriptor Duplication

In this section, you will learn hands-on how file descriptors can be duplicated
using `dup2()`.

 20. Modify `fork.c` according to the following:

     - Immediately before calling `execve()`, duplicate the file descriptor
       associated with the file stream you opened in connection with
       `fork-output.txt` such that the standard output of the child process
       goes to file descriptor associated with that stream instead (see the man
       pages for `fileno()` and `dup2()`).  Pay special attention to the
       ordering of the arguments passed to `dup2()`, or this will not work
       properly.

     Re-make and execute the following to show that it works:

     ```
     echo foobar | ./fork /bin/cat
     ```

     *Show the output from running this. Also show the contents of
     `fork-output.txt`.*


# Submission

Upload `forkexec.txt` to the assignment page on LearningSuite.
