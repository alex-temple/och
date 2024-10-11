#ifndef O_STRING
#define O_STRING

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "defines.h"

//clearly named macros

#define string_compare(left, right) strcmp(left, right)

#define string_ptr_of(str, c) strchr(str, c)
#define string_ptr_of_last(str, c) strrchr(str, c)

#define string_token(str, delimiters, ptr) strtok_r(str, delimiters, ptr)

//ostring functions

ostring ostring_new(const char* source, const size_t size);
ostring ostring_new_empty(const size_t size);
ostring ostring_new_from(const char* source);

void ostring_delete(ostring str);

ostring ostring_resize(ostring str, size_t new_length);
void ostring_clear(ostring str);

size_t ostring_length(const ostring str);
size_t ostring_size(const ostring str);

ostring ostring_format(const char* format, ...);
ostring ostring_format_args(const char* format, va_list args);

ostring ostring_push(ostring str, char c);

//i32 ostring_compare(const ostring left, const ostring right);

//regular string functions

i32 string_split(char* str, const char* delimiters, char*** sub_strings);

bool string_contains(const char* str, const char c);

#endif