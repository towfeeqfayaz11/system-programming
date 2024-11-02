// demo to show command line arguments of a process

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int count = 0;
    printf("the value of argc is: (%d)\n", argc);

    if(strstr(argv[1], "add")){
        printf("addition result = (%d)\n", atoi(argv[2]) + atoi(argv[3]));

    }else if(strstr(argv[1], "sub")){
        printf("subtraction result = (%d)\n", atoi(argv[2]) - atoi(argv[3]));
    }else{
        printf("wrong arguments");
    }
}