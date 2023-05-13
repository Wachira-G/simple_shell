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
 * _strlen - calculates the lenght of a string
 * @s: the string
 *
 * Return: the length of a string
 * (number of bytes in the string pointed to by s)
 */
size_t _strlen(const char *s)
{
	size_t len = 0;
	const char *p = s;

	if (s == NULL)
		return (0);
	while (*p != '\0')
		p++;
	len = (size_t)(p-s); /* diff of 2 pointers is ptrdiff type */
	return (len);
}

/**
 * _strcpy - copies the string pointed to by src,
 * including the terminating null byte ('\0'),
 * to the buffer pointed to by dest.
 * @dest: pointer to buffer where we will store the string
 * @src: pointer to location of string
 *
 * Return: a pointer to the destination string dest.
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	if (src == NULL)
		return NULL;
	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0'; /* null terminator to dest */
	return (dest);
}
