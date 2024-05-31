#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler(int signum) {
    printf("Caught SIGINT signal\n");
    exit(signum);
}

int main() {

    // Register signal handler
    // SIGINT is the signal sent to a process when the user sends an interrupt signal (Ctrl+C)
    // it is also known as the "program interrupt" signal
    signal(SIGINT, sigint_handler);

    printf("Waiting for SIGINT signal...\n");
    while (1) {
        // Do nothing
    }

    return 0;
}
