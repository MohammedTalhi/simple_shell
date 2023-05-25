#include "shell.h"

/**
 * prompt - Print prompt.
 * Return: Void.
 */
void prompt(void)
{
    if (isatty(STDIN_FILENO))  // Checking if the standard input is a terminal.
    {
        write(STDOUT_FILENO, "#cisfun$ ", 9);  // Writing the prompt string "#cisfun$ " to the standard output.
    }
}

