#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

void	run_command(char *input)
{
	char	*args[MAX_ARGS];
	char	*token;
	int		i = 0;
	pid_t	pid;

	// Split input into arguments
	token = strtok(input, " \t\n");
	while (token && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (args[0] == NULL)
		return ;

	pid = fork();
	if (pid == 0) // Child
	{
		execvp(args[0], args);
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0) // Parent
		wait(NULL);
	else
		perror("fork");
}

int	main(void)
{
	char	input[MAX_INPUT];

	while (1)
	{
		write(1, "mini-shell$ ", 12);
		if (!fgets(input, sizeof(input), stdin))
			break ;
		run_command(input);
	}
	return (0);
}
