#include <stdio.h>
#include <stdlib.h>

int main(){
    int *pint = NULL;
    int count = 10;

    pint = (int *)malloc(10 * sizeof(int));
    if(pint == NULL){
        printf("malloc failed\n");
        exit(-1);
    }

    printf("malloc succeeded\n");
    for(count=0; count<10; count++){
        pint[count] = count;
    }

    for(count=0; count<10; count++){
        printf("pint[%d] = (%d)\n", count, pint[count]);
    }

    free(pint);

    return 0;
}