#include <stdio.h>

#include "defines.h"
#include "ostring.h"
#include "olog.h"

#define WHITE "\033[0;0m"

#define BOLD_PURPLE "\033[1;35m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_RED "\033[1;31m"

static const char* tags[4] = { 
  BOLD_PURPLE "[DEBUG]" WHITE, 
  BOLD_GREEN "[INFO]" WHITE, 
  BOLD_YELLOW "[WARN]" WHITE, 
  BOLD_RED "[ERROR]" WHITE 
};

void output(const enum log_level level, const char* format, ...)
{
  	va_list args;
  	va_start(args, format);

    const ostring formatted = ostring_format_args(format, args);
    
    va_end(args);
    
    const ostring message = ostring_format("%s %s", tags[level], formatted);

    ostring_delete(formatted);

    fprintf(stderr, "%s", message);

    ostring_delete(message);
}
