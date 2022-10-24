
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 256

void client(int readfd, int writefd);
void server(int readfd,int writefd);

int main(int argc, char **argv)
{
	int pipe1[2], pipe2[2];
	pid_t childpid;

	pipe(pipe1);
	pipe(pipe2);

    // child
	if((childpid=fork())==0)
	{
		close(pipe1[1]);
		close(pipe2[0]);

		server(pipe1[0],pipe2[1]);
        return 0;
	}
	// parent
	close(pipe1[0]);
	close(pipe2[1]);

	client(pipe2[0],pipe1[1]);

	waitpid(childpid,NULL,0);
    return 0;
}

void client(int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	char buff[MAXLINE];

	fputs("CLIENT: Print filename : ", stdout);
	fgets(buff,MAXLINE,stdin);
    
	len = strlen(buff);
    
	if(buff[len-1] == '\n')
		len--;
	
	printf("\nCLIENT: Send filename to server\n");
	write(writefd, buff, len); //send to pipe

	sleep(1);
	printf("CLIENT: Got a msg from server -\t");
    
	//read from another pipe
	while((n=read(readfd,buff,MAXLINE))>0) {
		buff[n] = '\0';
		fputs(buff,stdout);
	}
}

void server(int readfd,int writefd)
{
	int fd;
	ssize_t n;
	char buff[MAXLINE+1];

    while (1) {
		if((n = read(readfd,buff,MAXLINE))!=0)
			break;
    }
    
	printf("SERVER: Started\n");
    
	buff[n]='\0';
    
	if((fd=open(buff,O_RDONLY))<0)
	{
		char b[] = "ERROR OF OPENING ";
		write(writefd,b,strlen(b));
		n=strlen(buff);
		write(writefd, buff, n);
		write(writefd, "\n", 1);
	}
	else
	{
		while((n=read(fd, buff, MAXLINE))>0)
			write(writefd, buff, n);
		close(fd);
	}
}

