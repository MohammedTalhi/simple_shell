# Simple Shell

This is a simple UNIX command interpreter implemented in C.

## Create List of Allowed Functions and System Calls

The following functions and system calls are used in this project:

- `access` (man 2 access)
- `chdir` (man 2 chdir)
- `close` (man 2 close)
- `closedir` (man 3 closedir)
- `execve` (man 2 execve)
- `exit` (man 3 exit)
- `_exit` (man 2 _exit)
- `fflush` (man 3 fflush)
- `fork` (man 2 fork)
- `free` (man 3 free)
- `getcwd` (man 3 getcwd)
- `getline` (man 3 getline)
- `getpid` (man 2 getpid)
- `isatty` (man 3 isatty)
- `kill` (man 2 kill)
- `malloc` (man 3 malloc)
- `open` (man 2 open)
- `opendir` (man 3 opendir)
- `perror` (man 3 perror)
- `read` (man 2 read)
- `readdir` (man 3 readdir)
- `signal` (man 2 signal)
- `stat` (`__xstat`) (man 2 stat)
- `lstat` (`__lxstat`) (man 2 lstat)
- `fstat` (`__fxstat`) (man 2 fstat)
- `strtok` (man 3 strtok)
- `wait` (man 2 wait)
- `waitpid` (man 2 waitpid)
- `wait3` (man 2 wait3)
- `wait4` (man 2 wait4)
- `write` (man 2 write)
Supported System Calls and Functions

The shell utilizes the following system calls and functions:

access
chdir
close
closedir
execve
exit
_exit
fflush
fork
free
getcwd
getline
getpid
isatty
kill
malloc
open
opendir
perror
read
readdir
signal
stat
lstat
fstat
strtok
wait
waitpid
wait3
wait4
write
Limitations

Advanced features like shell scripting and variable expansion are not supported.
Some advanced shell features may not be fully implemented.
Error handling may be limited for certain scenarios.
Credits

This shell was developed by Mohammed Talhi & Ouiam Charki as a project for Simple_shell. 

License

This project is licensed under the MIT License.