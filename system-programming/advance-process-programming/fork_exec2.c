#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    printf("I am new process called by execl()");
    printf("new program pid = (%d)\n", getpid());

    for(int i=0; i<argc;i++){
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    sleep(20);

    return 0;
}