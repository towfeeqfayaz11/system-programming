#include <pthread.h>
#include <stdio.h>

void *threadSafe(void *vargp);

int main(){
    printf("Not in the thread\n");

    int NUM_THREADS = 10;
    pthread_t threads[NUM_THREADS];

    for(int i=0; i<NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, threadSafe, (void *)&i);
    }

    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    printf("after all threads finished\n");

    pthread_exit(NULL);
    return 0;
}

void *threadSafe(void *args) {
    int *threadID = (int *)args;
    printf("Hello from thread: (%d)\n", *threadID);
}