#include "shell.h"

/**
 * get_shell_history_file - gets the shell history file
 * @info: structure containing potential arguments
 *
 * Return: allocated string containing the shell history file
 */
char *get_shell_history_file(info_t *info)
{
	char *buffer, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(SHELL_HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, SHELL_HIST_FILE);
	return (buffer);
}

/**
 * write_shell_history - writes the shell history to a file
 * @info: the structure containing potential arguments
 *
 * Return: 1 on success, -1 on failure
 */
int write_shell_history(info_t *info)
{
	ssize_t file_descriptor;
	char *filename = get_shell_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_descriptor == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}

	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * read_shell_history - reads the shell history from a file
 * @info: the structure containing potential arguments
 *
 * Return: the number of lines read from the history file, or 0 on failure
 */
int read_shell_history(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stat;
	char *buffer = NULL, *filename = get_shell_history_file(info);

	if (!filename)
		return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);
	if (file_descriptor == -1)
		return (0);

	if (!fstat(file_descriptor, &file_stat))
		file_size = file_stat.st_size;

	if (file_size < 2)
		return (0);

	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);

	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = '\0';
	if (read_length <= 0)
		return (free(buffer), 0);

	close(file_descriptor);

	for (i = 0; i < file_size; i++)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			build_shell_history_list(info, buffer + last, line_count++);
			last = i + 1;
		}
	}

	if (last != i)
		build_shell_history_list(info, buffer + last, line_count++);

	free(buffer);
	info->history_count = line_count;

	while (info->history_count-- >= SHELL_HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_shell_history(info);
	return (info->history_count);
}

/**
 * build_shell_history_list - adds an entry to the shell history linked list
 * @info: the structure containing potential arguments
 * @buffer: the buffer containing the history entry
 * @line_count: the history line count
 *
 * Return: Always 0
 */
int build_shell_history_list(info_t *info, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buffer, line_count);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumber_shell_history - renumbers the shell history linked list after changes
 * @info: the structure containing potential arguments
 *
 * Return: the new history count
 */
int renumber_shell_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->history_count = i);
}

