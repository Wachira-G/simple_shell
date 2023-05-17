#include "shell.h"

/**
 *_strncmp - Compares @size char of two strings.
 *@str1: First string.
 *@str2: Second string.
 *@size: Size to compare againest.
 *
 *Return: int
 */
int _strncmp(const char *str1, char *str2, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
	{
		if (str1[i] != str2[i])
		{
			return ((str1[i] < str2[i]) ? -1 : 1);
		}
		if (str1[i] == '\0')
		{
			return (0);
		}
	}
	return (0);
}

/**
 *_atoi - Converts a string to an integer
 *@s: String to be converted
 *
 *Return: Converted integer
 */
int _atoi(char *s)
{
	int sign;
	unsigned int num;
	char *str;

	str = s;
	num = 0;
	sign = 1;
	while (*str != 0 && (*str < '0' || *str > '9'))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (*str != 0)
	{
		do {
			num = num * 10 + (*str - '0');
			str++;
		} while (*str >= '0' && *str <= '9');
	}
	return (num * sign);
}

/**
 *_strdup - Duplicates a string.
 *@str: String to duplicate.
 *Return: Duplicated str.
 */
char *_strdup(char *str)
{
	size_t i, length = strlen(str) + 1;
	char *duplicate = malloc(length * sizeof(char));

	if (duplicate != NULL)
	{
		for (i = 0; i < length; i++)
			duplicate[i] = str[i];
	}

	return (duplicate);
}
