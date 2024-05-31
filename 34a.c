#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Close stdout
        if (close(STDOUT_FILENO) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }

        // Duplicate the write end of the pipe to stdout
        if (dup(fd[1]) == -1) {
            perror("dup");
            exit(EXIT_FAILURE);
        }

        // Close the read end of the pipe
        if (close(fd[0]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }

        // Close the original write end of the pipe
        if (close(fd[1]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }

        // Execute the "ls -l" command
        execlp("ls", "ls", "-l", NULL);
        perror("execlp"); // This will only run if execlp fails
        exit(EXIT_FAILURE);
    } else { // Parent process
        // Close stdin
        if (close(STDIN_FILENO) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }

        // Duplicate the read end of the pipe to stdin
        if (dup(fd[0]) == -1) {
            perror("dup");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe
        if (close(fd[1]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }

        // Close the original read end of the pipe
        if (close(fd[0]) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }

        // Execute the "wc" command
        execlp("wc", "wc", NULL);
        perror("execlp"); // This will only run if execlp fails
        exit(EXIT_FAILURE);
    }

    // Wait for the child process to finish
    if (wait(NULL) == -1) {
        perror("wait");
        exit(EXIT_FAILURE);
    }

    return 0;
}
