/*
 * export REDIS_SRC=../../../redis-2.8.19/src/
 * gcc ae_test.c -I$REDIS_SRC $REDIS_SRC/ae.c $REDIS_SRC/zmalloc.c
 */

#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "ae.h"

int TimerAction(struct aeEventLoop *eventLoop, long long id, void *clientData) {
	printf("timer %llu\n", id);
	return 5000;
}

void ReadAction(struct aeEventLoop *eventLoop, int fd, void *clientData, int mask) {
	char buffer[200];
	int len = read(fd, buffer, sizeof(buffer));
	buffer[len] = 0;
	printf("read: %d->%s\n", len, buffer);
	if (strncmp(buffer, "exit", 4) == 0) {
		printf("exit one\n");

		aeDeleteFileEvent(eventLoop, fd, AE_READABLE);

		close(fd);
	}
}

void AccpetAction(struct aeEventLoop *eventLoop, int fd, void *clientData, int mask) {
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	int client = accept(fd, (struct sockaddr *)&client_addr, &addr_len);
	if (client < 0) {
		fprintf(stderr, "accept failed:%s\n", strerror(errno));
		exit(-1);
	}
	
	aeCreateFileEvent(eventLoop, client, AE_READABLE, ReadAction, NULL);
}

int main()
{
	struct sockaddr_in server_addr;
	aeEventLoop *eventLoop;

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		fprintf(stderr, "socket failed:%s\n", strerror(errno));
		exit(-1);
	}

	memset(&server_addr, 0 , sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9999);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		fprintf(stderr, "bind failed:%s\n", strerror(errno));
		exit(-1);
	}

	if (listen(fd, 5) < 0) {
		fprintf(stderr, "listen failed:%s\n", strerror(errno));
		exit(-1);
	}

	eventLoop = aeCreateEventLoop(100);
	aeCreateFileEvent(eventLoop, fd, AE_READABLE, AccpetAction, NULL);
	long long id = aeCreateTimeEvent(eventLoop, 2000, TimerAction, NULL, NULL);
	printf("create timer: %llu\n", id);

	aeMain(eventLoop);
	return 0;
}

