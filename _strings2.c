#include "main.h"  // Including the header file "main.h" which likely contains function prototypes, definitions, and other declarations needed for the program.

int _putchar(char c)
{
    return (write(1, &c, 1));  // Writes the character 'c' to the standard output and returns the number of characters written.
}

int _strcmp(char *s1, char *s2)
{
    int i = 0;

    while (s1[i] != '\0' || s2[i] != '\0')  // Iterates over the characters of both strings until either of them reaches the end.
    {
        if (s1[i] != s2[i])  // Checks if the characters at the corresponding position in both strings are different.
            return (s1[i] - s2[i]);  // Returns the difference between the ASCII values of the characters.
        i++;
    }
    return (0);  // Returns 0 if both strings are identical.
}

int c_atoi(char *s)
{
    int i = 0;
    unsigned int num = 0;

    while (s[i] != '\0')  // Iterates over the characters of the string until it reaches the end.
    {
        if (s[i] >= '0' && s[i] <= '9')  // Checks if the character is a digit (0-9).
            num = num * 10 + (s[i] - '0');  // Converts the character to its corresponding integer value and accumulates it.
        if (s[i] > '9' || s[i] < '0')  // Checks if the character is a non-digit.
            return (-1);  // Returns -1 to indicate an error if a non-digit character is encountered.
        i++;
    }
    return (num);  // Returns the converted integer value.
}

