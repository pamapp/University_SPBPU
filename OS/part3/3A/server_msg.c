#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <unistd.h>
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
	key_t key1,key2;

	if((readid=msgget(MQ_KEY1, 0666|IPC_CREAT))<0)
	{
		printf("Server: can not get readid!\n");
        return 1;
	}
	printf("Server: read_id = %d\n",readid);

	if((writeid=msgget(MQ_KEY2, 0666|IPC_CREAT))<0)
	{
		printf("Server: can not get readid!\n");
        return 1;
	}
	printf("Server: write_id = %d\n",writeid);

    server(readid,writeid);

    return 0;
}

void server(int readid, int writeid)
{
    FILE *fp;
    ssize_t n;
    struct mymesg ourmesg;

	printf("Server: read_id = %d write_id = %d\n",readid,writeid);
	
	ourmesg.mesg_type=1;

	if((n=mesg_recv(readid, &ourmesg)) == 0)
	{
		printf("Server: can not read file name\n");
        return;
	}
        ourmesg.mesg_data[n]='\0';

	printf("Server: file name is '%s'\n",ourmesg.mesg_data);

    if((fp=fopen(ourmesg.mesg_data,"r"))==NULL)
	{
		printf("Server: can not open file name\n");
                	
	}
	else
	{
		printf("Server: '%s' is opened\n",ourmesg.mesg_data);

        while(fgets(ourmesg.mesg_data, MAXMESGDATA,fp) != NULL)
		{ 
			ourmesg.mesg_len=strlen(ourmesg.mesg_data);
			printf("Server: sending '%s'\n",ourmesg.mesg_data);
			mesg_send(writeid,&ourmesg);
		}
	}
	fclose(fp);
	ourmesg.mesg_len=0;
	mesg_send(writeid,&ourmesg);
	printf("Server: end");
}

ssize_t mesg_send(int id, struct mymesg *mptr)
{
	return(msgsnd(id, &(mptr->mesg_type),mptr->mesg_len, 0));	
}

ssize_t mesg_recv(int id, struct mymesg *mptr)
{
	ssize_t n;

	n=msgrcv(id, &(mptr->mesg_type),MAXMESGDATA,mptr->mesg_type, 0);
	mptr->mesg_len=n;

	return(n);	
}




