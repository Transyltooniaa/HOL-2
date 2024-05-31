#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#define MAX_MSG_SIZE 256

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
};

int main() {
    int msgid;

    // Generate a unique key 
    // ftok generates a key based on a file path and an id
    // . represents the current directory
    // The second argument 'a' is an arbitrary integer value. This value is combined with the inode number of the file specified by the first argument to generate the key.
    key_t key;
    if ((key = ftok(".", 'a')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create or access the message queue
    // Create or access a message queue
    // IPC_CREAT creates the message queue if it does not exist
    // 0644 is the permission for the message queue to be created
    // The message queue ID is returned by msgget
    // The key is used to identify the message queue
    if ((msgid = msgget(key, IPC_CREAT | 0644)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    struct msg_buffer buf;

    // Receive a message from the queue
    ssize_t bytes_received;
    if ((bytes_received = msgrcv(msgid, &buf, MAX_MSG_SIZE, 1L, IPC_NOWAIT)) == -1) {
        if (errno == ENOMSG) {
            printf("No message available in the queue.\n");
        } else {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
    } else {
        // Print the received message
        buf.msg_text[bytes_received] = '\0'; // Ensure null-termination
        printf("Received message: %s\n", buf.msg_text);
    }

    return 0;
}


// The IPC_NOWAIT flag, when used with the msgrcv() function, 
// specifies that the function should not wait for a message to become available if the message queue is currently empty.
//  Instead, if no message is immediately available, the msgrcv() function returns immediately with an error indicating that no message is available, rather than blocking (waiting) until a message arrives.
