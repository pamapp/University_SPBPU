#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	int filedes[2];// 0 - read; 1 - write;
	char temp_ch;
	FILE* fout;

//	system("clear");
	
	if(pipe(filedes)<0)
	{
		printf("Father can not create Pipe!\n");
        return 0;
	}
    
	printf("Father created Pipe!\n");
	
	if(fork()==0)
	{
		FILE* fin;
		char ch;
		close(filedes[0]);

		printf("\nChild is working!\n");
		fin=fopen("input.txt","rt");
		while(fscanf(fin,"%c",&ch)==1)
		{
			write(filedes[1],&ch,1);
		}

		fclose(fin);
		close(filedes[1]);
		printf("\nEnd of Child!\n");
        return 0;
	}
	else
	{
		close(filedes[1]);
		//sleep(1);
		printf("\nFather is working again!\n");

		fout=fopen("output.txt","wt");
		printf("From File: ");
		while(read(filedes[0],&temp_ch,1))
		{
			printf("%c",temp_ch);
			fprintf(fout,"%c",temp_ch);
		}

		fclose(fout);
		sleep(2);
		printf("End of Father!\n");
	}
	return 0;
}

