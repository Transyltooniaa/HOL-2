#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>

// Define the `ticket` structure
struct ticket {
    char train_name[50]; // Use fixed-size array for storing train name
    int ticket_num;
};

// Check if `union semun` is already defined, and define it only if it is not.
#if !defined(_SEM_SEMUN_UNDEFINED) && !defined(_LINUX_SEM_H) && !defined(SEMCTL_H)
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};
#endif

int main() {
    // Open or create the file
    int fd = open("ticket_record.txt", O_RDWR | O_CREAT, 0744);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Initialize a ticket record
    struct ticket ticket1;
    snprintf(ticket1.train_name, sizeof(ticket1.train_name), "Rajdhani");
    ticket1.ticket_num = 100;

    // Write the ticket to the file
    if (write(fd, &ticket1, sizeof(struct ticket)) == -1) {
        perror("write");
        close(fd);
        exit(1);
    }

    // Print the ticket details
    printf("Train name: %s\n", ticket1.train_name);
    printf("Ticket number: %d\n", ticket1.ticket_num);

    // Close the file
    close(fd);

    // Create a semaphore
    key_t key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int sem_id = semget(key, 1, IPC_CREAT | 0666);
    if (sem_id == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the semaphore
    union semun arg;
    arg.val = 1;
    if (semctl(sem_id, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    return 0;
}
