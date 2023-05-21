#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer sizes for read and write */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* Command chaining types */
#define CMD_NORMAL 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Conversion options for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Flag for using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

/**
 * Struct list_node - Singly linked list node
 * @num: The number field
 * @str: A string
 * @next: Pointer to the next node
 */
typedef struct list_node
{
	int num;
	char *str;
	struct list_node *next;
} list_t;

/**
 * Struct command_info - Contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for function pointers
 * @arg: A string generated from getline containing arguments
 * @argv: An array of strings generated from arg
 * @path: A string path for the current command
 * @argc: The argument count
 * @line_count: The error count
 * @err_num: The error code for exit() calls
 * @count_flag: If set, count this line of input
 * @filename: The program filename
 * @env_list: Linked list local copy of environ
 * @environ: Custom modified copy of environ from env_list
 * @history: The history node
 * @alias: The alias node
 * @env_changed: Set if environ was changed
 * @status: The return status of the last executed command
 * @command_buffer: Address of pointer to command buffer, used for chaining
 * @command_type: Command type (CMD_NORMAL, CMD_OR, CMD_AND)
 * @read_fd: The file descriptor from which to read line input
 * @hist_count: The history line number count
 */
typedef struct command_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int count_flag;
	char *filename;
	list_t *env_list;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **command_buffer; /* Pointer to command buffer for chaining */
	int command_type; /* Command type (CMD_NORMAL, CMD_OR, CMD_AND) */
	int read_fd;
	int hist_count;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * Struct built_in_command - Contains a built-in command string and its
 * corresponding function
 * @name: The built-in command name
 * @func: The corresponding function
 */
typedef struct built_in_command
{
	char *name;
	int (*func)(info_t *);
} built_in_table;

/* shell_loop.c */
int start_shell(info_t *, char **);
int find_built_in(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* parser.c */
int is_command(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_command_path(info_t *, char *, char *);

/* loophsh.c */
int loop_shell(char **);

/* errors.c */
void error_puts(char *);
int error_putchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* string.c */
int string_length(char *);
int string_compare(char *, char *);
char *string_starts_with(const char *, const char *);
char *string_concatenate(char *, char *);

/* string1.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void regular_puts(char *);
int regular_putchar(char);

/* exits.c */
char *string_copy_n(char *, char *, int);
char *string_concatenate_n(char *, char *, int);
char *string_find_char(char *, char);

/* tokenizer.c */
char **string_tokenize(char *, char *);
char **string_tokenize_2(char *, char);

/* realloc.c */
char *memory_set(char *, char, unsigned int);
void free_memory(char **);
void *memory_reallocate(void *, unsigned int, unsigned int);

/* memory.c */
int block_free(void **);

/* atoi.c */
int interactive_mode(info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int convert_to_integer(char *);

/* errors1.c */
int error_atoi(char *);
void print_error_message(info_t *, char *);
int print_decimal(int, int);
char *convert_to_string(long int, int, int);
void remove_comments(char *);

/* builtin.c */
int exit_builtin(info_t *);
int change_directory_builtin(info_t *);
int help_builtin(info_t *);

/* builtin1.c */
int history_builtin(info_t *);
int alias_builtin(info_t *);

/* getLine.c */
ssize_t get_user_input(info_t *);
int get_line(info_t *, char **, size_t *);
void sigint_handler(int);

/* getinfo.c */
void clear_command_info(info_t *);
void set_command_info(info_t *, char **);
void free_command_info(info_t *, int);

/* environ.c */
char *get_environment_variable(info_t *, const char *);
int environment_builtin(info_t *);
int set_environment_variable_builtin(info_t *);
int unset_environment_variable_builtin(info_t *);
int populate_environment_list(info_t *);

/* getenv.c */
char **get_environment(info_t *);
int unset_environment_variable(info_t *, char *);
int set_environment_variable(info_t *, char *, char *);

/* history.c */
char *get_history_file(info_t *info);
int write_history_file(info_t *info);
int read_history_file(info_t *info);
int build_history_list(info_t *info, char *buffer, int line_count);
int renumber_history_list(info_t *info);

/* lists.c */
list_t *add_list_node(list_t **, const char *, int);
list_t *add_list_node_end(list_t **, const char *, int);
size_t print_string_list(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list_nodes(list_t **);

/* lists1.c */
size_t list_length(const list_t *);
char **list_to_string_array(list_t *);
size_t print_generic_list(const list_t *);
list_t *find_node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* vars.c */
int is_command_chained(info_t *, char *, size_t *);
void check_command_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_variables(info_t *);
int replace_string_values(char **, char *);

#endif /* _SHELL_H_ */

