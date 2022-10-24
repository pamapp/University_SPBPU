#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>

#define BUFFSIZE 4096
#define BUFFNAME "/buffer3_a"
#define SEMNAME "/mysem3_a"

int main()
{
    sem_t* mutex;
    char* buf;
    int fd;
    size_t len;
    int a;

    if (fork())
    {

        //Инициализируем и открываем семафор
        if ((mutex = sem_open(SEMNAME, O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED)
        {
            fprintf(stderr, "client: Can not create semaphore\n");
            return 1;
        }
        sem_getvalue(mutex, &a);
        fprintf(stdout, "client: Semaphore created. Value: %d\n", a);
        
        //Инициализируем разделяемую память
        if ((fd = shm_open(BUFFNAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) < 0)
        {
            fprintf(stderr, "client: Can not create shared memory object\n");
            sem_close(mutex);
            return 1;
        }
        fprintf(stdout, "client: Shared memory object created\n");
        
        //Обрезаем до заданного размера
        if (ftruncate(fd, BUFFSIZE) < 0)
        {
            fprintf(stderr, "client: Can not resize shared memory\n");
            sem_close(mutex);
            close(fd);
            return 1;
        }
        fprintf(stdout, "client: Resized to %d bytes\n", BUFFSIZE);

        //Отражаем sm в памяти 
        if ((buf = mmap(NULL, BUFFSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) < 0)
        {
            fprintf(stderr, "client: Can not map shared memory\n");
            sem_close(mutex);
            close(fd);
            return 1;
        }
        fprintf(stdout, "client: Shared memory mapped\n");
        close(fd);
        
        sem_wait(mutex);
        sleep(1);

        //Читаем имя файла
        fprintf(stdout, "client: Enter file name: ");
        fscanf(stdin, "%s", buf);

        //Записываем его в разделяемую память
        fprintf(stdout, "client: Sending file name: %s\n", buf);
        sem_post(mutex);

        fprintf(stdout, "client: Ready to receive data\n");
        sleep(1);

        //Считываем данные из разделяемой памяти
        do
        {
            sem_wait(mutex);
            len = strlen(buf);
            fprintf(stdout, "client: %s\n", buf);
            sem_post(mutex);
            sleep(1);
        } while(len == BUFFSIZE - 1);

        sem_close(mutex);
        sem_unlink(SEMNAME);
        munmap(buf, BUFFSIZE);
        return 0;
    }
    else
    {
        FILE *f;

        //Инициализируем и открываем семафор
        if ((mutex = sem_open(SEMNAME, O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED)
        {
            fprintf(stderr, "server: Can not create semaphore\n");
            return 1;
        }
        sem_getvalue(mutex, &a);
        fprintf(stdout, "server: Semaphore opened. Value: %d\n", a);

        //Открываем разделяемую память
        if ((fd = shm_open(BUFFNAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) < 0)
        {
            fprintf(stderr, "server: Can not open shared memory object\n");
            sem_close(mutex);
            return 1;
        }
        fprintf(stdout, "server: Shared memory object opened\n");
        
        //Отражаем sm в памяти 
        if ((buf = mmap(NULL, BUFFSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) < 0)
        {
            fprintf(stderr, "server: Can not map shared memory\n");
            sem_close(mutex);
            close(fd);
            return 1;
        }
        fprintf(stdout, "server: Shared memory mapped\n");
        close(fd);
        
        //Получаем имя файла
        fprintf(stdout, "server: Receiving file name: ");
        sem_wait(mutex);

        fprintf(stdout, "%s\n", buf);

        f = fopen(buf, "r");

        if (!f)
        {
            fprintf(stdout, "server: Sending error message.\n");
            strcpy(buf, "no such file\0");
            sem_post(mutex);
            sem_close(mutex);
            munmap(buf, BUFFSIZE);
            return 1;
        }
        //Передаваем его содержимое в разделяемую память
        while(len = fread(buf, sizeof(char), BUFFSIZE - 1, f))
        {
            buf[len] = '\0';
            sem_post(mutex);
            sleep(1);
            sem_wait(mutex);
        }
        sem_post(mutex);
        sem_close(mutex);
        munmap(buf, BUFFSIZE);
        fclose(f);

        return 0;
    }
}
