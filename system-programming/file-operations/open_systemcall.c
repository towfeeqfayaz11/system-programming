/*
open() system call details;
int open(const char *filepath, int flags, int mode);

params:
pathname: path to file which we want to open

flags:
    O_RDONLY
    O_WRONLY
    O_RDWR
    O_CREAT

mode: specifies the file creation with access permissions 
      mode can be ommited if O_CREAT is not set as flag

return: if error occures, open() returns -1 and errno is set accordingly.
        Otherwise returns least non zero value which is called file descriptor.
        thus going forward all read/write opens on file are done via returned file descriptor
        most common errors are; EACCES, EEXIST, EISDIR 
*/

// open system call is declared in  fcntl.h library
// fcntl.h: defines necessary macros and flags that control how files are opened and interacted with.
// some common flags are;
   // O_RDONLY :- read only
   // O_WRONLY :- write only
   // O_RDWR   :- read and write
   // O_CREAT  :- create file if doesn't exist


#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h> // S_IRWXU|S_IRWXG|S_IROTH are defined in this header file,however gcc will implicitly include headers through other headers

// int main(){
//     int fd = open("pre-written-file.txt", O_RDONLY);
//     if(fd == -1){
//         printf("opne() was faild; errno=(%d)\n", errno);
//         perror("Error");
//     }else{
//         printf("opne( syscall executed successfully, the file descriptor of opened file is (%d)\n", fd);
//     }

// }


//------------------------------------------------


// int main(){
//     // open the file for both reading and writing if exists else create and open in
//     // read/write mode (taking help of bitwise or)
    
//     // int fd = open("new_file.txt", O_RDWR | O_CREAT, 0774); // 0774 is octal starting with 0
//     int fd = open("new_file.txt", O_RDWR | O_CREAT, S_IRWXU|S_IRWXG|S_IROTH);

//     /*
//     when you try to create file, the group permission will not get write permission because;

//     The file is being created with read and execute permission for the group because the umask setting
//     is likely subtracting the write permission from the group. You can adjust your umask to control how
//     file permissions are applied when files are created.

//     you can verify umask while by running command;
//     umask -> will show current umask value
//     e.g;
//     $ umask
//     0002

//     it can be temporarily overwritten as;
//     $ umask 0000

//     */
//     if(fd == -1){
//         printf("open() was faild; errno=(%d)\n", errno);
//         perror("Error");
//         /*
//         errno is a global variable defined in <errno.h>. It is used by system calls and library
//         functions to indicate what error occurred when they return an error.

//         perror() is a standard library function defined in <stdio.h>. It takes a custom string
//         (in your case, "Error") and prints it to standard error, followed by a textual description
//         of the error associated with the current value of errno.
//         */
//     }else{
//         printf("open( syscall executed successfully, the file descriptor of opened file is (%d)\n", fd);
//     }

// }

//------------------------------------------------------

int main(){
    int fd = open("new_file.txt", O_RDWR | O_CREAT | O_EXCL, 0774);
    /*
    O_EXCL is a flag used in combination with O_CREAT to ensure exclusive creation of a file.
    If the file doesn't exist, it will create a new file with the specified permissions.
    
    O_EXCL is Used with O_CREAT, it ensures that the file is created only if it doesn't
    already exist. If the file already exists, open() will fail, and the error EEXIST
    will be set in errno

    It ensures that the operation is atomic in the sense that no other process can create
    or open the same file between the open() call and the check for its existence.
    */
    if(fd == -1){
        printf("opne() was faild; errno=(%d)\n", errno);
        perror("Error");
    }else{
        printf("opne( syscall executed successfully, the file descriptor of opened file is (%d)\n", fd);
    }

}