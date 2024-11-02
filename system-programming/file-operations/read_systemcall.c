/*
man 2 read
the read() system call reads data from open file refered to by the file descriptor.
ssize_t read(int fd, void buf[count], size_t count);
or
ssize_t read(int fd, void *buf, size_t count);

The buffer argument supplies the address of the memory buffer into which the input data is to be placed.
This buffer must be atleast 'count' bytes long

ssize_t -> is an alias for signed integer
size_t  -> is an alias for unsigned integer

NOTE: the read() doesn't allocate any memory rather the user must allocate memory and pass to read()

A successful call to read returns the number of bytes actually read, or 0 if end-of-file is encountered. On error, the usual -1 is returned

NOTE: read() systemcalls are applied on files like regular files, PIPES, sockets, FIFO


*/

#include <fcntl.h>    // For O_RDONLY
#include <unistd.h>
#include <stdio.h>    // For printf, perror
#include <errno.h>    // For errno
#include <stdlib.h>   // For exit()


int main(){
    int fd, sz;
    char buf[21] = {0};

    fd  = open("pre-written-file.txt", O_RDONLY);
    if(fd < 0){
        printf("failed to open file, errno=(%d)\n", fd);
        perror("ERROR");
        exit(1);  // Use exit() with non-zero to indicate an error
    }

    sz = read(fd, buf, 20);
    printf("Call 1: called read. fd = (%d). %d bytes were read.\n", fd, sz);
    buf[sz] = '\0';
    printf("Read butes are as follows: \n<%s>\n", buf);

    printf("\nNote the next set of bytes read rrom file, it is continuous\n");

    sz = read(fd, buf, 15);
    printf("Call 2: called read. fd = (%d). %d bytes were read.\n", fd, sz);
    buf[sz] = '\0';
    printf("Read butes are as follows: \n<%s>\n", buf);
    
    sz = read(fd, buf, 10);
    printf("Call 3: called read. fd = (%d). %d bytes were read.\n", fd, sz);
    if(sz == 0){
        printf("EOF reached\n");
    }

    return 0;

}


// #include <fcntl.h>    // For open() and O_RDONLY
// #include <unistd.h>   // For read() and close()
// #include <stdio.h>    // For printf() and perror()
// #include <stdlib.h>   // For exit()

// #define BUFFER_SIZE 100  // Size of the buffer

// int main() {
//     int fd;
//     ssize_t bytes_read;
//     char buffer[BUFFER_SIZE];

//     // Open the file for reading
//     fd = open("example.txt", O_RDONLY);
//     if (fd == -1) {
//         perror("Failed to open file");
//         exit(1);
//     }

//     // Read the file in a loop until the end
//     while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
//         // Write buffer contents to stdout, ensuring to handle the exact number of bytes read
//         if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
//             perror("Failed to write output");
//             close(fd);
//             exit(1);
//         }
//     }

//     // Check for read error
//     if (bytes_read == -1) {
//         perror("Failed to read file");
//         close(fd);
//         exit(1);
//     }

//     // Close the file descriptor
//     close(fd);

//     return 0;   // Program completed successfully
// }

