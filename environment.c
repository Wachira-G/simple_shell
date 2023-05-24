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

	for (env = environ; *env != NULL; env++)
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
	char *existing = NULL, *new_env = NULL;
	int res;

	if (name == NULL || _strlen(name) == 0 ||
	_strchr(name, '=') != NULL) /* TODO  strchr func*/
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
		perror("malloc fail _setenv: ");
		free(new_env);
		return (-1);
	}
	_sprintf(new_env, "%s=%s", name, value);
	res = _putenv(new_env); /*TODO*/
	if (res != 0)
	{
		free(new_env);
		return (-1);
	}
	/* TODO free(new_env); */
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
	char **new_env = NULL, **env = environ;
	int i, new_env_index = 0, env_count = 0;

	if (name == NULL || _strlen(name) == 0 || strchr(name, '=') != NULL)
	{ /* invalid input: name = (null|empty|contain =). TODO set errno her*/
		error(" invalid environment variable name: ", -1);
	}
	if (_getenv(name) == NULL)
	{ /* if environment anme existe */
		error("environment variable not found: ", -1); /* set errno TODO*/
	}
	while (env[env_count] != NULL) /* count no of environ variables */
		env_count++;
	new_env = malloc(sizeof(char *) * (env_count + 1)); /* alloc mem env*/
	if (new_env == NULL)
	{
		error("memory allocation fail: ", -1);
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
	environ = new_env;
	return (0);
}
