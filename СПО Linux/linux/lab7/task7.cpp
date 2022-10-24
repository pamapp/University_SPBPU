/*
** semdemo.cpp -- demonstrates semaphore use like a file locking mechanism
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MAX_RETRIES 10

int initsem(key_t key, int nsems)  /* key from ftok() */
{
    int i;
    union semun arg;
    struct semid_ds buf;
    struct sembuf sb;
    int semid;

    semid = semget(key, nsems, IPC_CREAT | IPC_EXCL | 0666);

    if (semid >= 0) { /* we got it first */
        sb.sem_op = 1; sb.sem_flg = 0;
        arg.val = 1;

        printf("press Enter\n");
        
        getchar();

        for(sb.sem_num = 0; sb.sem_num < nsems; sb.sem_num++) {
            /* do a semop() to "free" the semaphores. */
            /* this sets the sem_otime field, as needed below. */
            if (semop(semid, &sb, 1) == -1) {
                int e = errno;
                semctl(semid, 0, IPC_RMID); /* clean up */
                errno = e;
                return -1; /* error, check errno */
            }
        }

    } else if (errno == EEXIST) { /* someone else got it first */
        int ready = 0;

        semid = semget(key, nsems, 0); /* get the id */
        if (semid < 0) return semid; /* error, check errno */

        /* wait for other process to initialize the semaphore: */
        arg.buf = &buf;
        for(i = 0; i < MAX_RETRIES && !ready; i++) {
            semctl(semid, nsems-1, IPC_STAT, arg);
            if (arg.buf->sem_otime != 0) {
                ready = 1;
            } else {
                sleep(1);
            }
        }
        if (!ready) {
            errno = ETIME;
            return -1;
        }
    } else {
        return semid; /* error, check errno */
    }

    return semid;
}


int main(void)
{
    key_t key;
    int semid;
    char u_char = 'J';
    struct sembuf sb;
    char sign = '\n';
    
    sb.sem_num = 0;
    sb.sem_op = -1;  /* set to allocate resource */
    sb.sem_flg = SEM_UNDO;

    if ((key = ftok(".", u_char)) == -1) {
        perror("ftok");
        exit(1);
    }

    /* grab the semaphore set created by initsem: */
    
    if ((semid = initsem(key, 1)) == -1) {
        perror("initsem");
        exit(1);
    }
    
    while (sign != 's') {
        printf("\n");
        printf("Press Enter to lock: ");
        sign = getchar();
        if (sign == 's') {
            printf("Process stop by 'S'");
            exit(1);
        }
        printf("Trying to lock...\n");
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(1);
        }
        printf("Locked.\n");
        printf("Press Enter to unlock: ");
        sign = getchar();
        if (sign == 's') {
            printf("Process stop by 'S'");
            exit(1);
        }
        sb.sem_op = 1; /* free resource */
        if (semop(semid, &sb, 1) == -1) {
            perror("semop");
            exit(1);
        }
        printf("Unlocked\n");
    }

    return 0;
}

//Попытайтесь улучшить программу semdemo.cpp, например, предоставив процессу возможность после освобождения ресурса становиться снова в очередь на повторное его занятие (а не завершаться), организовав при этом завершение процесса по вводу какого-либо символа.
