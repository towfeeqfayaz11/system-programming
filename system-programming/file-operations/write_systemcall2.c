// program to write data to a new file
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

    strcpy(buf, "This is example of O_APPEND:\n");
    int fd = open("new_output.txt", O_WRONLY | O_CREAT | O_APPEND, 0774); // O_TRUNC is the default mode

    //strcpy(buf, "This is example of O_TRUNC:\n");
    // int fd = open("new_output.txt", O_WRONLY | O_CREAT | O_TRUNC); // O_TRUNC is the default mode
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