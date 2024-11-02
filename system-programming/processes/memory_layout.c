/**
 * example program to demonstrate the different memory segment of a process
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function declaration
int add_num(int num_first, int num_second);

int g_var = 20; // initialized data segment
int g_flag; // uninitialized data segment

// this code will be stored in text segment as read only memory
int main(){ // stack frame of main function - stack segment
    int num1, num2, sum; // num1, num2, sum are part of stack frame of main()
    char *pstr; //pstr is part of stack frame of main()

    char *buf = "welcome"; /* "welcome" string is stored in text segment where as variable pointer buf is stored in stack fram of main() */
    char stack_buf[20] = {"stackData"}; // stack_buf is stored on stack frame and it contains value "stackData"

    //buf[0] = 'n'; // this will cause segmentation fault , as buf[0] tries to write to text segment, which is read only
    strcpy(stack_buf, "newString"); // this is possible because it is stored on stack

    num1 = 10; // 10 is stored on stack
    num2 = 20; // 20 is stored on stack
    sum = add_num(num1, num2); // value of sum is stored on stack

    printf(" tge result of add is (%d)\n", sum);

    num1 = 100;
    num2 = 200;
    sum = add_num(num1, num2);
    printf(" tge result of add is (%d)\n", sum);

    pstr = malloc(20); // heap segment, pstr points to 20 bytes on heap, but location of pstr itself is part of stack fram of main()
    strcpy(pstr, "Hello");
    print("string stored is (%s)\n", pstr);
}


// function arguments num_first, num_second stored on stack
int add_num(num_first, num_second){ // stack fram of add_num funcion - stack segment
    int res = 0; // stored on stack
    static int count = 0; // stored in initialized data segment

    count  = count + 1;

    res = num_first  + num_second;

    printf("number of tims the function add_num is called is (%d)", count);
    return (res);
}

/**
 * when a function returns, all data belonging to that function will become invalid or in other words stack fram of that function is deleted
 * so stack acts as growing when new function is called and shrinks when function returns back to calling function
*/