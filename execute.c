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
int execute(char **args, char **env, char *shell_name, size_t line_number)
{
	char *command = args[0];

	if (command == NULL)
	{
		return (1);
	}

	if (_strcmp(command, "exit") == 0)
	{
		exit_func(args);
	}
	else if (_strcmp(command, "cd") == 0)
	{
		cd_func(args);
	}
	else if (_strcmp(command, "env") == 0)
	{
		env_func(env);
	}
	else if (_strcmp(command, "pwd") == 0)
	{
		pwd_func(args);
	}
	else if (_strcmp(command, "echo") == 0)
	{
		echo_func(args);
	}
	else
	{
		handle_shell_operators(args, shell_name, line_number);
	}

	return (1);
}
