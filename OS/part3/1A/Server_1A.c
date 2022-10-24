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
	int msgid, length, n;


	printf("Server: starting\n");
	sleep(1);

	/*Получим ключ*/
	if ((key = ftok("server", 'A')) < 0) { 
		printf("Невозможно получить ключ\n"); 
        return 1;
	}

	printf("Server: got a key\n");
	sleep(1);

	/*Тип принимаемых сообщений*/
	message.mtype = 1L;

	/*Создадим очередь сообщений*/
	if ((msgid = msgget(key,PERM|IPC_CREAT)) < 0){ 
		printf("Невозможно создать очередь\n"); 
        return 1;
	}

	printf("Server: queue was created\n");
	sleep(1);

	printf("Server: wait for client\n");

	/*Примем сообщение*/
	n = msgrcv(msgid, &message, sizeof(message), message.mtype, 0);
	
	printf("Server: try to get a message..\n");
	sleep(1);	
	
	/*Если сообщение поступило, выведем его содержимое на терминал*/
	if(n>0){
		if(write(1, message.buff,n) != n) { 
			printf("Ошибка вывода\n"); 
            return 1;
		}
	}
	else { 
		printf("Ошибка чтения сообщения\n"); 
        return 1;
	}

	/*Удалить очередь должен клиент*/
	printf("Server: terminating\n");
    return 0;
}

