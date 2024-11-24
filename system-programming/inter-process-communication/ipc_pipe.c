/*
- Pipes are used for unidirectional communication between related processes (e.g., parent and child).
- pipe is created in memory

(What) is unidirectional pipe?
- A unidirectional pipe is a simple Inter-Process Communication (IPC) mechanism used to pass
  data between processes. It is called unidirectional because the data flows in only one
  direction—from the writing process to the reading process.


(Why) Use a Unidirectional Pipe?
- Simple Communication: It is one of the simplest and most efficient methods for communication
  between processes on the same machine, particularly when dealing with related processes (like parent-child).
- Low Overhead: Unlike other IPC mechanisms like message queues or sockets, a pipe provides
  low overhead for communication as it uses kernel-managed memory to buffer data.
- Automatic Synchronization: Pipes provide inherent synchronization mechanisms. For example,
  if the reading process is slow and the pipe is full, the writing process will block until
  there is room to write. Similarly, if the reading process tries to read from an empty pipe,
  it will block until data becomes available.


(How) Does a Unidirectional Pipe Work?
- Pipe Creation: A pipe is created using the pipe() system call, which returns two file descriptors:
    One for reading from the pipe (pipefd[0]).
    One for writing to the pipe (pipefd[1]).
- Communication Flow: The writing process writes data to the pipe using the write() system call,
  and the reading process reads from the pipe using the read() system call.
- Blocking and Non-blocking:
  Blocking: By default, pipes block the writing process if the pipe's buffer is full and the reading
            process has not yet consumed the data. Similarly, the reading process blocks if there is
            no data available to read.
  
  Non-blocking: Pipes can be set to non-blocking mode, where both read and write operations return
                immediately if the operation cannot be completed (e.g., if the pipe is empty or full).


(Where) is the Unidirectional Pipe Created?
- Kernel Memory: The pipe is created in the kernel space, not in the user space.
  The kernel manages the buffer that holds the data in the pipe.
- Temporary: The pipe exists only during the lifetime of the processes. Once the
  processes terminate or close the pipe, it is destroyed.


(When) to Use a Unidirectional Pipe?
- Simple Parent-Child Communication: Pipes are ideal when you have a parent and child process
  and want them to communicate. This is common in many applications that require a simple data
  exchange between related processes.

- Low Overhead: If you need a lightweight IPC mechanism without the need for complex setup,
  a pipe is a good choice.

- Sequential Data Flow: If data needs to flow in one direction (e.g., log data being written
  by one process and read by another), pipes are very appropriate.
*/



#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2]; // a pipe has two ends; read end (pipe_fd[0]) and write end (pipe_fd[1])
    char write_msg[] = "Hello from parent!";
    char read_msg[100];
    
    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }
    
    pid_t pid = fork();
    
    if (pid == 0) {  // Child process
        close(pipefd[1]);  // Close the write end of the pipe
        read(pipefd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(pipefd[0]);  // Close the read end of the pipe
    } else {  // Parent process
        close(pipefd[0]);  // Close the read end of the pipe
        write(pipefd[1], write_msg, strlen(write_msg) + 1);  // Write to pipe
        close(pipefd[1]);  // Close the write end after writing
    }
    
    return 0;
}

