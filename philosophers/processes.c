#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main()
{
    int pid = fork();
    if (pid == -1)
        return -1;
    printf("process id is %d!\n",getpid());
    if (pid != 0)
        wait(NULL);
}