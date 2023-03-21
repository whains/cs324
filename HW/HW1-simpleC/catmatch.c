//Part 1 - "man" hunt

    /*
1) What are the numbers associated with the manual sections for executable programs, system calls, and library calls, respectively?

1 Executable programs
2 System calls
3 Library calls

2) Which section number(s) contain an entry for open?

2

3) What three #include lines should be included to use the open() system call?

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

4) Which section number(s) contain an entry for socket?

2 & 7

5) Which socket option "Returns a value indicating whether or not this socket has been marked to accept connections with listen(2)"?

socket(7)

6) How many sections contain keyword references to getaddrinfo?

gai.conf (5)         - getaddrinfo(3) configuration file
getaddrinfo (3)      - network address and service translation
getaddrinfo_a (3)    - asynchronous network address and service translation

7) According to the "DESCRIPTION" section of the man page for string, the functions described in that man page are used to perform operations on strings that are null-terminated

8) What is the return value of strcmp() if the value of its first argument (i.e., s1) is greater than the value of its second argument (i.e., s2)?

A positive value
*/


//Part 2 - remote compilation and execution

// I completed the TMUX exercise from Part 2


//Part 3 - catmatch

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *fptr;

    fprintf(stderr, "getpid: %ld getppid: %ld\n\n", (long)getpid(), (long)getppid());

    fptr = fopen(argv[1], "rb");

    char line[256];
    char *envvar;
    int num, count, i, j;

    while (fgets(line, sizeof(line), fptr)) {
   	 num = 0;

	   if (getenv("CATMATCH_PATTERN")) {
      envvar = getenv("CATMATCH_PATTERN");

      for (i = 0; i < strlen(line);) {
         j = 0;
         count = 0;
         while ((line[i] == envvar[j])) {
           count++;
           i++;
           j++;
         }
         if (count == strlen(envvar)) {
           num++;
           count = 0;
         }
         else {
           i++;
		     }
        }
      }

  	  printf("%d ", num);
  	  printf("%s", line);
    }

    fclose(fptr);

    return 0;

}
