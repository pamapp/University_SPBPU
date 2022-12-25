/* The client program  pipe_client.cpp */
#include"p.h"
#include <signal.h>

int n, pr_fifo, pub_fifo;

void signal_handler(int sig)
{
    signal(sig, signal_handler);
    printf("\nReceived %d\n", sig);
    write(fileno(stdout), "\ncmd>", 6);
}

int main()
{
    static char buffer[PIPE_BUF];
    struct message msg;
    /* Make the name for the private FIFO */
    sprintf(msg.fifo_name, "/tmp/fifo %d", getpid());
    /* Generate the private FIFO */
    if (mknod(msg.fifo_name, S_IFIFO | 0666, 0) < 0) {
        perror(msg.fifo_name);
        exit(1);
    }
    if (system("pstree | grep pipe_server > /dev/null") != 0) {
        printf("\nServer started\n");
        system("./pipe_server &");
//        sleep(2);
    }
    /* OPEN the public FIFO for writing */
    if ((pub_fifo=open(PUBLIC, O_WRONLY)) == -1) {
        perror(PUBLIC);
        exit(2);
    }
    while(1) {	/* FOREVER */
        write(fileno(stdout), "\ncmd>", 6);
        memset(msg.cmd_line, 0x0, B_SIZ);	/* Clear first */
        n = read(fileno(stdin), msg.cmd_line, B_SIZ); /* Get cmd */
        
        if(!strncmp("quit", msg.cmd_line, n - 1))
            break;				/* EXIT? */
        
        write(pub_fifo, (char *) &msg, sizeof(msg)); /* to PUBLIC */
        /* OPEN private FIFO to read returned command oputput */
        if((pr_fifo = open(msg.fifo_name, O_RDONLY)) == -1) {
            perror(msg.fifo_name);
            exit(3);
        }
        
        /* READ private FIFO and display on standard error */
        while((n=read(pr_fifo, buffer, PIPE_BUF)) > 0) {
            write(fileno(stderr), buffer, n);
        }
        
        signal(SIGINT, signal_handler);
        close(pr_fifo);
    }
    close(pub_fifo);
    unlink(msg.fifo_name);
}
    
	



