#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main() {
    // Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(8080);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Send message to server
    const char *message = "This is a message from the client\n";
    ssize_t bytes_sent = write(client_socket, message, strlen(message));
    if (bytes_sent == -1) {
        perror("Write failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Receive response from server
    char buffer[100];
    ssize_t bytes_received = read(client_socket, buffer, sizeof(buffer));
    if (bytes_received == -1) {
        perror("Read failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Display response from server
    printf("Server response: %s\n", buffer);

    // Close socket
    close(client_socket);

    return 0;
}
