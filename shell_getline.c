#include "shell.h"

/**
 * _getline - Reads a line from user.
 * @lineptr: Pointer to character buff.
 * @n: Pointer to size.
 * @stream: file reader.
 *
 * Return: Characters read.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[LINE_BUF_SIZE];
	static size_t buffer_pos;
	static size_t num_chars_in_buffer;
	ssize_t num_chars_read = 0;
	size_t pos = 0;
	char c;

	buffer_pos = 0;
	num_chars_in_buffer = 0;
	if (*lineptr == NULL || *n == 0)
	{
		*n = LINE_BUF_SIZE;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		if (buffer_pos >= num_chars_in_buffer)
		{
			num_chars_in_buffer = _read_char(stream, buffer);
			buffer_pos = 0;
		}
		if (num_chars_in_buffer == 0)
			break;
		c = buffer[buffer_pos++];
		if (pos >= *n)
		{
			if (_ensure_capacity(lineptr, n, pos + 1) != 0)
				return (-1);
		}
		(*lineptr)[pos++] = c;
		if (c == '\n')
			break;
	}
	if (pos == 0)
		return (-1);
	(*lineptr)[pos] = '\0';
	num_chars_read = pos;
	return (num_chars_read);
}

/**
 * _ensure_capacity - Provide needed capacity.
 * @lineptr: Pointer to character buff.
 * @n: Pointer to size.
 * @new_size: New size.
 *
 * Return: 0 else -1.
 */
int _ensure_capacity(char **lineptr, size_t *n, size_t new_size)
{
	size_t new_capacity = (*n) * 2;
	char *new_buf;
	size_t i;

	if (new_capacity < new_size)
	{
		new_capacity = new_size;
	}
	new_buf = (char *)malloc(new_capacity);
	if (new_buf == NULL)
	{
		return (-1);
	}

	for (i = 0; i < *n; i++)
	{
		new_buf[i] = (*lineptr)[i];
	}

	free(*lineptr);

	*lineptr = new_buf;
	*n = new_capacity;

	return (0);
}

/**
 * _read_char - Read char.
 * @stream: File.
 * @c: char.
 *
 * Return: 0 else 1.
 */
int _read_char(FILE *stream, char *c)
{
	int rc;

	rc = _fgetc(stream);
	if (rc == EOF)
		return (0);

	*c = (char)rc;
	return (1);
}
