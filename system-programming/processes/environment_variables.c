/**
 * each process has access to set/list of strings called environment variables.
 * each of these strings are in form 'name=value'
 * 
 * NOTE: while cli arguments are availabel only to main function in c, the environment variables are available to all functions of the c
 */

#include <stdio.h>
#include <stdlib.h>

extern char **environ;

void my_func();

int main(int argc, char *argv[]){
    char **ep;
    for(ep = environ; *ep != NULL; ep++){
        printf("(%s)\n", *ep);
    }

    my_func();

    for(ep = environ; *ep != NULL; ep++){
        printf("(%s)\n", *ep);
    }
    return (0);
}

void my_func(){
    printf("\ncalling my_func\n\n\n");
    printf("PATH: (%s)\n", getenv("PATH"));
    printf("HOME: (%s)\n", getenv("HOME"));

    printf("setting new env variable\n\n");
    putenv("PARAM1=1024");

    printf("PARAM1: (%s)\n", getenv("PARAM1"));
}

