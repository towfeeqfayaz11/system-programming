#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

// allocated in data segemnt
static int gdata = 111;

int main(int argc, char *argv[]){
    // allocated in stack segment
    int istack = 222;
    pid_t childPid;

    switch(childPid = fork()){
        case -1:
            printf("fork() error");
            exit(-1);

        case 0:
            printf("I am child process\n");
            gdata *=3;
            istack *=3;
            printf("pid = (%d), gdata = (%d), istack = (%d)\n", getpid(), gdata, istack);
            sleep(5);
            break;
        
        default:
            printf("I am parent process\n");
            printf("pid = (%d), gdata = (%d), istack = (%d)\n", getpid(), gdata, istack);
            sleep(5);
        break;
    }

    /*
    give child process a chance to execute
    both parent and child come here
    */

   exit(0);
}

/*
NOTE: there is a concept called COW (copy on write),
      In most of modern linux systems. when a fork system is created, there will be a child and parent process,
      but both these processes will point to the same virtual memory rather than having its own virtual memory,
      but when any process tries to change the value of variables stored in virtual memory, then a new page frame of that
      page will be created, this is called copy on the write.
      
      This is used to avoid the unnecessary copying of the complete virtual memory from parent to child process.
      This copy on wirte is added as a node for some extra information 
*/