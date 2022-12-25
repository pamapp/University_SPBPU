#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>

int main(int argc, char *argv[])
{
    FILE	*fin, *fout1, *fout2;
    char	buffer[PIPE_BUF];
    int	n;
    
    if (argc < 3) {
        fprintf(stderr, "Usage %s cmd1 cmd2 cmd3\n", argv[0]);
        exit(1);
    }
    
    fin  = popen(argv[1], "r");
    fout1 = popen(argv[2], "w");
    fout2 = popen(argv[3], "w");
    
    while((n = read(fileno(fin), buffer, PIPE_BUF)) > 0)
        write(fileno(fout1), buffer, n);
    
    n = read(fileno(fin), buffer, PIPE_BUF);
    write(fileno(fout2), buffer, n);
    
    pclose(fin);
    pclose(fout1);
    pclose(fout2);
    exit(0);
    return 0;
}

