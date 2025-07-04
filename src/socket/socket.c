#include "config.h"

#ifdef BUILD_WITH_SOCKET

#include "string.h"
#include "socket.h"
#include "unistd.h"
#include <arpa/inet.h>

#include "err.h"
#include "logging.h"


static void sk_send(struct comm_t *comm,  uint8_t *in,  uint16_t len);
static void init(struct comm_t *comm);
static void deinit(struct comm_t *comm);
static void receive(struct comm_t *comm,
		    uint8_t *out,
		    uint16_t *len,
		    uint16_t out_buff_len);

void socket_init_instance(struct socket_t *sock)
{
	struct comm_t *comm;

	comm = &sock->comm;
	comm->init = init;
}

void init(struct comm_t *comm)
{
	struct socket_t *sock;
	int aux;
	struct sockaddr_in server_addr;

	sock = (struct socket_t *)comm;
		
	comm->send = sk_send;
	comm->receive = receive;
	comm->deinit = deinit;	
	err_clear();
		
	// create socket
 	sock->socket = socket(AF_INET, SOCK_STREAM, 0);

	if (sock->socket < 0) {
		err_set_mess("Socket creation error");
		return;
	}

	// setup server address struct
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(sock->port);	

	if (inet_pton(AF_INET, sock->ip, &server_addr.sin_addr) <= 0){
		err_set_mess("Invalid address/ Address not supported");
		goto end;
	}

	// connect to server
	if(connect(sock->socket,
		   (struct sockaddr*)&server_addr,
		   sizeof(struct sockaddr)) == -1){
		err_set_mess("Connection failed");
		goto end;
	}
	
	logg("Socket initialized");

 end:
	if (err_check()){
		err_backup();
		close(sock->socket);
		err_restore();
	}
}

void deinit(struct comm_t *comm)
{
	struct socket_t *sock;

	sock = (struct socket_t *)comm;
	close(sock->socket);
	err_update();
	logg("Socket closed");
}

void sk_send(struct comm_t *comm,  uint8_t *in,  uint16_t len)
{
	struct socket_t *sock;

	sock = (struct socket_t *)comm;
	send(sock->socket, in, len, 0);
	err_update();
}

void receive(struct comm_t *comm,
	     uint8_t *out,
	     uint16_t *len,
	     uint16_t out_buff_len)
{
	struct socket_t *sock;
	int aux;
	size_t size;
	uint8_t *buff;
	
	sock = (struct socket_t *)comm;
	err_clear();
	buff = out;

	// verify buffer length
	if (*len > out_buff_len){
		err_set(1);
		return;
	}
	
	// receive len
	size = *len;

	while(size > 0){
		aux = recv(sock->socket, buff, size, 0);
		err_update();
		
		if (err_check()){
			return;			
		}

		if (aux == 0) {
			break;
		}

		out += aux;
		size -= aux;
	}

	*len = buff - out;
}

#endif // BUILD_WITH_SOCKET
