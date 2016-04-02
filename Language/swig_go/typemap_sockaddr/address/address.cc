#include "address.h"

#include <arpa/inet.h>

struct sockaddr_in GetAddress()
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.1.1");
	addr.sin_port = htons(9876);
	return addr;
}

void UpdateAddress(struct sockaddr_in addr)
{
}

