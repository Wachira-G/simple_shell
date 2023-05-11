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
