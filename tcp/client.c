#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    const char* message = "Hello, server!";
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP address from string to binary format
    if (inet_pton(AF_INET, "ServerIpAddr", &serv_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // Send message to the server
    send(sock, message, strlen(message), 0);
    printf("Message sent to the server.\n");

    // Read server response
    valread = read(sock, buffer, BUFFER_SIZE);
    printf("Server response: %s\n", buffer);

	getchar();

    close(sock);

    return 0;
}
