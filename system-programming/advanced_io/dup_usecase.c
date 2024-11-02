/*
dup() syscall usecase - to write the output to a file instead of screen
*/

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int fd, newfd;

    fd = open("newFile1.log", O_RDWR | O_CREAT, 0767);
    if(fd == -1){
        printf("open() was failed - errno = (%d)\n", errno);
        perror("ERROR:");
        exit(1);
    }else{
        printf("open() syscall succesfull, inital fd value is (%d)\n", fd);
    }

    close(1); // close the standard output(screen)
    newfd = dup(fd); // since the fd 1 is already closed, this will assign 
                     // the lowest available fd to newfd here, which is 1.
                     // hence, when printf will try to write to fd 1 (default stdout),
                     // instead of screen it will go to the file being represented by 1
                     // (that is newFile1.log) since fd 1 is a duplicate for fd of newFile1.log


    // newfd = dup2(fd, 1); //equivalent to line 23 and 24, for details reffer dup2() man page
                            // advantage is all steos of dup2() will be performed in atomic manner

    printf("output not written to screen, rather written to file using dup() system call\n");

}