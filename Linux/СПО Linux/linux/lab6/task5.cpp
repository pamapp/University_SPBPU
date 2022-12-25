#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

void signal_handler(int sig)
{
    signal(sig, signal_handler);
    printf("Received %d\n", sig);
    
    if (sig == SIGQUIT) {
        printf("stop");
        exit(3);
    }
}

int main(void)
{
    pid_t parent_pid;
    pid_t child_pid;
    parent_pid = getpid();
    
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    
    if ((child_pid = fork()) == 0) {
        printf("Child send SIGUSR1\n");
        kill(parent_pid, SIGUSR1);
        sleep(2);
        
        printf("Child send SIGUSR2\n");
        kill(parent_pid, SIGUSR2);
        sleep(2);
        
        printf("Child send SIGINT\n");
        kill(parent_pid, SIGINT);
        sleep(2);
        
        while(1){}
    } else {
        sleep(2);
        printf("Parent send SIGUSR1\n");
        kill(child_pid, SIGUSR1);
        sleep(2);
        
        printf("Parent send SIGUSR2\n");
        kill(child_pid, SIGUSR2);
        sleep(2);
        
        printf("Parent send SIGINT\n");
        kill(child_pid, SIGINT);
        sleep(2);
        
        printf("Parent send SIGQUIT\n");
        kill(child_pid, SIGQUIT);
    }

	return 0;
}



