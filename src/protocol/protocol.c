#include "config.h"

#ifdef BUILD_WITH_PROTOCOL

#include "stddef.h"
#include "protocol.h"
#include "errno.h"

void protocol_init(struct protocol_t *proto)
{
	errno = 0;
	
	if (proto == NULL) {
		errno = 1;
		return;
	}

	proto->initialized = 0;
	
        if (proto->init == NULL) {
		errno = 1;
                return;
        }

        proto->init(proto);
        if (errno) {
                return;
        }

        if ((NULL == proto->send) && (NULL == proto->receive)) {
		errno = 1;
		return;
        }

        comm_init(proto->comm);

	if (!errno){
		proto->initialized = 1;
	}
}

void protocol_deinit(struct protocol_t *proto)
{
        if (proto == NULL){
                return;
        }
	
        if (proto->deinit != NULL) {
                proto->deinit(proto);
        }

        if (proto->comm != NULL) {
                comm_deinit(proto->comm);
                proto->comm = NULL;
        }
}

void protocol_send(struct protocol_t *proto,
		    uint8_t *in,
		    uint32_t len,
		    uint32_t in_buff_len)
{
        if (proto == NULL){
		errno = 1;
                return;
        }

	if (!proto->initialized){
		errno = 1;
		return;
	}

	if (proto->send == NULL) {
		errno = 1;
                return;
        }

        if ((in == NULL) && (len > 0)){
		errno = 1;
                return;
        }

        if (len > in_buff_len){
		errno = 1;
                return;
        }

        if (len == 0){
                return;
        }

	proto->send(proto, in, len);
}

void protocol_receive(struct protocol_t *proto,
		      uint8_t *out,
		      uint32_t *len,
		      uint32_t out_buff_len)
{
        if (proto == NULL){
		errno = 1;
                return;
        }

	if (!proto->initialized){
		errno = 1;
		return;
	}

        if (proto->receive == NULL) {
		errno = 1;
                return;
        }

        if ((out == NULL) || (len == NULL)){
		errno = 1;
                return;
        }

	proto->receive(proto, out, len, out_buff_len);
}

#endoif // BUILD_WITH_PROTOCOL
