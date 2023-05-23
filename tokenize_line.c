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

		buffer[num_tokens] = _strdup(token); /*added strdup */
		num_tokens++;
		token = shell_strtok(NULL, TOKEN_DELIMETER);
	}

	if (num_tokens >= buffer_size)
	{
		resize_buffer(&buffer, &buffer_size, buffer_size + 1);
	}

	buffer[num_tokens] = NULL;
	/* free(line); original line after tokenization */
	return (buffer);
}

/**
 *split_commands - Splits commands using separator ;.
 *@tokens: Tokens to split.
 *Return: Pointer to splited command pointer.
 */
char ***split_commands(char **tokens)
{
	int buffer_size = MAX_TOKENS;
	char ***commands = malloc(sizeof(char **) * buffer_size);
	int i, num_commands = 0, num_tokens_in_command = 0;

	char **current_command = malloc(sizeof(char *) * MAX_TOKENS);

	for (i = 0; tokens[i] != NULL; i++)
	{
		if (strcmp(tokens[i], ";") == 0)
		{
			current_command[num_tokens_in_command] = NULL;
			commands[num_commands++] = current_command;

			if (num_commands >= buffer_size)
			{
				buffer_size += MAX_TOKENS;
				commands = _realloc(commands, sizeof(char **) *
						    buffer_size);
			}

			current_command = malloc(sizeof(char *) * MAX_TOKENS);
			num_tokens_in_command = 0;
		}
		else
		{
			current_command[num_tokens_in_command++] =
				strdup(tokens[i]);
		}
	}
	current_command[num_tokens_in_command] = NULL;
	commands[num_commands++] = current_command;

	if (num_commands >= buffer_size)
	{
		buffer_size++;
		commands = _realloc(commands, sizeof(char **) * buffer_size);
	}
	commands[num_commands] = NULL;

	return (commands);
}

/**
 *free_commands - Free command memory.
 *@commands: pointer to commands pointers.
 */
void free_commands(char ***commands)
{
	int i, j;

	for (i = 0; commands[i] != NULL; i++)
	{
		char **command = commands[i];

		for (j = 0; command[j] != NULL; j++)
		{
			free(command[j]);
		}
		free(command);
	}

	free(commands);
}

/**
 *_realloc - reallocate memory byte.
 *@ptr: Void pointer.
 *@size: byte size.
 *Return: Byte size reallocated.
 */
void *_realloc(void *ptr, size_t size)
{
	void *new_ptr;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(size);
	if (new_ptr == NULL)
	{
		perror("Error: Can't allocate memory");
		exit(EXIT_FAILURE);
	}

	if (ptr != NULL)
	{
		size_t i;
		char *src = (char *)ptr;
		char *dest = (char *)new_ptr;

		for (i = 0; i < size; i++)
		{
			dest[i] = src[i];
		}

		free(ptr);
	}
	return (new_ptr);
}
