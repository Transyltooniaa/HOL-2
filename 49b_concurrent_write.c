#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

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



// IN this program, we will create a shared memory and semaphore.
//  We will write to the shared memory from parent and child processes.
//  We will use semaphore to lock the shared memory while writing.




int main()
{
    union semun arg;    

    // Generate a unique key for the shared memory and semaphore
    key_t key = ftok(".", 'a');
    
    // Create a shared memory segment with the generated key, with permissions 0744
    int shmid = shmget(key, 1024, IPC_CREAT | 0744);
    
    // Create a semaphore set with one semaphore, with permissions 0744
    int semid = semget(key, 1, IPC_CREAT | 0744);
    
    // Attach the shared memory segment to the process's address space
    char *data = shmat(shmid, (void *)0, 0);

    // Fork a new process
    int pid = fork();
    if (pid == 0)
    {
        // Child process
        
        // Lock the semaphore (decrement operation)
        struct sembuf buf = {0, -1, SEM_UNDO};
        int retval = semop(semid, &buf, 1);
        
        printf("Child is writing\n");
        printf("Enter the text: ");
        scanf("%[^\n]s", data);
        printf("Data written by child\n");

        // Unlock the semaphore (increment operation)
        buf.sem_op = 1;
        semop(semid, &buf, 1);
        return 0;
    }
    else
    {
        // Parent process
        
        // Lock the semaphore (decrement operation)
        struct sembuf buf = {0, -1, SEM_UNDO};
        int retval = semop(semid, &buf, 1);
        int wstatus;

        printf("Parent is writing\n");
        printf("Enter the text: ");
        scanf("%[^\n]s", data);
        printf("Data written by Parent\n");

        // Unlock the semaphore (increment operation)
        buf.sem_op = 1;
        
        // Wait for the user to press return to ensure the child process has time to write
        getchar();
        getchar();

        // Unlock the semaphore (increment operation)
        semop(semid, &buf, 1);
        
        // Wait for the child process to terminate
        waitpid(pid, &wstatus, W_OK);
    }

    // Fetch and print data from the shared memory
    printf("Data: %s\n", data);
    
    // Detach the shared memory segment from the process's address space
    shmdt(data);
    
    // Remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
