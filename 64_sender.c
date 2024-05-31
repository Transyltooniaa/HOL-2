#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    // Get the process ID of the receiver program
    pid_t receiver_pid = 63359; // NOTE - THIS PID WILL ALWAYS CHANGE. YOU HAVE TO FIND THE PID OF THE RECEIVER PROGRAM ON A THIRD TERMINAL AND THEN PUT IT IN PLACE OF THE "receiver_pid" VARIABLE EACH TIME YOU WANT TO CHECK THE 64TH QUESTION.

    // Send SIGSTOP signal to the receiver program
    if (kill(receiver_pid, SIGSTOP) == -1) {
        perror("kill");
        exit(EXIT_FAILURE);
    }

    printf("SIGSTOP signal sent to the receiver program\n");

    return 0;
}
