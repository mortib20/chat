#include "macros.h"
#include "net.h"
#include <stdlib.h>

#define PRINT_USAGE()                                                                                                                      \
  printf("Usage: %s address port\n", argv[0]);                                                                                             \
  exit(EXIT_SUCCESS);

#define DOMAIN AF_INET
#define TYPE SOCK_STREAM
#define PROTOCOL 0
#define ADDRESS argv[1]
#define PORT atoi(argv[2])

struct DATA {
  signed char *msg;
  uint32_t len;
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    PRINT_USAGE()
  }

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
      data.msg[i] = ~(data.msg[i];
    }

    printf("MSG = %s\n", data.msg);

    Close(client);

    free(data.msg);
  }

  Close(sock);

  return 0;
}