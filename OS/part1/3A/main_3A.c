#include <pthread.h>
#include <stdio.h>
#include <signal.h>

#include <sys/stat.h>

#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

long count = 0;
int c = 0; //choose option
pthread_t t1, t2;

static void sig_hndl(int sig)
{
	printf("\nGot a signal SIGUSR1 (id = %i)\n",sig);
	sleep(1);
	printf("Thread2: Exiting\n");
	pthread_exit(NULL);
}

void* thread1 (){     
	while (count < 10) {
		++count;
		printf("Thread_1:  Count is now:  %li\n",count);
		sleep(1);
		if (count > 5 && c >= 2)
			pthread_kill(t2,SIGUSR1);
	}
	printf("	Thread_1 ends\n");
	pthread_exit(0);
}

void* thread2 (){ 
	if (c == 2)
		signal(SIGUSR1,SIG_DFL);
	else if (c == 3)
		signal(SIGUSR1,sig_hndl);
	while (count < 10) {
		++count;
		printf("Thread_2:  Count is now:  %li\n",count);
		sleep(1);
	}
	printf("	Thread_2 ends\n");
	pthread_exit(0);
}

int main()
{
	printf("Choose option :\n\t1 - Kill process, 2 - kill thread_2, 3 - handle SIGUSR1 in thread_2\nPrint : ");
	scanf("%d",&c);

	pthread_create(&t1, NULL, thread1,NULL);
	sleep(1);
	pthread_create(&t2, NULL, thread2,NULL);

	if (c == 1) {
		sleep(2);
		printf("\nMain thread closed\n");
		kill(getpid(),SIGINT);
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

    return 0;
}
