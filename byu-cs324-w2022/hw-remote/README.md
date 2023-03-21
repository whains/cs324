# Remote Compilation and Execution

The purpose of these exercises is to familiarize you with remote copy,
compilation, and execution, using `scp`, `ssh`, and `tmux`.

 1. Copy `hello.c` to one of the BYU CS lab machines using `scp`:

    ```
    scp hello.c username@schizo.cs.byu.edu:
    ```

    (replace `username` with your BYU CS username)

 2. Log in to one of the CS machines using the following command:

    ```
    ssh username@schizo.cs.byu.edu
    ```
    (again, use your actual username)

 3. Run the following command:

    ```
    tmux
    ```

    Your screen will look similar to how it did before, but note that the shell
    instance corresponding to the prompt you are seeing is running within
    `tmux`, a terminal multiplexer.  The idea is that you can now instantiate
    other shells on the same remote machine, in different windows and panes
    displayed alongside one another, disconnect and re-connect to your `tmux`
    instance on the remote machine, and more.

 4. Type `ctrl`+`b` followed by `"` (double quotation mark).  This will split
    the window in `tmux` horizontally into two panes and create a separate
    shell instance in the lower pane.

 5. Run the following command in the newly created pane:

    ```bash
    echo hello from lower pane
    ```

 6. Type `ctrl`+`b` followed by `%` (percent sign).  This will split the lower
    pane (i.e., where your "focus" is) vertically and create a separate shell
    instance in the new one (i.e., the one on the lower right).

 7. Run the following command in the newly created pane:

    ```bash
    echo hello from lower-right pane
    ```

 8. Type `ctrl`+`b` followed by the left arrow/cursor key.  This will move the
    focus back to the lower-left pane.

 9. Run the following command in lower-left pane, where the focus currently is:

    ```bash
    echo hello again
    ```

 10. Type `ctrl`+`b` followed by the up arrow/cursor key.  This will move
     focus to the upper pane, i.e., the original/first pane that was
     created.

 11. Run `echo upper` in the upper pane:

 12. In the upper pane, run the following to compile and run `hello.c`:

     ```
     gcc -o hello hello.c
     ./hello
     ```

 13. In the upper pane, run the following to see which host you are currently
     running on:

     ```
     hostname
     ```

     Make note of the return value!

 13. Type `ctrl`+`b` followed by `d` to detach from your current tmux instance.

 14. Run the following to log out of the BYU CS machine:

     ```
     exit
     ```

 15. Log in to one of the CS machines using the following command:

     ```
     ssh username@schizo.cs.byu.edu
     ```
     (again, use your actual username)

     Because schizo is not actually a lab machine but simply logs you in to
     _some_ lab machine, this is likely not the lab machine you were working on
     previously--i.e., the one where your `tmux` instance is _still_ running.

 16. Log in to the CS machine on which you were working previously using the
     following command:

     ```
     ssh username@hostname
     ```
     (again, use your actual username and the hostname of the machine you were
     working on previously)

 17. Run the following command:

     ```
     tmux attach
     ```

     This should reattach you to the tmux instance that you were working on
     earlier, and it should look exactly as it did before you detached.

 18. Type `exit` or `ctrl`+`d` in each of the panes in your `tmux` instance, to
     close each shell and (when the last one closes) the `tmux` instance
     itself.  `ctrl`+`d` essentially passes an end-of-file, so the shell knows
     that its input has finished--its signal to terminate!
