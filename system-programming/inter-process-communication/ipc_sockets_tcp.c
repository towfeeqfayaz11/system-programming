/*
What are Sockets?
A socket is an IPC (Inter-Process Communication) mechanism that provides a communication endpoint
for exchanging data between processes. Unlike other IPC methods, sockets support bidirectional
communication, which can occur:
- Locally (on the same machine): Through domain sockets or loopback addresses.
- Remotely (across different machines): Through network protocols like TCP or UDP.


Why Use Sockets?
Flexibility:
Sockets allow communication between processes on the same machine or across a network, making them versatile.

Protocol Independence:
Sockets support both connection-oriented (TCP) and connectionless (UDP) protocols.

Standardized Interface:
Sockets are supported by virtually all operating systems, enabling cross-platform communication.

Reliability:
TCP sockets ensure reliable, ordered, and error-checked delivery of data.

Concurrency:
Sockets enable multiple clients to connect to a server simultaneously.



How Do Sockets Work?
Sockets are based on the client-server model, where:
- The server listens for incoming connections and establishes a communication channel when a client connects.
- The client initiates the connection and communicates with the server.

Steps for Using Sockets
Server Process:
    > Create a socket.
    > Bind it to an address (IP and port).
    > Listen for incoming connections.
    > Accept a connection from a client.
    > Communicate with the client.
    > Close the socket.

Client Process:
    > Create a socket.
    > Connect to the server's address.
    > Communicate with the server.
    > Close the socket.


Where Are Sockets Created?
Kernel Space:
- The socket itself (an abstraction) is managed by the kernel.
- System calls like socket(), bind(), and accept() allocate resources in the kernel to manage communication.
User Space:
- Applications interact with sockets via file descriptors, which represent the communication endpoint in user space.



When to Use Sockets
Sockets are ideal when:
    Processes Are on Different Machines:
    - Sockets are the go-to IPC mechanism for distributed systems.
    Remote Communication Is Required:
    - Sockets support network-based communication.
    Bidirectional and Concurrent Communication:
    - Multiple clients can connect to a single server simultaneously.
    Protocol Support Is Needed:
    - TCP for reliability, UDP for low-latency, and domain sockets for efficient local communication.


When Not to Use Sockets?
    High-Speed Local Communication:
        - Shared memory is faster than sockets for local communication because it avoids the kernel overhead of data transfer.
    Small and Simple Data Transfers:
        - Pipes or message queues may be simpler for straightforward IPC.
    Synchronization Is Needed:
        - Sockets don’t natively provide synchronization; other mechanisms (e.g., semaphores or mutexes) must be used.


Types of Sockets
Stream Sockets (SOCK_STREAM):
    - Use TCP for reliable, ordered communication.
    - Suitable for file transfers, web communication, etc.
Datagram Sockets (SOCK_DGRAM):
    - Use UDP for connectionless, fast communication.
    - Ideal for real-time applications like gaming or video streaming.
Raw Sockets (SOCK_RAW):
    - Provide low-level access to the network for custom protocols.
    - Used in networking tools like ping or traceroute.
Domain Sockets:
    - For processes on the same machine, often faster than TCP/UDP.
    - Used in applications like database servers (e.g., MySQL).


=====================================================
The socket system call in Linux is used to create a socket. Its prototype is as follows:
int socket(int domain, int type, int protocol);


Domain (Address Family)
The first argument specifies the communication domain or address family. It determines the type of addresses the socket
can communicate with. Common options include:
Domain	       Description
AF_INET	       IPv4 Internet protocols. Used for communication over IPv4 networks.
AF_INET6	   IPv6 Internet protocols. Used for communication over IPv6 networks.
AF_UNIX	       Local (Unix domain) socket communication.
AF_LOCAL	   Alias for AF_UNIX.
AF_PACKET	   Low-level access to raw network packets.
AF_NETLINK	   Communication between user space and kernel. Used for system configuration.
AF_X25	       X.25 packet-switching network protocol.
AF_BLUETOOTH   Communication over Bluetooth networks.


Type
The second argument specifies the communication semantics of the socket. It defines how
the socket will behave in terms of data delivery and connection management. Common options include:
Type	       Description
SOCK_STREAM	   Provides reliable, connection-oriented, byte-stream communication (e.g., TCP).
SOCK_DGRAM	   Provides connectionless, unreliable datagram communication (e.g., UDP).
SOCK_RAW	   Allows direct access to lower-level protocols (e.g., ICMP).
SOCK_SEQPACKET Provides connection-oriented, reliable message-based communication with fixed-length messages.
SOCK_RDM	   Reliable datagram communication. Rarely used.
SOCK_PACKET	   Obsolete. Use AF_PACKET instead.



Protocol
The third argument specifies the specific protocol to be used. If set to 0, the system selects
the default protocol for the given domain and type. Common options include:

Protocol	     Description
IPPROTO_TCP	     Transmission Control Protocol (TCP). Default for SOCK_STREAM.
IPPROTO_UDP	     User Datagram Protocol (UDP). Default for SOCK_DGRAM.
IPPROTO_ICMP     Internet Control Message Protocol (ICMP).
IPPROTO_RAW	     Raw IP packets.
0	             Automatically select the default protocol for the given domain and type.


Example Configurations 
1 => (IPv4 TCP Socket (Stream-based communication))
int sock = socket(AF_INET, SOCK_STREAM, 0); // Equivalent to IPPROTO_TCP
    Domain: IPv4 (AF_INET).
    Type: Reliable, connection-oriented communication (SOCK_STREAM).
    Protocol: Default (TCP).

2 => IPv4 UDP Socket (Datagram-based communication)
int sock = socket(AF_INET, SOCK_DGRAM, 0); // Equivalent to IPPROTO_UDP
    Domain: IPv4 (AF_INET).
    Type: Unreliable, connectionless communication (SOCK_DGRAM).
    Protocol: Default (UDP).

3 => Unix Domain Socket (Local communication):
int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    Domain: Unix domain (AF_UNIX).
    Type: Reliable, connection-oriented communication (SOCK_STREAM).
    Protocol: Default (not used for Unix sockets, so 0).

4 => Raw Socket (Custom protocol):
int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    Domain: IPv4 (AF_INET).
    Type: Raw access to lower-level protocols (SOCK_RAW).
    Protocol: Internet Control Message Protocol (IPPROTO_ICMP).


When to Use Each Type:
Use Case	                     Recommended Configuration
Internet-based applications	     socket(AF_INET, SOCK_STREAM, 0) (TCP)
Fast local communication	     socket(AF_UNIX, SOCK_STREAM, 0)
Non-reliable datagram services	 socket(AF_INET, SOCK_DGRAM, 0) (UDP)
Custom protocol development	     socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)
Monitoring network packets	     socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))
*/

// TCP Sockets Example

// server process
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *message = "Hello from server";

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the network interface
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Accept a client connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Read data and respond
    read(new_socket, buffer, 1024);
    printf("Client: %s\n", buffer);
    send(new_socket, message, strlen(message), 0);

    // Close sockets
    close(new_socket);
    close(server_fd);
    return 0;
}


// Client Process
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char *message = "Hello from client";
    char buffer[1024] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send data and receive response
    send(sock, message, strlen(message), 0);
    read(sock, buffer, 1024);
    printf("Server: %s\n", buffer);

    // Close socket
    close(sock);
    return 0;
}