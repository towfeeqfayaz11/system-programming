// demonstration of execve() system call
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    char *argVec[10] = {"welcome", "to", "lsp", NULL}; // argVec is an array of char*
    char *envVec[10] = {"ENV=10", "ENV=20", "ENV=100", NULL};

    execve(argv[1], argVec, envVec);

    printf("This line will not be executed in program..\n");

    exit(0);
}

/*
NOTE: the main advantage of execve() is we can change the environment of the second program,
If we would have otherwise set the environment variables in program1 and then called program2, then those
env variable won't be reflected in program2, because program1 virtual memory is completely replaced by program2,

Thus we have to use above method to set env variables for program2, this not only sets, but replaces all the exiting env of program with passed env variables
*/


/*
$ gcc execve_syscall_p1.c -o execve_syscall_p1
$ gcc execve_syscall_p2.c -o execve_syscall_p2

$ ./execve_syscall_p2 param1 param2

$ ./execve_syscall_p1 execve_syscall_p2

*/