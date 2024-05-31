#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#define MAX_MSG_SIZE 256

// Define a structure for the message buffer
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

    // Prepare the message buffer
    struct msg_buffer buf;

    // Set the message type to 1 (arbitrary value) and copy the message text
    buf.msg_type = 1L;
    strcpy(buf.msg_text, "hello");


    // Send the message
    if (msgsnd(msgid, &buf, strlen(buf.msg_text) + 1, 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message sent successfully: %s\n", buf.msg_text);

    return 0;
}
// In this program, we first generate a key using ftok() and then create a message queue using msgget().
// We prepare a message buffer structure with a message type and text. We then send the message using msgsnd(). If the message is sent successfully, we print a success message to the console. If there is an error, we print an error message using perror() and exit with a failure status.