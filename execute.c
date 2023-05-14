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
        return (0);
    }
    else
    {
        handle_shell_operators(args);
    }

    return (1);
}
