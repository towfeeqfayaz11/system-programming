#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *threadSafe(void *vargp);

int main(){
    printf("Not in the thread\n");

    pthread_t tid;
    pthread_create(&tid, NULL, threadSafe, NULL);
    pthread_join(tid, NULL);

    printf("after thread finished\n");


    return 0;
}

void *threadSafe(void *vargp) {
    printf("Hello from thread, thread will sleep for 5 secs\n");
    sleep(5);
    printf("completed sleeping for 5 secs from thread, exiting from thread\n");
}