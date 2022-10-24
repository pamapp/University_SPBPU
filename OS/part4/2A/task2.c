#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include "unpipc.h"

// char	*px_ipc_name(const char *);

int main(int argc,char **argv) {
	int fd,i,nloop;

	char *ptr; sem_t *mutex; nloop=10;
	if((fd=open("home/tvk/IPC/filedata",O_RDONLY))<0) {
		printf("Can not open file name\n");
		return 1;
	}
	printf("File is opened!\n"); 
	ptr=mmap(NULL,sizeof(char),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0); 
	close(fd);
	mutex=sem_open(px_ipc_name("mysem"),O_CREAT|O_EXCL,0 );

	sem_unlink(px_ipc_name("mysem")); 
	setbuf(stdout,NULL);
	
	if(fork()==0) {
		for(i=0;i<nloop;i++) {
			sem_wait(mutex); 
			printf("Child: %c\n",(*ptr)++); 
			sem_post(mutex);
		}
		return 0;
	} 
	for(i=0;i<nloop;i++)
	{
		sem_wait(mutex);
		printf("Parent: %c\n",(*ptr)++);
		sem_post(mutex); 
	}
	return 0;
}