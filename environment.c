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

/**
 * _unsetenv - implementation of the builtin unsetenv func
 *   that deletes the variable name from the environment.
 *   If name does not exist in the environment, then the function succeeds,
 *   and the environment is unchanged.
 * @name: environment variable we want to unset
 * Return: zero on success, or -1 on error,
 *   with errno set to indicate the cause of the error. (EINVAL name is NULL,
 *   points to a string of length 0, or contains an '=' character.
 */
int _unsetenv(char *name)
{
	char **new_env = NULL, **env = __environ;
	int i, new_env_index = 0, env_count = 0;

	if (name == NULL || _strlen(name) == 0 || strchr(name, '=') != NULL)
	{ /* invalid input: name = (null|empty|contain =). TODO set errno her*/
		perror(" invalid environment variable name: ");
		return (-1);
	}
	if (_getenv(name) == NULL)
	{ /* if environment anme existe */
		perror("environment variable not found: "); /* set errno TODO*/
		return (-1);
	}
	while (env[env_count] != NULL) /* count no of environ variables */
		env_count++;
	new_env = malloc(sizeof(char *) * (env_count + 1)); /* alloc mem env*/
	if (new_env == NULL)
	{
		perror("memory allocation fail: ");
		return (-1);
	}
	for (i = 0; i < env_count; i++)
	{       /* copy environment varilables except the one to  be unset */
		if (_strncmp(env[i], name, _strlen(name)) != 0 ||
				env[i][_strlen(name)] != '=')
		{     /* duplicate the environment varilable string */
			new_env[new_env_index] = _strdup(env[i]);
			if (new_env[new_env_index] == NULL)
			{
				perror("mem allocation failed: ");
				while (new_env_index > 0) /* free mem so far*/
					free(new_env[--new_env_index]);
				free(new_env);
				return (-1);
			}
			new_env_index++;
		}
	}  /* set last element of the new environmnt array ot null */
	new_env[new_env_index] = NULL;
	__environ = new_env;
	return (0);
}
