#include "shell.h"

/**
 * execute_external_command - Executes external commands.
 * @args: Pointer to string arguments.
 * @shell_name: name of shell.
 * @line_number: line number of the current command
 *
 *Return: void.
 */
void execute_external_command(char **args, char *shell_name, int line_number) {
    pid_t pid;
    int status, process_id, exit_status;
    char *command = get_filename(args[0]);
    char *path, *env[] = {"HOME", NULL};

    path = get_path(command);
    if (path == NULL)
	{
		external_comm_error(command, shell_name, line_number);
        free(command);
        return;
    }
    if (_strlen(command) > 0) {
        pid = fork();
        if (pid == 0) {
            exit_status = 0;
            process_id = getpid();
            replace_variables(args, exit_status, process_id);
            if (execve(path, args, env) == -1) {
				execve_error(command, path);
            }
            free(path);
        } else if (pid < 0) {
            perror("Fork error");
            free(path);
            free(command);
            exit(EXIT_FAILURE);
        } else {
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                free(path);
                free(command);
                exit(EXIT_FAILURE);
            }
        }
    }
    free(path);
    free(command);
}

/**
 *create_replacement_string - Create a replacement string object.
 *@value: value replace.
 *Return: Pointer to representation of a value.
 */
char *create_replacement_string(int value) {
	char *str;
    int length = 1;
    int temp = value;

    while (temp > 9) {
        temp /= 10;
        length++;
    }

    str = malloc(length + 2);

    _sprintf(str, "%d", value);
    return str;
}

/**
 *perform_variable_replacement - Replaces the variable occurance in the args.
 *@arg: Arguments.
 *@variable: Pointer to variable occurance.
 *@replacement: Pointer to replacement.
 *Return: pointer to replacement.
 */
char *perform_variable_replacement(char *arg, char *variable, char *replacement) {
    size_t arg_len = _strlen(arg);
    size_t variable_len = _strlen(variable);
    size_t replacement_len = _strlen(replacement);
    char *result = malloc(arg_len + replacement_len + 1);
    char *dest = result;
    char *src = arg;
    char *pos = _strstr(arg, variable);

    while (src < pos) {
        *dest = *src;
        dest++;
        src++;
    }

    src = replacement;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    src = pos + variable_len;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return result;
}

/**
 *replace_variables - Replace variable occurences in a string.
 *@command: String command.
 *@exit_status: Exiting status.
 *@process_id: pid id.
 */
void replace_variables(char **command, int exit_status, int process_id) {
    int i;

    for (i = 0; command[i] != NULL; i++) {
        char *arg = command[i];
        char *pos = _strstr(arg, "$?");
        if (pos != NULL) {
            char *exit_status_str = create_replacement_string(exit_status);
            char *new_arg = perform_variable_replacement(arg, "$?", exit_status_str);
            free(exit_status_str);
            free(command[i]);
            command[i] = new_arg;
        }

        pos = _strstr(arg, "$$");
        if (pos != NULL) {
            char *process_id_str = create_replacement_string(process_id);
            char *new_arg = perform_variable_replacement(arg, "$$", process_id_str);
            free(process_id_str);
            free(command[i]);
            command[i] = new_arg;
        }
    }
}