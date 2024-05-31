#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h> // Include errno for error handling

#define FIFO_PATH "/tmp/my_fifo"

int main() {
    // Create the FIFO (named pipe) with error handling
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        if (errno != EEXIST) { // Check if error is not due to existing FIFO
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    // Open the FIFO for reading and writing
    int fd = open(FIFO_PATH, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Loop for communication
    while (1) {
        char buffer[256];

        // Read from the FIFO
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        } else if (bytes_read == 0) { // No data to read, client might have closed the connection
            printf("Client has closed the connection.\n");
            break;
        }

        // Null-terminate the string
        buffer[bytes_read] = '\0';

        // Display the message received from the client
        printf("Client: %s\n", buffer);

        // Check if the client wants to exit
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Get input from the server
        printf("Server: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        // Write to the FIFO
        ssize_t bytes_written = write(fd, buffer, strlen(buffer));
        if (bytes_written == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    // Close the FIFO
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    // Remove the FIFO
    if (unlink(FIFO_PATH) == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}
