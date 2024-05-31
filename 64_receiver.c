#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigstop_handler(int signum) {
    printf("Received SIGSTOP signal\n");
    exit(EXIT_SUCCESS);
}

int main() {
    // Register signal handler for SIGSTOP
    signal(SIGSTOP, sigstop_handler);

    printf("Waiting for SIGSTOP signal...\n");
    
    // Infinite loop to keep the program running
    while (1) {
        // Do nothing, just keep the program running
    }

    return 0;
}
