#include "shell.h"

/**
 * buffer_input - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of length var
 *
 * Return: bytes read
 */
ssize_t buffer_input(info_t *info, char **buffer, size_t *length)
{
	ssize_t read_bytes = 0;
	size_t length_pos = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buffer);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, interruptHandler);
#if USE_GETLINE
		read_bytes = getline(buffer, &length_pos, stdin);
#else
		read_bytes = _getline(info, buffer, &length_pos);
#endif
		if (read_bytes > 0)
		{
			if ((*buffer)[read_bytes - 1] == '\n')
			{
				(*buffer)[read_bytes - 1] = '\0'; /* remove trailing newline */
				read_bytes--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->history_count++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*length = read_bytes;
				info->cmd_buffer = buffer;
			}
		}
	}
	return (read_bytes);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t i, j, length;
	ssize_t read_bytes = 0;
	char **buffer_pos = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	read_bytes = buffer_input(info, &buffer, &length);
	if (read_bytes == -1) /* EOF */
		return (-1);
	if (length) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buffer position */
		p = buffer + i; /* get pointer for return */

		check_chain(info, buffer, &j, i, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (is_chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= length) /* reached end of buffer? */
		{
			i = length = 0; /* reset position and length */
			info->cmd_buffer_type = CMD_NORM;
		}

		*buffer_pos = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buffer_pos = buffer; /* else not a chain, pass back buffer from _getline() */
	return (read_bytes); /* return length of buffer from _getline() */
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @pos: size
 *
 * Return: read_bytes
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *pos)
{
	ssize_t read_bytes = 0;

	if (*pos)
		return (0);
	read_bytes = read(info->readfd, buffer, READ_BUF_SIZE);
	if (read_bytes >= 0)
		*pos = read_bytes;
	return (read_bytes);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t read_bytes = 0, size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		size = *length;
	if (i == len)
		i = len = 0;

	read_bytes = read_buffer(info, buffer, &len);
	if (read_bytes == -1 || (read_bytes == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, size, size ? size + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (size)
		_strncat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);

	size += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = size;
	*ptr = p;
	return (size);
}

/**
 * interruptHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void interruptHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

