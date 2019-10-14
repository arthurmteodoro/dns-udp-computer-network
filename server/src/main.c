#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "message.h"

#define PORT 8080
#define BUF_SIZE 1024

char* get_ip(char* filename, char* name) {
    FILE* file = fopen(filename, "r");
    char line[BUF_SIZE];

    while(fgets(line, BUF_SIZE, file) != NULL) {
        if(line[strlen(line)-1] == '\n')
            line[strlen(line)-1] = '\0';

        char* name_file = strtok(line, " ");
        char* ip = strtok(NULL, " ");

        if(!strcmp(name_file, name)) {
            char* ret = (char*) malloc(sizeof(char)*BUF_SIZE);
            strcpy(ret, ip);

            fclose(file);
            return ret;
        }
    }

    fclose(file);
    return NULL;
}

void save_ip(char* filename, char* name, char* ip) {
    FILE* file = fopen(filename, "a");
    fprintf(file, "%s %s\n", name, ip);
    fclose(file);
}

int main() {
    int sockfd;
    char buffer[BUF_SIZE];
    char *not_found_message = "IP not founded";
    char *ip_saved = "IP saved with success";
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

        struct message message_client;

        decode_message(buffer, &message_client);

        if (message_client.op == 1) {
            char* ip = get_ip("name_ip_list.txt", message_client.name);
            if (ip != NULL) {
                sendto(sockfd, (const char *) ip, strlen(ip), MSG_CONFIRM, (const struct sockaddr *) &client_addr, len);
            } else {
                sendto(sockfd, (const char *) not_found_message, strlen(not_found_message), MSG_CONFIRM, (const struct sockaddr *) &client_addr, len);
            }
        } else if (message_client.op == 2) {
            save_ip("name_ip_list.txt", message_client.name, message_client.ip);
            sendto(sockfd, (const char *) ip_saved, strlen(ip_saved), MSG_CONFIRM, (const struct sockaddr *) &client_addr, len);
        }
    }

    return 0;
}