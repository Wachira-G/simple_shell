#include "shell.h"

/**
 * sig_handler - Signal handler function for Ctrl-C, Ctrl-D, and EOF.
 * @signo: Signal number.
 *
 * Return: void.
 */
static void sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		_puts("\n$ ");
	}
	else if (signo == SIGQUIT)
	{
		_puts("Quit (core dumped)\n");
		exit(1);
	}
	else if (signo == EOF)
	{
		_puts("EOF\n");
		exit(0);
	}
}

/**
 * main - Entry point to the shell program.
 * @argc: Number of arguments passed.
 * @argv: Array of arguments passed to the main.
 * @env: Array of environmental variables.
 *
 * Return: Exit status.
 */
int main(int argc, char **argv, char **env)
{
	size_t buf = 0;
	int isatty_flag = isatty(STDIN_FILENO);
	char *line = NULL, **args = NULL;

	(void)argc, (void)argv, (void)env;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);

	while (1)
	{
		if (isatty_flag)
			_puts("$ ");
		if (_getline(&line, &buf, stdin) == -1)
		{
			if (isatty_flag)
				_puts("\n");
			exit(0);
		}
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		args = tokenize_line(line);
		if (args == NULL)
		{
			perror("Failed to tokenize line");
			exit(EXIT_FAILURE);
		}
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free(args);
				exit(0);
			}
		}
		free(args);
	}
	return (0);
}