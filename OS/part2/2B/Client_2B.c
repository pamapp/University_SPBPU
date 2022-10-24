#include <sys/stat.h>

#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO1 "fifo1_2b"
#define FIFO2 "fifo2_2b"

#define MAXLINE 4096

void client(int readfd, int writefd);

int main(int argc,char **argv)
{
    int readfd, writefd;

	printf("Client: starting\n");
		
    if((writefd=open(FIFO1, O_WRONLY))<0)
    {
        printf("Client: can not open FIFO1 for write\n");
        return 1;
    }

	printf("Client: FIFO1 is opened for write, writefd = %d\n",writefd);


    if( (readfd=open(FIFO2, O_RDONLY))<0)
    {
        printf("Client: can not open FIFO2 for read\n");
        return 1;
    }

	printf("Client: FIFO2 is opened for read, readfd = %d\n",readfd);

    client(readfd,writefd);

    close(readfd);
    close(writefd);

    if (unlink(FIFO1) < 0)
    {
       printf("Client: can delete FIFO1\n");
        return 1;
    }

	printf("Client: FIFO1 is deleted!\n");

    if (unlink(FIFO2) < 0)
    {
        printf("Client: can delete FIFO2\n");
        return 1;
    }

	printf("Client: FIFO2 is deleted!\n");

	printf("Client: end\n");

    return 0;
}

void client(int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	char buff[MAXLINE];

	fputs("Client: Print filename : ",stdout); 
	fgets(buff,MAXLINE,stdin);
	len = strlen(buff);
    
	if(buff[len-1]=='\n')
		len--;
	
	printf("\nClient: Send filename to server\n");
	write(writefd,buff,len); //send to pipe

	sleep(1);
	printf("Client: Got a msg from server -\t");

	//read from another pipe
	while((n=read(readfd,buff,MAXLINE))>0) {
		buff[n] = '\0';
		fputs(buff,stdout);
	}
}

