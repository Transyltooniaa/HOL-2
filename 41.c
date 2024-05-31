#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    int msgid;

    // Generate a unique key 
    // ftok generates a key based on a file path and an id
    // . represents the current directory
    // The second argument 'a' is an arbitrary integer value. This value is combined with the inode number of the file specified by the first argument to generate the key.
    key_t key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create or access a message queue
    // IPC_CREAT creates the message queue if it does not exist
    // 0644 is the permission for the message queue to be created
    // The message queue ID is returned by msgget
    // The key is used to identify the message queue
    msgid = msgget(key, IPC_CREAT | 0644);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // You can think of msgget() as a function that registers or retrieves a message queue with the kernel, using the provided key. Once registered or retrieved, the kernel assigns an ID to the message queue and manages it internally.

    // Output key and message queue ID
    printf("Key value is %d\n", key);
    printf("Key value in hex is 0x%x\n", key);
    printf("Message queue ID is %d\n", msgid);

    return 0;
}
