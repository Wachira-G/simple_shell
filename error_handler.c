#include "shell.h"

/**
 * external_comm_error - print error.
 * @command: Command to check.
 * @shell_name: name of the shell program
 * @line_number: line in file with error.
 */
void external_comm_error(char *command, char *shell_name, int line_number)
{
	if (!isatty(STDIN_FILENO))
	{
		char *itoa = intoa(line_number);

		_puts(shell_name);
		_puts(": ");
		_puts(itoa);
		_puts(": ");
		_puts(command);
		_puts(": not found\n");
		free(itoa);
	}
	else
	{
		_puts(shell_name);
		_puts(": No such file or directory\n");
	}
}

/**
 * execve_error - print execve error.
 * @command: command.
 * @path: path.
 */
void execve_error(char *command, char *path)
{
	_puts("execve: ");
	_puts(strerror(errno));
	_puts("\n");
	free(path);
	free(command);
	exit(EXIT_FAILURE);
}

/**
 *error - Print error message
 *@str: message.
 *@value: return value.
 *Return: Int value specified.
 */
int error(char *str, int value)
{
	perror(str);
	return (value);
}

/**
 *free_waitpit - print error and free mem.
 *@command: Command.
 *@path: path variable.
 */
void free_waitpit(char *command, char *path)
{
	perror("waitpid");
	free(path);
	free(command);
	exit(EXIT_FAILURE);
}
