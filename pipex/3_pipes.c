#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>



int main()
{
    int pid1,pid2,pid3;
    int pipe1[2];
    int pipe2[2];
    if (pipe(pipe1) == -1)
    {
        perror("pipe1");
        exit(1);
    }
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork1");
        exit(1);
    }
    if (pid1 == 0)
    {
        close(pipe1[0]);
        dup2(pipe1[1],STDOUT_FILENO);
        close(pipe1[1]);
        char *av[] = {"ls",NULL};
        execv("/bin/ls",av);
        perror("execv1");
        exit(1);
    }
    if(pipe(pipe2) == -1)
    {
        perror("pipe2");
        exit(1);
    }
    pid2 = fork();
    if (pid2 == 0)
    {
        close(pipe1[1]);
        dup2(pipe1[0],STDIN_FILENO);
        close(pipe1[0]);

        close(pipe2[0]);
        dup2(pipe2[1],STDOUT_FILENO);
        close(pipe2[1]);

        char *av[] = {"grep","pipe.c",NULL};
        execv("/bin/grep",av);
        perror("execv2");
        exit(1);
    }
    pid3 = fork();
    if (pid3 == 0)
    {
        close(pipe1[0]);
        close(pipe1[1]);

        close(pipe2[1]);
        dup2(pipe2[0],STDIN_FILENO);
        close(pipe2[0]);
        char *av[] = {"wc","-c",NULL};
        execv("/bin/wc",av);
        perror("execv3");
        exit(1);
    }
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);
    while (wait(NULL) > 0)
        ;
}