#include "main.h"  // Including the header file "main.h" which likely contains function prototypes, definitions, and other declarations needed for the program.

int if_file_exists(char *s)
{
	struct stat st;  // Creating a struct variable to store file status information.

	return (stat(s, &st));  // Checking if the file with the given path exists by calling the stat() function.
}

char *path_builder(char **tokens)
{
	char path1[100] = "/bin/";  // Initializing the first part of the path with "/bin/".
	char path2[100] = "/usr/bin/";  // Initializing the second part of the path with "/usr/bin/".

	char *finalPath1;  // Declaring a pointer to store the final path.
	char *finalPath2;  // Declaring a pointer to store the final path.

	finalPath1 = _strcat(path1, tokens[0]);  // Concatenating the first part of the path with the command name.

	if ((if_file_exists(finalPath1) == 0))  // Checking if the file exists at the final path.
		return (finalPath1);  // Returning the final path.

	finalPath2 = _strcat(path2, tokens[0]);  // Concatenating the second part of the path with the command name.
	if ((if_file_exists(finalPath2) == 0))  // Checking if the file exists at the final path.
		return (finalPath2);  // Returning the final path.

	return (NULL);  // Returning NULL if the file does not exist at either path.
}

int execute2(char **tokens, char *path, char *args)
{
	char *err1, *err2, *err3;  // Declaring pointers to store error messages.
	pid_t child_pid;  // Declaring a variable to store the process ID of the child process.
	int status;  // Declaring a variable to store the exit status of the child process.

	child_pid = fork();  // Creating a child process.
	if (child_pid == -1)  // Checking if the fork failed.
	{
		perror("Error: ");  // Printing an error message using perror().
		return (1);  // Returning an error status.
	}

	if (child_pid == 0)  // Code executed by the child process.
	{
		tokens[0] = path;  // Replacing the first token with the path.

		if (execve(tokens[0], tokens, NULL) == -1)  // Executing the command with the arguments.
		{
			err1 = _strcat(*tokens, ": No such file or directory\n");  // Creating an error message for a non-existent file or directory.
			err2 = _strcat(args, ":");  // Concatenating the command arguments with ":".
			err3 = _strcat(err2, err1);  // Concatenating the error message parts.
			write(STDERR_FILENO, err3, _strlen(err3));  // Writing the error message to stderr.
			free(tokens);  // Freeing the memory allocated for the tokens.
			exit(EXIT_FAILURE);  // Exiting the child process with a failure status.
		}
		return (EXIT_SUCCESS);
	}
	wait(&status);  // Waiting for the child process to complete.
	return (EXIT_SUCCESS);  // Returning the exit status of the child process.
}

