#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

// echo "hello world" > file.txt

int main()
{
    extern char **environ;
    char *av[] = { "/bin/echo" , "so thats for the file" ,NULL};
    int pid = fork();
    if (pid == 0)
    {
        int fd = open("file.txt", O_CREAT | O_WRONLY, 0677);
        dup2(fd,1);
        execve("/bin/echo",av,environ);
    }
    wait(NULL);
}