#include "main.h"

/**
 * _setenv - Updates or adds an environment variable.
 * @var_name: The name of the variable to be updated or added.
 * @var_value: The value to set for the variable.
 * Return: 0 if the operation is successful, otherwise -1.
 */

int _setenv(char *var_name, char *var_value)
{
    int i = 0;
    size_t name_len;
    char *var_new;

    name_len = _strlen(var_name);
    i = 0;

    // Updating an existing variable
    while (environ[i])
    {
        if (strncmp(environ[i], var_name, name_len) == 0)
        {
            var_new = var_build(var_name, var_value);

            // Clearing the memory before writing
            environ[i] = NULL;

            // Updating the environment variable
            environ[i] = _strdup(var_new);
            free(environ[i]);
            environ[i] = _strdup(var_new);
            free(var_new);
            return (0);
        }
        i++;
    }

    // Adding a variable that never existed before
    var_new = var_build(var_name, var_value);
    free(environ[i]);
    environ[i] = _strdup(var_new);
    i++;
    environ[i] = NULL;
    var_new = NULL;

    return (0);
}

/**
 * var_build - Builds an environment variable string from its name and value.
 * @var_name: The name of the variable.
 * @var_value: The value of the variable.
 * Return: A string containing the full environment variable.
 */

char *var_build(char *var_name, char *var_value)
{
    char *new_var;
    size_t var_len;

    var_len = _strlen(var_name) + _strlen(var_value) + 2;
    new_var = malloc(sizeof(char) * var_len);
    if (new_var == NULL)
    {
        perror("Error: Insufficient memory\n");
        return (NULL);
    }
    memset(new_var, 0, var_len);

    // Data in the form: var_name=var_value
    new_var = _strcat(new_var, var_name);
    new_var = _strcat(new_var, "=");
    new_var = _strcat(new_var, var_value);

    return (new_var);
}

/**
 * _unsetenv - Removes an environment variable.
 * @var_name: Variable name.
 * Return: 0 if successful, -1 otherwise.
 */
int _unsetenv(char *var_name)
{
    int i = 0;
    char **env_temp;
    size_t name_len;

    name_len = _strlen(var_name);

    while (environ[i])
    {
        if (strncmp(environ[i], var_name, name_len) == 0)
        {
            env_temp = environ;

            // Freeing the memory of the environment variable
            free(env_temp[0]);

            do {
                env_temp[0] = env_temp[1];
                env_temp++;
            } while (*env_temp);
        }
        i++;
    }

    return (0);
}

