#include "shell.h"

/**
 *_getenv - Search for specific name in env variables.
 *@env_name: Pointer to env name.
 *
 *Return: Pointer to the value of the variable.
 */
char *_getenv(char *env_name)
{
	char **env;
	size_t var_len = _strlen(env_name);

	for (env = __environ; *env != NULL; env++)
	{
		if (_strncmp(env_name, *env, var_len) == 0)
		{
			return (&((*env)[var_len + 1]));
		}
	}
	return (NULL);
}
