#ifndef O_STRING
#define O_STRING

#include <stdarg.h>

#ifndef O_DEFINES

typedef char* ostring;

#endif

ostring ostring_new(const char* source, const size_t size);
ostring ostring_new_empty(const size_t size);
ostring ostring_new_from(const char* source);

void ostring_delete(ostring str);

size_t ostring_length(const ostring str);
size_t ostring_size(const ostring str);

ostring ostring_format(const char* format, ...);
ostring ostring_format_args(const char* format, va_list args);

const char* ostring_ptr_of(const char* str, const char c);
const char* ostring_ptr_of_last(const char* str, const char c);

#endif
