#ifndef SHELL_H
#define SHELL_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define LINE_BUF_SIZE 1024

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _ensure_capacity(char **lineptr, size_t *n, size_t new_size);
int _read_char(FILE *stream, char *c);

char *shell_strtok(char *str_line, const char *delimiter);

/** String helper functions */
int _fileno(FILE *stream);
int _fgetc(FILE *stream);
char *_strpbrk(char *str, const char *accept);
size_t _strlen(const char *s);
char *_strcpy(char *dest, const char *src);

#endif
