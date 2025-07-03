#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "comm.h"

struct protocol_t {
	uint8_t initialized;
        struct comm_t *comm;
        void (*init)(struct protocol_t *proto);
        void (*deinit)(struct protocol_t *proto);
        void (*send)(struct protocol_t *proto,
		     uint8_t *in,
		     uint32_t len);
        void(*receive)(struct protocol_t *proto,
		       uint8_t *out,
		       uint32_t *len,
		       uint32_t out_buff_len);
};

void protocol_init(struct protocol_t *proto);

void protocol_deinit(struct protocol_t *proto);

void protocol_send(struct protocol_t *proto,
		   uint8_t *in,
		   uint32_t len,
		   uint32_t in_buff_len);

void protocol_receive(struct protocol_t *proto,
		      uint8_t *out,
		      uint32_t *len,
		      uint32_t out_buff_len);

#endif // PROTOCOL_H
