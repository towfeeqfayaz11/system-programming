/*
#include <signal.h>

- sighandler_t signal(int signo, sighandler_t my_handler)
  :- first paramter is signal number, 2nd paramter is function pointer
- void my_handler(int signo)
- when a signal is delivered to a process, using signal(), the signal can either perform default action or ignore the particular signal.
- SIG_DFL: set the behaviour of the signal given by signo to its default. For example, in the case of SIGPIPE, the process will terminate
- SIG_IGN: ignore the signal given by signo

*/