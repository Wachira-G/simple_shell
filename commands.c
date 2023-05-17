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
	char *path, *command = get_filename(args[0]);
	char *env[] = {"HOME", NULL};

	path = get_path(command);
	if (path == NULL)
	{
		_puts(command);
		_puts(": command not found\n");
		free(command);
		return;
	}
	if (_strlen(command) > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, args, env) == -1)
			{
				_puts("execve: ");
				_puts(strerror(errno));
				_puts("\n");
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
	free(command);
}

