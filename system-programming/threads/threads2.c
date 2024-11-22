#include <pthread.h>
#include <stdio.h>

void *threadSafe(void *vargp);

int main(){
    printf("Not in the thread\n");

    int NUM_THREADS = 10;
    pthread_t threads[NUM_THREADS];

    for(int i=0; i<NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, threadSafe, (void *)&i);
    }

    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    printf("after all threads finished\n");

    pthread_exit(NULL);
    return 0;
}

void *threadSafe(void *args) {
    int *threadID = (int *)args;
    printf("Hello from thread: (%d)\n", *threadID);
}


/*
NOTES:

Memory Segments and Threads
Code Segment (Text Segment):

Stores the program's compiled machine code.
Common to all threads within a process.
Read-only and shared.
Data Segment (Global and Static Variables):

Stores global and static variables.
Common to all threads within a process.
Read-write and shared.
Heap:

Stores dynamically allocated memory (malloc, new, etc.).
Common to all threads within a process.
Read-write and shared.
Stack:

Each thread has its own stack for storing local variables, function call arguments, and return addresses.
Unique to each thread and not shared.



Where is i stored?

The variable i is a local variable of the main function, and local variables are always stored in the stack of the thread that creates them.

The main function runs in the main thread, so i resides in the stack of the main thread.

Why is i shared across threads?
When you pass (void *)&i to pthread_create, you're passing the address of i in the main thread's stack to the new threads.

All threads dereference this address (&i) to access the value of i.
Since i exists in the main thread's stack (shared memory location passed by address), all threads access the same memory location.
This makes i logically shared among threads, even though it is physically located in the main thread's stack.

======================================


Issue with above code?
# it doesn't print the correct value of i for each thred beacause;

Understanding the Problem
Variable i is shared: The loop variable i is shared among all threads because it's defined in the main function.

Threads use the address of i: When you pass (void *)&i to pthread_create, all threads receive the same memory
address. Each thread dereferences the pointer to get the value of i.

Timing issue: By the time a thread starts execution, the i value may have already changed in the loop.
This causes threads to print incorrect or repeated values.



Possible solutions;

approach 1: Pass i by value
----------------------
#include <pthread.h>
#include <stdio.h>

void *threadSafe(void *vargp);

int main(){
    printf("Not in the thread\n");

    int NUM_THREADS = 10;
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        int *arg = malloc(sizeof(*arg)); // Allocate memory for each thread's argument
        *arg = i; // Store the value of `i` at the allocated memory
        pthread_create(&threads[i], NULL, threadSafe, arg);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("After all threads finished\n");

    pthread_exit(NULL);
    return 0;
}

void *threadSafe(void *args) {
    int threadID = *(int *)args; // Dereference the pointer
    printf("Hello from thread: (%d)\n", threadID);
    free(args); // Free the allocated memory
    return NULL;
}


Explanation:
Allocate memory for each thread: Use malloc to dynamically allocate memory for each thread's copy of i.
Copy the value of i: Assign the value of i to the allocated memory.
Free memory: Ensure you free the memory inside the thread function to avoid memory leaks.
----------------------



approach 2: Use a local array
----------------------
#include <pthread.h>
#include <stdio.h>

void *threadSafe(void *vargp);

int main(){
    printf("Not in the thread\n");

    int NUM_THREADS = 10;
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS]; // Array to store thread arguments

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i; // Store `i` in the array
        pthread_create(&threads[i], NULL, threadSafe, (void *)&thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("After all threads finished\n");

    pthread_exit(NULL);
    return 0;
}

void *threadSafe(void *args) {
    int threadID = *(int *)args;
    printf("Hello from thread: (%d)\n", threadID);
    return NULL;
}



Explanation:
Store thread arguments in an array: Use a fixed-size array (thread_ids) to store the thread IDs.
Pass the array elements: Pass the address of each array element to pthread_create. Since each element has a unique address, threads won't interfere with each other.
----------------------
*/