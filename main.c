#include "main.h"

/**
 * main - The main function serves as the entry point for the Simple Shell program.
 * @argc: The number of command-line arguments passed to the program.
 * @argv: An array of strings containing the command-line arguments.
 * Return: Returns 0 upon successful execution, otherwise returns 1.
 */

int main(int argc, char *argv[])
{
    char *line; // Stores the user input line
    int Status; // Stores the status of the shell
    char **tokens; // Array of tokens obtained from the user input

    (void)argc; // Suppress unused parameter warning

    signal(SIGINT, ctrlc); // Set up signal handler for Ctrl+C
    Status = 0; // Initialize the shell status

    while (Status == 0)
    {
        prompt(); // Display the shell prompt

        line = read_line(); // Read a line of input from the user

        if (_strcmp(line, "\n") == 0)
        {
            tokens = NULL; // Empty line entered, reset tokens
            free(line); // Free the line buffer
            continue; // Continue to the next iteration of the loop
        }

        tokens = _strtotokens(line); // Tokenize the input line

        if (tokens[0] == NULL)
        {
            free(tokens); // No tokens found, free tokens
            free(line); // Free the line buffer
            continue; // Continue to the next iteration of the loop
        }

        if (_strcmp(tokens[0], "exit") == 0)
        {
            _exitSimpleShell(tokens, line); // Handle the "exit" command
        }
        else
        {
            Status = _execute(tokens, argv[0]); // Execute the command
        }

        free(line); // Free the line buffer
        free(tokens); // Free the tokens array
    }

    return (Status); // Return the final shell status
}

