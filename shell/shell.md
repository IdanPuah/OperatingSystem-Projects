# Shell Project Documentation

This project implements a simple shell that can execute commands, change directories, print the working directory, and maintain a history of executed commands.

## File Descriptions

### 1. `main.c`
Contains the `main` function, which sets the new PATH environment variable based on command-line arguments and starts the shell.

### 2. `exec_command.c`
Implements the `execCommand` function, which forks a new process to execute a command using `execvp` and waits for the command to complete.

### 3. `free_args.c`
Implements the `freeArgs` function, which frees the memory allocated for the command arguments.

### 4. `get_input.c`
Implements the `getInput` function, which reads a line of input from the user, splits it into command arguments, and stores them in an array.

### 5. `set_path.c`
Implements the `setPath` function, which constructs a new PATH string from the provided command-line arguments and sets it as the new PATH environment variable.

### 6. `change_directory.c`
Implements the `changeDirectory` function, which changes the current working directory to the specified path.

### 7. `print_working_directory.c`
Implements the `printWorkingDirectory` function, which prints the current working directory to the console.

### 8. `display_history.c`
Implements the `displayHistory` function, which prints the command history stored in an array.

### 9. `shell.c`
Implements the `shell` function, which manages the main loop of the shell, handles user input, and executes built-in commands and other commands.

### 10. `utils.h`
Header file that declares the utility functions used throughout the project.
