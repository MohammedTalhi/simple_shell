#include "shell.h"

/**
 * list_len - Determines the length of the linked list
 * @h: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * list_to_strings - Converts the list of strings to an array of strings
 * @head: Pointer to the first node
 *
 * Return: Array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t count = list_len(head);
	char **strs;
	size_t i;

	if (!head || !count)
		return (NULL);

	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		strs[i] = _strdup(node->str);
		if (!strs[i])
		{
			while (i > 0)
				free(strs[--i]);
			free(strs);
			return (NULL);
		}
	}

	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - Prints all elements of a list_t linked list
 * @h: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * node_starts_with - Returns the node whose string starts with the prefix
 * @node: Pointer to the list head
 * @prefix: String to match
 * @c: The next character after prefix to match
 *
 * Return: Matched node or NULL
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}

	return (NULL);
}

/**
 * get_node_index - Gets the index of a node
 * @head: Pointer to the list head
 * @node: Pointer to the node
 *
 * Return: Index of the node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}

	return (-1);
}

