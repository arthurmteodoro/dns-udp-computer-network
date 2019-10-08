#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUF_SIZE];
    char *hello = "Hello from server";
    struct sockaddr_in server_addr, client_addr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *) &server_addr,
             sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int n;
    socklen_t len;

    for(;;) {
        n = recvfrom(sockfd, (char *) buffer, BUF_SIZE, MSG_WAITALL, (struct sockaddr *) &client_addr, &len);
        buffer[n] = '\0';

        printf("Client : %s\n", buffer);
        sendto(sockfd, (const char *) hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &client_addr, len);
        printf("Hello message sent.\n");
    }

    return 0;
}