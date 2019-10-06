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

/* Driver code */
int main() {
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in server_addr;

    /* Creating socket file descriptor */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    /* Filling server information */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int n;
    socklen_t len;

    char message[] = "Ola mundo";

    sendto(sockfd, (const char *) message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &server_addr, sizeof(server_addr));
    printf("Hello message sent.\n");

    n = recvfrom(sockfd, (char *) buffer, BUF_SIZE, MSG_WAITALL, (struct sockaddr *) &server_addr, &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    close(sockfd);
    return 0;
}