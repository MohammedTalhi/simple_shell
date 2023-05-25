#include "shell.h"

char *_fill_memory(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return s;
}

void free_string_array(char **strings)
{
	char **p = strings;

	if (!strings)
		return;
	while (*strings)
		free(*strings++);
	free(p);
}

void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return malloc(new_size);
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return ptr;

	p = malloc(new_size);
	if (!p)
		return NULL;

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return p;
}

