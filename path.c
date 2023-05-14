#include "shell.h"

/**
 *get_path - Get full path of command.
 *@command: Command to print path.
 *
 *Return: Full path.
 */
char *get_path(char *command)
{
    char *path = _getenv("PATH");
    char *path_cpy = malloc(_strlen(path) + 1);
    char *dir = NULL;
    char *full_path = NULL;
    _strcpy(path_cpy, path);

    dir = shell_strtok(path_cpy, ":");

    while (dir != NULL)
    {
        full_path = malloc(_strlen(dir) + _strlen(command) + 2);
        sprintf(full_path, "%s/%s", dir, command);

        if (access(full_path, X_OK) == 0)
        {
            free(path_cpy);
            return (full_path);
        }
        free(full_path);
        dir = shell_strtok(NULL, ":");
    }

    free(path_cpy);
    return (NULL);
}
