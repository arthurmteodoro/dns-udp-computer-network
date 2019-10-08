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

// void decode_message(char* buffer, Message message);