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

void client(int readid, int writeid);
ssize_t mesg_send(int id, struct mymesg *mptr);
ssize_t mesg_recv(int id, struct mymesg *mptr);

int main(int argc,char **argv)
{
    int readid, writeid;

    if((writeid=msgget(MQ_KEY1,0666)) <0)
	{
		printf("Client: can not get writeid!\n");
        return 1;
	}
    
	printf("Client: write_id = %d\n",writeid);

    if((readid=msgget(MQ_KEY2,0666)) <0)
	{
		printf("Client: can not get readid!\n");
        return 1;
	}
    
	printf("Client: read_id = %d\n",readid);

        client(readid,writeid);

    if((msgctl(readid,IPC_RMID, NULL)) < 0)
	{
		printf("Client: can not delete massage queue2!\n");
        return 1;
	}

    if((msgctl(writeid,IPC_RMID, NULL)) <0)
	{
		printf("Client: can not delete massage queue1!\n");
        return 1;
	}

    return 0;
}

void client(int readid, int writeid)
{
    size_t len;
    ssize_t n;
    struct mymesg ourmesg;
	
	printf("Client: read_id = %d write_id = %d\n",readid,writeid);
	printf("Enter file name, please:\n");

    fgets(ourmesg.mesg_data,MAXMESGDATA, stdin);
    len=strlen(ourmesg.mesg_data);

    if (ourmesg.mesg_data[len-1] == '\n')
        len--;
    
    ourmesg.mesg_len=len;
 
	ourmesg.mesg_type=1;

	printf("Client: sending %s",ourmesg.mesg_data);

	mesg_send(writeid,&ourmesg);

    while((n = mesg_recv(readid, &ourmesg))>0)
    //n= mesg_recv(readid, &ourmesg);
    	write(1,ourmesg.mesg_data, n);
}

ssize_t mesg_send(int id, struct mymesg *mptr)
{
	return(msgsnd(id, &(mptr->mesg_type),mptr->mesg_len, 0));
}

ssize_t mesg_recv(int id, struct mymesg *mptr)
{
	ssize_t n;

	n = msgrcv(id, &(mptr->mesg_type),MAXMESGDATA,mptr->mesg_type, 0);
	mptr->mesg_len=n;
	printf("\nClient: n = %zd\n",n);

	return(n);	
}




