#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
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

void server(int readid, int writeid);
ssize_t mesg_send(int id, struct mymesg *mptr);
ssize_t mesg_recv(int id, struct mymesg *mptr);

int main(int argc,char **argv)
{
	int readid, writeid;
	key_t key1, key2;

	printf("Server: HELLO!\n");
	
  if((readid=msgget(MQ_KEY1, 0666|IPC_CREAT))<0)
	{
		printf("Server: can not get readid!\n"); exit(1);
	}
	printf("Server: readid=%d\n",readid);
	
  if((writeid=msgget(MQ_KEY2, 0666|IPC_CREAT))<0)
	{
		printf("Server: can not get readid!\n"); exit(1);
	}
	printf("Server: writeid=%d\n",writeid);

	server(writeid,readid);

	exit(0);
}

void server(int readid, int writeid)
{
	FILE *fp;
	ssize_t n;
	struct mymesg ourmesg;
	
	printf("Server:readid=%d writeid=%d\n",readid,writeid);

	ourmesg.mesg_type=1;

	n = mesg_recv(readid, &ourmesg);
  printf("Server: recieved: \"%s\"\n",ourmesg.mesg_data);
/*  if(n == 0)
	{ 
    printf("** Server: can not read file name **%s\n",strerror(errno)); 
    exit(1); 
  }
  else
  { 
    printf("Server: recieved message \"%s\"\n",ourmesg.mesg_data);
  }
	ourmesg.mesg_data[n]='\0';

	printf("Server: file name: \"%s\"\n",ourmesg.mesg_data);

	if( (fp=fopen(ourmesg.mesg_data,"r"))==NULL)
	{ printf("Server: can not open file name\n"); }
	else
	{
		printf("Server: %s is opened\n",ourmesg.mesg_data);
 
  	while(fgets(ourmesg.mesg_data, MAXMESGDATA,fp) != NULL)
		{ 
			ourmesg.mesg_len=strlen(ourmesg.mesg_data);
			printf("Server: %s\n",ourmesg.mesg_data);
			mesg_send(writeid,&ourmesg);
		}
	}
	fclose(fp);
	ourmesg.mesg_len=0;
	mesg_send(writeid,&ourmesg);*/
}

ssize_t mesg_send(int id, struct mymesg *mptr)
{
  if(msgsnd(id,mptr,mptr->mesg_len,0) > 0)
   {
    printf("Server: failed to msgsnd.\n");
    return(0);
   }
   else
   {
     mptr->mesg_data[mptr->mesg_len] = '\0';
     printf("Server: sent message: \"%s\"\n",mptr->mesg_data);
     return(mptr->mesg_len);
   }
}

ssize_t mesg_recv(int id, struct mymesg *mptr)
{
 msgrcv(id,mptr,mptr->mesg_len,mptr->mesg_type,0);
 // while(msgrcv(id,mptr,mptr->mesg_len,mptr->mesg_type,IPC_NOWAIT)<0)
 // {
 //   printf("Server: waiting...\n");
 // }
 // printf("Server: done waiting.\n");

 // if(err < 0)
 // {
 //   printf("Server: failed to recieve the message. errno:%d\n",errno);
 //   return 0;
 // }
 // else
 // {
 //   printf("Server: The message recieved is: %s%d\n",mptr->mesg_data,errno);
    return mptr->mesg_len; 
 // }
}
