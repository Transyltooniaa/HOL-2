#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler function for SIGINT
void sigint_handler(int signum) {
    printf("Caught SIGINT signal\n");
    exit(signum);
}

int main() {
    // Ignore SIGINT signal
    // SIGINT is the signal sent to a process when the user sends an interrupt signal (Ctrl+C)
    // SIG_IGN is used to ignore the signal
    signal(SIGINT, SIG_IGN);
    printf("SIGINT signal is ignored.\n");

    // Wait for user input to reset SIGINT signal
    printf("Press enter to reset SIGINT signal to default action.\n");
    getchar();

    // Reset SIGINT signal to default action
    signal(SIGINT, SIG_DFL);
    printf("SIGINT signal is reset to default action.\n");

    // Wait for user input to generate SIGINT signal
    printf("Press enter to generate SIGINT signal.\n");
    getchar();

    // Generate SIGINT signal
    raise(SIGINT);

    return 0;
}
