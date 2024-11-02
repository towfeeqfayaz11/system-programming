/*
Demo To Show write() system call

ssize_t -> is an alias for signed integer
size_t  -> is an alias for unsigned integer

*/

#include <unistd.h>
#include <string.h>

int main(){
    size_t len;
    int msg_len = 0;
    char buf[100];

    strncpy(buf, "This is for writing to screen via write() syscall instead of printf library function call\n", 99);
    msg_len = strlen(buf); 
    // fd(posix name)  - details
    // 0(STDIN_FILENO) - FD for STDIN
    // 1(STDOUT_FILENO) - FD for STDOUT
    // 2(STDERR_FILENO) - FD for STDERR
    len = write(1, buf, msg_len);

}