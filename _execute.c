#include "shell.h"

/**
 * _execute - Executes a file or command.
 * @tokens: Array of tokens obtained from the input string.
 * @args: Program arguments.
 * Return: 0 if execution is successful, otherwise -1.
 */

int _execute(char **tokens, char *args)
{
    char *err1, *err2, *err3;
    pid_t child_pid;
    int status;
    char *path;

    // Check if the first token is a built-in command
    if (_isBuiltIn(*tokens) == 0)
    {
        status = _executeBuiltIn(tokens);
        return (status);
    }

    // If path wasn't entered (e.g., ls, pwd, etc.)
    path = path_builder(tokens);
    if (path != NULL)
    {
        status = execute2(tokens, path, args);
        return (status);
    }

    // If path was entered (e.g., /bin/ls)
    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error: ");
        return (1);
    }

    if (child_pid == 0)
    {
        // Child process

        // Execute the command
        if (execve(tokens[0], tokens, NULL) == -1)
        {
            // Error occurred during execution
            err1 = _strcat(*tokens, ": No such file or directory\n");
            err2 = _strcat(args, ":");
            err3 = _strcat(err2, err1);
            write(STDERR_FILENO, err3, _strlen(err3));
            free(tokens);
            exit(EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
    }

    // Parent process
    wait(&status);
    return (0);
}

