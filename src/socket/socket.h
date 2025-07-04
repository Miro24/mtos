#ifndef SOCKET_H
#define SOCKET_H

#include "comm.h"

struct socket_t{
	struct comm_t comm;
	int socket;
};

void socket_init_instance(struct socket_t *socket);

#endif // SOCKET_H
