#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_PATH "/tmp/myfifo"
#define BUFFER_SIZE 256
#define TIMEOUT_SECONDS 10

int main() {
    int fd;

    // Create the FIFO (named pipe) with error handling
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        if (errno != EEXIST) { // Check if error is not due to existing FIFO
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    // Open the FIFO for reading
    fd = open(FIFO_PATH, O_RDONLY | O_NONBLOCK); // Open in non-blocking mode

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Set up variables for select
    fd_set read_fds;

    // Set the timeout for select using timeval struct, which has seconds and microseconds
    struct timeval timeout;

    // Set the timeout
    timeout.tv_sec = TIMEOUT_SECONDS;
    // Set the microseconds
    timeout.tv_usec = 0;

    // Initialize the file descriptor set
    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);

    // Wait for data to be available in the FIFO or timeout
    int result = select(fd + 1, &read_fds, NULL, NULL, &timeout);

    if (result == -1) {
        perror("select");
        exit(EXIT_FAILURE);
    } else if (result == 0) {
        printf("No data available in FIFO after %d seconds.\n", TIMEOUT_SECONDS);
    } else {
        printf("Data available in FIFO.\n");

        // Read data from the FIFO
        char buf[BUFFER_SIZE];
        ssize_t bytes_read = read(fd, buf, sizeof(buf));

        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Received data from FIFO: %s\n", buf);
    }

    // Close the FIFO
    close(fd);

    return 0;
}
