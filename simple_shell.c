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
		exit(128 + signo);
	}
	else if (signo == SIGQUIT)
	{
		_puts("Quit (core dumped)\n");
		exit(128 + signo);
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
	int line_number = 1;

	(void)argc, (void)argv;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);

	while (1)
	{
		char ***commands;
		int i;

		if (isatty_flag)
			_puts("$ ");
		if (_getline(&line, &buf, stdin) == -1)
		{
			if (isatty_flag)
				_puts("\n");
			exit(0);
		}
		if (line[_strlen(line) - 1] == '\n')
			line[_strlen(line) - 1] = '\0';
		args = tokenize_line(line);
		commands = split_commands(args);
		for (i = 0; commands[i] != NULL; i++)
		{
			char **command = commands[i];

			execute(command, env, argv[0], line_number);
		}
		line_number++;
		free_commands(commands);
		for (i = 0; args[i] != NULL; i++)
			free(args[i]);
		free(args);
		free(line);
	}
	return (0);
}
