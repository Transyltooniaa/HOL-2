#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char buffer[100];
    pid_t x;

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a new process
    x = fork();
    if (x == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (x != 0) { // Parent process
        // Close the read end of the pipe in the parent process
        close(fd[0]);

        // Write a message to the pipe
        const char *message = "hello world";
        ssize_t num_written = write(fd[1], message, strlen(message));
        if (num_written == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe in the parent process
        close(fd[1]);
    } else { // Child process
        // Close the write end of the pipe in the child process
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
        printf("Child read: %s\n", buffer);

        // Close the read end of the pipe in the child process
        close(fd[0]);
    }

    return 0;
}
