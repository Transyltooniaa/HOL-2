#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

// Function to handle the SIGALRM signal
void sigalrm_handler(int signum) {
    printf("Caught SIGALRM signal\n");
    exit(signum); // Exit the program with the signal number
}

int main() {
    // Set up the signal handler for SIGALRM
    struct sigaction sa;
    sa.sa_handler = sigalrm_handler; // Assign the signal handler function
    sigemptyset(&sa.sa_mask); // Clear the signal mask
    sa.sa_flags = 0; // No special flags
    sigaction(SIGALRM, &sa, NULL); // Register the signal handler for SIGALRM

    // Set up the timer
    struct itimerval timer;
    timer.it_value.tv_sec = 2; // Initial time interval: 2 seconds
    timer.it_value.tv_usec = 0; // Microseconds part

    // No repeat interval
    timer.it_interval.tv_sec = 0; 
    timer.it_interval.tv_usec = 0;

    // Start the timer
    setitimer(ITIMER_REAL, &timer, NULL);

    // Print a message indicating waiting for SIGALRM signal
    printf("Waiting for SIGALRM signal...\n");

    // Keep the program running indefinitely
    while (1) {
        // Do nothing, just wait for the signal
    }

    return 0;
}
