/*
What is a Unix Domain Socket (UDS) File?
- A Unix Domain Socket (UDS) file is a type of inter-process communication (IPC) mechanism that
  allows processes on the same host to communicate with each other. It uses the file system as
  a namespace for identifying the communication endpoint.
- Unlike network sockets (TCP/IP or UDP), Unix domain sockets operate entirely within the kernel,
  making them faster for local IPC since they bypass the overhead of the network stack.


Why Use a Unix Domain Socket File?
Efficiency:
    - No need to go through the network stack.
    - Kernel-managed communication reduces latency and improves throughput.
Bidirectional Communication:
    - Supports stream-oriented (like TCP) or datagram-oriented (like UDP) communication.
File-Based Namespace:
    - The socket is identified by a file path, making it easy to manage and secure using filesystem permissions.
Flexibility:
    - Can handle large amounts of data and complex interactions between processes.



How Does Unix Domain Socket Work?
1. Creation:
    - A Unix domain socket file is created in the filesystem when a process uses the socket() and bind()
      system calls with the AF_UNIX address family.
2. Communication:
    - One process (server) binds to the socket file and listens for incoming connections.
    - Another process (client) connects to the socket file and starts exchanging data.
    - The data transfer happens via kernel buffers, avoiding the overhead of packetization as in TCP/UDP.
3. Closing and Cleanup:
    - After communication, the socket file can be deleted using unlink() to clean up the filesystem.



Where is it Created?
The UDS file is typically created in a directory like /tmp or /var/run to ensure it is accessible and ephemeral.
Example paths:
    - /tmp/my_socket
    - /var/run/my_service.sock


When to Use Unix Domain Sockets?

Use Cases:
    Local IPC for High Performance:
        - Database clients (e.g., MySQL or PostgreSQL) connecting to a local database instance.
    Secure Local Services:
        - Local-only services (e.g., a backend microservice only accessible on the same host).
    Replaces TCP/UDP for Local Communication:
        - When you need bidirectional, fast communication without involving networking overhead.
Avoid When:
    Remote Communication:
        - UDS only works for processes on the same host.
    Simple Data Transfer:
        - For simple, one-time IPC, alternatives like pipes or shared memory may suffice.
    High Traffic Use Across Multiple Hosts:
        - TCP or UDP sockets are necessary for inter-host communication.

*/

// Unix Domain Socket File Implementation

// server code
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SOCKET_PATH "/tmp/uds_example.sock"
#define BUFFER_SIZE 128

int main() {
    int server_fd, client_fd;
    struct sockaddr_un address;
    char buffer[BUFFER_SIZE];

    // Create a socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the address structure
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);

    // Remove existing socket file if any
    unlink(SOCKET_PATH);

    // Bind the socket to the file
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 5) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on %s...\n", SOCKET_PATH);

    // Accept a client connection
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // Receive data from the client
    int received = read(client_fd, buffer, BUFFER_SIZE);
    if (received > 0) {
        printf("Server received: %s\n", buffer);
    }

    // Send a response
    write(client_fd, "Message received!", 18);

    // Cleanup
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH);

    return 0;
}



// client code
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SOCKET_PATH "/tmp/uds_example.sock"
#define BUFFER_SIZE 128

int main() {
    int client_fd;
    struct sockaddr_un address;
    char buffer[BUFFER_SIZE] = "Hello from client!";

    // Create a socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the address structure
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("Connect failed");
        exit(EXIT_FAILURE);
    }

    // Send data to the server
    write(client_fd, buffer, strlen(buffer) + 1);

    // Receive the server's response
    int received = read(client_fd, buffer, BUFFER_SIZE);
    if (received > 0) {
        printf("Client received: %s\n", buffer);
    }

    // Cleanup
    close(client_fd);

    return 0;
}
