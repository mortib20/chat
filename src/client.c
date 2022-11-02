#include "net.h"
#include <stdlib.h>
#include <byteswap.h>

#define ERROR(name, err)                                                                                                                   \
  if ((err) == -1)                                                                                                                         \
    perror(name);

#define DOMAIN AF_INET
#define TYPE SOCK_STREAM
#define PROTOCOL 0
#define ADDRESS "127.0.0.1"
#define PORT 3277

struct DATA {
  char *msg;
  uint32_t len;
};

int main(int argc, char *argv[]) {
  int err;

  int sock = Socket(DOMAIN, SOCK_STREAM, PROTOCOL);
  ERROR("Socket", sock);

  err = ConnectIP(sock, ADDRESS, PORT);
  ERROR("ConnectIP", err);
  if (err == 0)
    printf("Wrong formatted IP");

  printf("Connecting to %s:%i\n", ADDRESS, PORT);

  struct DATA data;
  data.msg = argv[1];
  data.len = strlen(data.msg);

  Send(sock, &data.len, sizeof(data.len), 0);

  for(int i = 0; i < data.len; i++)
  {
    data.msg[i] = ~data.msg[i];
  }

  Send(sock, data.msg, strlen(data.msg), 0);

  Close(sock);

  return 0;
}