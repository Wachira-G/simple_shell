#include "shell.h"

/**
 * execute_external_command - Executes external commands.
 * @args: Pointer to string arguments.
 * @shell_name: name of shell.
 * @line_number: line number of the current command
 *
 *Return: void.
 */
void execute_external_command(char **args,
		char *shell_name, int line_number)
{
	pid_t pid;
	int status, process_id, exit_status;
	char *command = get_filename(args[0]);
	char *path, *env[] = {"HOME", NULL};

	path = get_path(command);
	if (path == NULL)
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
		free(command);
		return;
	}
	if (_strlen(command) > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			exit_status = 0;
			process_id = getpid();
			replace_variables(args, exit_status, process_id);
			if (execve(path, args, env) == -1)
			{
				_puts("execve: ");
				_puts(strerror(errno));
				_puts("\n");
				exit(EXIT_FAILURE);
			}
			free(path);
		}
		else if (pid < 0)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		}
	}
	free(command);
}

/**
 *create_replacement_string - Create a replacement string object.
 *@value: value replace.
 *Return: Pointer to representation of a value.
 */
char *create_replacement_string(int value)
{
	char *str;
	int length = 1, temp = value;

	while (temp > 9)
	{
		temp /= 10;
		length++;
	}

	str = malloc(length + 1);
	sprintf(str, "%d", value);
	return (str);
}

/**
 *perform_variable_replacement - Replaces the variable occurance in the args.
 *@arg: Arguments.
 *@variable: Pointer to variable occurance.
 *@replacement: Pointer to replacement.
 *Return: pointer to replacement.
 */
char *perform_variable_replacement(char *arg, char *variable,
		char *replacement)
{
	char *result = malloc(strlen(arg) + _strlen(replacement));
	char *dest = result;
	char *src = arg;
	char *pos = _strstr(arg, variable);

	while (src < pos)
	{
		*dest = *src;
		dest++;
		src++;
	}

	src = replacement;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	src = pos + _strlen(variable);
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (result);
}

/**
 *replace_variables - Replace variable occurences in a string.
 *@command: String command.
 *@exit_status: Exiting status.
 *@process_id: pid id.
 */
void replace_variables(char **command, int exit_status, int process_id)
{
	int i;
	char *arg = NULL;
	char *pos = NULL;
	char *exit_status_str = NULL;
	char *new_arg = NULL;
	char *process_id_str = NULL;

	for (i = 0; command[i] != NULL; i++)
	{
		arg = command[i];
		pos = _strstr(arg, "$?");
		if (pos != NULL)
		{
			exit_status_str = create_replacement_string(exit_status);
			new_arg = perform_variable_replacement(arg, "$?", exit_status_str);
			free(command[i]);
			command[i] = new_arg;
			free(exit_status_str);
		}

		pos = _strstr(arg, "$$");
		if (pos != NULL)
		{
			process_id_str = create_replacement_string(process_id);
			new_arg = perform_variable_replacement(arg, "$$", process_id_str);
			free(command[i]);
			command[i] = new_arg;
			free(process_id_str);
		}
	}
}
