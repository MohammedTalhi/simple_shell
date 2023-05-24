#include "main.h"  // Including the header file "main.h" which likely contains function prototypes, definitions, and other declarations needed for the program.

char *read_line(void)
{
	char *line =  NULL;  // Initializing a pointer to store the input line.
	size_t len = 0;  // Initializing the initial size of the line.
	ssize_t chars = 0;  // Initializing a variable to store the number of characters read.

	/* inbuilt getline */
	chars = getline(&line, &len, stdin);  // Reading a line from the standard input using the getline() function.

	/* custom get line */
	/*chars = get_line(&line);*/  // An alternative custom function to read a line from the standard input.

	if (chars == EOF)  // Checking if the end-of-file indicator is reached.
	{
		free(line);  // Freeing the memory allocated for the line.
		exit(0);  // Exiting the program with a status of 0.
	}

	if (line == NULL)  // Checking if the line is NULL, indicating an error in input.
	{
		write(STDOUT_FILENO, "\n", 1);  // Writing a newline character to the standard output.
		free(line);  // Freeing the memory allocated for the line.
		exit(-1);  // Exiting the program with a status of -1.
	}

	return (line);  // Returning the input line.
}

