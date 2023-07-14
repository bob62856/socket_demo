#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8888       // Server port number
#define BUFFER_SIZE 1024       // Maximum buffer size

int main() {
    int server_socket;
    struct sockaddr_in server_address, client_address;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address details
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);

    // Convert IP address from string to binary format
    if (inet_pton(AF_INET, "ServerIpAddr", &server_address.sin_addr) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the server address
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", SERVER_PORT);

    // Receive data from client
    memset(buffer, 0, sizeof(buffer));
    socklen_t client_addr_len = sizeof(client_address);
    int received_bytes = recvfrom(server_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_address, &client_addr_len);
    printf("Received message from client: %s\n", buffer);

    // Process data (e.g., perform some operations or send a response back)
    // ...

    // Send response back to the client
    sendto(server_socket, "Message received.", strlen("Message received."), 0,
           (struct sockaddr*)&client_address, sizeof(client_address));
    printf("Response sent to client.\n");

	getchar();

    // Close the socket
    close(server_socket);

    return 0;
}
