#include "config.h"

#ifdef BUILD_WITH_COMM

#include "comm.h"
#include "stddef.h"
#include "err.h"

void comm_init(struct comm_t *comm)
{
	err_clear();
	
	if (comm == NULL) {
		err_set(1);
		return;
        }

	comm->initialized = 0;
	
	if (comm->init == NULL) {
		err_set(1);
		return;
        }
	
	comm->init(comm);
	if(err_check()){
		return;
	}

	if ((comm->send == NULL) && (comm->receive == NULL)) {
		err_set(1);
		return;
        }

	if(!err_check()){
		 comm->initialized = 1;
	 }
}

void comm_deinit(struct comm_t *comm)
{
	if (comm == NULL) {
		return;
        }

	comm->initialized = 0;
	
	if (comm->deinit == NULL) {
		return;
        }

	err_clear();
	comm->deinit(comm);
}

void comm_send(struct comm_t *comm, uint8_t *in, uint16_t len)
{
	err_clear();
	
	if (comm == NULL) {
		err_set(1);
		return;
        }

	if (!comm->initialized){
		err_set(1);
		return;		
	}

	if (comm->send == NULL){
		err_set(1);
		return;
	}

	comm->send(comm, in, len);
}

void comm_receive(struct comm_t *comm,
		  uint8_t *out,
		  uint16_t *len,
		  uint16_t out_buff_len)
{
	err_clear();
	
	if (comm == NULL) {
		err_set(1);
		return;
        }

	if (!comm->initialized){
		err_set(1);
		return;		
	}

	if (comm->receive == NULL){
		err_set(1);
		return;
	}

	comm->receive(comm, out, len, out_buff_len);
}

#endif  // BUILD_WITH_COMM
