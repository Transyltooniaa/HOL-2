#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/ipc.h>

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

// Remove a semaphore.
int main()
{
    union semun arg;
    key_t key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int semid = semget(key, 1, 0);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    if (semctl(semid, 0, IPC_RMID, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    return 0;
}
