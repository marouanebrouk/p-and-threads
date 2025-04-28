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
    if (pid1 == 0)
    {
        close(pipe1[0]);
        dup2(pipe1[1],STDOUT_FILENO);
        close(pipe1[1]);
        char *args[] = {"/bin/ls",NULL};
        execv("/bin/ls",args);
        perror("execv ls");
        exit(1);
    }
    if (pipe(pipe2) == -1)
    {
        perror("pipe2");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork2");
        exit(1);
    }
    if (pid2 == 0)
    {   // ls | grep a.out | wc -l
        close(pipe1[1]);
        dup2(pipe1[0],STDIN_FILENO);
        close(pipe1[0]);

        close(pipe2[0]);
        dup2(pipe2[1],STDOUT_FILENO);
        close(pipe2[1]);

        char *args2[] = {"/bin/grep","a.out",NULL};
        execv("/bin/grep",args2);
        perror("execv");
        exit(1);
    }
    pid3 = fork();
    if (pid3 == -1)
    {
        perror("fork3");
        exit(1);
    }
    if (pid3 == 0)
    { // ls | grep a.out | wc -l
        close(pipe2[1]);
        close(pipe1[1]);
        close(pipe1[0]);
        dup2(pipe2[0],STDIN_FILENO);
        close(pipe2[0]);
        
        char *args3[] = {"usr/bin/wc","-l",NULL};
        execv("/bin/wc",args3);
        perror("execv wc");
        exit(1);
    }
    else
    {
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        wait(NULL);
        wait(NULL);
        wait(NULL);
    }
}