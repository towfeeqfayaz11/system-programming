/* Demo to show SIGUSR signal between child-parent process*/

#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h> 
#include<signal.h>
  

static void signal_handler (int signo)
{
    if (signo == SIGUSR1)
        printf ("Parent: Caught SIGUSR1 in parent!\n");
}

int main() 
{ 
    pid_t cpid; 
    int status = 0;
    int num  = 5;
    cpid = fork();
    if(cpid == -1)
        exit(-1);           /* terminate */

    if(cpid == 0){
        printf("\nChild: Before exec\n");
        execl("./program2","arg1","arg2",NULL);
        printf("\n Child: line is not printed\n");
    } 
    else{   
        if (signal (SIGUSR1, signal_handler) == SIG_ERR) {
            fprintf (stderr, "Cannot handle SIGUSR1!\n");
            exit (-1);
        }
 
        printf("\nParent: Parent executing before wait(), child process created by parent is = (%d)\n",cpid);
        sleep(2);
        //kill is used to send signal from one process to other
        kill(cpid,SIGUSR2);
        cpid = wait(&status); /* waiting for child process to exit*/
        printf("\nParent: wait() in parent done\nParent pid = %d\n", getpid()); 
        printf("\nParent: cpid returned is (%d)\n",cpid);
        printf("\nParent: status is (%d)\n",status);
    }
  
    return 0; 
} 

/*
Program Flow Analysis
========================
program1 (Parent Process)
Fork a Child Process:

cpid = fork(); creates a new child process.
cpid == 0 indicates the child process, which executes the execl() call to replace its code with program2.

Signal Handling for Parent:
signal(SIGUSR1, signal_handler); registers a handler in the parent process for SIGUSR1.
If the parent process receives SIGUSR1, it prints Parent: Caught SIGUSR1 in parent!.

Sleep and Signal:
Parent sleeps for 2 seconds (sleep(2);) to ensure the child process has started.
It sends a SIGUSR2 signal to the child (kill(cpid, SIGUSR2);).

Wait for Child Process:
Parent waits for the child to terminate using wait(&status);.
After the child exits, the parent prints additional status and information about the child process.
------------------------------------------------------
program2 (Child Process)

Replaces Itself:
The execl("./program2", "arg1", "arg2", NULL); replaces the original child process code with program2.
The printf("\n Child: line is not printed\n"); will not execute because execl() replaces the process.

Signal Handling for Child:
signal(SIGUSR2, signal_handler); registers a handler in the child for SIGUSR2.
If the child process receives SIGUSR2, it prints Child: Caught SIGUSR2 in child!.

Signal to Parent:
After processing arguments, the child sends SIGUSR1 to the parent using kill(getppid(), SIGUSR1);.

Child Exit:
After waiting (sleep(10);), the child exits, and the parent is notified via wait().


------------------
Key Observations

Signals Between Processes:
SIGUSR2 is sent by the parent to the child after a delay. If the child has properly registered its signal handler, it will handle the signal and print:


Child: Caught SIGUSR2 in child!
The child sends SIGUSR1 to the parent, and if the parent handler is properly set up, the parent prints:


Parent: Caught SIGUSR1 in parent!
Synchronization:

The sleep calls (sleep(2) in parent and sleep(5) in child) are necessary to give the processes time to set up their respective signal handlers before signals are sent.
Child Termination:

The parent waits for the child to exit using wait(). The status variable holds the exit status of the child.




===================

What Are SIGUSR1 and SIGUSR2?
Definition:

SIGUSR1 and SIGUSR2 are two user-defined signals provided by Unix/Linux systems.
They are not assigned a predefined behavior (like SIGINT or SIGTERM), so you can use them for custom inter-process communication.
Purpose:

These signals are meant for user-defined actions in your programs.
For example, you can use them to notify a parent process about some event in the child process (like a custom handshake or status update).
Why Use Them?

They give flexibility to send signals between processes without overriding system-defined signals like SIGTERM.
They allow processes to "talk" to each other in a structured way.
Why Use kill() to Send Signals?
The kill() function allows one process to send a signal to another process. It's not just for "killing" processes (despite the name). Here’s how it works:

kill() Syntax:
$ kill(pid, signal_number);

pid: The process ID to which you want to send the signal.
signal_number: The signal you want to send (e.g., SIGUSR1, SIGUSR2).

NOTE: kill <pid> ~= kill -15 <pid>   // cli based kill
      kill(pid, signal_number)       // code based kill
*/