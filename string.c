#include "shell.h"

int string_length(char *s)
{
	int length = 0;

	if (!s)
		return 0;

	while (*s++)
		length++;
	return length;
}

int string_compare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return *s1 - *s2;
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return 0;
	else
		return *s1 < *s2 ? -1 : 1;
}

char *find_prefix(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return NULL;
	return (char *)haystack;
}

char *string_concatenate(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return result;
}

