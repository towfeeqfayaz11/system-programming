/*
lseek() systemcall:
A file can be considered as a continuous set of bytes.
There is an internal indicator present, which points to the offset byte if the file.
This offset is used to read/write the next set of bytes/data from file.
This indicator is updated when we do any file operation like read() or write()

lseek is a system call that is used to change the location of the read/write pointer of a file descriptor.
The location can be be set either in absolute or relative terms.

off_t lseek(int fd, off_t offset, int whence);
fd - file descriptor of the open file
offset - the offset pointer (measured in bytes)
whence - the method in which the offset is to be interpretted
    SEEK_SET -> the offset is set to offset bytes (0 + offset)
    SEEK_END -> the offset is set to the size of file plus offset bytes (size_of_file + offset)
    SEEK_CUR -> the offset is set to its current location plus offset bytes (current_pointer + offset)

returns new file offset on success or -1 on error 
(returns the offset of the pointer (in bytes) from the beginning of the file. If the return is -1,
then there was an error in moving the pointer)

off_t is typically an alias for a signed integer type
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
    int sz, seek_pos = 0;
    char buf[100];

    int fd = open("input.txt", O_RDWR);
    if(fd < 0){
        perror("Error occured during open");
        exit(1);
    }

    seek_pos = lseek(fd, 0, SEEK_SET);
    printf("Initial offset position: (%d)\n", seek_pos);

    seek_pos = lseek(fd, 2, SEEK_SET);
    printf("offset position: (%d)\n", seek_pos);

    seek_pos = lseek(fd, 6, SEEK_CUR);
    printf("offset position: (%d)\n", seek_pos);

    sz = read(fd, buf, 10);
    printf("read bytes from file after lseek is=(%d)\n", sz);
    buf[sz] = '\0';
    printf("Read bytes are as follows: \n%s\n", buf);

    seek_pos = lseek(fd, 0, SEEK_END);
    printf("\noffset position after (SEEK_END + 0): (%d) \n", seek_pos);

    strcpy(buf, "New String appended after SEEK_END\n");
    sz = write(fd, buf, strlen(buf));

    close(fd);
    return 0;
}
