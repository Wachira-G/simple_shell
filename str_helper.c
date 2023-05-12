#include "shell.h"

/**
 *_fgetc - Reads single byte from file descriptor.
 *@stream: Ponter to sream input.
 *
 *Return: int.
 */
int _fgetc(FILE *stream)
{
	char bf[1];

	return ((read(fileno(stream), bf, 1) == 1) ?
		(unsigned char)bf[0] : EOF);
}

/**
 *_fileno - obtains the int file descriptor.
 *@stream: Ponter to sream input.
 *
 *Return: int file descpritor.
 */

int _fileno(FILE *stream)
{
	int fd;

	if (stream == stdin)
	{
		fd = STDIN_FILENO;
	}
	else if (stream == stdout)
	{
		fd = STDOUT_FILENO;
	}
	else if (stream == stderr)
	{
		fd = STDERR_FILENO;
	}
	else
	{
		fd = -1;
	}
	return (fd);
}

/**
 *_strpbrk - Searches a string for a give byte.
 *@str: String to scan.
 *@accept: Bytes of string to be serached.
 *
 *Return: A pointer to the byte.
 */
char *_strpbrk(char *str, const char *accept)
{
	int i, j;

	for (i = 0; str[i] != '\0'; i++)
	{

		for (j = 0; accept[j] != '\0'; j++)
		{
			if (str[i] == accept[j])
			{
				return (str + i);
			}
		}
	}
	return (NULL);
}

/**
 *_puts - Print a string.
 *@str: String.
 *Return: Void.
 */
void _puts(char *str)
{
	write(STDOUT_FILENO, str, strlen(str));
}
