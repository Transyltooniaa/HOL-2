
#! /bin/bash 

echo "enter the file name"
# Prints the message "enter the file name" to prompt the user for input.

read file
# Reads the user's input and assigns it to the variable 'file'.

mknod $file p
# Creates a named pipe (FIFO) with the name specified by the user and stored in the 'file' variable.

echo "Named pipe $file created."
# Informs the user that the named pipe has been created.



# mknod [filename] [type] [major minor]
#  * filename: The name of the file to create.
#  *type: The type of special file. Common types are:
#       *p: Named pipe (FIFO).
#       *b: Block device.
#       *c or u: Character device.