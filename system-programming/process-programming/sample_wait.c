#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t cpid;
    int status = 0;
    
    cpid = fork();
    if(cpid == -1)
        exit(-1);

    if(cpid == 0){
        printf("child process executing first with pid = (%d)\n", getpid());
        sleep(10);
        printf("child pid = (%d)\n", getpid());
        exit(3);  // exit status will be in 8 msb bits of 'status' of parent
    }else{
        printf("parent executing before wait() call\n");
        //cpid = wait(NULL);
        cpid = wait(&status);  // here status will have 768 
        printf("wait() in parent done\n Parent pid = (%d)\n", getpid());
        printf("cpid returned is (%d)\n", cpid);
        printf("status is (%d)\n", status);

    }

    return 0;
}

/*
Process termination status (int) 16 bit number
1. status value if  child process has normal exit/termination
   15......8    |     7......0
   XXXXXXXX     |     XXXXXXXX 
   exitStaus    |     0


2. killed by signal
    15......8    |     7   ......0
    unused       |     X   termination signal
                       |
                       |-----> core dump flag


decimal:         768
16 bit binary:   00000011 00000000    // here 3 is  in 8 bit msb


*/