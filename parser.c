#include "shell.h"

int check_executable_file(char *path)
{
	struct stat st;

	if (!path || stat(path, &st) != 0)
		return 0;

	if (st.st_mode & S_IFREG)
		return 1;

	return 0;
}

char *copy_chars(char *path_str, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
	{
		if (path_str[i] != ':')
			buffer[k++] = path_str[i];
	}

	buffer[k] = '\0';
	return buffer;
}

char *find_command_path(char *path_str, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_str)
		return NULL;

	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (check_executable_file(command))
			return command;
	}

	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = copy_chars(path_str, curr_pos, i);

			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}

			if (check_executable_file(path))
				return path;

			if (!path_str[i])
				break;

			curr_pos = i;
		}
		i++;
	}

	return NULL;
}

