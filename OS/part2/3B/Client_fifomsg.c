#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define MAXMESGDATA 4096

struct mymesg {
	long mesg_len;
	long mesg_type;
	char mesg_data[MAXMESGDATA];
};

#define MESGHDRSIZE 2*sizeof(long)

void client(int readfd, int writefd);
ssize_t mesg_send(int fd, struct mymesg *mptr);
ssize_t mesg_recv(int fd, struct mymesg *mptr);

int main(int argc,char **argv)
{
  int readfd = 0;
  int writefd = 0;

  if( (writefd=open(FIFO1, O_WRONLY))<0)
  {
    printf("Client: can not open FIFO1 for write\n");
          exit(1);
  }
	printf("Client: FIFO1 is opened for write writefd=%d\n",writefd);

  if( (readfd=open(FIFO2, O_RDONLY))<0)
  {
    printf("Client: can not open FIFO2 for read\n");
          exit(1);
  }
	printf("Client: FIFO2 is opened for read readfd=%d\n",readfd);

  client(readfd,writefd);

  close(readfd);
  close(writefd);

  if (unlink(FIFO1) < 0)
  {
     printf("Client: can delete FIFO1\n");
              exit(1);
  }
   
   printf("Client: FIFO1 is deleted!\n");

  if (unlink(FIFO2) < 0)
  {
     printf("Client: can delete FIFO2\n");
              exit(1);
  }
	printf("Client: FIFO2 is deleted!\n");

	printf("Client: end\n");

  exit(0);
}

void client(int readfd, int writefd)
{
	struct mymesg *message = malloc(sizeof(struct mymesg));
  message->mesg_len = 0;
  message->mesg_type = 0;

  //size_t len;
	ssize_t n;

  printf("Enter file name: \n");

	//char buff[LINE_MAX];

	fgets(message->mesg_data,MAXMESGDATA,stdin);
  message->mesg_len=strlen(message->mesg_data);
  message->mesg_data[message->mesg_len-1] = '\0';
  printf("file name: \"%s\"\n",message->mesg_data);
  
  printf("Client: sent message to server: \"%s\"\n",message->mesg_data);
  mesg_send(writefd,message);
  
  mesg_recv(readfd,message);
  printf("Client: recieved message from server: \"%s\"\n",message->mesg_data);
  message->mesg_data[message->mesg_len-1] = '\n';
  message->mesg_data[message->mesg_len] = '\0';
  mesg_send(1,message);
 // printf("client sent message to stdout: \"%s\"\n",message->mesg_data);
}

ssize_t mesg_send(int fd, struct mymesg *mptr)
{
	return(write(fd, mptr,MESGHDRSIZE + mptr->mesg_len));	
}

ssize_t mesg_recv(int fd, struct mymesg *mptr)
{
	ssize_t n;
	size_t len;

	if (( n=read(fd,mptr,MESGHDRSIZE))==0) return(0); //end of file
	else if(n!=MESGHDRSIZE) { printf("Client: error MESGHDRSIZE\n");return(0); }
	if((len=mptr->mesg_len)>0)
		if((n=read(fd,mptr->mesg_data,len))!=len)
		{
			printf("Client: message data expected len %zu got n %zd\n",len,n);
   	            exit(1);		
		}
	return(len);	
}

