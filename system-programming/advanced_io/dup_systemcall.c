/*
dup() syscall is present in unistd.h
int dup(int oldfd)

- dup() syscall creates a copy of the file descriptor oldfd, using the 
  lowest-numbered unused file descriptor for tha new descriptpr

*/

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int fd, newfd;

    fd = open("newFile.log", O_RDWR | O_CREAT, 0767);
    if(fd == -1){
        printf("open() was failed - errno = (%d)\n", errno);
        perror("ERROR:");
        exit(1);
    }else{
        printf("open() syscall succesfull, inital fd value is (%d)\n", fd);
    }

    newfd = dup(fd);

    printf("new fd value after dup() is (%d), oldfd value of file is (%d)\n", newfd, fd);

    write(newfd, "writing using file descriptor obtained from dup() system call        \n", 71);
    write(fd, "writing using original file descriptor obtained from open() system call \n", 74);

}