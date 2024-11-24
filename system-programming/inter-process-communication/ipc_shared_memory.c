/*
What is Shared Memory?
Shared Memory is an IPC (Inter-Process Communication) mechanism that allows two or more processes
to share a region of memory for communication. Unlike pipes or message queues, where data is copied
between processes, shared memory enables processes to directly access the same memory space.
This makes shared memory extremely fast compared to other IPC mechanisms.

Key characteristics:
- Direct Access: Processes share the same memory region, eliminating the need for intermediate copying.
- Synchronization: Shared memory itself doesn’t handle synchronization, so mechanisms like
  semaphores or mutexes are typically used to avoid race conditions.
- Kernel Involvement: The kernel is involved only in setting up the shared memory segment,
  not in reading or writing data, which minimizes overhead.

Why Use Shared Memory?
- High Speed: Since data is not copied, but directly read/written to a shared memory
  segment, it is the fastest IPC method.
- Efficient for Large Data: Suitable for sharing large volumes of data that would
  otherwise involve significant overhead if copied via pipes or message queues.
- Flexibility: Processes can implement their own access logic to the shared memory.


How Does Shared Memory Work?
Creation and Access:
    A process creates a shared memory segment using system calls
    (shmget in System V or mmap/shm_open in POSIX).
    Other processes attach to the shared memory segment to access it.

Reading/Writing Data:
    Once a process attaches to the shared memory, it can directly read from
    or write to the memory using standard pointers.Synchronization must be managed separately.

Detachment and Cleanup:
    A process detaches from the shared memory segment using shmdt.The segment is deleted when
    no processes are attached, or explicitly using shmctl.


Where is Shared Memory Created?
- Kernel Space: Shared memory segments are created and managed by the kernel.
  They are identified by a unique key or name.The memory is mapped into the virtual address
  space of the processes that attach to it.


When to Use Shared Memory?
Shared memory is ideal for:
- High-performance applications: When low latency and high throughput are required.
- Large data sharing: To avoid the overhead of copying large volumes of data.
- Producer-consumer patterns: Where one process produces data that another consumes.


When Not to Use Shared Memory?
Avoid shared memory if:
- Synchronization is complex: Without proper synchronization, shared memory can lead to race conditions,
  deadlocks, and data corruption.
- Small data needs to be shared: For small messages, mechanisms like message queues or pipes may be simpler.
- Processes are on different machines: Shared memory only works on the same machine. Use sockets or other
  network-based IPC for cross-machine communication.


How to Implement Shared Memory?
Shared memory can be implemented using System V APIs or POSIX APIs.
System V is older and more widely supported, while POSIX is more modern and user-friendly.
*/

// ----------------------------------------------------------------
// System V Shared Memory Example

// Writer Process (Create and Write Data):
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>

#define SHM_SIZE 1024  // Size of shared memory

int main() {
    key_t key;
    int shmid;
    char *data;

    // Generate a unique key
    key = ftok("shmfile", 65);

    // Create shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to shared memory
    data = (char *)shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Write to shared memory
    printf("Writing to shared memory...\n");
    strncpy(data, "Hello from Writer!", SHM_SIZE);

    // Detach from shared memory
    shmdt(data);

    return 0;
}


// Reader Process (Read Data):
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define SHM_SIZE 1024  // Size of shared memory

int main() {
    key_t key;
    int shmid;
    char *data;

    // Generate the same unique key
    key = ftok("shmfile", 65);

    // Access the shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to shared memory
    data = (char *)shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Read from shared memory
    printf("Data read from shared memory: %s\n", data);

    // Detach from shared memory
    shmdt(data);

    // Optionally, destroy the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

//--------------------------------------------------------------------

// POSIX Shared Memory Example
// POSIX shared memory is simpler and uses file-based semantics. Here’s an example:

// Writer Process (Create and Write Data):
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/posix_shm"
#define SHM_SIZE 1024

int main() {
    int shm_fd;
    char *data;

    // Create shared memory object
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Resize the shared memory
    ftruncate(shm_fd, SHM_SIZE);

    // Map the shared memory into the process address space
    data = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Write data to shared memory
    strncpy(data, "Hello from Writer!", SHM_SIZE);

    // Unmap shared memory
    munmap(data, SHM_SIZE);

    return 0;
}


// Reader Process (Read Data):
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/posix_shm"
#define SHM_SIZE 1024

int main() {
    int shm_fd;
    char *data;

    // Open existing shared memory object
    shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Map the shared memory into the process address space
    data = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Read data from shared memory
    printf("Data read from shared memory: %s\n", data);

    // Unmap shared memory
    munmap(data, SHM_SIZE);

    return 0;
}
