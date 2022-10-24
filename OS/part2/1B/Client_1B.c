#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define FIFO “fifo/1”
#define MAXBUFF 80

int main()
{
//	system("clear");
	int writefd, n;

    printf("CLIENT: Starting\n");
    sleep(1);

    /*Получим доступ к FIFO*/
    if ((writefd = open("fifo", O_WRONLY)) < 0) {
        printf("CLIENT: Невозможно открыть FIFO\n");
        return 1;
    }

    printf("CLIENT: Sending message..\n");
    sleep(1);
    
    /*Передадим сообщение серверу FIFO*/
    if (write(writefd, "Hello Server!\n", 14) != 14) {
        printf("CLEINT: Ошибка записи\n");
        return 1;
    }

    printf("CLIENT: Closing\n");
    sleep(1);
    /*Закроем FIFO*/
    close(writefd);

    /*Удалим FIFO*/
    if (unlink("fifo") < 0) {
        printf("CLEINT: Невозможно удалить FIFO\n");
        return 1;
    }

    return 0;
}


