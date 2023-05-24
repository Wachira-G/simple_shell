#include "shell.h"

/**
 * handle_shell_operators - Handles operators.
 * @args: Pointer to string elents.
 * @shell_name: name of the shell program.
 * @line_number: line number of the current command
 *
 *Return: void.
 */
void handle_shell_operators(char **args, char *shell_name, int line_number)
{
	execute_external_command(args, shell_name, line_number);
}
