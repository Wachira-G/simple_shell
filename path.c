#include "shell.h"

/**
 *get_path - Get full path of command.
 *@command: Command to print path.
 *
 *Return: Full path.
 */
char *get_path(char *command)
{
	char *path = _getenv("PATH");
	char *path_cpy = malloc(_strlen(path) + 1);
	char *dir = NULL;
	char *full_path = NULL;

	_strcpy(path_cpy, path);

	dir = shell_strtok(path_cpy, ":");

	while (dir != NULL)
	{
		full_path = malloc(_strlen(dir) + _strlen(command) + 2);
		_sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_cpy);
			return (full_path);
		}
		free(full_path);
		dir = shell_strtok(NULL, ":");
	}

	free(path_cpy);
	return (NULL);
}

/**
 *get_filename - Get the filename path.
 *@path: String path.
 *Return: File path.
 */
char *get_filename(char *path)
{
	char *filename = _strrchr(path, '/'); /* TODO */

	if (filename == NULL)
	{
		return (_strdup(path));
	}
	else
	{
		return (_strdup(filename + 1));
	}
}

/**
 *_sprintf -return formated string.
 *@str: String
 *@format: Formater.
 *Return: Formated String.
 */
int _sprintf(char *str, const char *format, ...)
{
	va_list arg;
	int written = 0;

	va_start(arg, format);

	while (*format)
	{
		if (*format != '%')
		{
			written += write_char(&str, *format++);
			continue;
		}
		format++;

		switch (*format)
		{
		case 'c':
			written += write_char(&str, va_arg(arg, int));
			break;
		case 'd':
			written += write_integer(&str, va_arg(arg, int));
			break;
		case 's':
			written += write_string(&str, va_arg(arg, char *));
			break;
		default:
			written += write_char(&str, *format);
			break;
		}
		format++;
	}
	*str = '\0';
	va_end(arg);
	return (written);
}
