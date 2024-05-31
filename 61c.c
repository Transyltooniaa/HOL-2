#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigfpe_handler(int signum) {
    printf("Caught SIGFPE\n");
    exit(signum);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigfpe_handler;
    sigemptyset(&sa.sa_mask);

    // sa_flags is set to 0 to indicate that no flags are set for the signal handler.
    //  Alternatively, it can be set to SA_RESTART to restart system calls that are interrupted by the signal.
    sa.sa_flags = 0;

    if (sigaction(SIGFPE, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    // Cause a divide by zero
    int a = 10, b = 0;
    int result = a / b;

    return 0;
}
