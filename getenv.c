#include "shell.h"

/**
 * get_shell_environment - returns a copy of the shell environment
 * @info: Structure containing potential arguments. Used to maintain
 *          consistent function prototype.
 * Return: Copy of the shell environment as a string array
 */
char **get_shell_environment(info_t *info)
{
	if (!info->environment || info->env_changed)
	{
		info->environment = list_to_string_array(info->env_list);
		info->env_changed = 0;
	}

	return (info->environment);
}

/**
 * unset_shell_variable - Remove a shell environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        consistent function prototype.
 * @variable: The name of the environment variable to unset
 * Return: 1 if the variable is successfully unset, 0 otherwise
 */
int unset_shell_variable(info_t *info, char *variable)
{
	list_t *node = info->env_list;
	size_t index = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env_list), index);
			index = 0;
			node = info->env_list;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * set_shell_variable - Initialize a new shell environment variable
 *                      or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        consistent function prototype.
 * @variable: The name of the environment variable
 * @value: The value to assign to the environment variable
 * Return: Always 0
 */
int set_shell_variable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env_list;
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env_list), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

