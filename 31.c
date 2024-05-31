#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// The program creates a pipe and writes a message to it

int main() {
    int fd[2]; // File descriptors for the pipe
    char buffer[100]; // Buffer to read data from the pipe

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Write a message to the pipe
    const char *message = "hello";

    // Write to the pipe - write end of the pipe is fd[1]
    ssize_t num_written = write(fd[1], message, strlen(message));
    if (num_written == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Close the write end of the pipe
    close(fd[1]);

    // Read from the pipe
    ssize_t num_read = read(fd[0], buffer, sizeof(buffer) - 1);
    if (num_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Null-terminate the buffer to make it a proper string
    buffer[num_read] = '\0';

    // Print the content to the terminal
    printf("Read from pipe: %s\n", buffer);

    // Close the read end of the pipe
    close(fd[0]);

    return 0;
}
