// demonstrate zombie process
/*
Zombie Process
Definition: A zombie process is a terminated process that still has an entry in the process table because its parent has not yet collected its exit status.

Behavior: The child process has finished execution, but the parent has not called wait (or similar) to retrieve the exit status.
This leaves a "zombie" entry in the process table, occupying system resources.

Lifecycle: The zombie state remains until the parent either collects the exit status (via wait) or terminates itself, allowing init to clean up the zombie.

Example Scenario: A child process completes, but the parent process is still running and hasn’t used wait to collect the child’s status.
This can happen if the parent is busy or not programmed to handle child termination.


ps aux  | grep Z  // to grep for zombie process
watch -n 0.2 'ps aux | grep Z | grep -v grep'


// zombie state could have been removed from process table if parent would have waited for zombie using wait() / waitpid() syscall.
// but anyways after parent also exits, and init owns the zombie, it will do cleanup of zombie from process table
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t id;
    printf("Parent Process executing before fork() - pid = (%d)\n", getpid());
    id  = fork(); // from this point of code, parent and child processs both execute parallely
    if(id < 0){
        printf("fork failed\n");
        exit(-1);
    }

    if(id > 0){
        sleep(15);
        printf("Parent proces: I have created child process with pid (%d)\n", id);
        printf("Parent proces exited\n");

    }else{ // child process, exiting before parent process and parent doesen't capture its status
        sleep(5);
        printf("child process executing\n");
        printf("child process pid is (%d)\n", getpid());
        printf("creator of child process is (%d)\n", getppid());
    }

    return 0;
}