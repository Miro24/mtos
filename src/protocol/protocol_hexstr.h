#ifndef PROTOCOL_HEXSTR
#define PROTOCOL_HEXSTR

#include "protocol.h"

// Hex string  protocol
// data are sent in hexadecimal string format with an end terminator,
// which is the newline character '\n'

void protocol_hexstr_init(struct protocol_t *p, struct comm_t *comm);

#endif // PROTOCOL_HEXSTR
