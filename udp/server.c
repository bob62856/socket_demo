#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[1000];
    int n;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(22000);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 1024);

    for (;;) {
        connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

        while ((n = read(connfd, buff, 1000)) > 0) {
            write(connfd, buff, n);
        }

        close(connfd);
    }

    return 0;
}

