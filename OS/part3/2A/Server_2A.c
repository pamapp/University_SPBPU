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

int msgid;

void sig_handler_int(int sig)
{
	printf("\nServer: got a SIGINT. deleting queue..\n");
	sleep(2);
	if (msgctl(msgid, IPC_RMID, 0) < 0) { 
		printf("Server: Can't delete queue!\n"); 
		exit(1);
	}
	
	printf("Server: queue was deleted. Closing server..\n");
	sleep(1);
	signal(SIGINT,SIG_DFL);
	exit(0);	
}

int main()
{
	Message message;
	key_t key;
	int length, n;

	system("clear");
	printf("Server: starting\n");
	sleep(1);
	signal(SIGINT,sig_handler_int);

    /*Получим ключ*/
	if ((key = ftok("server", 'A')) < 0) { 
		printf("Невозможно получить ключ\n"); 
        return 1;
	}

	printf("Server: got a key\n");
	sleep(1);

	/*Создадим очередь сообщений*/
	if ((msgid = msgget(key,PERM|IPC_CREAT)) < 0){ 
		printf("Невозможно создать очередь\n"); 
        return 1;
	}

	printf("Server: queue was created\n");
	sleep(1);

    while (1) {
        /*Тип принимаемых сообщений*/
        message.mtype = 1L;

        printf("Server: wait for client..\n");
        /*Примем сообщение*/
        n = msgrcv(msgid, &message, sizeof(message), message.mtype, 0);
        
        printf("Server: try to get a message..\n");
        sleep(1);
        
        /*Если сообщение поступило, выведем его содержимое на терминал*/
        if(n>0) {
            if(write(1, message.buff,n) != n) {
                printf("Ошибка вывода\n");
                kill(getpid(),SIGINT);
                return 1;
            }
        }
        else {
            printf("Ошибка чтения сообщения\n");
            kill(getpid(),SIGINT);
            return 1;
        }
        
        if (!strcmp(message.buff,"exit")) {
            printf("\nServer: got a command to exit. Do it..\n");
            length = strlen("exit");
            if (msgsnd(msgid, (void*) &message, length, 0) != 0) {
                printf("Server: couldn't send exit to clients\n");
                kill(getpid(),SIGINT);
            }
            sleep(2);
            kill(getpid(),SIGINT);
        }

        char answer[MAXBUFF];
        printf("\n\tPrint an answer to clients: ");
        //fgets(answer,80,stdin);
        scanf("%s",answer);

        strcpy(message.buff,answer);
        length = strlen(answer);
        message.mtype = 2L;
        if (answer[length-1] == '\n') {
            length--;
            message.buff[length] = '\0';
        }

        if (msgsnd(msgid, (void*) &message, length, 0) != 0) {
            printf("Server: couldn't send an aswer to clients\n");
            kill(getpid(),SIGINT);
        }
        sleep(1);
    }

	printf("Server: terminating\n");
    return 0;
}

