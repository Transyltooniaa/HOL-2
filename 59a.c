#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigsegv_handler(int signum) {
    printf("Caught SIGSEGV signal\n");
    exit(signum);
}

int main() {

    // Register signal handler
    // SIGSEGV is the signal sent to a process when it makes an invalid memory reference, or segmentation fault
    // it is also known as the "segmentation violation" signal
    signal(SIGSEGV, sigsegv_handler);


    // Cause segmentation fault because of NULL pointer dereference 
    int *ptr = NULL;
    *ptr = 10;

    return 0;
}
