#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(void)
{
    key_t key;
    int semid;
    struct sembuf sb;

    sb.sem_num = 0;
    sb.sem_op = -1;
    sb.sem_flg = SEM_UNDO;

    if ((key = ftok(".", 'J')) == -1) {
        perror("ftok");
        exit(1);
    }
    
    if ((semid = semget(key, 1, 0)) == -1) {
        perror("semget");
        exit(1);
    }

    while (1) {
        printf("Number of waiting processes: %d\n", semctl(semid, 0, GETNCNT));
        sleep(3);
    }
    
	return 0;
}

