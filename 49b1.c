#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SHM_SIZE 1024

#if defined(__APPLE__) && defined(__MACH__)
    // Apple platforms do not need union semun to be defined as it's already in the system headers
#else
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
};
#endif

// This program creates a shared memory segment and a semaphore to be used by other programs
// It does so by creating a shared memory segment of size 1024 and a semaphore with value 1
// The shared memory segment is then attached to the process address space
// The shared memory segment is then initialized to 0



int main()
{

    // Generate unique keys for shared memory and semaphore
    // Current directory and different id to differentiate
    int shm_key = ftok(".", 'S');
    int sem_key = ftok(".", 'T');

    // Create the shared memory segment of size 1024
    int shm_id = shmget(shm_key, 1024, IPC_CREAT | 0666);
    int sem_id = semget(sem_key, 1, IPC_CREAT | 0666);

    // Set the semaphore value to 1 - Binary semaphore
    union semun sem_args;
    sem_args.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_args) == -1)
    {
        printf("Error in semctl system call\n");
        return -1;
    }

    // Attach the shared memory segment to process address space
    int *shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *)-1)
    {
        // Error while attaching
        printf("Error in shmat call\n");
        return -1;
    }

    // Initialize the shared data - pointer
    *shm_ptr = 0;
}