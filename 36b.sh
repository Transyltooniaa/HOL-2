#! /bin/bash
# This line specifies that the script should be run using the Bash shell.

echo "enter the file name"
# Prints the message "enter the file name" to prompt the user for input.

read file
# Reads the user's input and assigns it to the variable 'file'.

mkfifo $file
# Creates a named pipe (FIFO) with the name specified by the user and stored in the 'file' variable.

echo "Named pipe $file created."
