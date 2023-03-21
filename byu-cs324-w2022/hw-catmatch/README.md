# catmatch

In this assignment, you will learn and practice basic coding, compilation,
environment, and string searching in C, including basic Input/Output.  Read the
entire assignment before beginning!


# Specification

Your program will be run from the command line in the following way:

```bash
./catmatch filename
```

The `./` at the beginning simply means that you are directing the shell to look
for the program `catmatch` in the current directory (i.e., `.`).  `filename`
indicates that the program will take the file `filename` to read as a
command-line argument.  The program will also look for an environment variable
`CATMATCH_PATTERN`, which is a pattern.

Your program should:

- Print the process ID to standard error (`stderr`)--not standard output
  (`stdout`)--followed by two newlines.
- Open the file specified on the command line
- For each line in the file:
  - read the entire line into a buffer (i.e., "C string"; you will want to
    declare this as an array of `char`);
  - if `CATMATCH_PATTERN` exists as an environment variable, check the line for
    the pattern specified in the environment;
  - print the line to `stdout`, prefaced with `1` or `0` (and a space),
    indicating that the pattern was found or not found, respectively; if the
    `CATMATCH_PATTERN` environment variable is not found, then `0` should be used.

Save your file as `catmatch.c`, and use the following command to compile your
program:

```bash
gcc -o catmatch catmatch.c
```

Your code should compile with no warnings!

The `-o` option names the resulting binary being named `catmatch` (as opposed
to the default, `a.out`).


# Testing


## Manual Testing

Consider the file [lorem-ipsum.txt](lorem-ipsum.txt).  If run with:

```bash
CATMATCH_PATTERN=al ./catmatch lorem-ipsum.txt
```

then the output would be:

```
1234

0 Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor
1 incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis
1 nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
0 Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu
0 fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in
0 culpa qui officia deserunt mollit anim id est laborum.
```

(where `1234` is the process ID)

Try with several different patterns and with and without the `CATMATCH_PATTERN`
environment variable set.  You can check your work with the command-line
program `grep`.  `grep` does not produce the same output, but it can be used as
a sanity check for identifying the lines with specified pattern.


## Automated Testing

For your convenience, a [script](driver.sh) is also provided for automated
testing.  This is not a replacement for manual testing but can be used as a
sanity check.  You can use it by simply running the following, where the
script, `driver.sh`, is in the same directory as `catmatch.c`.

```
./driver.sh
```


# Helps

Reading the man pages for each of the following will make your life easier:

 - `getpid()`
 - `printf()`
 - `fprintf()`
 - `fopen()`
 - `fgets()`
 - `getenv()`
 - `strstr()`
 - `stdout`
 - `stderr`
