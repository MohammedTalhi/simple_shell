#include "main.h"  // Including the header file "main.h" which likely contains function prototypes, definitions, and other declarations needed for the program.

int is_delim(char c, const char *delim)
{
	while (delim && *delim)  // Looping through the characters of the delimiter string.
	{
		if (c == *delim)  // Checking if the character 'c' matches the current delimiter character.
		{
			return (1);  // Returning 1 if 'c' is a delimiter.
		}
		++delim;  // Moving to the next character in the delimiter string.
	}
	return (0);  // Returning 0 if 'c' is not a delimiter.
}

char *_strtok(char *src, const char *delim)
{
	static char *s;
	static unsigned int i;
	char *result = NULL;
	int is_space = 0;

	if (src)
	{
		s = src;
		for (i = 0; s[i]; i++)
		{
			if (is_delim(s[i], delim))  // Checking if the current character is a delimiter.
				s[i] = '\0';  // Replacing the delimiter character with null termination.
		}
	}

	if (s == NULL || *s == '\0')
		return (NULL);

	result = s;  // Setting the result to the current position in the string.
	i = _strlen(s);  // Getting the length of the current token.
	if (s[i] == '\0' && _strlen(s) > 0)
		is_space = 1;  // Checking if the current token is followed by whitespace.
	s = s + _strlen(s) + is_space;  // Moving the position to the start of the next token.
	return (result);  // Returning the current token.
}

void ctrlc(int signum)
{
	(void)signum;

	write(STDOUT_FILENO, "\n#cisfun$ ", 10);  // Writing the prompt string to the standard output after a Ctrl+C signal is received.
}

ssize_t get_line(char **str)
{
	ssize_t i = 0, size = 0, t = 0, t2 = 0, n = 0;
	char buff[1024];

	/* read while there's stdin greater than buffsize; -1 to add a '\0' */
	while (t2 == 0 && (i = read(STDIN_FILENO, buff, 1024 - 1)))  // Reading input from stdin until there's no more data or a newline is encountered.
	{
		if (i == -1) /* check if read errored */
			return (-1);

		buff[i] = '\0'; /* terminate buff with \0 to use with _strcat */

		n = 0; /* last loop if \n is found in the stdin read */
		while (buff[n] != '\0')  // Looping through the characters of the input buffer.
		{
			if (buff[n] == '\n')  // Checking if a newline character is found.
				t2 = 1;  // Setting a flag to indicate that a newline is encountered.
			n++;
		}

		/* copy what's read to buff into get_line's buffer */
		if (t == 0) /* malloc the first time */
		{
			i++;
			*str = malloc(sizeof(char) * i);  // Allocating memory for the first time to store the input.
			*str = _strcpy(*str, buff);  // Copying the input to the allocated memory.
			size = i;  // Storing the size of the input.
			t = 1;  // Setting a flag to indicate that memory has been allocated.
		}
		else /* _realloc via _strcat with each loop */
		{
			size += i;  // Incrementing the total size of the input.
			*str = _strcat(*str, buff);  // Concatenating the input with the existing buffer.
		}
	}
	return (size);  // Returning the size of the input.
}

/**
 *  _strdup - Duplicates string.
 *  @str: String to duplicate.
 *  Return: Pointer to duplicated string in allocated memory.
 */
char *_strdup(char *str)
{
	char *duplicate_str;
	int i, len = 0;

	if (str == NULL)
		return (NULL);
	while (str[len])
		len++;
	len++;  // Incrementing the length to account for the null terminator.
	duplicate_str = malloc(sizeof(char) * len);  // Allocating memory for the duplicated string.
	if (duplicate_str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		duplicate_str[i] = str[i];  // Copying each character from the original string to the duplicated string.
		i++;
	}
	return (duplicate_str);  // Returning the duplicated string.
}

