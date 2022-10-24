#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
	int son_pid;
	son_pid = getpid();
	printf("sig_son %d is starting\n", son_pid);
    
	// if((kill(getppid(), SIGUSR1)) == -1)
	// {
 //       perror("kill");
 //       return 1;
 //   }
	// else
	// {
 //       printf("son: send signal to Father\n");
 //       return 0;
 //   }
}
