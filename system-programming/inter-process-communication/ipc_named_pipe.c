/*
- FIFOs (named pipes) allow communication between unrelated processes
- fifo pipe is created as a file


What is a Named Pipe?
- A named pipe (also known as a FIFO, which stands for First In, First Out) is a special kind of
  inter-process communication (IPC) mechanism that allows data to flow between two or more processes.
- Unlike regular (anonymous) pipes, named pipes have a specific name and exist as a file system object,
  meaning they can be accessed like a regular file. They are called named pipes because they are given
  a name, allowing multiple processes to reference and communicate through the same pipe.

Named Pipe Characteristics:
    Unidirectional: Named pipes are typically unidirectional (data flows in one direction from one
                    process to another).
    File-based: Unlike regular pipes, named pipes are associated with a file path in the file system.
    FIFO (First In, First Out): Data written into a named pipe is read in the same order it is written,
                                preserving the first-in, first-out order.


Why Use Named Pipes?
Named pipes are useful in scenarios where:
- Two processes need to communicate with each other and pass data between them.
- Unrelated processes need a mechanism to communicate and synchronize, without the
  need for shared memory or complex socket setups.
- Persistent communication is required, where the pipe can exist as a file in the
  filesystem even after the processes using it are terminated.

Named pipes are particularly useful because they:
- Allow communication between processes without the need for shared memory or network communication.
- Provide a simple, file-like abstraction, which can be read and written like files.
- Enable communication between unrelated processes on the same machine.
- Are more flexible than anonymous pipes because they persist as files and can be accessed by multiple processes.


How Does a Named Pipe Work?
- Creating a Named Pipe:
  > Named pipes are created using the system call mkfifo() or by using the shell command mkfifo.
  > The pipe is created as a special file in the file system with the specified path.
- Communication via Named Pipe:
  > One process writes data into the pipe using regular file I/O operations (write(), fwrite(), etc.).
  > Another process reads data from the pipe using regular file I/O operations (read(), fread(), etc.).
  > The data is transmitted in a first-in, first-out (FIFO) order, ensuring the sequence of data is preserved.
- Blocking Behavior:
  > Named pipes are blocking by default. If the pipe is empty, the reading process will block until data is
    written into the pipe.
  > Similarly, if the pipe is full and the writing process tries to write more data, it will block until
    space becomes available in the pipe.
- Process Interaction:
  > Named pipes can be used for communication between related processes (parent-child) or unrelated processes
    that both have access to the named pipe file.
  > The writing process sends data to the named pipe, while the reading process retrieves data from it.


Where is a Named Pipe Created?
- A named pipe is created in the file system, usually in a directory that is accessible by the processes
  that need to communicate.
- The named pipe is created using the mkfifo() system call, which creates a special file (a pipe) that
  exists in the file system.
- Named pipes are not files in the traditional sense, but they appear in the filesystem like regular
  files. They are special file types, and the kernel handles them differently.


When to Use Named Pipes?
Named pipes are most useful in the following scenarios:
- Communication between unrelated processes: If two processes that are not directly
  related (not parent-child) need to communicate, named pipes are an excellent choice.
- IPC within the same machine: Named pipes are typically used for inter-process communication
  within the same machine. If communication needs to occur over a network, sockets may be a better choice.
- Sequential data transfer: If you need to ensure that data flows in a first-in, first-out
  (FIFO) manner, named pipes are ideal.
- Process synchronization: If processes need to wait for data to be available or synchronized,
  the blocking behavior of named pipes can be used effectively.



Important Considerations
Blocking Behavior:
- Named pipes have blocking behavior. If a process tries to read from a pipe with no data or write
  to a pipe that's full, it will block until the operation can proceed. This could lead to deadlocks
  if not carefully managed.

File Permissions:
- Named pipes, being regular files, are subject to file permissions. Make sure the processes that
  need to read/write to the pipe have appropriate permissions.

Unidirectional:
- Named pipes are typically unidirectional, meaning data flows in one direction (from a writer
  to a reader). If you need bidirectional communication, you may need two pipes (one for each
  direction).

Buffering:
- Like other IPC mechanisms, named pipes may have internal buffering. If the buffer is full,
  a writing process may block until space is available. This needs to be considered when designing a communication system.
*/


#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/my_fifo_file"

int main() {
    char buffer[50];
    mkfifo(FIFO_NAME, 0666); // Create a named pipe with given permission, can be also created from cli as `mkfifo /tmp/my_named_pipe`

    if (fork() == 0) {
        // Child Process
        int fd = open(FIFO_NAME, O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd);
    } else {
        // Parent Process
        int fd = open(FIFO_NAME, O_WRONLY);
        write(fd, "Hello from parent!", 19);
        close(fd);
    }
    unlink(FIFO_NAME); // Remove the FIFO file
    return 0;
}

//-------------------------------------------
/*
$ mkfifo /tmp/my_pipe

// Writer Process:
// The writer process will send data to the named pipe
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open the named pipe for writing
    int fd = open("/tmp/my_pipe", O_WRONLY);
    if (fd == -1) {
        perror("Error opening pipe for writing");
        return 1;
    }

    // Write data to the pipe
    write(fd, "Hello from Writer!", 18);
    printf("Data written to the pipe\n");

    // Close the pipe
    close(fd);
    return 0;
}




// Reader Process:
// The reader process will read data from the named pipe
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[100];

    // Open the named pipe for reading
    int fd = open("/tmp/my_pipe", O_RDONLY);
    if (fd == -1) {
        perror("Error opening pipe for reading");
        return 1;
    }

    // Read data from the pipe
    read(fd, buffer, sizeof(buffer));
    printf("Data read from pipe: %s\n", buffer);

    // Close the pipe
    close(fd);
    return 0;
}


*/