// program to demonstrate wait for a specific pid and exit
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t cpid, cpid2, ret_pid;

    int status = 0;
    cpid = fork();
    if(cpid == -1)
        exit(-1);

    if(cpid == 0){
        printf("child-1 executing, its pid = (%d)\n", getpid());
        sleep(5);

        printf("child-1 exited\n");
        exit(0);
    }else{
        cpid2 = fork();
        if(cpid2 == -1)
            exit(-1);

        if(cpid2 == 0){
            printf("child-2 executing, its pid = (%d)\n", getpid());
            sleep(5);

            printf("child-2 exited\n");
            exit(1);
        }

        printf("parent executing before wait(),\nparent pid is (%d)\n", getpid());
        ret_pid = waitpid(cpid2, &status, 0); // note this is a blocking wait call
        printf("cpid returned is (%d)\n", ret_pid);
        printf("status is (%d)\n", status);

        ret_pid = waitpid(cpid, &status, 0); // note this is a blocking wait call
        printf("cpid returned is (%d)\n", ret_pid);
        printf("status is (%d)\n", status);

        printf("parent exited\n");
    }

    return 0;

}

/*
using waitpid(), parent process has a control one which child process to wait on, unlike wait() where parent doesn't have
control on whcih child process to wait on rather the child process which completes first returns.

Thus wait() and waitpid() gives process synchronization between the parent and child process.
Process synchronization is a method in which we can control the process, so that they don't give the result, whhich is not acceptable
*/