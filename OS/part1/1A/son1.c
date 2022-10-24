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
    printf("son1 %d is starting\n", son_pid);
    signal(SIGUSR1, SIG_DFL);
    sleep(3);
    printf("son1 end\n");
    return 0;
}
