#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    key_t key;
    int msgid;

    // This structure is used to hold information about the attributes of a message queue, such as permissions, ownership, and other properties.
    struct msqid_ds buf;

    // Generate a unique key 
    // ftok generates a key based on a file path and an id
    // . represents the current directory
    // The second argument 'A' is an arbitrary integer value. This value is combined with the inode number of the file specified by the first argument to generate the key.
    if ((key = ftok("/tmp", 'A')) == -1) {
        perror("error in ftok");
        exit(EXIT_FAILURE);
    }

    // Get the message queue ID
    // Create or access a message queue
    // IPC_CREAT creates the message queue if it does not exist
    // 0644 is the permission for the message queue to be created
    // The message queue ID is returned by msgget
    // The key is used to identify the message queue
    if ((msgid = msgget(key, IPC_CREAT | 0644)) == -1) {
        perror("error in msgget");
        exit(EXIT_FAILURE);
    }

    // Get current attributes of the message queue
    // IPC_STAT is used to get the current attributes of the message queue.
    // The attributes are stored in the msqid_ds structure pointed to by the third argument.
    // msgctl() is used to perform various operations on a message queue, such as getting or setting attributes, sending control commands, and removing the message queue.
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("error in msgctl");
        exit(EXIT_FAILURE);
    }

    // Change permissions to read and write for everyone
    buf.msg_perm.mode = 0633;

    // Update the attributes of the message queue
    if (msgctl(msgid, IPC_SET, &buf) == -1) {
        perror("Permissions could not be changed");
        exit(EXIT_FAILURE);
    }

    printf("Message queue permissions changed successfully.\n");

}