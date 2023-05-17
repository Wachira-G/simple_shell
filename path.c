#include "shell.h"

/**
 *get_path - Get full path of command.
 *@command: Command to print path.
 *
 *Return: Full path.
 */
char *get_path(char *command)
{
	char *path = getenv("PATH");
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
	char *filename = strrchr(path, '/');

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
	char *s, c, *p;
	int d;

	va_start(arg, format);

	while (*format)
	{
		if (*format != '%')
		{
			*str++ = *format++;
			written++;
			continue;
		}
		format++;

		switch (*format)
		{
		case 'c':
			c = va_arg(arg, int);
			*str++ = c;
			written++;
			break;
		case 'd':
			d = va_arg(arg, int);
			p = (char *)malloc(12);
			_itoa(d, p);
			s = p;
			while (*s)
			{
				*str++ = *s++;
				written++;
			}
			free(p);
			break;
		case 's':
			s = va_arg(arg, char *);
			while (*s)
			{
				*str++ = *s++;
				written++;
			}
			break;
		default:
			*str++ = *format;
			written++;
			break;
		}
		format++;
	}
	*str = '\0';
	va_end(arg);
	return (written);
}
