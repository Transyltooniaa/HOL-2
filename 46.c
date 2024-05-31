#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;

    // Generate a key for the message queue
     // Generate a unique key 
    // ftok generates a key based on a file path and an id
    // . represents the current directory
    // The second argument 'a' is an arbitrary integer value. This value is combined with the inode number of the file specified by the first argument to generate the key.
    if ((key = ftok("/tmp", 'A')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the message queue ID
    // Create or access a message queue
    // IPC_CREAT creates the message queue if it does not exist
    // 0644 is the permission for the message queue to be created
    // The message queue ID is returned by msgget
    // The key is used to identify the message queue
    if ((msgid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Remove the message queue
    // IPC_RMID is used to remove the message queue.
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Message queue removed successfully.\n");

    return 0;
}
