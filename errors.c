#include "shell.h"

/**
 * print_error - Prints an error message.
 * @info: Pointer to the parameter and return info struct.
 * @error_type: String containing the specified error type.
 */
void print_error(info_t *info, char *error_type)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_type);
}

/**
 * print_d - Prints a decimal (integer) number (base 10).
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*print_char)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		print_char = _eputchar;
	if (input < 0)
	{
		absolute_value = -input;
		print_char('-');
		count++;
	}
	else
		absolute_value = input;
	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			print_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	print_char('0' + current);
	count++;

	return (count);
}

