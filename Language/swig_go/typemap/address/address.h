#ifndef ADDRESS_H
#define ADDRESS_H

#include <sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in GetAddress();
void UpdateAddress(struct sockaddr_in addr);


#endif // ADDRESS_H

