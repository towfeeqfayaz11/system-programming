// demo to show command line arguments of a process

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    int count = 0;
    printf("the value of argc is: (%d)\n", argc);

    while(count < argc){
        printf("(%d)the string is (%s)\n", count, argv[count]);
        count++;
    }  
}