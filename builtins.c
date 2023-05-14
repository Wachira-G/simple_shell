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
		exit(_atoi(args[1]));
	}
}

/**
 * pwd_func - implements the pwd shell builtin
 * @args: array of strings from the tokensization operation
 * Return: Returns 0 unless an invalid option is given
 * or the current directory cannot be read.
 */
int pwd_func(__attribute__((unused)) char **args)
{
	ssize_t nwrite;
	size_t len = 0;
	char *pwd = NULL;

	pwd = _getenv("PWD");
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


/**
 * cd_func - implements the builtin cd function
 * @args: array of strings from the tokensization operation
 * chdir - On success, zero is returned. On error, -1 is returned,
 *   and errno is set appropriately
 * Return: 0 on success and 1 on fail
 */
int cd_func(char **args)
{
	char *new_pwd, *old_pwd = getenv("OLDPWD");

	/* cd alone or '~' */
	if (args[1] == NULL || _strcmp(args[1], "~") == 0)
	{
		new_pwd = _getenv("HOME");
		if (new_pwd == NULL)
		{
			perror("cd - HOME not set: ");
			return (1);
		}
	} /* cd - */
	else if (_strcmp(args[1], "-") == 0)
	{
		if (old_pwd == NULL)
		{
			perror("cd - OLDPWD not set: ");
			return (1);
		}
		new_pwd = old_pwd;
	} /* cd path  -- TODO relook into below bit and chdir */
	else
	{
		/* new_pwd  = realpath(args[i], NULL); */
		new_pwd = args[1];
		if (new_pwd == NULL)
		{
			perror("cd - path not set: ");
			return (1);
		}
	}
	if (chdir(new_pwd) != 0)
	{
		perror("cd - chdir fail: ");
		return (1);
	}
	_setenv("OLDPWD", _getenv("PWD"), 1);
	_setenv("PWD", new_pwd, 1);
	/* free(new_pwd); if set by realpath */
	return (0);
}

/**
 * env_func - implements the env builtin
 * @args: envp array passed from main or 'extern environ';
 * Return: 0 on success and 1 on any fail
 *
 * limitation:
 * this does not update environment in case of new process or in case of chdir
 */
int env_func(char **args)
{
	char **ptr = args, *name = NULL;
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
	return (0);
}
