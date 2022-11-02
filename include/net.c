#include "net.h"

/**
 * @brief Create an endpoint for communication
 *
 * @param domain
 * @param type
 * @param protocol
 * @return int
 */
int Socket(int domain, int type, int protocol) {
  int sock;

  sock = socket(domain, type, protocol);

  if (sock == -1)
    return -1;

  return sock;
}

/**
 * @brief Bind a name to a socket
 *
 * @param sockfd
 * @param addr
 * @param addrlen
 * @return int
 */
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) { return bind(sockfd, addr, addrlen); }

/**
 * @brief Bind IPv4 to socket
 *
 * @param sockfd
 * @param address
 * @return int
 */
int BindV4(int sockfd, struct sockaddr_in address) { return Bind(sockfd, (struct sockaddr *)&address, sizeof(address)); }

/**
 * @brief Bind IPv6 to socket
 *
 * @param sockfd
 * @param address
 * @return int
 */
int BindV6(int sockfd, struct sockaddr_in6 address) { return Bind(sockfd, (struct sockaddr *)&address, sizeof(address)); }

/**
 * @brief Bind an IPv4 or IPv6 address to socket
 *
 * @param sockfd
 * @param address
 * @param port
 * @return int
 */
int BindIP(int sockfd, const char *address, uint16_t port) {
  int err;
  int domain;
  int optlen = sizeof(domain);

  if (Getsockopt(sockfd, SOL_SOCKET, SO_DOMAIN, &domain, &optlen) == -1)
    return -1;

  if (domain == AF_INET) {
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = domain;
    addr.sin_port = htons(port);
    err = inet_pton(AF_INET, address, &addr.sin_addr);

    if (err <= 0) {
      if (err == 0) {
        return 0; // Something went wrong
      } else {
        return -1; // Wrong format of address
      }
    }

    if (BindV4(sockfd, addr) == -1)
      return -1;
  }

  if (domain == AF_INET6) {
    int err;
    struct sockaddr_in6 addr;

    memset(&addr, 0, sizeof(addr));

    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(port);
    err = inet_pton(AF_INET6, address, &addr.sin6_addr);

    if (err <= 0) {
      if (err == 0) {
        return 0; // Something went wrong
      } else {
        return -1; // Wrong format of address
      }
    }

    if (BindV6(sockfd, addr) == -1)
      return -1;
  }

  return 1;
}

/**
 * @brief Listen for connections on a socket
 *
 * @param sockfd
 * @param backlog
 * @return int
 */
int Listen(int sockfd, int backlog) {
  if (listen(sockfd, backlog) == -1) {
    perror("LISTEN");
    return -1;
  }

  return 0;
}

/**
 * @brief Accept a connection on a socket
 *
 * @param sockfd
 * @param addr
 * @param addrlen
 * @return int
 */
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
  int sock;

  sock = accept(sockfd, addr, addrlen);

  if (sock == -1)
    return -1;

  return sock;
}

/**
 * @brief Initiate a connection on a socket
 *
 * @param sockfd
 * @param addr
 * @param addrlen
 * @return int
 */
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  if (connect(sockfd, addr, addrlen) == -1) {
    perror("CONNECT");
    return -1;
  }

  return 0;
}

/**
 * @brief Connect to IPv4 socket
 *
 * @param sockfd
 * @param address
 * @return int
 */
int ConnectV4(int sockfd, struct sockaddr_in address) { return Connect(sockfd, (struct sockaddr *)&address, sizeof(address)); }

/**
 * @brief Connect to IPv6 socket
 *
 * @param sockfd
 * @param address
 * @return int
 */
int ConnectV6(int sockfd, struct sockaddr_in6 address) { return Connect(sockfd, (struct sockaddr *)&address, sizeof(address)); }

/**
 * @brief Connect to IPv4 or IPv6
 * 
 * @param sockfd 
 * @param address 
 * @param port 
 * @return int 
 */
int ConnectIP(int sockfd, const char *address, uint16_t port) {
  int err;
  int domain;
  int optlen = sizeof(domain);

  if (Getsockopt(sockfd, SOL_SOCKET, SO_DOMAIN, &domain, &optlen) == -1)
    return -1;

  if (domain == AF_INET) {
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = domain;
    addr.sin_port = htons(port);
    err = inet_pton(AF_INET, address, &addr.sin_addr);

    if (err <= 0) {
      if (err == 0) {
        return 0; // Something went wrong
      } else {
        return -1; // Wrong format of address
      }
    }

    if (ConnectV4(sockfd, addr) == -1)
      return -1;
  }

  if (domain == AF_INET6) {
    int err;
    struct sockaddr_in6 addr;

    memset(&addr, 0, sizeof(addr));

    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(port);
    err = inet_pton(AF_INET6, address, &addr.sin6_addr);

    if (err <= 0) {
      if (err == 0) {
        return 0; // Something went wrong
      } else {
        return -1; // Wrong format of address
      }
    }

    if (ConnectV6(sockfd, addr) == -1)
      return -1;
  }

  return 1;
}

/**
 * @brief Receive a message from a socket
 *
 * @param sockfd
 * @param buf
 * @param len
 * @param flags
 * @return int
 */
ssize_t Recv(int sockfd, void *buf, size_t len, int flags) {
  ssize_t bytes;

  bytes = recv(sockfd, buf, len, flags);

  if (bytes == -1)
    return -1;

  return bytes;
}

/**
 * @brief Send a message on a socket
 *
 * @param sockfd
 * @param buf
 * @param len
 * @param flags
 * @return int
 */
ssize_t Send(int sockfd, void *buf, size_t len, int flags) {
  ssize_t bytes;

  bytes = send(sockfd, buf, len, flags);

  if (bytes == -1)
    return -1;

  return bytes;
}

/**
 * @brief Close a socket
 * 
 * @param sockfd 
 * @return int 
 */
int Close(int sockfd) {
  return close(sockfd);
}

/**
 * @brief Get options on sockets
 *
 * @param sockfd
 * @param level
 * @param optname
 * @param optval
 * @param optlen
 * @return int
 */
int Getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen) {
  return getsockopt(sockfd, level, optname, optval, optlen);
}

/**
 * @brief Set options on sockets
 *
 * @param sockfd
 * @param level
 * @param optname
 * @param optval
 * @param optlen
 * @return int
 */
int Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) {
  return setsockopt(sockfd, level, optname, optval, optlen);
}

/**
 * @brief Set reuse of local address
 *
 * @param sockfd
 * @param val
 * @return int
 */
int Reuseaddr(int sockfd, int val) { return Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)); }

/**
 * @brief Set reuse of local port
 * 
 * @param sockfd 
 * @param val 
 * @return int 
 */
int Reuseport(int sockfd, int val) { return Setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val)); }