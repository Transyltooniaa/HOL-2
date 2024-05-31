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

int main()
{
    int shm_key = ftok(".", 'C');
    int shm_key2 = ftok(".", 'D');
    int sem_key = ftok(".", 'E');

    // Create 2 shared memory segment - since we need two resoueces
    int shm_id = shmget(shm_key, 1024, IPC_CREAT | 0666);
    int shm_id2 = shmget(shm_key2, 1024, IPC_CREAT | 0666);
    if (shm_id == -1 || shm_id2 == -1)
    {
        printf("Error in shmget call\n");
        return -1;
    }

    // Attach the shared memory segment to process address space
    int *shm_ptr = shmat(shm_id, NULL, 0);
    int *shm_ptr2 = shmat(shm_id2, NULL, 0);
    if (shm_ptr == (void *)-1 || shm_ptr2 == (void *)-1)
    {
        // Error while attaching
        printf("Error in shmat call\n");
        return -1;
    }

    // Initialize the shared data - pointers
    *shm_ptr = 0;
    *shm_ptr2 = 0;

    // Create the semaphores
    int sem_id = semget(sem_key, 1, IPC_CREAT | 0666);
    if (sem_id == -1)
    {
        printf("Error in semget system call\n");
        return -1;
    }

    // Set the semaphore values to 2 - Counting semaphores
    union semun sem_args;
    sem_args.val = 2;
    if (semctl(sem_id, 0, SETVAL, sem_args) == -1)
    {
        printf("Error in semctl system call\n");
        return -1;
    }
}