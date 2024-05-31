#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigalrm_handler(int signum) {
    printf("Caught SIGALRM signal\n");
    exit(signum);
}

int main() {

    // Register signal handler
    // SIGALRM is the signal sent to a process when the timer set by the alarm function expires
    // it is also known as the "alarm clock" signal
    signal(SIGALRM, sigalrm_handler);

    // Set alarm for 2 seconds
    alarm(2);

    printf("Waiting for SIGALRM signal...\n");
    while (1) {
        // Do nothing
    }

    return 0;
}
