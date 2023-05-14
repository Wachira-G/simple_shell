#include "shell.h"

/**
 *execute_external_command - Executes external commands.
 *@args: Pointer to string arguments.
 *
 *Return: void.
 */
void execute_external_command(char **args)
{
    pid_t pid, w_pid;
    int status;
    char *path;

    if (pid == 0)
    {
        path = get_path(args[0]);
            if (path == NULL)
            {
                fprintf(stderr, "%s: command not found\n", args[0]);
                exit(EXIT_FAILURE);
            }

            if (execve(path, args, 0) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
            free(path);
    }
    else if (pid < 0)
    {
        perror("Fork error");
        exit(EXIT_FAILURE);
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        
    }
}
