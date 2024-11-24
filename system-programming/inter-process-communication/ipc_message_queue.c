/*
What is a Message Queue?
- A Message Queue is an inter-process communication (IPC) mechanism that allows processes to exchange
  discrete messages. Unlike pipes or shared memory, where communication is more direct, message queues
  provide asynchronous, buffered communication. Messages can be sent by one process and stored in the
  queue until another process retrieves them.

Key characteristics:
- Asynchronous: The sender and receiver do not need to interact simultaneously. Messages can be queued and retrieved later.
- Buffered: The kernel manages the queue and buffers the messages.
- Discrete Messages: Data is passed as individual messages, making it easier to structure and manage communication.
- Multiple Recipients: Multiple processes can write to and read from the same queue.


Why Use a Message Queue?
Message queues are useful because they:
- Allow decoupled communication: Processes do not need to be directly connected or running at the same time.
- Preserve message order: Messages are usually retrieved in the order they are sent (FIFO—First In, First Out).
- Support complex communication patterns: By using message types, you can filter messages or have different
  processes handle different types of messages.
- Enable persistence: Messages can persist in the queue until explicitly read, making them suitable
  for asynchronous tasks.


How Does a Message Queue Work?
Creation:
- A message queue is created by a process using the msgget() system call.
- The queue is identified by a unique key or identifier.

Message Sending:
- Processes send messages to the queue using msgsnd(). Each message includes:
    > A type (an integer, often used for categorization or filtering).
    > The message body (the actual data).

Message Receiving:
- Processes read messages from the queue using msgrcv(). They can:
    > Retrieve the next message in the queue (FIFO).
    > Retrieve messages of a specific type.
- Messages remain in the queue until they are read.

Deletion:
- When no longer needed, the queue can be deleted using msgctl() to free system resources.



Where is a Message Queue Created?
- Message queues exist in kernel space.
- They are not file-based (unlike pipes or shared memory). Instead, they are managed
  entirely by the operating system kernel.
- Each message queue is identified by a unique queue ID or key, which is shared among
  the processes that need to communicate.


When to Use Message Queues?
Message queues are ideal for:
- Asynchronous communication: When processes do not need to interact at the same time.
- Complex workflows: When you need to send discrete, structured messages with filtering
  and prioritization capabilities.
- Process decoupling: When you want to allow processes to operate independently of each other.
- Multiple producer-consumer scenarios: When several processes need to write to or read
  from the same communication channel.


When Not to Use Message Queues
You may want to avoid message queues if:
- High throughput is needed: Message queues involve overhead due to kernel management,
  which can slow down communication compared to shared memory.
- Large data needs to be shared: Message queues are not suitable for sharing large
  volumes of data because of size limitations on messages and queues.
- Real-time communication: Since message queues can block processes or involve delays,
  they may not be ideal for real-time applications.
- Cross-machine communication: Message queues are restricted to processes on the same
  machine. For communication between machines, sockets or network-based messaging systems are better.


System V vs POSIX Message Queues
- System V Message Queues:
    - Use the msgget(), msgsnd(), and msgrcv() APIs.
    - Messages are identified by a key and stored in the kernel.
    - Older, more widely supported.

- POSIX Message Queues:
    - Use mq_open(), mq_send(), and mq_receive() APIs.
    - Messages are identified by names (e.g., /myqueue).
    - Provide more features, like notification mechanisms.
    - Limited to newer systems.


Important Details
Blocking vs Non-blocking:
- By default, message queue operations block until they can proceed (e.g., until a
  message is available for reading).
- You can set a flag (IPC_NOWAIT) to make them non-blocking.


Message Size and Queue Limits:
- Each message has a size limit (e.g., 8 KB on Linux).
- The total size of the queue is also limited. These limits can be adjusted via system parameters.

Prioritization:
- Messages can be retrieved based on their type, allowing prioritization or filtering.

Security:
- Access to the queue is governed by permissions. Only processes with the appropriate
  permissions can interact with the queue.
*/


// System V Message Queue
// Here’s an example of two processes communicating via a message queue.
// Creating the Queue and Sending Messages (Writer Process):

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

// Structure for message
struct message {
    long type;          // Message type
    char text[100];     // Message text
};

int main() {
    key_t key;
    int msgid;

    // Generate a unique key
    key = ftok("progfile", 65);

    // Create a message queue and return ID
    msgid = msgget(key, 0666 | IPC_CREAT);

    struct message msg;
    msg.type = 1;  // Message type
    strcpy(msg.text, "Hello, from Writer!");

    // Send message to the queue
    msgsnd(msgid, &msg, sizeof(msg.text), 0);
    printf("Message sent: %s\n", msg.text);

    return 0;
}


/*
// Receiving Messages (Reader Process):
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

// Structure for message
struct message {
    long type;          // Message type
    char text[100];     // Message text
};

int main() {
    key_t key;
    int msgid;

    // Generate a unique key
    key = ftok("progfile", 65);

    // Access the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    struct message msg;

    // Receive the message of type 1
    msgrcv(msgid, &msg, sizeof(msg.text), 1, 0);

    // Display the received message
    printf("Message received: %s\n", msg.text);

    // Destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

*/