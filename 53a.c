#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h> // Include for the pause() function


// Signal handler for the timer expiration
// signum: signal number (in this case, SIGALRM)
void timer_handler(int signum) {
    printf("Timer expired.\n");
    // EXIT_SUCCESS: status code indicating successful program execution.
    exit(EXIT_SUCCESS);
}


int main() {

    // itimerval struct for setting the timer for both the initial expiration and subsequent intervals
    // sigaction struct for setting the signal handler 
    struct itimerval timer;
    struct sigaction sa;

    // Set up the signal handler
    // sa_handler: pointer to the signal handler function
    sa.sa_handler = timer_handler;

    // Set the sa_flags field to 0
    sa.sa_flags = 0;

    // Initialize the signal set to empty
    // This is done to avoid blocking any signals while the handler is running(some signals are blocked by default when the handler is running)
    // This is not necessary in this case, but it is good practice
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Set timer expiration
    timer.it_value.tv_sec = 10;         // 10 seconds
    timer.it_value.tv_usec = 0;          // No microseconds

    // Set timer interval to 0 to make it a one-shot timer(only expires once)
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;


    // Start the timer
    // ITIMER_REAL: decrements in real time, and delivers SIGALRM upon expiration
    // timer: pointer to the itimerval struct
    // NULL: old value of the timer (not needed here)
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    // Wait for the timer to expire (no busy-wait loop needed)
    pause();

    return 0;
}
// ITIMER_REAL measures real time.
// ITIMER_VIRTUAL measures CPU time consumed by the process in user mode.
// ITIMER_PROF measures CPU time consumed by the process in both user and kernel mode, as well as time spent in blocking I/O operations.