#include "shell.h"

/**
 * count_nodes - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t count_nodes(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * list_to_array - returns an array of strings from the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_array(list_t *head)
{
	list_t *node = head;
	size_t count = count_nodes(head);
	size_t i, j;
	char **strings;
	char *str;

	if (!head || !count)
		return (NULL);
	strings = malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strings[i] = str;
	}
	strings[i] = NULL;
	return (strings);
}


/**
 * print_linked_list - prints all elements of a linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_linked_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * find_node_starts_with - returns node whose string starts with prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @next_char: the next character after prefix to match
 *
 * Return: matching node or NULL
 */
list_t *find_node_starts_with(list_t *head, char *prefix, char next_char)
{
	char *p = NULL;

	while (head)
	{
		p = starts_with(head->str, prefix);
		if (p && ((next_char == -1) || (*p == next_char)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
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

