#define MAXBUFF 80
#define PERM 0666

/*Определим структуру сообщения*/
typedef struct our_msgbuf {
	long mtype;
	char buff[MAXBUFF];
} Message;

