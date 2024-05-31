#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8000
#define MAX_CLIENTS 5

// Function to handle client connections
void *handle_connection(void *arg) {
    int client_socket = *((int *)arg);
    char buffer[1000];
    
    // Read message from client
    ssize_t bytes_received = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_received == -1) {
        perror("Read failed");
        close(client_socket);
        pthread_exit(NULL);
    }
    
    buffer[bytes_received] = '\0'; // Null-terminate the received data
    printf("Message from client: %s\n", buffer);

    // Send response to client
    const char *response_message = "Hello from server\n";
    ssize_t bytes_sent = write(client_socket, response_message, strlen(response_message));
    if (bytes_sent == -1) {
        perror("Write failed");
    }

    // Close client socket
    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int server_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length;
    pthread_t thread_id;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address parameters
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept and handle client connections
    while (true) {
        client_address_length = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length);
        if (client_socket == -1) {
            perror("Accept failed");
            continue; // Continue to the next iteration of the loop
        }

        // Create a new thread to handle the client connection
        // NULL is used for default thread attributes
        // The thread function is handle_connection
        // The last argument is a pointer to the client socket file descriptor which is a parameter to the thread function
        if (pthread_create(&thread_id, NULL, handle_connection, (void *)&client_socket) != 0) {
            perror("Thread creation failed");
            close(client_socket);
            continue; // Continue to the next iteration of the loop
        }
    }

    // Close server socket (not reached in this code)
    close(server_socket);
    return 0;
}
