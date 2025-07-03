#ifndef COMM_H
#define COMM_H

#include "stdint.h"

struct comm_t {
	uint8_t initialized;
	void (*init)(struct comm_t *comm);
	void (*deinit)(struct comm_t *comm);
        void (*send)(struct comm_t *comm,
		     uint8_t *in,
		     uint16_t len);
        void (*receive)(struct comm_t *comm,
                        uint8_t *out,
                        uint16_t *len,
			uint16_t out_buff_len);
};

void comm_init(struct comm_t *comm);

void comm_deinit(struct comm_t *comm);

void comm_send(struct comm_t *comm, uint8_t *in, uint16_t len);

void comm_receive(struct comm_t *comm,
		  uint8_t *out,
		  uint16_t *len,
		  uint16_t out_buff_len);

#endif // COMM_H
