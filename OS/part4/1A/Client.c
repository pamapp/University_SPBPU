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
/*Получим доступ к разделяемой памяти*/
	if((shmid = shmget(key, sizeof(Message), 0))<0) {
		printf("Ошибка доступа\n"); 
		return 1;
	}
/*Присоединим ее*/
	if((msgptr = (Message *)shmat(shmid, 0, 0))<0){
		printf("Ошибка присоединения\n"); 
		return 1;
	}
/*Получим доступ к семафору*/
	if((semid = semget(key, 2, PERM))<0){
		printf("Ошибка доступа\n"); 
		return 1;
	}
/*Заблокируем разделяемую память*/
	if(semop(semid, &mem_lock[0], 2)<0){
		printf("Невозможно выполнить операцию\n");
		return 1;
	}
/*Уведомим сервер о начале работы*/
	if(semop(semid, &proc_start[0], 1)<0){
		printf("Невозможно выполнить операцию\n");
		return 1;
	}
/*Запишем в разделяемую память сообщение*/
	sprintf(msgptr->buff, "Good luck!\n");
/*Освободим разделяемую память*/
	if(semop(semid, &mem_unlock[0], 1)<0){
		printf("Невозможно выполнить операцию\n");
		return 1;
	}
/*Ждем, пока сервер в свою очередь не освободит разделяемую память*/
	if(semop(semid, &mem_lock[0], 2)<0){
		printf("Невозможно выполнить операцию\n");
		return 1;
	}
/*Отключимся от области*/
	if(shmdt(msgptr)<0){
		printf("Ошибка отключения\n"); 
		return 1;
	}
/*Удалим созданные объекты IPC*/
	if(shmctl(shmid, IPC_RMID, 0)<0){
		printf("Невозможно удалить область\n");
		return 1;
	}

	if(semctl(semid, 0, IPC_RMID)<0){
		printf("Невозможно удалить семафор\n");
		return 1;
	}
	return 0;
}

