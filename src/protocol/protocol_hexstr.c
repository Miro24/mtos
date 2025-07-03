#include "config.h"

#ifdef BUILD_WITH_PROTOCOL_HEXSTR

#include "protocol_hexstr.h"
#include "stddef.h"
#include "errno.h"

#define END '\n'

#define convert_nibble_to_ascii(n) \
        if ((n) < 10) {\
                n = (n) + '0';\
        } else {\
                n = (n - 10) + 'A';\
        }

static void init(struct protocol_t *proto);

static void send(struct protocol_t *proto,
		 uint8_t *in,
		 uint32_t len);

static void receive(struct protocol_t *proto,
		    uint8_t *out,
		    uint32_t *len,
		    uint32_t out_buff_len);


void protocol_hexstr_init(struct protocol_t *p, struct comm_t *comm)
{
	p->init = init;
	p->comm = comm;
}

void init(struct protocol_t *proto)
{
	proto->send = send;
	proto->receive = receive;
	proto->deinit = NULL;
}

void send(struct protocol_t *proto, uint8_t *in, uint32_t len)
{
	char c;
	struct comm_t *comm;

	errno = 0;
	comm = proto->comm;
	
	while (len){
		c = (*in >> 4) & 0x0f;
		convert_nibble_to_ascii(c);
		
		comm_send(comm, &c, 1);
		if (errno){
			return;
		}
		
		c = (*in) & 0x0f;
		convert_nibble_to_ascii(c);
		
		comm_send(comm, &c, 1);
		if (errno){
			return;
		}

		len--;
		in++;
	}

	c = END;
	comm_send(comm, &c, 1);
}

void receive(struct protocol_t *proto,
	     uint8_t *out,
	     uint32_t *len,
	     uint32_t out_buff_len)
{
	uint8_t v;
	uint8_t nibble;
	char c;
	uint16_t temp;

	nibble = 0;
	errno = 0;
	*len = 0;
	
	while(1){
		comm_receive(proto->comm, &c, &temp, 1);
		if (errno){
			return;
		}
				
		if (c == END){
			if (nibble){
				errno = 1;
			}

			break;
		}

		if ((c >= '0') && (c <= '9')) {
			c = c - '0';
		} else if ((c >= 'a') && (c <= 'f')) {
			c = c - 'a' + 10;
		} else if ((c >= 'A') && (c <= 'F')) {
			c = c - 'A' + 10;
		} else {
			errno = 1;
			break;
		}
		
		if (nibble){
			if (out_buff_len == *len){
				errno = 1;
				break;
			}
					
			nibble = 0;
			v |= (c & 0x0f);
			out[*len] = v;
			*len = *len + 1;
		} else {
			nibble = 1;
			v = (c << 4) & 0xF0;
		}
	}
}

#endif // BUILD_WITH_PROTOCOL_HEXSTR

