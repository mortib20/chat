#pragma once

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netdb.h>
#include <arpa/inet.h>


int Socket(int domain, int type, int protocol);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int BindV4(int sockfd, struct sockaddr_in address);
int BindV6(int sockfd, struct sockaddr_in6 address);
int BindIP(int sockfd, const char *address, uint16_t port);

int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int ConnectBindV4(int sockfd, struct sockaddr_in address);
int ConnectV6(int sockfd, struct sockaddr_in6 address);
int ConnectIP(int sockfd, const char *address, uint16_t port);

ssize_t Recv(int sockfd, void *buf, size_t len, int flags);
ssize_t Send(int sockfd, void *buf, size_t len, int flags);

int Close(int sockfd);

int Getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
int Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

int Reuseaddr(int sockfd, int val);