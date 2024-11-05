// program to demonstrate wait for a specific pid and exit with non blocking wait()
// we can use WNOHANG flag to make waitpid() a non blocking call
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(){
    pid_t cpid, ret_pid;

    int status = 0;
    cpid = fork();
    if(cpid == -1)
        exit(-1);

    if(cpid == 0){
        printf("child-1 executing, its pid = (%d)\n", getpid());
        sleep(20);

        printf("child-1 exited\n");
        exit(0);
    }else{

        printf("parent executing before wait(),\nparent pid is (%d)\n", getpid());
        // ret_pid = waitpid(80, &status, WNOHANG);
        ret_pid = waitpid(cpid, &status, WNOHANG); // here WNOHANG makes it a non blocking call
        if(ret_pid == -1){
            perror("Error is: ");
            printf("\nwaitpid returned error (%d)\n", errno);
        }

        printf("cpid returned is (%d)\n", ret_pid);
        printf("status is (%d)\n", status);

        printf("parent exited\n");
    }

    return 0;

}

/*
Orphaned Process Cleanup:
When a process becomes orphaned (i.e., its parent process terminates while it is still running), it is automatically adopted by init.

init takes over as the parent process of the orphan, and when this orphaned child eventually finishes, init will immediately call wait
(or a similar function) on the process to collect its exit status.

This ensures that the orphaned process does not turn into a zombie when it terminates since init handles the cleanup instantly.


Zombie Process Cleanup:
A zombie process is a child process that has terminated, but its exit status has not been collected by its parent.

Normally, when a parent process calls wait or waitpid for its terminated child, the zombie status is removed as
the exit status is collected.

If the parent fails to call wait (or if the parent itself terminates while zombies exist), the zombie process
will remain in the process table temporarily.

When the parent terminates with zombie children, init will automatically adopt these zombies as orphans.

Immediate Cleanup by init: Once init becomes the new parent of a zombie process, it immediately calls wait
on the zombie, releasing its resources and fully removing it from the process table.

Key Points to Remember
Orphaned Running Process: Adopted by init, and init waits on it when it terminates.
Zombie Process (from terminated parent): Adopted by init, which then immediately performs a wait to fully clean it up.



If the child process is guaranteed to complete after the parent process finishes, using waitpid(cpid, &status, WNOHANG);
in the parent process has little to no significance. Here’s why:

No Zombie Risk: Since the parent will exit first, it cannot wait for the child’s exit status. The child will become
an orphan when the parent exits, and init will adopt and clean it up automatically, preventing it from becoming a zombie.

No State Check Needed: With WNOHANG, waitpid would only check if the child is done without waiting. However,
if the child will always outlive the parent, there’s no need for this check because the child will still be running when the parent finishes.

In short: If the parent process always finishes before the child, waitpid(cpid, &status, WNOHANG); is unnecessary and can be safely omitted.
*/