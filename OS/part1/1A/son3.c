#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void sig_handler_usr1(int sig)
{
    if(sig == SIGUSR1) {
        printf("son3: i receive SIGUSR1(%d) signal\n",sig);
    }
    else {
        printf("son3: not my signal\n");
    }
}

int main()
{
	int son_pid;
	son_pid = getpid();
	printf("son3 %d is starting\n", son_pid);
    
    signal(SIGUSR1, sig_handler_usr1);
    sleep(5);
    printf("son3 end\n");
    return 0;
}
