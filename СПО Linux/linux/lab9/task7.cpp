#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1023

int main(int argc, char *argv[])
{
	int shmid1, shmid2, shmid3;
	char *data1, *data2, *data3;
    
	if ((shmid1 = shmget(IPC_PRIVATE, SHM_SIZE, 0666 | IPC_CREAT)) == -1
        || (shmid2 = shmget(IPC_PRIVATE, SHM_SIZE, 0666 | IPC_CREAT)) == -1
        || (shmid3 = shmget(IPC_PRIVATE, SHM_SIZE, 0666 | IPC_CREAT)) == -1) {
		perror("shmget");
		exit(1);
	}

	data1 = (char *) shmat(shmid1, 0, 0);
    data2 = (char *) shmat(shmid2, 0, 0);
    data3 = (char *) shmat(shmid3, 0, 0);
    
	if (data1 == (char *)(-1)
        || data2 == (char *)(-1)
        || data3 == (char *)(-1)) {
		perror("shmat");
		exit(1);
	}

    printf("1: %10p\n", data1);
    printf("2: %10p\n", data2);
    printf("3: %10p\n", data3);
    
    *(data1 + SHM_SIZE) = 'f';
    *(data2 + SHM_SIZE) = 's';
    *(data3 + SHM_SIZE) = 't';
    
    printf("1 (1024th byte): %c\n", *(data1 + SHM_SIZE));
    printf("2 (1024th byte): %c\n", *(data2 + SHM_SIZE));
    printf("3 (1024th byte): %c\n", *(data3 + SHM_SIZE));
    
    shmctl(shmid1, IPC_RMID, (struct shmid_ds *) 0);
    shmctl(shmid2, IPC_RMID, (struct shmid_ds *) 0);
    shmctl(shmid3, IPC_RMID, (struct shmid_ds *) 0);
    
    //	/* detach from the segment: */
	if ((shmdt(data1) == -1) || (shmdt(data2) == -1) || (shmdt(data3) == -1)) {
        perror("shmdt");
        exit(1);
    }
    
	return 0;
}

