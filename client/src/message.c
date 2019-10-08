#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"

void create_message(Message message, char* buffer) {
  if (message->op == 1) {
    strcpy(buffer, "1 ");
    strcat(buffer, message->name);
  } else {
    strcpy(buffer, "2 ");
    strcat(buffer, message->name);
    strcat(buffer, " ");
    strcat(buffer, message->ip);
  }
}

void decode_message(char* buffer, Message message) {
  char buf[1024];
  strcpy(buf, buffer);

  char* token = strtok(buf, " ");
  message->op = atoi(token);
  
  token = strtok(NULL, " ");
  strcpy(message->name, token);

  if (message->op == 2) {
    token = strtok(NULL, " ");

    strcpy(message->ip, token);
  }
}