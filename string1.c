#include "shell.h"

char *string_copy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return dest;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return dest;
}

char *string_duplicate(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return NULL;
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return NULL;
	for (length++; length--;)
		ret[length] = *--str;
	return ret;
}

void print_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		print_character(str[i]);
		i++;
	}
}

int print_character(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return 1;
}

