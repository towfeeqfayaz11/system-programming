/* demonstration of execv() library function*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    printf("I am main program of program1.c, mypid = (%d)\n", getpid());
    // a null terminated array of character pointers
    char *args[] = {"arg1", "arg2", "arg3", NULL};

    execv("./program2", args); // after this line, first program (program1's) virtual memory is replaced by second program (program2 )
                               // but pid of both will remain same (under same process)
    printf("This line will not be printed...\n");

    return 0;
}


/*
$ gcc program1.c -o program1
$ gcc program2.c -o program2
$ ./program1
*/