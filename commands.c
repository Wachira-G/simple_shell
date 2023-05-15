#include "shell.h"

/**
 *execute_external_command - Executes external commands.
 *@args: Pointer to string arguments.
 *
 *Return: void.
 */
void execute_external_command(char **args)
{
	pid_t pid;
	int status;
	char *path;

	path = get_path(args[0]);
	if (path == NULL)
	{
		_sprintf("%s: command not found\n", args[0]);
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, NULL) == -1)
		{
			_sprintf("execve: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		free(path);
	}
	else if (pid < 0)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
