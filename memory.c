#include "shell.h"

/**
 * bfree - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 *
 * This function frees the memory allocated for the pointer and sets the pointer
 * to NULL to avoid any dangling references.
 *
 * Return: 1 if the pointer was freed successfully, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

