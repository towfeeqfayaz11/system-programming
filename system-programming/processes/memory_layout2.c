/**
 * Example program to demonstrate the memory layout of a process in C.
 * This code provides detailed explanations of each memory segment:
 * text, initialized data, uninitialized data (BSS), stack, and heap.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global Variables
// ==========================
// Initialized data segment
int g_var = 20;          // Explicitly initialized global variable in initialized data segment

// Uninitialized data segment (BSS)
// Stores global/static variables without explicit initialization, auto-initialized to 0
int g_flag;              // Global variable without an explicit value

// Text Segment
// ==========================
// Global constant string literals are stored here and are read-only.
const char *global_literal = "Global constant string literal";

/**
 * Function to add two numbers (stored in the text segment)
 * Takes two integers and returns their sum.
 */
int add_num(int num_first, int num_second);

int main() { 
    // Stack Segment
    // ==========================
    // Local variables specific to main() are stored here, in main’s stack frame.
    int num1, num2, sum;          // Local integers stored on the stack
    char *pstr;                   // Pointer stored on the stack, points to dynamic memory (heap)
    char *buf = "welcome";        /* Points to a read-only string literal in the text segment.
                                     Modifying *buf will cause a segmentation fault. */

    // Stack Array (stored on stack with initial values)
    char stack_buf[20] = "stackData"; // Array initialized with a string, stored on stack

    // Alternative initializer syntax with braces (works the same for stack)
    char stack_buf_alt[20] = {"stackData"};

    // Uncommenting this will cause a segmentation fault since "welcome" is read-only
    // buf[0] = 'n';

    // Valid modification on stack array since it is writable memory
    strcpy(stack_buf, "newString"); // Copies new data into stack buffer

    // Assigning values to stack variables
    num1 = 10;
    num2 = 20;
    sum = add_num(num1, num2);     // sum is computed and stored on stack
    printf("The result of add_num is: %d\n", sum);

    // Reassigning values and calling add_num() again
    num1 = 100;
    num2 = 200;
    sum = add_num(num1, num2);
    printf("The result of add_num is: %d\n", sum);

    // Heap Segment
    // ==========================
    // Dynamic memory allocation using malloc()
    pstr = malloc(20);             // Allocates 20 bytes on the heap, pointed to by stack variable pstr
    if (pstr == NULL) {
        perror("Failed to allocate memory");
        return 1;                  // Exit if memory allocation fails
    }
    strcpy(pstr, "Hello Heap");    // Copies string into heap memory, which is writable
    printf("String stored in heap: %s\n", pstr);

    // Deallocate heap memory to avoid memory leaks
    free(pstr);                    // pstr points to freed heap memory, should not be accessed further

    return 0;                      // End of main, main’s stack frame is removed
}

/**
 * Function to add two numbers, using a static variable for demonstration.
 * Function arguments and local variables stored on stack,
 * static variable stored in initialized data segment.
 */
int add_num(int num_first, int num_second) {
    // Stack Segment
    int res = 0;                  // Local variable stored on stack

    // Initialized Data Segment
    static int count = 0;         // Static variable in initialized data segment, retains value between calls

    count++;                      // Increment count, persists across function calls
    res = num_first + num_second;

    printf("add_num called %d times.\n", count);
    return res;
}

/**
Explanation of Key Sections:
Text Segment:
Contains all the executable code and read-only data, such as string literals like "welcome"
and "Global constant string literal". Attempting to write to these literals will cause a
segmentation fault since they are stored in a read-only section of memory.

Initialized Data Segment:
Stores explicitly initialized global and static variables (int g_var = 20; and static int count = 0;).
These retain their values throughout the program's execution.

Uninitialized Data Segment (BSS):
Holds uninitialized global and static variables (int g_flag;). These are auto-initialized to 0
by the system, minimizing memory usage for uninitialized data.

Stack Segment:
Contains local variables for each function, including num1, num2, sum, and stack arrays like
stack_buf. Each function call generates a new stack frame, which is removed when the function returns.

Heap Segment:
Allocated dynamically at runtime using malloc() (or similar functions). The pointer pstr points
to a 20-byte block of memory in the heap where "Hello Heap" is stored. It’s essential to free
this memory to avoid leaks.
 */