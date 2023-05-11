#include "shell.h"

/**
 *shell_strtok - Tokenize a string @str_line.
 *@str_line: String to be tokenized.
 *@delimiter: Separator used in the string.
 *
 *Return: Pointer to token.
 */
char *shell_strtok(char *str_line, const char *delimiter)
{
	static char *next_pos;
	char *token, *pos_end;

	if (str_line != NULL)
	{
		next_pos = str_line;
	}

	if (next_pos == NULL)
	{
		return (NULL);
	}

	token = next_pos;
	pos_end = _strpbrk(next_pos, delimiter);
	if (pos_end != NULL)
	{
		*pos_end = '\0';
		next_pos = pos_end + 1;
	}
	else
	{
		next_pos = NULL;
	}

	return (token);
}
