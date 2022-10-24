#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "mesg.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	Message message;
	key_t key;
	int msgid, length;


	printf("Client: starting\n");
	sleep(1);	

	/*Тип посылаемого сообщения*/
	message.mtype = 1L;

	/*Получим ключ*/
	if ((key = ftok("server", 'A')) < 0) { 
		printf("Невозможно получить ключ\n"); 
        return 1;
	}

	printf("Client: got a key\n");
	sleep(1);

	/*Получим доступ к очереди сообщений*/
	/*очередь уже должна быть создана сервером*/
	if ((msgid = msgget(key, 0)) < 0) { 
		printf("Невозможно получить доступ кочереди\n"); 
        return 1;
	}

	printf("Client: got an access to queue\n");
	sleep(1);

	/*Подготовим сообщение*/
	if ((length = sprintf(message.buff,"IPC Messages!\n")) < 0) { 
		printf("Ошибка копирования в буфер\n"); 
        return 1;
	}

	printf("Client: sending message to queue..\n");
	sleep(1);

	/*Передадим сообщение*/
	if (msgsnd(msgid, (void*) &message, length, 0) != 0) { 
		printf("Ошибка записи сообщения в очередь\n"); 
        return 1;
	}

	printf("Client: deleting queue\n");
	sleep(1);

	/*Удалим очередь сообщений*/
	if (msgctl(msgid, IPC_RMID, 0) < 0) { 
		printf("Ошибка удаления очереди\n"); 
        return 1;
	}

	printf("Client: terminating\n");
    return 0;
}

