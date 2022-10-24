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
	int father_pid, son1_pid, son2_pid, son3_pid, status;
	father_pid = getpid();
	printf("father %d is starting\n", father_pid);
 
	if((son1_pid = fork()) == 0)
	{
		execl("son1", "son1", NULL);
	}
    
    sleep(1);
    
    if((son2_pid = fork()) == 0)
    {
        execl("son2", "son2", NULL);
    }
    
    sleep(1);
    
    if((son3_pid = fork()) == 0)
    {
        execl("son3", "son3", NULL);
    }
    
//    sleep(3);
    
    system("echo '\nBefore signals:\n' > file");
    
    system("ps -f >> file");
    
    if((kill(son1_pid, SIGUSR1)) == -1)
    {
        perror("kill");
        return 1;
    }
    else
    {
        printf("father: send signal to son1\n");
    }
    
    sleep(1);
    
    system("echo '\nAfter son1 signal:\n' >> file");
    
    system("ps -f >> file");
    
    if((kill(son2_pid, SIGUSR1)) == -1)
    {
        perror("kill");
        return 1;
    }
    else
    {
        printf("father: send signal to son2\n");
    }
    
    sleep(1);
    
    system("echo '\nAfter son2 signal:\n' >> file");
    
    system("ps -f >> file");
    
    if((kill(son3_pid, SIGUSR1)) == -1)
    {
        perror("kill");
    }
    else
    {
        printf("father: send signal to son3\n");
    }
    
    sleep(3);
    
    system("echo '\nAfter son3 signal:\n' >> file");
    system("ps -f >> file");

    sleep(5);
    wait(&status);
    
    system("echo '\nAfter all signals:\n' >> file");
    system("ps -f >> file");
    
	printf("father end\n");
	return 0;	
}
