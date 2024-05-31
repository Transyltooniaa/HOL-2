#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigsegv_handler(int signum) {
    printf("Caught SIGSEGV\n");
    exit(signum);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigsegv_handler;
    sigemptyset(&sa.sa_mask);

    // sa_flags is set to 0 to indicate that no flags are set for the signal handler.
    //  Alternatively, it can be set to SA_RESTART to restart system calls that are interrupted by the signal.
    sa.sa_flags = 0;

    // NULL pointer dereference will cause a segmentation fault
    if (sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    // Cause a segmentation fault
    int *ptr = NULL;
    *ptr = 42;

    return 0;
}
