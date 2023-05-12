#include "shell.h"

/**
 *resize_buffer - Resize buffer size.
 *@buffer: Buffer.
 *@buffer_size: size of buffer.
 *@new_size: new buffer size.
 *
 *Return: Void.
 */
void resize_buffer(char ***buffer, int *buffer_size, int new_size)
{
	int i;

	char **new_buffer = malloc(sizeof(char *) * new_size);

	if (new_buffer == NULL)
	{
		perror("Error: Can't allocate memory");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < *buffer_size; i++)
	{
		new_buffer[i] = (*buffer)[i];
	}

	free(*buffer);
	*buffer = new_buffer;
	*buffer_size = new_size;
}

/**
 *tokenize_line - Tokenize a string from a user.
 *@line: Pointer to line.
 *
 *Return: Arrays of tokens.
 */
char **tokenize_line(char *line)
{
	int buffer_size = BUFF_SIZE;
	char **buffer = malloc(sizeof(char *) * buffer_size);
	char *token = shell_strtok(line, TOKEN_DELIMETER);
	int num_tokens = 0;

	while (token != NULL)
	{
		if (num_tokens >= buffer_size)
		{
			resize_buffer(&buffer, &buffer_size,
				      buffer_size + BUFF_SIZE);
		}

		buffer[num_tokens] = token;
		num_tokens++;
		token = shell_strtok(NULL, TOKEN_DELIMETER);
	}

	if (num_tokens >= buffer_size)
	{
		resize_buffer(&buffer, &buffer_size, buffer_size + 1);
	}

	buffer[num_tokens] = NULL;
	return (buffer);
}
