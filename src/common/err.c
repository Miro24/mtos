
#include "err.h"
#include "string.h"
#include "errno.h"

char err_buffer[500] = {'\0', '\0'};
char err_buffer_backup[500] = {'\0', '\0'};
int errno_backup;

void err_backup(void)
{
	strcpy(err_buffer_backup, err_buffer);
	errno_backup = errno;
	errno = 0;
}

void err_restore(void)
{
	strcpy(err_buffer, err_buffer_backup);
	errno = errno_backup;
}
