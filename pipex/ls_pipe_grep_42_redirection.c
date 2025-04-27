#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(void)
{
	int fds[2];
	int pid;
	pipe(fds);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1],STDOUT_FILENO);
		close(fds[1]);
		char *args1[] = {"/bin/ls", NULL};
		execv("/bin/ls",args1);
		perror("execv");
		exit(1);
	}
	int pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid2 == 0)
	{
		close(fds[1]);
        int file = open("yess",O_CREAT | O_RDWR, 0644);
        dup2(file,STDOUT_FILENO);
		dup2(fds[0],STDIN_FILENO);
		close(fds[0]);
		close(file);
		char *args2[] = {"/bin/grep","a.out",NULL};
		execv("/bin/grep",args2);
		perror("execv");
		exit(1);
	}
	else
	{
		close(fds[0]);
		close(fds[1]);
		wait(NULL);
		wait(NULL);
	}
	return 0;
}
