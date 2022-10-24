#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "mesg.h"
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int main()
{
	Message message;
	key_t key;
	int msgid, length,n;

	system("clear");
	printf("Client: starting\n");
	sleep(1);	

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

    while (1) {
        char answer[MAXBUFF];
        printf("\tPrint a message to server: ");
        //fgets(answer,MAXBUFF,stdin);
        scanf("%s",answer);

        strcpy(message.buff,answer);
        length = strlen(answer);
        message.mtype = 1L;
        if (answer[length-1] == '\n') {
            length--;
            message.buff[length] = '\0';
        }

        if (msgsnd(msgid, (void*) &message, length, 0) != 0) {
                printf("Client: couldn't send a message to server\n");
                return 1;
            }
        sleep(1);

        if (!strcmp(message.buff,"bye")) {
            printf("Client: you put a 'bye'. Closing..\n");
            sleep(1);
            return 0;
        }

        /*Тип принимаемых сообщений*/
        message.mtype = 2L;

        printf("Client: wait for server..\n");
        /*Примем сообщение*/
        n = msgrcv(msgid, &message, sizeof(message), message.mtype, 0);
        
        printf("Client: try to get a message..\n");
        sleep(1);
        
        /*Если сообщение поступило, выведем его содержимое на терминал*/
        if(n>0) {
            if(write(1, message.buff,n) != n) {
                printf("Ошибка вывода\n");
                return 1;
            }
        }
        else {
            printf("Ошибка чтения сообщения\n");
            return 1;
        }
        
        if (!strcmp(message.buff,"exit")) {
            printf("\nClient: got a command to exit. Do it..\n");
            sleep(1);
            return 0;
        }
        printf("\n");
    }
    return 0;
}

