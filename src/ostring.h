#ifndef O_STRING
#define O_STRING

#include "defines.h"

typedef char* ostring;

ostring ostring_new(const char* source, const size_t size);
ostring ostring_new_empty(const size_t size);
ostring ostring_new_from(const char* source);

void ostring_delete(ostring str);

OINLINE size_t ostring_length(const ostring str);
OINLINE size_t ostring_size(const ostring str);

ostring ostring_format(const char* format, ...);
ostring ostring_format_args(const char* format, va_list args);

char* ostring_ptr_of(ostring str, const char c);
char* ostring_ptr_of_last(ostring str, const char c);

#endif
