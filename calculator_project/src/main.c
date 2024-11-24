#include <stdio.h>

#include "math_addition.h"
#include "math_multiplication.h"
#include "math_division.h"
#include "math_subtraction.h"
#include "math_remainder.h"

int main(int argc, char *argv[]){
    int a, b;
    printf("starting the code...\n");
    printf("Enter two numbers\n");

    printf("enter first number:");
    scanf("%d",&a);
    printf("enter second number:");
    scanf("%d",&b);

    printf("Addition: %d\n", add(a,b));
    printf("Subtraction: %d\n", subtract(a,b));
    printf("Multiplication: %d\n", multiply(a,b));
    printf("Division: %d\n", divide(a,b));
    printf("Remainder: %d\n", remaind(a,b));
    return 0;
}
