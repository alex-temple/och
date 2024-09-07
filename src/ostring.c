#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "ostring.h"

ostring ostring_new(const char* source, const size_t length)
{
    const size_t struct_size = sizeof(struct ostring_def);

    struct ostring_def* def = malloc(struct_size + length + 1);

    if (!def) return NULL;

    def->size = length;

    if (length && source)
    {
        const size_t source_length = strlen(source);
        const size_t copy_length = (source_length < length) ? source_length : length;
        memcpy(def->buffer, source, copy_length);
        memset(def->buffer + copy_length, 0, length - copy_length);
        def->length = copy_length;
    }
    else
    {
        memset(def->buffer, 0, length);
        def->length = 0;
    }

    def->buffer[length] = '\0';

    return def->buffer;
}

ostring ostring_new_empty(const size_t length)
{
    return ostring_new(NULL, length);
}

ostring ostring_new_from(const char* source)
{
    return ostring_new(source, strlen(source));
}

void ostring_delete(const ostring str)
{
    free(GET_DEF(str));
}

ostring ostring_format(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    const ostring formatted = ostring_format_args(format, args);

    va_end(args);

    return formatted;
}

ostring ostring_format_args(const char* format, va_list args)
{
    if (!format) return NULL;

    va_list copy;
    va_copy(copy, args);

    const i32 length = vsnprintf(NULL, 0, format, copy);

    va_end(copy);

    const ostring str = ostring_new_empty(length);

    if (!str) return NULL;

    vsnprintf(str, length + 1, format, args);

    return str;
}