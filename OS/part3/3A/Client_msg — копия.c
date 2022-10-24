#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#define MQ_KEY1 1234L
#define MQ_KEY2 2345L
#define MAXMESGDATA 4096

struct mymesg {
	long mesg_len;
	long mesg_type;
	char mesg_data[MAXMESGDATA];
	};

void client(int readid, int writeid);
ssize_t mesg_send(int id, struct mymesg *mptr);
ssize_t mesg_recv(int id, struct mymesg *mptr);

int main(int argc,char **argv)
{
	int readid, writeid;

	if( (writeid=msgget(MQ_KEY1,0666)) <0)
	{
		printf("Client: can not get writeid!\n"); exit(1);
	}
	printf("Client:writeid=%d\n",writeid);

	if((readid=msgget(MQ_KEY2,0666)) <0)
	{
		printf("Client: can not get readid!\n"); exit(1);
	}
	printf("Client: readid=%d\n",readid);

	client(readid,writeid);
/*
	printf("Client: removing identifiers.\n");
  if((msgctl(readid,IPC_RMID, NULL)) < 0)
	{
		printf("Client: can not delete massage queue2!\n"); exit(1);
	}

	if((msgctl(writeid,IPC_RMID, NULL)) <0)
	{ printf("Client: can not delete massage queue1!\n"); exit(1); }
*/
	exit(0);
}

void client(int readid, int writeid)
{
	size_t len;
	ssize_t n;
	struct mymesg ourmesg;
	
	printf("Client:readid=%d writeid=%d\n",readid,writeid);

	fgets(ourmesg.mesg_data,MAXMESGDATA, stdin);
	len=strlen(ourmesg.mesg_data);

	if(ourmesg.mesg_data[len-1]=='\n') len--;
	ourmesg.mesg_len=len;

	ourmesg.mesg_type=1;

	printf("Client: %s\n",ourmesg.mesg_data);

  if(mesg_send(writeid,&ourmesg) == 0)
  {
    printf("Failed to send mesage.\n");
    return;
  }
/*  else
  {

  }

 	
//	printf("Client: before recv!\n");
 // n = mesg_recv(readid, &ourmesg);
  //printf("Client: recieved message: \"%s\"\n",ourmesg.mesg_data);
	while((n= mesg_recv(readid, &ourmesg))>0)
		write(1,ourmesg.mesg_data, n);
*/
}

ssize_t mesg_send(int id, struct mymesg *mptr)
{
   if(msgsnd(id,mptr,mptr->mesg_len,0) == 0)
   {
     mptr->mesg_data[mptr->mesg_len] = '\0';
     printf("client sent message: \"%s\"\n",mptr->mesg_data);
     return(mptr->mesg_len);
   }
   else
   {
    printf("client failed to msgsnd.\n");
    return(0);
   }
  
}

ssize_t mesg_recv(int id, struct mymesg *mptr)
{
  int err = msgrcv(id,mptr,mptr->mesg_len,mptr->mesg_type,0);
  if(err < 0)
  {
    printf("Client: failed to recieve the message. errno:%d\n",errno);
    return 0;
  }
  else
  {
    printf("Client: The message recieved is: %s%d\n",mptr->mesg_data,errno);
    return mptr->mesg_len; 
  }
}

