#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>

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


// Pass arg.val as command-line argument.
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./a.out <arg.val>\n");
        exit(1);
    }

    // Generate a unique key for the semaphore set
    union semun arg;

    // Generate a unique key for the semaphore set using ftok
    key_t key = ftok(".", 'a');

    // Create a semaphore set with 1 semaphore, with permissions 0744 [binary semaphore]
    // IPC_CREAT flag is used to create the semaphore set
    int semid = semget(key, 1, IPC_CREAT | 0744);
    if (semid == -1)
    {
        printf("Unable to create semaphore.\n");
    }
    arg.val = atoi(argv[1]);
    int res = semctl(semid, 0, SETVAL, arg);
    if (res == 0)
    {
        printf("arg.val set to: %d\n", arg.val);
    }
    return (0);
}