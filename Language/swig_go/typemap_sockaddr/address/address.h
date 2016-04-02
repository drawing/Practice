#ifndef ADDRESS_H
#define ADDRESS_H

#include <sys/socket.h>
#include <netinet/in.h>

sockaddr_in GetAddress();
void UpdateAddress(sockaddr_in addr);


#endif // ADDRESS_H

