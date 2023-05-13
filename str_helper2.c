#include "shell.h"

/**
 * _strcmp - compares characters in two strings
 *   starting from the first character,
 *   and continues until either the end of both strings is reached
 *   or a character that is not equal is encountered.
 * The comparison is done using the ASCII values of the characters
 *
 * @s1: the first string
 * @s2: the second string
 *
 * Return: an integer less than, equal to, or greater than zero
 *   if s1 (or the first n bytes thereof) is found, respectively,
 *   to be less than, to match, or be greater than s2.
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strcat - definition
 * Description: concatenates two strings by
 * appending src to the dest then add terminating null byte
 * @dest: destination string
 * @src: source string
 * Return: pointer to the resulting string dest
 */
char *_strcat(char *dest, char *src)
{
	int i, src_len = 0, dest_len = 0;

	while (src[src_len] != '\0')
		src_len++;
	while (dest[dest_len] != '\0')
		dest_len++;

	for (i = 0; i <= dest_len; i++)
		dest[dest_len + i] = src[i];
	return (dest);
}
