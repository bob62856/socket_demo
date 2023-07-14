#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8888       // Server port number
#define BUFFER_SIZE 1024       // Maximum buffer size

int main(int argc, char *argv[]) {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

	if (argc <= 1) {
		perror("Enter server address ip argument");
		exit(EXIT_FAILURE);
	}

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address details
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, argv[1], &(server_address.sin_addr)) <= 0) {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

    // Send data to server
    printf("Enter message: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&server_address, sizeof(server_address));
    printf("Message sent to server.\n");

    // Receive response from server
    memset(buffer, 0, sizeof(buffer));
    socklen_t server_addr_len = sizeof(server_address);
    recvfrom(client_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&server_address, &server_addr_len);
    printf("Server response: %s\n", buffer);

	getchar();

    // Close the socket
    close(client_socket);

    return 0;
}
