#ifndef O_STRING
#define O_STRING

#include "defines.h"

typedef char* ostring;

struct ostring_def {
    size_t length;
    size_t size;
    char buffer[];
};

#define GET_DEF(x) ((struct ostring_def*)(x - sizeof(struct ostring_def)))

OINLINE size_t ostring_length(const ostring str)
{
    return GET_DEF(str)->length;
}

OINLINE size_t ostring_size(const ostring str)
{
    return GET_DEF(str)->size;
}

ostring ostring_new(const char* source, const size_t length);
ostring ostring_new_empty(const size_t length);
ostring ostring_new_from(const char* source);

void ostring_delete(ostring str);

inline size_t ostring_length(const ostring str);
inline size_t ostring_size(const ostring str);

ostring ostring_format(const char* format, ...);
ostring ostring_format_args(const char* format, va_list args);

#endif
