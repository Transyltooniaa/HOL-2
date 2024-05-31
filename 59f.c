#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

// Function to handle the SIGVTALRM signal
void sigvtalrm_handler(int signum) {
    printf("Caught SIGVTALRM signal\n");
    exit(signum); // Exit the program with the signal number
}

int main() {
    // Set up the signal handler for SIGVTALRM
    struct sigaction sa;
    sa.sa_handler = sigvtalrm_handler; // Assign the signal handler function
    sigemptyset(&sa.sa_mask); // Clear the signal mask
    sa.sa_flags = 0; // No special flags
    sigaction(SIGVTALRM, &sa, NULL); // Register the signal handler for SIGVTALRM

    // Set up the timer
    struct itimerval timer;
    timer.it_value.tv_sec = 2; // Initial time interval: 2 seconds
    timer.it_value.tv_usec = 0; // Microseconds part
    timer.it_interval.tv_sec = 0; // No repeat interval
    timer.it_interval.tv_usec = 0;

    // Start the timer
    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    // Print a message indicating waiting for SIGVTALRM signal
    printf("Waiting for SIGVTALRM signal...\n");

    // Keep the program running indefinitely
    while (1) {
        // Do nothing, just wait for the signal
    }

    return 0;
}
