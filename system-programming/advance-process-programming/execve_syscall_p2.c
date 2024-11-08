#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[]){
    char **ep;

    printf("executing execve_syscall_p2\n");

    for(int i=0;i<argc;i++){
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    for(ep = environ; *ep != NULL; ep++){
        printf("environ: %s\n",*ep);
    }

    exit(0);
}