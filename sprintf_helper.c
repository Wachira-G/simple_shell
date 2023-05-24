#include "shell.h"

/**
 * write_char - character
 * @str: string
 * @c: character.
 * Return: 1.
 */
int write_char(char **str, char c)
{
	**str = c;
	(*str)++;
	return (1);
}

/**
 * write_string - String
 * @str: string
 * @s: pointer to char
 * Return: formated string.
 */
int write_string(char **str, const char *s)
{
	int written = 0;

	while (*s)
	{
		**str = *s;
		(*str)++;
		s++;
		written++;
	}
	return (written);
}

/**
 * write_integer - write interger.
 * @str: string
 * @d: integer input.
 * Return: formated int.
 */
int write_integer(char **str, int d)
{
	int written;
	char *p = (char *)malloc(12);

	_itoa(d, p);
	written = write_string(str, p);
	free(p);
	return (written);
}
