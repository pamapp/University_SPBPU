#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define FIFO “fifo/1”
#define MAXBUFF 80

int main()
{
//	system("clear");
	int readfd, n;
	char buff[MAXBUFF]; /*буфер для чтения данных из FIFO*/

    /*Создадим специальный файл FIFO с открытыми для всех правами доступа на чтение и запись*/

    if (mknod("fifo", S_IFIFO | 0666, 0) < 0) {
        printf("SERVER: Невозможно создать FIFO\n");
        return 1;
    }

    printf("SERVER: waiting for a message from client\n");

    /*Получим доступ к FIFO*/
    if ((readfd = open("fifo", O_RDONLY)) < 0) {
        printf("SERVER: Невозможно открыть FIFO\n");
        return 1;
    }

    /*Прочитаем сообщение и выведем его на экран*/

    while((n = read(readfd, buff, MAXBUFF)) > 0)
        if(write(1, buff, n) != n) {
            printf("Ошибка вывода\n");
            return 1;
        }

    /*Закроем FIFO, удаление FIFO – дело клиента*/
    printf("\n");
    close(readfd);
    return 0;
}

