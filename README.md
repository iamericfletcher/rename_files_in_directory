# Renaming Files with Prefix and Random Suffixes

## Overview
This is a C program that renames files in a specified directory with a new prefix and a suffix. 
The user must provide the directory path and the new prefix as command-line arguments.

This program assumes that the total number of files with the same extension in the directory is less than or equal 
to the number of names in the `names` array. Otherwise, the program will error out since two files cannot have the 
same name. 

Also, the program does not enter nor rename subdirectories.

I plan on making the program more robust such that it can:

1. Handle the case where the number of files with the same extension in the directory is greater than the number of names in the `names` array.
2. Add prefix and suffixes from a file instead of the `names` array.

### Compilation
To compile the program, run the following command in the terminal:

`gcc -o rename_files rename_files.c`

### Usage
To use the program, run the following command in the terminal:

`./rename_files <directory> <new_prefix>`

- `<directory>`: the path to the directory containing the files to be renamed.

- `<new_prefix>`: the new prefix to add to the beginning of the file names.

The program adds a suffix to each file name from the `names` array.

### Dependencies
This program depends on the following C standard libraries:

`<sys/stat.h>`

- Using `stat` instead of `dirent` to check if the file is a directory. The `d_type` member of the `dirent` structure 
is not supported by all file systems, and its availability depends on the operating system and the underlying file 
system.

`errno.h`

`stdio.h`

`string.h`