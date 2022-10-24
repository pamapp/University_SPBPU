#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int fd, n;
    ssize_t ret;
    char ch;
    fd = open("task_5.txt", O_RDONLY, 0666);
    if (fd < 0) {
        printf("\nCan't open file\n");
        _exit(1);
    }
    if (!fork()) {
        printf("\nStart of child process\n");
        n = 0;
        
        while((n < 3) && ((ret = read(fd, &ch, 1)) > 0)) {
            n++;
            putchar(ch);
        }
        
        printf("\nEnd of child process\n");
        _exit(0);
    } else {
        printf("\nStart of parent process\n");
        int status;
        wait(&status);
        printf("\nContinuation of the parent process\n");
        while((ret = read(fd, &ch, 1)) > 0) {
            putchar(ch);
        }
        printf("\nEnd of parent process\n\n");
    }
    return 0;
}      


