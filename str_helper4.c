#include "shell.h"

/**
 * _putenv - implements the putenv function
 * @string: name=value string to set environment with
 *
 * Return: 0 on success, -1 on fail
 */
int _putenv(char *string)
{
	size_t name_len, num_env;
	char **env = NULL, **new_env = NULL;

	if (string == NULL || _strchr(string, '=') == NULL)
		return (-1);

	name_len = _strchr(string, '=') - string;
	env = __environ;
	while (*env != NULL)
	{
		if (_strncmp(*env, string, name_len) == 0 && (*env)[name_len] == '=')
		{
			_strcpy(*env, string);
			return (0);
		}
		env++;
	}

	num_env = env - __environ;

	new_env = _realloc(__environ, (num_env + 2) * sizeof(char *)); /*!!!*/
	if (new_env == NULL)
		return (-1);
	__environ = new_env;

	__environ[num_env] = _strdup(string);
	__environ[num_env + 1] = NULL;

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
