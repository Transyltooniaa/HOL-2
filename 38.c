#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h> // Include errno for error handling

int main()
{
    int fd1 = -1;
    int fd2 = -1;
    char buf[100];

    // Create FIFOs with error handling
    if (mkfifo("myFifo", 0666) == -1) {
        if (errno != EEXIST) { // Check if error is not due to existing FIFO
            perror("mkfifo myFifo");
            exit(EXIT_FAILURE);
        }
    }

    if (mkfifo("yourFifo", 0666) == -1) {
        if (errno != EEXIST) { // Check if error is not due to existing FIFO
            perror("mkfifo yourFifo");
            exit(EXIT_FAILURE);
        }
    }

    int choice = 0;
    printf("1. read/write (program 1)\n2. read/write (program 2)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        // Open FIFOs with error handling
        fd1 = open("myFifo", O_WRONLY);
        if (fd1 == -1) {
            perror("open myFifo for writing");
            exit(EXIT_FAILURE);
        }

        // Write to myFifo
        write(fd1, "Hello from 1 to 2\n", sizeof("Hello from 1 to 2\n"));
        close(fd1);

        // Open yourFifo for reading
        fd2 = open("yourFifo", O_RDONLY);
        if (fd2 == -1) {
            perror("open yourFifo for reading");
            exit(EXIT_FAILURE);
        }

        // Read from yourFifo
        read(fd2, buf, sizeof(buf));
        printf("Message from 2 to 1: %s", buf);
        close(fd2);
        break;

    case 2:
        // Open FIFOs with error handling
        fd2 = open("myFifo", O_RDONLY);
        if (fd2 == -1) {
            perror("open myFifo for reading");
            exit(EXIT_FAILURE);
        }

        // Read from myFifo
        read(fd2, buf, sizeof(buf));
        printf("Message from writer: %s", buf);
        close(fd2);

        // Open yourFifo for writing
        fd1 = open("yourFifo", O_WRONLY);
        if (fd1 == -1) {
            perror("open yourFifo for writing");
            exit(EXIT_FAILURE);
        }

        // Write to yourFifo
        write(fd1, "Hello from 2 to 1\n", sizeof("Hello from 2 to 1\n"));
        close(fd1);
        break;

    default:
        printf("Choose a valid choice\n");
        break;
    }

    // Remove FIFOs
    if (unlink("myFifo") == -1) {
        perror("unlink myFifo");
        exit(EXIT_FAILURE);
    }

    if (unlink("yourFifo") == -1) {
        perror("unlink yourFifo");
        exit(EXIT_FAILURE);
    }

    return (0);
}
