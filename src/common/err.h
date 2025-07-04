#ifndef ERR_H
#define ERR_H

#include "errno.h"
#include "stdio.h"

extern char err_buffer[];

#define err_get() errno

#define err_check() (errno != 0)

#define err_check_and_goto(label)		\
	if(errno) goto label

#define err_clear()				\
	{					\
		  errno = 0;			\
		  err_buffer[0] ='\0';		\
	}

#define err_set(err)							\
	if(err) {							\
		err_buffer[0] = '\0';					\
		sprintf(err_buffer,					\
			"Error in: %s: %s(): %d",				\
			__FILE__, __func__, __LINE__);			\
		errno = err;						\
	}

#define err_update()							\
	if(errno) {							\
		err_buffer[0] = '\0';					\
		sprintf(err_buffer,					\
			"Error in: %s: %s(): %d",				\
			__FILE__, __func__, __LINE__);			\
	}

#define err_set_with_mess(err, mess)					\
	if(err) {							\
		err_buffer[0] = '\0';					\
		sprintf(err_buffer,					\
			"Error in: %s: %s():%d:\n%s",			\
			__FILE__, __func__, __LINE__, mess);		\
		errno = err;						\
	}

#define err_set_mess(mess)						\
	if(errno) {							\
		err_buffer[0] = '\0';					\
		sprintf(err_buffer,					\
			"Error in: %s: %s():%d:\n%s",			\
			__FILE__, __func__, __LINE__, mess);		\
	}


void err_backup(void);
void err_restore(void);

#endif // ERR_H
