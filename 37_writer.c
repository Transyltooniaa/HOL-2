// Program to write data into the FIFO

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE "fifo_test2"

int main() {
    // Open the FIFO file in write mode
    int fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open FIFO file");
        return 1;
    }

    // Write message into the FIFO file
    const char* message = "Hello, FIFO!";
    ssize_t bytes_written = write(fd, message, strlen(message));
    if (bytes_written == -1) {
        perror("Failed to write to FIFO file");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    close(fd);

    printf("Data written to FIFO file successfully!\n");

    return 0;
}
