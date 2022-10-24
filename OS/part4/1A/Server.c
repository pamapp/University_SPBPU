#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "shmem.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	Message	*msgptr;
	key_t	key;
	int	shmid, semid;

	/*Получим ключ. Один и тот же ключ можно использовать как для семафора, так и для разделяемой памяти*/
	if(( key = ftok("server", 'A'))<0) {
		printf("Невозможно получить ключ\n"); 
		return 1;
	}

	/*Создадим область разделяемой памяти*/
	if((shmid = shmget(key, sizeof(Message), PERM|IPC_CREAT))<0) {
		printf("Невозможно создать область\n");
		return 1;
	}

	/*Присоединим ее*/
	if((msgptr = (Message *)shmat(shmid, 0, 0))<0) {
		printf("Ошибка присоединения\n"); 
		return 1;
	}
	/*Создадим группу из двух семафоров:
	Первый семафор – для синхронизации работы с разделяемой памятью
	Второй семафор – для синхронизации выполнения процессов*/
	if((semid = semget(key, 2, PERM|IPC_CREAT))<0) {
		printf("Невозможно создать семафор\n");
		return 1;
	}
	/*Ждем, пока клиент начнет работу и заблокирует разделяемую память*/
	if(semop(semid, &proc_wait[0], 1)<0) {
		printf("Невозможно выполнить операцию\n");
		return 1;
	}
	/*Выведем сообщение на терминал*/
	printf("%s", msgptr->buff);
	/*Освободим разделяемую память*/
	if(shmdt(msgptr)<0) {
		printf("Ошибка отключения\n"); 
		return 1;
	}
	/*Всю остальную работу по удалению объектов сделает клиент*/
	return 0;
}

