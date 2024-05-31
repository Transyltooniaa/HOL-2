#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds buf;

    // Generate a unique key 
    // ftok generates a key based on a file path and an id
    // . represents the current directory
    // The second argument 'a' is an arbitrary integer value. This value is combined with the inode number of the file specified by the first argument to generate the key.
    if ((key = ftok(".", 'a')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create or access a message queue
    // IPC_CREAT creates the message queue if it does not exist
    // 0644 is the permission for the message queue to be created
    // The message queue ID is returned by msgget
    // The key is used to identify the message queue
    if ((msgid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Get information about the message queue
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    // Access permission
    printf("Access permission: %o\n", buf.msg_perm.mode);

    // UID and GID
    printf("UID of owner: %d\n", buf.msg_perm.uid);
    printf("GID of owner: %d\n", buf.msg_perm.gid);

    // Time of last message sent and received
    printf("Time of last message sent: %s", ctime(&buf.msg_stime));
    printf("Time of last message received: %s", ctime(&buf.msg_rtime));

    // Time of last change in the message queue
    printf("Time of last change in the message queue: %s", ctime(&buf.msg_ctime));

    // Number of messages in the queue
    printf("Number of messages in the queue: %ld\n", buf.msg_qnum);

    // Maximum number of bytes allowed
    printf("Maximum number of bytes allowed: %ld\n", buf.msg_qbytes);

    // PID of the msgsnd and msgrcv
    printf("PID of the msgsnd: %d\n", buf.msg_lspid);
    printf("PID of the msgrcv: %d\n", buf.msg_lrpid);

    return 0;
}
// In this program, we first generate a key using ftok() and then create a message queue using msgget(). 
// We then use msgctl() with IPC_STAT to get information about the message queue. The information includes access permissions, UID and GID of the owner, time of last message sent and received, time of last change in the message queue, number of messages in the queue, maximum number of bytes allowed, and the PIDs of the msgsnd and msgrcv operations. We print this information to the console.