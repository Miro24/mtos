#ifndef LOGGING_H
#define LOGGING_H

#include "err.h"

#define logg(...)							\
	log_print(__FILE__, (char*)__func__, __LINE__, __VA_ARGS__)

#define logg_if_err()							\
	if(errno) {							\
		logg("mess: %s", err_buffer);				\
		logg("errno = %d : %s", errno, strerror(errno));	\
	}

#define logg_message_if_err(message)					\
	if(errno) {							\
		logg("mess: %s", err_buffer);			\
		logg("errno = %d : %s", errno, strerror(errno));	\
		logg("%s", message);				\
	}

void log_print(char *module, char *func, int line, const char *fmt, ...);

#endif // LOGGING_H
