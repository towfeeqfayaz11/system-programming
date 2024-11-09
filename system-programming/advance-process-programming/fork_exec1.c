/* usage of fork() and exec togerther

# fork is a syscall used to create a child process, where as exec family of function calls
  are the one which replaces the existing program's virtual memory by the new program virtual memory

we will see how combination of fork and exec work (in most usecases, exec is usually used along with fork)
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
  pid_t cpid;
  int status=0, num=5;

  cpid = fork();
  if(cpid == -1)
    exit(-1);    // terminate child
  
  if(cpid == 0){ // inside child
    printf("Before exec\n");
    execl("./fork_exec2", "arg1", "arg2", NULL);
    /*
      sequence of events when above line is executed:
      - in child process we are called execl()
      - before calling execl, there will be two processes in memory (parent and child), with exactly same virtual memory of `fork_exec1`
      - when execl is executed in child process, we are replacing the virutal memory of child by the virtual memory of new process called `fork_exec2`
      - now we will have two seperate and different virtual memories

      - in earlier cases, when we were using only fork, virtual memory of parent and child were similiar

    */
    printf("this line will not be printed\n");
  }else{
    printf("Parent executing before wait(), child process created by parent is = (%d)\n", cpid);
    cpid = wait(&status); // waiting for child process to exit
    printf("wait() in parent done\nparent pid = (%d)\n", getpid());
    printf("cpid returned is (%d)\n", cpid);
    printf("status is (%d)\n", status);

  }

  return 0;
}