/*
#include <signal.h>

- sighandler_t signal(int signo, sighandler_t my_handler)
  :- first paramter is signal number, 2nd paramter is function pointer
- void my_handler(int signo)

- when a signal is delivered to a process, using signal() the signal can
  either perform default action or ignore the particular signal or or handle the signal with a custom handler
- SIG_DFL: set the behaviour of the signal given by signo to its default.
  For example, in the case of SIGPIPE, the process will terminate
- SIG_IGN: ignore the signal given by signo

*/


#include<stdio.h> 
#include<signal.h>
#include <unistd.h>

void handle_sigint(int sig){
  printf("I will not exit...(%d)\n", sig);
}

int main() 
{ 
    // Set default behavior for SIGINT
    signal(SIGINT, handle_sigint);  // SIG_DFL / SIG_IGN / custom_handler_function

    while (1) 
    { 
        printf("hello world\n"); 
        sleep(1); 
    } 

    return 0; 
} 
