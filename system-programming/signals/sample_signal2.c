#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// handler for SIGINT and SIGTERM
void signal_handler(int signo){
    if(signo == SIGINT) // SIGINT is when we press ctrl+c
        printf("Caught SIGINT!\n");
    else if(signo == SIGTERM) // when we run `kill -15 <pid>`, SIGTERM occurs since SIGTERM number is 15 
        printf("Caught SIGTERM!\n");
    
    exit(EXIT_SUCCESS);
}

int main(){
    printf("process ID is (%d)\n", getpid());

    if(signal(SIGINT, signal_handler) == SIG_ERR){
        fprintf(stderr, "Cannot handle SIGHUP!\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGTERM, signal_handler) == SIG_ERR){
        fprintf(stderr, "Cannot handle SIGTERM!\n");
        exit(-1);
    }

    // if (signal(999, signal_handler) == SIG_ERR) {
    //     fprintf(stderr, "Cannot handle signal 999!\n");
    //     exit(-1);
    // }

    while(1);
}

/*
The signal() function returns SIG_ERR in the following cases:
    Some signals cannot be caught, blocked, or ignored, such as:
        SIGKILL: Used to forcefully terminate a process (kill -9 <pid>).
        SIGSTOP: Used to stop a process (kill -19 <pid>).
*/