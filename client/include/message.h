#ifndef __MESSAGE__
#define __MESSAGE__

struct message {
  int op;
  char name[256];
  char ip[20];
};
typedef struct message *Message;

void create_message(Message message, char* buffer);
// void decode_message(char* buffer, Message message);

#endif