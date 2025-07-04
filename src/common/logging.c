#include "logging.h"
#include "stdarg.h"

void log_print(char *module, char *func, int line, const char *fmt, ...)
{
	printf(":%s:%s:%d: ", module, func, line);
	va_list args;
	va_start(args, fmt);
	vprintf(fmt,  args);
	va_end(args);
	printf("\n");
}
