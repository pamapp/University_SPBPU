#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO1 "fifo1_2b"
#define FIFO2 "fifo2_2b"
#define MAXLINE 4096

void server(int readfd, int writefd);

int main(int argc,char **argv)
{
    int readfd, writefd;

    printf("Server: starting\n");

    if(mknod(FIFO1, S_IFIFO | 0666, 0)<0)
    {
        printf("Server: can not create FIFO1\n");
        return 1;
    }

	printf("Server: FIFO1 is created!\n");


    if (mknod(FIFO2, S_IFIFO | 0666, 0)<0)
    {
        unlink(FIFO1);
        printf("Server: can not create FIFO2\n");
        return 1;
    }

	printf("Server: FIFO2 is created!\n");

	printf("Server: waiting for client\n");

    if( (readfd=open(FIFO1, O_RDONLY))<0)
    {
      printf("Server: can not open FIFO1 for read\n");
        return 1;
    }

	printf("Server: FIFO1 is opened for read and readfd = %d\n",readfd);

    if( (writefd=open(FIFO2, O_WRONLY))<0)
    {
      printf("Server: can not open FIFO2 for write\n");
        return 1;
    }

	printf("Server: FIFO2 is opened for write and writefd = %d\n",writefd);

    server(readfd,writefd);

    printf("Server: end\n");
    return 0;
}

void server(int readfd, int writefd)
{
	int fd;
	ssize_t n;
	char buff[MAXLINE+1];

	while (1)
		if((n=read(readfd,buff,MAXLINE))!=0)
			break; 
				
	buff[n]='\0';	

	if((fd=open(buff,O_RDONLY))<0)
	{
		printf("\nServer: mistakes, send a report\n");
		char b[] = "ERROR OF OPENING ";
		write(writefd,b,strlen(b));
		n=strlen(buff);
		write(writefd,buff,n);
		write(writefd,"\n",1);
	}
	else
	{
		printf("\nServer: got a message from client\n");
		sleep(1);
		printf("Server: resend a message to client\n");
		while((n=read(fd,buff,MAXLINE))>0)
			write(writefd,buff,n);
		close(fd);
	}
	sleep(1);
}

