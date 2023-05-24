#include "main.h"  // Including the header file "main.h" which likely contains function prototypes, definitions, and other declarations needed for the program.

void _printenv(void)
{
	int i = 0;

	while (environ[i])  // Looping through the environment variables until a NULL pointer is encountered.
	{
		_puts(environ[i]);  // Printing each environment variable.
		i++;
	}
}

int _isBuiltIn(char *str)
{
	/* check if strings are equal */
	if ((_strcmp(str, "env")) == 0)  // Checking if the input string is equal to "env".
	{
		return (0);  // Returning 0 to indicate that the input is a built-in command.
	}
	if ((_strcmp(str, "exit")) == 0)  // Checking if the input string is equal to "exit".
		return (0);
	if ((_strcmp(str, "setenv")) == 0)  // Checking if the input string is equal to "setenv".
		return (0);
	if ((_strcmp(str, "unsetenv")) == 0)  // Checking if the input string is equal to "unsetenv".
		return (0);
	return (1);  // Returning 1 to indicate that the input is not a built-in command.
}

int _executeBuiltIn(char **tokens)
{
	/* check if first token is equal to string */
	if ((_strcmp(*tokens, "env")) == 0)  // Checking if the first token is equal to "env".
	{
		_printenv();  // Executing the "env" built-in command.
		return (0);
	}
	if ((_strcmp(*tokens, "setenv")) == 0)  // Checking if the first token is equal to "setenv".
	{
		/*check if user inputs it in the form: setenv var_name var_value*/
		if (tokens[1] && tokens[2])  // Checking if both variable name and value are provided.
		{
			_setenv(tokens[1], tokens[2]);  // Calling the function to set the environment variable.
			return (0);
		}
		/*else print an error message*/
		printf("Usage: setenv var_name var_value\n");
		return (0);
	}
	if (_strcmp(*tokens, "unsetenv") == 0)  // Checking if the first token is equal to "unsetenv".
	{
		/*check for var_name to change*/
		if (tokens[1])  // Checking if a variable name is provided.
		{
			_unsetenv(tokens[1]);  // Calling the function to unset the environment variable.
			return (0);
		}
		/*else print an error message*/
		printf("Usage: unsetenv VAR_NAME\n");
		return (0);
	}

	/* will never reach here */
	/* because of _isBuiltin() if check in _execute() */
	return (1);
}

void _exitSimpleShell(char **tokens, char *line)
{
	int status;

	if (tokens[1] != NULL)  // Checking if an exit status is provided.
	{
		status = atoi(tokens[1]);  // Converting the exit status from string to integer.
		if (status >= 0)  // Checking if the exit status is non-negative.
		{
			free(line);  // Freeing the memory allocated for the input line.
			free(tokens);  // Freeing the memory allocated for the tokens.
			exit(status);  // Exiting the shell with the provided exit status.
		}
		write(STDERR_FILENO, "Exit: illegal exit status: ", 28);  // Writing an error message to stderr.
		write(STDERR_FILENO, tokens[1], 1);  // Writing the invalid exit status to stderr.
		write(STDERR_FILENO, "\n", 1);  // Writing a newline character to stderr.
	}
	else
	{
		free(line);  // Freeing the memory allocated for the input line.
		free(tokens);  // Freeing the memory allocated for the tokens.
		exit(0);  // Exiting the shell with a status of 0.
	}
}

