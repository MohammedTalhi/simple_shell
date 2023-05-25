#include "shell.h"

int is_delimiter(info_t *info, char *buffer, size_t *pos)
{
    size_t j = *pos;

    if (buffer[j] == '|' && buffer[j + 1] == '|')
    {
        buffer[j] = '\0';
        j++;
        info->buffer_type = BUFFER_OR;
    }
    else if (buffer[j] == '&' && buffer[j + 1] == '&')
    {
        buffer[j] = '\0';
        j++;
        info->buffer_type = BUFFER_AND;
    }
    else if (buffer[j] == ';')
    {
        buffer[j] = '\0';
        info->buffer_type = BUFFER_CHAIN;
    }
    else
        return 0;

    *pos = j;
    return 1;
}

void check_buffer(info_t *info, char *buffer, size_t *pos, size_t start, size_t length)
{
    size_t j = *pos;

    if (info->buffer_type == BUFFER_AND)
    {
        if (info->status)
        {
            buffer[start] = '\0';
            j = length;
        }
    }

    if (info->buffer_type == BUFFER_OR)
    {
        if (!info->status)
        {
            buffer[start] = '\0';
            j = length;
        }
    }

    *pos = j;
}

int replace_alias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = find_alias(info->alias, info->arguments[0], '=');
        if (!node)
            return 0;
        free(info->arguments[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return 0;
        p = string_duplicate(p + 1);
        if (!p)
            return 0;
        info->arguments[0] = p;
    }
    return 1;
}

int replace_variables(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->arguments[i]; i++)
    {
        if (info->arguments[i][0] != '$' || !info->arguments[i][1])
            continue;

        if (!_strcmp(info->arguments[i], "$?"))
        {
            free(info->arguments[i]);
            info->arguments[i] = string_duplicate(_itoa(info->status));
            if (!info->arguments[i])
                return 0;
            continue;
        }

        if (info->arguments[i][1] == '?')
        {
            free(info->arguments[i]);
            info->arguments[i] = string_duplicate(_itoa(info->status));
            if (!info->arguments[i])
                return 0;
            continue;
        }

        node = find_env(info, info->arguments[i] + 1, '=');
        if (!node)
            continue;

        free(info->arguments[i]);
        info->arguments[i] = string_duplicate(node->str + _strlen(info->arguments[i]) - 1);
        if (!info->arguments[i])
            return 0;
    }

    return 1;
}

