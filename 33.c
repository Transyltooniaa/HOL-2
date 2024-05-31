#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd1[2]; // Pipe 1 for communication from child to parent
    int fd2[2]; // Pipe 2 for communication from parent to child

    // Create pipes and check for errors
    if (pipe(fd1) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (pipe(fd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int x = fork();
    if (x == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (x == 0) { // Child process
        // Close unused ends of the pipes
        close(fd1[0]); // Close read end of fd1
        close(fd2[1]); // Close write end of fd2

        char buff[100];
        char string[] = "Hello parent process";

        // Write to fd1
        if (write(fd1[1], string, sizeof(string)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Read from fd2
        ssize_t num_read = read(fd2[0], buff, sizeof(buff) - 1);
        if (num_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buff[num_read] = '\0'; // Null-terminate the string

        printf("Received from parent process: %s\n", buff);

        // Close used ends of the pipes
        close(fd1[1]);
        close(fd2[0]);
    } else { // Parent process
        // Close unused ends of the pipes
        close(fd1[1]); // Close write end of fd1
        close(fd2[0]); // Close read end of fd2

        char buffer[100];
        char string[] = "Hello child process";

        // Read from fd1
        ssize_t num_read = read(fd1[0], buffer, sizeof(buffer) - 1);
        if (num_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buffer[num_read] = '\0'; // Null-terminate the string

        // Write to fd2
        if (write(fd2[1], string, sizeof(string)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        printf("Received from child process: %s\n", buffer);

        // Wait for the child process to finish
        wait(NULL);

        // Close used ends of the pipes
        close(fd1[0]);
        close(fd2[1]);
    }

    return 0;
}
