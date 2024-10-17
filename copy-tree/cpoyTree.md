# Implementing a Directory Copy Library in C

implement a C library that provides functionalities similar to Python's shutil.copytree. This library will allow users to copy entire directory trees, including files and subdirectories, from a source location to a destination location, while handling symbolic links and file permissions as specified by flags.

## File Descriptions

### `copy_content.c`  
This file contains the `copy_content` function, which handles the copying of file contents from a source to a destination. It opens both the source and destination files, reads the contents of the source file into a dynamically allocated buffer, and writes it to the destination file. If requested, it also copies the file permissions. It includes error handling for file operations to ensure robustness.

### `copy_directory.c`  
This file implements the `copy_directory` function, which recursively copies the contents of a source directory to a destination directory. It opens the source directory, creates the corresponding destination directory, and iterates through each entry. If an entry is a directory, it calls itself recursively; otherwise, it calls `copy_file` to copy files.

### `copy_file.c`  
This file defines the `copy_file` function, which determines whether to copy files as symbolic links or regular files based on user input. If the `copy_symlinks` flag is set, it calls the `copySymlinks` function; otherwise, it uses the `copy_content` function to copy the file's content.

### `copy_symlinks.c`  
This file contains the `copySymlinks` function, which handles the copying of symbolic links. It checks if the source path is a symbolic link and, if so, reads its target. It adjusts the link path if necessary and copies the contents of the target file to the destination, ensuring the link structure is preserved if specified.

### `copytree.h`  
This header file contains the declarations of functions used in the `copy-tree` project. It defines function prototypes for copying files, directories, symbolic links, and creating directories recursively. It also includes necessary macros and includes to ensure code modularity and reusability.

### `create_directory_recursive.c`  
This file implements the `create_directory_recursive` function, which creates a directory and all necessary parent directories. It iterates through the path, creating each segment as needed. It includes error handling to ensure that the directory structure is created properly.

### `main.c`  
The main entry point for the application. This file handles command-line arguments for the source and destination directories, as well as flags for copying symbolic links and file permissions. It orchestrates the copying process by invoking the `copy_directory` function and provides usage information if the input is incorrect.
