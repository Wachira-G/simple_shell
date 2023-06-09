#include "shell.h"

/**
 * execute - Execute corresponding command from the user input.
 * @args: Pointer to string elents.
 * @env: pointer to environ variables.
 * @shell_name: name of the shell program.
 * @line_number: line number of the current command
 *
 *Return: An int inticating success or failer.
 */
int execute(char **args, char **env, char *shell_name, int line_number)
{
	char *command = args[0];

	if (command == NULL)
		return (1);

	if (_strcmp(command, "exit") == 0)
	{
		exit_func(args);
	}
	else if (_strcmp(command, "cd") == 0)
	{
		cd_func(args);
	}
	else if (_strcmp(command, "env") == 0 ||
			(_strcmp(command, "set") == 0 && args[1] == NULL))
	{ /* set - limited as it doesn't print the internals */
		/* env -  doesnt Execute a command with modified environment:*/
		/* env VARIABLE_NAME=VALUE command*/
		env_func(env);
	}
	else if (_strcmp(command, "pwd") == 0)
	{
		pwd_func(args);
	}
	else if (_strcmp(command, "setenv") == 0)
			/* TODO || _strcmp(command, "export") == 0) */
	{
		_setenv(args[1], args[2], 1);
	}
	else if (_strcmp(command, "unsetenv") == 0
			|| _strcmp(command, "unset") == 0)
	{
		_unsetenv(args[1]);
	}
	else
	{
		handle_shell_operators(args, shell_name, line_number);
	}
	return (1);
}
