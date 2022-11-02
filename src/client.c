#include "macros.h"
#include "net.h"
#include <byteswap.h>
#include <stdlib.h>

#define PRINT_USAGE()                                                                                                                      \
  printf("Usage: %s address port [message]\n", argv[0]);                                                                                   \
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
  if (argc < 3) {
    PRINT_USAGE()
  }

  int err;

  int sock = Socket(DOMAIN, SOCK_STREAM, PROTOCOL);
  ERROR("Socket", sock);

  err = ConnectIP(sock, ADDRESS, PORT);
  ERROR("ConnectIP", err);
  if (err == 0)
    printf("Wrong formatted IP");

  printf("Connecting to %s:%i\n", ADDRESS, PORT);

  struct DATA data;
  data.msg = argv[3];
  data.len = strlen(data.msg);

  Send(sock, &data.len, sizeof(data.len), 0);

  for (int i = 0; i < data.len; i++) {
    data.msg[i] = ~data.msg[i];
  }

  Send(sock, data.msg, strlen(data.msg), 0);

  Close(sock);

  return 0;
}