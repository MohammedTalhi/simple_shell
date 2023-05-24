/***************************************************
 * main.h
 *
 * Header file for the main functions and utilities
 * used in the Simple Shell program.
 ***************************************************/

#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include <dirent.h>
#include <signal.h>

/* External variable to access the environment */
extern char **environ;

/* Function declarations */

void _puts(char *str); // Function to print a string to the standard output
void prompt(void); // Function to display the shell prompt
char *read_line(void); // Function to read a line of input from the user
int _strlen(char *s); // Function to calculate the length of a string
int _strcmp(char *s1, char *s2); // Function to compare two strings
int _executeBuiltIn(char **tokens); // Function to execute built-in shell commands
int _isBuiltIn(char *str); // Function to check if a command is a built-in shell command
int c_atoi(char *s); // Function to convert a string to an integer
void _kill(char *lineptr, char *tmp, char **tok); // Function to handle the "kill" command
void _exitSimpleShell(char **tokens, char *line); // Function to handle the "exit" command
void ctrlc(int signum); // Signal handler for the Ctrl+C signal
int is_delim(char c, const char *delim); // Function to check if a character is a delimiter
char *_strtok(char *src, const char *delim); // Function to tokenize a string
char *_strcpy(char *dest, char *src); // Function to copy a string
char *_strcat(char *dest, char *src); // Function to concatenate two strings
char **_strtotokens(char *str); // Function to convert a string to an array of tokens
int _execute(char **tokens, char *args); // Function to execute a command
void _printenv(void); // Function to print the environment variables
int _putchar(char c); // Function to print a character to the standard output

ssize_t get_line(char **str); // Function to read a line of input from a file
int handle_path(char **tokens); // Function to handle the "path" command
int if_file_exists(char *s); // Function to check if a file exists
char *path_builder(char **tokens); // Function to build the full path of a command
int execute2(char **tokens, char *path, char *args); // Function to execute a command with a specified path
char *var_build(char *var_name, char *var_value); // Function to build an environment variable string
int _setenv(char *var_name, char *var_value); // Function to set an environment variable
int _unsetenv(char *var_name); // Function to unset an environment variable
char *_strdup(char *str); // Function to duplicate a string

#endif  /* MAIN_H */


