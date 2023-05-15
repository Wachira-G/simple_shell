#ifndef SHELL_H
#define SHELL_H

#include<stdio.h>
#include <limits.h>
#include <signal.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <stdarg.h>
#include <errno.h>

#define LINE_BUF_SIZE 128
#define BUFF_SIZE 1024
#define TOKEN_DELIMETER " \t\r\n\a"

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _ensure_capacity(char **lineptr, size_t *n, size_t new_size);
int _read_char(FILE *stream, char *c);

char *shell_strtok(char *str_line, const char *delimiter);

int execute(char **args);
void handle_shell_operators(char **args);
void execute_external_command(char **args);

/** Tokenize string line */
char **tokenize_line(char *line);

/** String helper functions */
int _fileno(FILE *stream);
int _fgetc(FILE *stream);
char *_strpbrk(char *str, const char *accept);
size_t _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
void _puts(char *str);
int _strcmp(char *s1, char *s2);
void reverse(char *str);
void _itoa(int n, char *str);
int _sprintf(char *str, const char *format, ...);
int _strncmp(const char *str1, char *str2, size_t size);
int _atoi(char *s);
char *_strcat(char *dest, char *src);

/* Environmental */
char *_getenv(char *env_name);
int _setenv(char *name, char *value, int over);

/* builtins */
int cd_func(char **args);
int echo_func(char **args);
int pwd_func(char **args);
void exit_func(char **args);
int env_func(char **args);

/* Path */
char *get_path(char *command);

#endif
