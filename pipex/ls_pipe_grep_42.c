#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
	// "ls | grep 42"
	int fds[2];
	int pid;
	pipe(fds);

	pid = fork(); //hadi fork for the child process li a texecuta fih ls
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
	int pid2 = fork(); //hadi fork for the second child process li a texecuta fih grep "42"
	if (pid2 == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid2 == 0)
	{
		close(fds[1]);
		dup2(fds[0],STDIN_FILENO);
		close(fds[0]);
		char *args2[] = {"/bin/grep","42",NULL};
		execv("/bin/grep",args2);
		perror("execv");
		exit(1);
	}
	else //this one is the parent process waiting for the childs to finish there work
	{
		close(fds[0]);
		close(fds[1]);
		wait(NULL);
		wait(NULL);
	}
	return 0;
}
