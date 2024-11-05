// program to demonstrate wait and exit
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t cpid, cpid2;

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
        cpid = wait(&status); //here the parent process doesn't have the control to specify which child process it is waiting on
                              //any of the child process which exited first, will update here
        printf("cpid returned is (%d)\n", cpid);
        printf("status is (%d)\n", status);

        cpid = wait(&status);
        printf("cpid returned is (%d)\n", cpid);
        printf("status is (%d)\n", status);

        printf("parent exited\n");
    }

    return 0;

}