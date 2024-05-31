#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler(int signum) {
    printf("Caught SIGINT\n");
}

int main() {
    struct sigaction sa;
    sa.sa_handler = SIG_IGN; // Ignore SIGINT initially
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Ignore SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("SIGINT is ignored. Press Ctrl+C to trigger it.\n");

    // Wait for user input
    getchar();

    // Reset SIGINT to default action
    sa.sa_handler = SIG_DFL;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("SIGINT is reset to default action.\n");

    // Infinite loop to keep the program running
    while (1) {}

    return 0;
}
