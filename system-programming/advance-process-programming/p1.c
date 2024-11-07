/* demonstration of execl() library function*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    printf("I am main process pid = (%d)\n", getpid());
    execl("./p2", "arg1", "arg2", "arg3", NULL); // after this line, first program (p1's) virtual memory is replaced by second program (p2 )
                                                 // but pid of both will remain same (under same process)
    printf("This line will not be printed...\n");

    return 0;
}


/*
$ gcc p1.c -o p1
$ gcc p2.c -o p2
$ ./p1
*/