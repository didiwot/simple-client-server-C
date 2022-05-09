#ifndef ERPROC_H
#define ERPROC_H
//т.к. все функции могут вернуть ошибки - сделаем обёртку для каждой из них
#include <sys/types.h> //sockaddr
#include <sys/socket.h>

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);
	
int Accept(int sockfd, struct sockaddr *addr,socklen_t *addrlen);

void Connect(int sockfd,const struct sockaddr *addr, socklen_t addrlen);

void Inet_pton(int af, const char *src, void *dst);

#endif