// demonstrate orphan process
/*
Orphan Process
Definition: An orphan process is a running process whose parent has terminated.

Behavior: When the parent exits before the child, the child process is "orphaned" and is automatically
adopted by the init process (or systemd in modern systems), which becomes its new parent.

Lifecycle: The process continues running as usual and is fully managed by init, which will eventually
collect its exit status when it terminates.

Example Scenario: A child process is performing a long-running task, and its parent process exits or crashes before the task completes.
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

    if(id > 0){ // parent process, exiting before child process
        printf("Parent proces exited\n");
        return (0);

    }else{ // child process
        printf("child process executing\n");
        printf("child process pid is (%d)\n", getpid());
        sleep(10);
        printf("I am child process, id value is (%d)\n", id);
    }

    return 0;
}