#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static void * threadFunc(void *arg)
{


    char *s = (char *) arg;
    printf("ThreadFunc: %s , printed in threadFunc pid = (%d)\n", s,getpid());
    (void)sleep(15);
    printf("\nthreadFunc: exiting now\n");
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t t1;
    void *res;
    int s;

    s = pthread_create(&t1, NULL, threadFunc, "Hello world");
    if (s != 0)
        perror("Thread create error");
    printf("main thread: Message from main() , pid = (%d)\n",getpid());

    sleep(5);
    printf("\nmain thread: after sleep 5 sec\n");

    exit(0); // if this line eecutes before termination of thread, then thread will be killed as well along with main thread
    //pthread_exit(0); // if instead of exit(), we use, pthread_exit(), then even if main thread exits, other threads will continue to run
}
