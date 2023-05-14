#include "shell.h"

/**
 *execute - Execute corresponding command from the user input.
 *@args: Pointer to string elents.
 *
 *Return: An int inticating success or failer.
 */
int execute(char **args)
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
		env_func(args);
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
		handle_shell_operators(args);
	}

	return (1);
}
