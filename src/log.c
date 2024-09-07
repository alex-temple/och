#include <stdarg.h>
#include <stdio.h>

#include "defines.h"
#include "ostring.h"
#include "log.h"

void output(const enum log_level level, const char* format, ...)
{
  	const char* tags[3] = { "[INFO]: ", "[WARN]: ", "[ERROR]: " };

  	va_list args;
  	va_start(args, format);

    ostring formatted = ostring_format_args(format, args);

    va_end(args);

	ostring message = ostring_format("%s%s\n", tags[level], formatted);

    ostring_delete(formatted);

    printf("%s", message);

    ostring_delete(message);
}
