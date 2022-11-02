#include "net.h"
#include <stdlib.h>

#define ERROR(name, err)                                                                                                                   \
  if ((err) == -1)                                                                                                                         \
    perror(name);

#define DOMAIN AF_PACKET
#define TYPE SOCK_RAW
#define PROTOCOL 0
#define ADDRESS "0.0.0.0"
#define PORT 3277

struct DATA {
  char *msg;
  uint32_t len;
};

int main(void) {
  int err;

  int sock = Socket(DOMAIN, TYPE, PROTOCOL);
  ERROR("Socket", sock);

  Reuseaddr(sock, 1);

  err = BindIP(sock, ADDRESS, PORT);
  ERROR("BindIP", err);
  if (err == 0)
    printf("Wrong formatted IP");

  err = Listen(sock, 10);
  ERROR("Listen", err)

  printf("Listening on %s:%i\n", ADDRESS, PORT);

  for (;;) {
    int client = Accept(sock, NULL, NULL);
    Reuseaddr(client, 1);

    struct DATA data;

    Recv(client, &data.len, sizeof(data.len), 0);
    printf("Len = %i\n", data.len);

    data.msg = (char *)malloc(sizeof(char) * data.len);

    Recv(client, data.msg, data.len, 0);

    for (int i = 0; i < data.len; i++) {
      data.msg[i] = ~data.msg[i];
    }

    printf("MSG = %s\n", data.msg);

    Close(client);

    free(data.msg);
  }

  Close(sock);

  return 0;
}