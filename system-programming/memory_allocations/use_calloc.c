#include <stdio.h>
#include <stdlib.h>

typedef struct User{
    int sal;
    int id;
}user;

int main(){
    user *puser = NULL;
    int count = 10;

    puser = (user *)calloc(10, sizeof(user));
    if(puser == NULL){
        printf("calloc failed\n");
        exit(-1);
    }

    printf("calloc succeeded\n");
    for(count=0; count<10; count++){
        puser[count].id = count;
        puser[count].sal = count + 100;
    }

    for(count=0; count<10; count++){
        printf("user[%d] id = (%d)\n", count, puser[count].id);
        printf("user[%d] salary = (%d)\n", count, puser[count].sal);
    }

    free(puser);

    return 0;
}