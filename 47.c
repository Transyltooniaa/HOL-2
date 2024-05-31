#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    key_t key;
    int shmid;
    char *shmaddr;

     // Generate a unique key 
    // ftok generates a key based on a file path and an id
    // . represents the current directory
    // The second argument 'a' is an arbitrary integer value. This value is combined with the inode number of the file specified by the first argument to generate the key.
    if ((key = ftok("/tmp", 'A')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a shared memory segment
    // IPC_CREAT flag is used to create the shared memory segment if it does not already exist.
    // 0666 specifies the permissions for the shared memory segment.
    // The shared memory segment is created with read and write permissions for the owner, group, and others.
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment
    // The shmat() function is used to attach the shared memory segment to the address space of the calling process.
    // The address parameter is set to NULL, indicating that the system should choose a suitable address for the shared memory segment.
    // The flags parameter is set to 0, indicating that the shared memory segment should be attached with read and write permissions.
    // If the shared memory segment is successfully attached, shmat() returns a pointer to the shared memory segment.
    if ((shmaddr = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Write some data to the shared memory
    strncpy(shmaddr, "Hello, shared memory!", SHM_SIZE);


    // Attach with O_RDONLY and check if overwriting is possible
    // The shmat() function can also be used to attach the shared memory segment with read-only permissions.
    // To do this, the flags parameter should be set to SHM_RDONLY.
    // This allows the shared memory segment to be attached with read-only permissions, preventing the calling process from writing to the shared memory segment.
    char *readonly_addr = shmat(shmid, NULL, SHM_RDONLY);
    if (readonly_addr == (char *) -1) {
        perror("shmat O_RDONLY");
        exit(EXIT_FAILURE);
    }

    printf("Data in shared memory (O_RDONLY): %s\n", readonly_addr);

    // Detach the shared memory segment
    // The shmdt() function is used to detach the shared memory segment from the address space of the calling process.
    // If the shared memory segment is successfully detached, shmdt() returns 0.
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Remove the shared memory segment
    // IPC_RMID is used to remove the shared memory segment.
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory removed.\n");

    return 0;
}
