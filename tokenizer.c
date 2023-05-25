#include "shell.h"

char **split_string(char *str, char *delimiter)
{
	int i, j, k, m, num_words = 0;
	char **result;

	if (str == NULL || str[0] == '\0')
		return NULL;
	if (!delimiter)
		delimiter = " ";

	for (i = 0; str[i] != '\0'; i++) {
		if (!is_delimiter(str[i], delimiter) && (is_delimiter(str[i + 1], delimiter) || !str[i + 1]))
			num_words++;
	}

	if (num_words == 0)
		return NULL;

	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return NULL;

	for (i = 0, j = 0; j < num_words; j++) {
		while (is_delimiter(str[i], delimiter))
			i++;

		k = 0;
		while (!is_delimiter(str[i + k], delimiter) && str[i + k])
			k++;

		result[j] = malloc((k + 1) * sizeof(char));
		if (!result[j]) {
			for (k = 0; k < j; k++)
				free(result[k]);
			free(result);
			return NULL;
		}

		for (m = 0; m < k; m++)
			result[j][m] = str[i++];

		result[j][m] = '\0';
	}

	result[j] = NULL;
	return result;
}

char **split_string2(char *str, char delimiter)
{
	int i, j, k, m, num_words = 0;
	char **result;

	if (str == NULL || str[0] == '\0')
		return NULL;

	for (i = 0; str[i] != '\0'; i++) {
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
				    (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
			num_words++;
	}

	if (num_words == 0)
		return NULL;

	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return NULL;

	for (i = 0, j = 0; j < num_words; j++) {
		while (str[i] == delimiter && str[i] != delimiter)
			i++;

		k = 0;
		while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
			k++;

		result[j] = malloc((k + 1) * sizeof(char));
		if (!result[j]) {
			for (k = 0; k < j; k++)
				free(result[k]);
			free(result);
			return NULL;
		}

		for (m = 0; m < k; m++)
			result[j][m] = str[i++];

		result[j][m] = '\0';
	}

	result[j] = NULL;
	return result;
}

