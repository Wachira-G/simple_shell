#include "shell.h"

/**
 * exit_func - exit func builtin
 * @args: array of strings from the tokensization operation
 */
void exit_func(char **args)
{
	int i = 0, status = 0;

	if (args[1] != NULL && args[2] != NULL)
	{
		status = 1;
		perror(": exit: too many arguments");
		exit(status);
	}
	if (args[1] != NULL)
	{/* check non-numerics */
		char *str = args[0];
		/* Check for negative sign */
		if (str[0] == '-')
			i = 1;
		/* Check each character in the string */
		for (; str[i] != '\0'; i++)
		{
			/* If a non-digit character is found, return false */
			if (str[i] < '0' || str[i] > '9')
			{
				status = 2;
				_puts(": exit: ");
				_puts(args[1]);
				perror(": numeric argument required");
				exit(status);
			}
		}
		/*if numeric */
		status = _atoi(args[1]);
		if (status < 0)
		{
			status = 2;
			_puts(": exit: Illegal number: ");
			_puts(args[1]);
			_puts("\n");
		}
	}
	exit(status);
}

/**
 * pwd_func - implements the pwd shell builtin
 * @args: array of strings from the tokensization operation
 * Return: Returns 0 unless an invalid option is given
 * or the current directory cannot be read.
 */
int pwd_func(__attribute__((unused)) char **args)
{
	char *buffer = NULL;
	ssize_t nwrite;

	buffer = malloc(PATH_MAX + 1);
	if (buffer == NULL)
	{
		perror("pwd buffer malloc fail");
		return (EXIT_FAILURE);
	}

	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		perror("getcwd pwd fail");
		free(buffer);
		return (EXIT_FAILURE);
	}

	nwrite = write(STDOUT_FILENO, buffer, _strlen(buffer));
	if (nwrite == -1)
	{
		perror("pwd write fail");
		free(buffer);
		return (EXIT_FAILURE);
	}
	nwrite = write(STDOUT_FILENO, "\n", 1);
	if (nwrite == -1)
	{
		perror("pwd write /n fail");
		free(buffer);
		return (EXIT_FAILURE);
	}
	free(buffer);
	return (0);
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
		nwrite = write(STDOUT_FILENO, "\n", 1); /* newline */
		if (nwrite == -1)
		{
			perror("name write fail: ");
			return (1);
		}
		return (0);
	}
	perror(" echo fail: ");
	return (1);
}


/**
 * cd_func - implements the builtin cd function
 * @args: array of strings from the tokensization operation
 * chdir - On success, zero is returned. On error, -1 is returned,
 *   and errno is set appropriately
 * Return: 0 on success and 1 on fail
 */
int cd_func(char **args)
{
	char *new_pwd, *old_pwd = _getenv("OLDPWD");

	if (args[1] == NULL || _strcmp(args[1], "~") == 0 || _strlen(args[1]) == 0)
	{
		new_pwd = _getenv("HOME");
		if (new_pwd == NULL)
		{
			perror("cd - HOME not set: ");
			return (1);
		}
	}
	else if (_strcmp(args[1], "-") == 0)
	{
		if (old_pwd == NULL)
		{
			perror("cd - OLDPWD not set: ");
			return (1);
		}
		new_pwd = old_pwd;
	}
	else
	{
		new_pwd = _strdup(args[1]);
		if (new_pwd == NULL)
		{
			error("cd - path not set: ", 1);
		}
	}
	if (chdir(new_pwd) != 0)
	{
		perror("cd - chdir fail: ");
		if (args[1] != NULL && _strlen(args[1]) > 0)
			free(new_pwd);
		return (1);
	}
	_setenv("OLDPWD", _getenv("PWD"), 1);
	_setenv("PWD", new_pwd, 1);
	return (0);
}

/**
 * env_func - implements the env builtin
 * @env: env array passed from main or 'extern environ';
 * Return: 0 on success and 1 on any fail
 *
 * limitation:
 * this does not update environment in case of new process or in case of chdir
 */
int env_func(__attribute__((unused)) char **env)
{
	char **ptr = __environ, *name = NULL;
	ssize_t nwrite;
	size_t len = 0;

	while (*ptr != NULL)
	{
		name = *ptr;
		len = _strlen(name);
		if (name != NULL)
		{
			nwrite = write(STDOUT_FILENO, name, len);
			if (nwrite == -1)
			{
				perror("name write fail: ");
				return (1);
			}
			if (*(ptr + 1) != NULL)
			{
				nwrite = write(STDOUT_FILENO, "\n", 1);
				if (nwrite == -1)
				{
					perror("name write fail: ");
					return (1);
				}
			}
		}
		ptr++;
	}
	nwrite = write(STDOUT_FILENO, "\n", 1);
	if (nwrite == -1)
	{
		perror("name write fail: ");
		return (1);
	}
	return (0);
}
