#include "shell.h"

/**
 * execute_external_command - Executes external commands.
 * @args: Pointer to string arguments.
 * @shell_name: name of shell.
 * @line_number: line number of the current command
 *
 *Return: void.
 */
void execute_external_command(char **args,
		char *shell_name, int line_number)
{
	pid_t pid;
	int status;
	char *command = get_filename(args[0]);
	char *path, *env[] = {"HOME", NULL};

	path = get_path(command);
	if (path == NULL)
	{
		_puts(shell_name);
		_puts(": ");
		_puts(intoa(line_number));
		_puts(": ");
		_puts(command);
		_puts(": not found\n");
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

