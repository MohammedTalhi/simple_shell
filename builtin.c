#include "shell.h"

/**
 * custom_exit - Exits the shell.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int custom_exit(info_t *info)
{
    int exit_status;

    if (info->argv[1]) /* If there is an exit argument */
    {
        exit_status = err_atoi(info->argv[1]);
        if (exit_status == -1)
        {
            info->status = 2;
            print_error_msg(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return (1);
        }
        info->err_num = err_atoi(info->argv[1]);
        return (-2);
    }
    info->err_num = -1;
    return (-2);
}

/**
 * custom_cd - Changes the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0.
 */
int custom_cd(info_t *info)
{
    char *current_dir, *target_dir, buffer[1024];
    int chdir_ret;

    current_dir = getcwd(buffer, 1024);
    if (!current_dir)
        _puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        target_dir = _getenv(info, "HOME=");
        if (!target_dir)
            chdir_ret = /* TODO: what should this be? */
                chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
        else
            chdir_ret = chdir(target_dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(current_dir);
            _putchar('\n');
            return (1);
        }
        _puts(_getenv(info, "OLDPWD=")), _putchar('\n');
        chdir_ret = /* TODO: what should this be? */
            chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
    }
    else
        chdir_ret = chdir(info->argv[1]);
    if (chdir_ret == -1)
    {
        print_error_msg(info, "can't cd to ");
        _eputs(info->argv[1]), _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * custom_help - Provides help information.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0.
 */
int custom_help(info_t *info)
{
    char **arguments;

    arguments = info->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arguments); /* temp att_unused workaround */
    return (0);
}

