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
//	printf("father: usr1 handler %d\n",sig);
	if(sig == SIGUSR1) {
        printf("father: i receive SIGUSR1(%d) signal\n",sig);
    }
	else {
        printf("father: not my signal\n");
    }
}

void sig_handler_usr2(int sig)
{
//    printf("father: usr2 handler %d\n",sig);
    if(sig == SIGUSR2) {
        printf("father: i receive SIGUSR2(%d) signal\n",sig);
    }
    else {
        printf("father: not my signal\n");
    }
}

int main()
{
	int son_pid, status;
	printf("sig_father %d is starting\n", getpid());
    
	signal(SIGUSR1, sig_handler_usr1);
	signal(SIGUSR2, sig_handler_usr2);
	signal(SIGINT, SIG_DFL);
    signal(SIGCHLD, SIG_IGN);

	if((son_pid = fork()) == 0)
	{
		execl("Sig_son", "Sig_son", NULL);
	}

	sleep(1000);
    
	wait(&status);
    
	return 0;	
}
