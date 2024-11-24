#include <stdio.h>
#include "math_add.h"

int main(int argc, char *argv[]){
    int a, b;
    printf("starting the code...\n");
    printf("Enter two numbers to get the result for addition and multiplication\n");

    printf("enter first number:");
    scanf("%d",&a);
    printf("enter second number:");
    scanf("%d",&b);

    printf("Result of addition is: (%d)\n", add(a,b));
    //printf("Result of multiplication is: (%d)\n", add(a,b));
    return 0;
}
