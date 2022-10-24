#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
#include<sys/wait.h>

int fork_func(int in, int out, char *argv) {
    pid_t pid;

    if ((pid = fork()) == 0) {
        if (in != 0) {
            dup2(in, 0);
            close(in);
        }
        
        if (out != 1) {
            dup2(out, 1);
            close(out);
        }
        
        return execlp(argv, argv, NULL);
    }
    
    return pid;
}

int main(int argc, char *argv[]) {
    pid_t pid;
    
    int i, fd[2], in = 0;
    
    for (i = 0; i < argc - 1; ++i) {
        pipe(fd);
        fork_func(in, fd[1], argv[i]);
        close(fd[1]);
        in = fd[0];
    }
    
    if (in != 0) {
        dup2(in, 0);
    }
    
    return execlp(argv[i], argv[i], NULL);
}

//int main(int argc, char *argv[]) {
//    return make_pipes(argc, argv);
//}

