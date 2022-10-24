#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int variant = 0;

void sig_handler(int sig)
{
	if (sig != SIGINT)
		printf("Signal %i is comming\n",sig);
	else if (variant > 0) {
			printf("SIGINT handled, send it to process..\n");
			signal(SIGINT, SIG_DFL);
			kill(getpid(), sig);
			variant = 2;
			if (variant == 2) {
				printf("SIGINT is being ignored. Killing..\n");
				kill(getpid(),SIGKILL);
				system("ps");
			}
		}
	if (sig != 2) {
		sleep(20);
		printf("I'm coming back\n");
	}
}

void set_action(int sig,struct sigaction* new_action, struct sigaction* old_action)
{
	new_action->sa_handler=sig_handler;
	sigemptyset(&(new_action->sa_mask));
	sigaddset(&(new_action->sa_mask),SIGINT);
	new_action->sa_flags=0;

	if(sigaction(sig,new_action,old_action)<0)
	{
		printf("Action %i is not setted\n",sig);
		exit(0);
	}
	printf("Action %i is setted\n",sig);
	return;
}

void restore_action(int sig, struct sigaction* old_action)
{
	if(sigaction(sig,old_action,NULL)<0)
	{
		printf("We can not restore action!\n");
		exit(0);
	}
	printf("We restored action!\n");
	return;
}

int main(int argc, char **argv)
{
	struct sigaction new_usr1_action,old_usr1_action, new_usr2_action,old_usr2_action;

//	system("clear");
	printf("\nHELLO, my pid = %i\n",getpid());
	variant = atoi(argv[1]);

	set_action(SIGUSR1,&new_usr1_action,&old_usr1_action);
	set_action(SIGUSR2,&new_usr2_action,&old_usr2_action);

	//for choice 1
	if (variant != 0)
		signal(SIGINT,sig_handler);

	if((kill(getpid(),SIGUSR1))==-1)
	{
		printf("Signal send with error!\n");
	}
	else
	{
		printf("Signal send OK!\n");
	}

	sleep(5);

	restore_action(SIGUSR1,&old_usr1_action);
	restore_action(SIGUSR2,&old_usr2_action);

	return 0;
}

