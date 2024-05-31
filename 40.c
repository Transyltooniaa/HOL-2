#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h> // For strerror
#include <errno.h> // For errno

#ifndef F_GETPIPE_SZ
#define F_GETPIPE_SZ 1032 // This value is system-dependent, please verify it
#endif


int main() {

    
    // Create a pipe
    int p[2];
    if (pipe(p) == -1) {
        perror("pipe creation");
        return 1;
    }

    // Get the size of the pipe using the write end of the pipe
    int size = fcntl(p[1], F_GETPIPE_SZ);
    if (size == -1)
        printf("Error getting pipe size: %s\n", strerror(errno));
    else
        printf("Size of pipe: %d\n", size);

    // Get the maximum number of files that can be opened within a process
    long max_files = sysconf(_SC_OPEN_MAX);
    if (max_files == -1) {
        perror("sysconf");
        return 1;
    }
    printf("Max files opened within a process: %ld\n", max_files);

    return 0;
}