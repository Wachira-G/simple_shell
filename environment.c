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

/**
 *_setenv - Search for specific name in env variables.
 *@name: Command name.
 *@value: Pointer env var.
 *@over: Value of the var.
 *
 *Return: Pointer to the value of the variable.
 */
int _setenv(char *name, char *value, int over)
{
	char *existing, *new_env;
	int res;

	if (name == NULL || _strlen(name) == 0 ||
	strchr(name, '=') != NULL)
	{
		return (-1);
	}

	existing = _getenv(name);
	if (existing != NULL && !over)
	{
		return (0);
	}

	new_env = malloc(_strlen(name) + _strlen(value) + 2);
	if (new_env == NULL)
	{
		free(new_env);
		return (-1);
	}

	_sprintf(new_env, "%s=%s", name, value);
	res = putenv(new_env);
	if (res != 0)
	{
		free(new_env);
		return (-1);
	}
	return (0);
}
