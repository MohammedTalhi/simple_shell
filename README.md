Project 0x16 - C - Simple Shell

This project is a simple UNIX command interpreter, also known as a shell, implemented in the C programming language. The purpose of this shell is to provide basic command execution functionality similar to the popular Unix shell, /bin/sh.

Contributors

Mohammed Talhi
Ouiam Charki
Description

The project implements a basic shell that allows users to interact with the underlying operating system by executing various commands. It provides a command prompt where users can input commands, which are then executed and their output displayed on the terminal.

List of Allowed Functions and System Calls

The following functions and system calls are allowed to be used in this project:

access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getcwd (man 3 getcwd)
getline (man 3 getline)
getpid (man 2 getpid)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)
Please ensure that your implementation adheres to the guidelines and restrictions mentioned in the project requirements.

Getting Started

To run the shell and interact with it, follow these steps:

Clone the repository: $ git clone https://github.com/your-username/your-repository.git
Compile the source code: $ gcc -Wall -Werror -Wextra -pedantic *.c -o shell
Run the shell: $ ./shell
The command prompt will be displayed. You can now enter commands and press Enter to execute them.
Usage

The shell supports the execution of various commands available in your system, as well as some built-in commands. You can enter both single commands and command pipelines.

Here are a few examples:

Execute a single command: $ ls -l
Execute multiple commands in a pipeline: $ ls | grep shell
Change directory: $ cd /path/to/directory
Exit the shell: $ exit
Please note that this is a basic shell implementation and may not support all the features and functionalities of a full-fledged shell.


