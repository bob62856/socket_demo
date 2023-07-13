#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in servaddr;
    char sendline[1000];
    char recvline[1000];

    if (argc != 2) {
        printf("usage: ./client <IP address>\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (fgets(sendline, 10000, stdin) != NULL) {
        write(sockfd, sendline, strlen(sendline));
        read(sockfd, recvline, 10000);
        printf("%s", recvline);
    }

    return 0;
}
