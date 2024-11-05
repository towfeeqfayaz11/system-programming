#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t id;
    printf("Parent process: Executed by parent process before fork() - PID = (%d)\n", getpid());
    id = fork();

    if(id < 0){
        printf("fork() failed\n");
    }
    if(id > 0){
        printf("Parent process: I have created child process with PID = (%d)\n", id);
    }else{
        printf("I am child process, id value is (%d)\n", id);
        printf("Inside child proces, my PID is (%d)\n", getpid());
        printf("Creator of child processis (%d)\n", getppid()); // this line can occasionaly print 1 for below reason

        /*
        n this code, the child process's parent PID (as printed by getppid()) shows 1, which is
        typically the PID of the init process (or systemd on modern Linux systems). This happens
        because the parent process (your original process with PID 12015) has likely exited
        before the child process could print the parent PID. When a process’s parent exits before
        the child, the child is "adopted" by the init process, which has PID 1.

        we can use wait() systemcall for this case, if we want the parent process to wait untill child process completes execution
        */
    }

    return 0;
}