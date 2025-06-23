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
        int fd = open("file.txt", O_CREAT | O_WRONLY | O_APPEND, 0677);
        dup2(fd,1);
        execve("/bin/echo",av,environ);
    }
    wait(NULL);
}
// ls | pwd | cat | pwd | cat | pwd | cat | wc -l | wc -w | wc -l | cat /dev/random | head -n 5| wc -l | a