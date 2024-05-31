#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int pipe_fd[2];
    pipe(pipe_fd);

    if (fork() == 0) {
        // Child process
        close(pipe_fd[0]); // Close read end of the pipe
        fcntl(pipe_fd[1], F_SETFD, FD_CLOEXEC); // Close pipe_fd[1] on exec
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to write end of pipe
        close(pipe_fd[1]); // Close pipe_fd[1]
        execlp("ls", "ls", "-l", NULL); // Execute ls -l
    } else {
        // Parent process
        close(pipe_fd[1]); // Close write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to read end of pipe
        close(pipe_fd[0]); // Close pipe_fd[0]
        execlp("wc", "wc", NULL); // Execute wc
    }

    return 0;
}
