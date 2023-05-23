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
		_puts(shell_name);
		_puts(": ");
		_puts(intoa(line_number));
		_puts(": ");
		_puts(command);
		_puts(": not found\n");
	}
	else
	{
		_puts(command);
		_puts(": command not found\n");
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
