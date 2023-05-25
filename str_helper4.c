#include "shell.h"

#include <stdlib.h>
#include <string.h>

/**
 * _putenv - implements the putenv function
 * @string: name=value string to set environment with
 *
 * Return: 0 on success, -1 on fail
 */
int _putenv(char *string)
{
	size_t num_env, name_len;
	char **env, **new_env;

	if (string == NULL || _strchr(string, '=') == NULL)
		return (-1);

	name_len = _strchr(string, '=') - string;
	env = environ;

	while (*env != NULL)
	{
		if (_strncmp(*env, string, name_len) == 0 && (*env)[name_len] == '=')
		{
			*env = string;
			return (0);
		}
		env++;
	}

	num_env = env - environ;
	new_env = malloc(sizeof(environ));
	new_env = _realloc(environ, (num_env + 2) * sizeof(char *));
	if (new_env == NULL)
		return (-1);

	new_env[num_env] = string;
	new_env[num_env + 1] = NULL;
	environ = new_env;

	return (0);
}

/**
 * _strchr - scans the characters of the string
 * starting from the beginning (str)
 * until it finds the first occurrence of the specified character
 * or reaches the end of the string ('\0').
 *
 * @character: character to check.
 * @str: string to search
 *
 * Return: a pointer to the location of that character in the string,
 * If the character is found, If the character is not found,
 * it returns a null pointer (NULL).
*/
char *_strchr(char *str, int character)
{
	if (str == NULL)
		return (NULL);

	while (*str != '\0')
	{
		if (*str == character)
			return (str);
		str++;
	}
	return (NULL);
}

/**
 *free_env - free env.
 *@new_env: env variable.
 *@num_env: size.
 *Return: int status.
 */
int free_env(char **new_env, size_t num_env)
{
	size_t i;
	int status;

	for (i = 0; i < num_env; i++)
	{
		new_env[i] = _strdup(environ[i]);
		if (new_env[i] == NULL)
		{
			size_t j;

			for (j = 0; j < i; j++)
			{
				free(new_env[j]);
			}
			free(new_env);
			status = -1;
		}
	}
	return (status);
}

/**
 * _strrchr - function returns a pointer to the last occurrence
 * of the character c in the string s.
 * @str: string to search.
 * @ch: character to search for.
 * Return: pointer to last occurence of  string s;
 */
char *_strrchr(const char *str, int ch)
{
	char *last_occurrence = NULL;

	while (*str != '\0')
	{
		if (*str == ch)
			last_occurrence = (char *)str;
		str++;
	}
	if (*str == ch)
		return ((char *)str);
	return (last_occurrence);
}
