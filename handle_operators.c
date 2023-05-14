#include "shell.h"

/**
 *handle_shell_operators - Handles operators.
 *@args: Pointer to string elents.
 *
 *Return: void.
 */
void handle_shell_operators(char **args)
{
    execute_external_command(args);
}
