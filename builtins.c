#include "shell.h"

/**
 * exit_func - exit func builtin
 * @args: array of strings from the tokensization operation
 */
void exit_func(char **args)
{
	if (args[1] == NULL)
		exit(0);
	else
	{
		exit(atoi(args[1]));
	}
}

/**
 * pwd_func - implements the pwd shell builtin
 * @args: array of strings from the tokensization operation
 * Return: Returns 0 unless an invalid option is given
 * or the current directory cannot be read.
 */
int pwd_func(char **args)
{
	ssize_t nwrite;
	size_t len = 0;
	char *pwd = NULL;

	pwd = getenv("PWD");
	_strcat(pwd, "\n"); /* should we check this on fail? */
	len = _strlen(pwd);
	if (pwd != NULL)
	{
		nwrite = write(STDOUT_FILENO, pwd, len);
		if (nwrite == -1)
		{
			perror("pwd write fail: ");
			return (1);
		}
		return (0);
	}
	perror(" pwd getenv fail: ");
	return (1);
}


/**
 * echo_func - implements the pwd shell builtin
 * @args: array of strings from the tokensization operation
 * Return: success (0) unless a write error occurs.
 */
int echo_func(char **args)
{
	ssize_t nwrite = 0;
	size_t len = 0;
	char **ptr = args;

	ptr++; /* pass the 'echo' arg */
	if (*ptr)
	{
		while (*ptr != NULL)
		{
			len = _strlen(*ptr);
			nwrite = write(STDOUT_FILENO, *ptr, len);
			if (nwrite == -1)
			{
				perror("echo write fail: ");
				return (1);
			}
			if (*(ptr + 1) != NULL)
			{
				nwrite = write(STDOUT_FILENO, " ", 1);
				if (nwrite == -1)
				{
					perror("echo write fail: ");
					return (1);
				}
			}
			ptr++;
		}
		return (0);
	}
	perror(" echo fail: ");
	return (1);
}

