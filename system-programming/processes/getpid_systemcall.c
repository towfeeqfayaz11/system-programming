/*
processid and parent processid
*/

#include <unistd.h>
#include <stdio.h>

int main(){
    printf("ProcessID of current process is (%d)\n", getpid());
    printf("Parent ProcessID of current process is (%d)\n", getppid());
    sleep(5);
}