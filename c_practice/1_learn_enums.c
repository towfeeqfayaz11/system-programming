/**
 * An enum (short for enumeration) in C is a user-defined data type that consists of a set of
   named integer constants. It allows you to create a variable that can hold a predefined set
   of values, making your code more readable and maintainable. Enumerations are often used to
   represent a collection of related constants, which improves clarity in your code.


   Enums can be created in different ways as below
 */

#include <stdio.h>

/*

// code example 1 for enums

enum TaskStatus {
    NOT_STARTED,      // implicitly assigned 0
    IN_PROGRESS,      // implicitly assigned 1
    COMPLETED = 5,    // explicitly assigned 5
    CANCELLED         // implicitly assigned 6 (5+1)
};

int main(){

    printf("NOT_STARTED: (%d)\n", NOT_STARTED);
    printf("IN_PROGRESS: (%d)\n", IN_PROGRESS);
    printf("COMPLETED: (%d)\n", COMPLETED);
    printf("CANCELLED: (%d)\n", CANCELLED);


    enum TaskStatus task = IN_PROGRESS; // Must use 'enum' keyword
    printf("task: (%d)\n", task);
    return 0;
}

*/


// code example 2 for enums

typedef enum {
    RED,          // implicitly assigns 0
    GREEN = 3,    // explicitly assigns 3
    BLUE,         // implicitly assigns 4 (3+1)
    ORANGE        // implicitly assigns 5 (4+1)
} Color;

/**
 * Note: reffer learnC.txt for explaination on typedef
 */

int main(){
    printf("RED: (%d)\n", RED);
    printf("GREEN: (%d)\n", GREEN);
    printf("BLUE: (%d)\n", BLUE);
    printf("ORANGE: (%d)\n", ORANGE);

    Color myColor = GREEN;
    printf("myColor: (%d)\n", myColor);
}

