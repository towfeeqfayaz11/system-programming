#include <stdio.h>
#include "mysum.h"

int main(){
    printf("Starting main code...!\n");
    int x = 143;
    int y = 327;
    int result = sum(x, y);
    printf("sum of %d and %d is %d\n", x, y , result);
}