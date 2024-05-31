#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        printf("Child process (PID: %d) created.\n", getpid());

        // Sleep for a while to give the parent process time to continue execution
        sleep(2);

        // Send SIGKILL to the parent process
        if (kill(getppid(), SIGKILL) == -1) {
            perror("kill");
            return 1;
        }

        printf("SIGKILL signal sent to the parent process.\n");
    } else {
        // Parent process
        printf("Parent process (PID: %d) created.\n", getpid());
        while(1){}
        // Orphan process - parent exits immediately
        printf("Parent process exits, creating an orphan process.\n");
        exit(0);
    }

    return 0;
}