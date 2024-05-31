#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigfpe_handler(int signum) {
    printf("Caught SIGFPE signal\n");
    exit(signum);
}

int main() {

    // Register signal handler 
    // SIGFPE is the signal sent to a process when it executes an erroneous arithmetic operation, such as division by zero
    // it is also known as the "floating-point exception" signal
    signal(SIGFPE, sigfpe_handler);

    // Cause floating-point exception (division by zero)
    int a = 10, b = 0;
    int result = a / b;

    return 0;
}
