/*
the write() system call writes data to an opened file
ssize_t write(int fd, const void buf[count], size_t count);
or
ssize_t write(int fd, const void *buf, size_t count);

returns number of bytes written or -1 on error

arguments;
fd - is the handler for file to which the data is to be written
buf - is the address of the data to be written to file via fd
count - is the number of bytes to write file from buffer

the buf must be atleast 'count' bytes long
NOTE: the actual bytes written to file may also be lesser than 'count' bytes. 
ssize_t -> is an alias for signed integer
size_t  -> is an alias for unsigned integer

*/

// program to write data to an exiting file using O_APPEND and O_TRUNC mode
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
    int sz;
    char buf[100];

    /* O_TRUNC  => write to file from beginning, discarding old contents*/
    /* O_APPEND => write the contents of the file from the end of existing file contents*/

    strcpy(buf, "This is example of O_TRUNC:\n");
    int fd = open("output.txt", O_WRONLY | O_TRUNC);

    //strcpy(buf, "This is example of O_APPEND:\n");
    // int fd = open("output.txt", O_WRONLY | O_APPEND);
    if(fd<0){
        perror("Error occured during open");
        exit(1);
    }

    printf("Len of buf is (%d)\n", (int)strlen(buf));
    sz = write(fd, buf, strlen(buf));

    printf("\nwrite() returned (%d)\n", sz);
    close(fd);

    return 0;
}