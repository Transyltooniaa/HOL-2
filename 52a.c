#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>



int main() {
    // Create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define server address
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY; // Use any available IP address 
    server_address.sin_port = htons(5000);

    // Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 5000\n");

    while (1) {
        // Accept incoming connection
        int client_socket;
        int client_address_length = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t *)&client_address_length);
        if (client_socket == -1) {
            perror("Accept failed");
            continue; // Continue to the next iteration of the loop
        }

        // Handle client request
        int pid = fork();
        if (pid == -1) {
            perror("Fork failed");
            close(client_socket);
            continue; // Continue to the next iteration of the loop
        } else if (pid == 0) { // Child process
            close(server_socket); // Close unused copy of server socket

            printf("Handling client %s from child process with pid %d\n", inet_ntoa(client_address.sin_addr), getpid());

            char buf[1000];
            ssize_t bytes_received = read(client_socket, buf, sizeof(buf) - 1);
            if (bytes_received == -1) {
                perror("Read failed");
            } else {
                buf[bytes_received] = '\0'; // Null-terminate the received data
                printf("Message from client: %s\n", buf);
            }

            const char *response_message = "Hello, from server\n";
            ssize_t bytes_sent = write(client_socket, response_message, strlen(response_message));
            if (bytes_sent == -1) {
                perror("Write failed");
            }

            // Close client socket and exit child process
            close(client_socket);
            exit(EXIT_SUCCESS);
        } else { // Parent process
            // Close client socket in parent process
            close(client_socket);
        }
    }

    // Close server socket (not reached in this code)
    close(server_socket);

    return 0;
}
