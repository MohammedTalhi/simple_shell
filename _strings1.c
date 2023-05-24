#include "main.h"

/**
 * _strlen - Computes the length of a string.
 * @s: Pointer to the string.
 *
 * Return: The length of the string.
 */

int _strlen(char *s)
{
	int index;

	index = 0;
	while (s[index] != '\0')  /* Loop until the null terminator is reached */
	{
		index++;
	}
	return (index);
}

/**
 * _strcat - CONCATENATE
 * @dest: Pointer to the string 
 * @src: Pointer 
 * Return: Pointer
 */
char *_strcat(char *dest, char *src)
{
	char *destAddress;
	int destLen;

	destAddress = dest;
	destLen = _strlen(dest);  /* Get the length of the destination string */
	destAddress = destAddress + destLen;  /* Move the pointer to the end of the destination string */
	while (*src != '\0')  /* Copy characters from src to the end of dest */
	{
		*destAddress = *src;
		src++;
		destAddress++;
	}
	*destAddress = '\0';  /* Add the null terminator at the end */

	return (dest);
}

/**
 * _check_white_space - Checks for white spaces in a string.
 * @s: Pointer to the string to be checked.
 * Return: The number of white spaces found in the string.
 */

unsigned int _check_white_space(char *s)
{
	int i, count = 0;

	for (i = 0; s[i] != '\0'; i++)  /* Iterate through each character in the string */
	{
		if (s[i]  == ' ' || s[i] == '\t' || s[i] == '\n')  /* Check if the character is a white space */
			count++;  /* Increment the count for each white space found */
	}
	return (count);
}

/**
 * _strtotokens - Splits a string into individual tokens.
 * @str: Pointer to the string to be split.
 * Return: Pointer to an array of tokens (words).
 */

char **_strtotokens(char *str)
{
	int i = 0;
	const char delimeter[] = " \t\n";  /* Delimiters used to split the string */
	int space = _check_white_space(str);  /* Get the count of white spaces in the string */
	char **tokens = malloc(sizeof(char *) * (space + 1));  /* Allocate memory for the array of tokens */
	char *token;

	if (!tokens)  /* Check if memory allocation was successful */
	{
		free(tokens);
		fprintf(stderr, "sh: allocation error\n");
		exit(1);
	}

	token = strtok(str, delimeter);  /* Get the first token using strtok */

	while (token != NULL)  /* Loop until there are no more tokens */
	{
		tokens[i] = token;  /* Store the token in the array */
		token = strtok(NULL, delimeter);  /* Get the next token */
		i++;
	}
	tokens[i] =  NULL;  /* Add a null terminator at the end of the array to mark the end */

	return (tokens);  /* Return the array of tokens */
}

/**
 * _puts - Prints a string, followed by a new line, to the standard output.
 * @str: Pointer to the string to be printed.
 */

void _puts(char *str)
{
	unsigned long i = 0;

	while (str[i] != '\0')  /* Loop until the null terminator is reached */
	{
		_putchar(str[i]);  /* Print each character */
		i++;
	}

	_putchar('\n');  /* Print a new line character at the end */
}

