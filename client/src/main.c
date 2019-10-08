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
int main(int argc, char* argv[]) {
    if (argc == 2 && !strcmp("-h", argv[1])) {
        printf("Usage: \n");
        printf("client <mode> <name> [IP address]\n");
        printf("\nModes:\n");
        printf("\t1 - for translate name to IP address\n");
        printf("\t2 - for save name and IP in server\n");
        printf("name: server name. Example: www.google.com\n");
        printf("IP address: IP address to respective server name\n");
        printf("\n\nUsage examples:\n");
        printf("\tGet IP adress: client 1 www.google.com\n");
        printf("\tSave IP address in server: client 2 www.google.com 172.217.29.228\n");

        exit(EXIT_SUCCESS);
    }

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