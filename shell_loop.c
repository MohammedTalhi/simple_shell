#include "shell.h"

int shell_loop(info_t *info, char **av)
{
    ssize_t input_status = 0;
    int builtin_status = 0;

    while (input_status != -1 && builtin_status != -2)
    {
        clear_info(info);
        if (is_interactive(info))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        input_status = get_input(info);
        if (input_status != -1)
        {
            set_info(info, av);
            builtin_status = find_builtin_command(info);
            if (builtin_status == -1)
                find_command(info);
        }
        else if (is_interactive(info))
            _putchar('\n');
        free_info(info, 0);
    }
    write_history(info);
    free_info(info, 1);
    if (!is_interactive(info) && info->status)
        exit(info->status);
    if (builtin_status == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return (builtin_status);
}

int find_builtin_command(info_t *info)
{
    int i, builtin_status = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            builtin_status = builtintbl[i].func(info);
            break;
        }
    return (builtin_status);
}

void find_command(info_t *info)
{
    char *path = NULL;
    int i, arg_count;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, arg_count = 0; info->arg[i]; i++)
        if (!is_delimiter(info->arg[i], " \t\n"))
            arg_count++;
    if (!arg_count)
        return;

    path = find_command_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_command(info);
    }
    else
    {
        if ((is_interactive(info) || _getenv(info, "PATH=")
                || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
            fork_command(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

void fork_command(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environ(info)) == -1)
        {
            free_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}

