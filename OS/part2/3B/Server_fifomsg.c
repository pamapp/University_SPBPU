#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define MAXMESGDATA 4096

struct mymesg {
	long mesg_len;
	long mesg_type;
	char mesg_data[MAXMESGDATA];
};

#define MESGHDRSIZE 2*sizeof(long)


ssize_t mesg_send(int fd, struct mymesg *mptr);
ssize_t mesg_recv(int fd, struct mymesg *mptr);


void server(int readfd, int writefd);

int main(int argc,char **argv)
{
  int readfd, writefd;

  if( mknod(FIFO1, S_IFIFO | 0666, 0)<0)
  {
          printf("Server: can not create FIFO1 errno:%d\n",errno);
          exit(1);
  }
  printf("Server: FIFO1 is created!\n");
  if( mknod(FIFO2, S_IFIFO | 0666, 0)<0)
  {
          unlink(FIFO1);
          printf("Server: can not create FIFO2\n");
          exit(1);
  }
  printf("Server: FIFO2 is created!\n");

  if( (readfd=open(FIFO1, O_RDONLY))<0)
  {
    printf("Server: can not open FIFO1 for read\n");
          exit(1);
  }
  printf("Server: FIFO1 is opened for read and readfd=%d\n",
      readfd);

  if( (writefd=open(FIFO2, O_WRONLY))<0)
  {
    printf("Server: can not open FIFO2 for write\n");
          exit(1);
  }
  printf("Server: FIFO2 is opened for write and writefd=%d\n",
      writefd);

  server(readfd,writefd);

  exit(0);
}

void server(int readfd, int writefd)
{
  struct mymesg *message = malloc(sizeof(struct mymesg));
  message->mesg_len = 0;
  message->mesg_type = 0;
  
  mesg_recv(readfd,message); 
  printf("Server: recieved message from client: \"%s\"\n",message->mesg_data);
  
  int fd;
  if((fd=open(message->mesg_data,O_RDONLY))<0)
  {
    printf("Server: failed to open file. %d\n",fd);
    return;
  }
  else
  {
    ssize_t n;
    while((n=read(fd,message->mesg_data,MESGHDRSIZE))>0)
    {
      
    }
    
    message->mesg_len = strlen(message->mesg_data);
    message->mesg_data[message->mesg_len-1] = '\0';
    printf("Server: read from file: \"%s\"\n",message->mesg_data);
    mesg_send(writefd,message);
    close(fd);
    printf("Server: end");
  }  
}

ssize_t mesg_send(int fd, struct mymesg *mptr)
{
	return(write(fd, mptr,MESGHDRSIZE+mptr->mesg_len));	
}

ssize_t mesg_recv(int fd, struct mymesg *mptr)
{
	ssize_t n;
	size_t len;
	
	if((n=read(fd,mptr,MESGHDRSIZE))==0)
	{
		printf("Server: end of file\n");
    return(0);		
	}
	else if(n!=MESGHDRSIZE) 
  { 
    printf("Server: error n=%zd is not equal MESGHDRSIZE=%ld\n",n,MESGHDRSIZE); 
    return(0); 
  }
	//printf("Server: n=%d\n",mptr->mesg_len);

  if((len=mptr->mesg_len)>0)
  {
    if((n=read(fd,mptr->mesg_data,len))!=len)
    {
      printf("Server: %s\n",mptr->mesg_data);
      printf("Server: can not read msg\n");
      exit(1);
    }
  }
	return(len);
}

