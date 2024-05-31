#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main() {

    // Create socket
    // AF_INET: IPv4, SOCK_STREAM: TCP, 0: IP
    // 0 is the protocol value for IP, which is the default protocol
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define server address
    struct sockaddr_in server_address;

    // Address family is AF_INET, IP address of the host is INADDR_ANY, port number is 5000
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

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

    // Accept incoming connection
    struct sockaddr_in client_address;
    int client_socket;
    int client_address_length = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t *)&client_address_length);
    if (client_socket == -1) {
        perror("Accept failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Read data from client
    char buffer[100];
    ssize_t bytes_received = read(client_socket, buffer, sizeof(buffer));
    if (bytes_received == -1) {
        perror("Read failed");
        close(client_socket);
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Display received data
    // STDOUT_FILENO is a file descriptor for standard output
    write(STDOUT_FILENO, buffer, bytes_received);

    // Send response to client
    const char *response_message = "This is a message from the server\n";
    ssize_t bytes_sent = write(client_socket, response_message, strlen(response_message));
    
    if (bytes_sent == -1) {
        perror("Write failed");
        close(client_socket);
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
