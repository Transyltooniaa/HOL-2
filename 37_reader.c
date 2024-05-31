// Program to read data from the FIFO

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_FILE "fifo_test2"
#define BUFFER_SIZE 100

int main() {
    // Buffer to store the data read from the FIFO file
    char buffer[BUFFER_SIZE];

    // Open the FIFO file in read mode
    int fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open FIFO file");
        return 1;
    }

    // Read data from the FIFO file
    // ssize_t is used to represent the size of objects in bytes
    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read == -1) {
        perror("Failed to read from FIFO file");
        close(fd);
        return 1;
    }

    // Null-terminate the buffer to ensure it is a valid string
    buffer[bytes_read] = '\0';

    // Print the data read from the FIFO file
    printf("Data read from FIFO file: %s\n", buffer);

    // Close the file descriptor
    close(fd);

    return 0;
}
