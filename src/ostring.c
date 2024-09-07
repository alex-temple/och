#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ostring.h"

struct ostring_def {
    size_t length;
    size_t size;
    char buffer[];
};

#define GET_DEF(x) ((struct ostring_def*)(x - sizeof(struct ostring_def)))

ostring ostring_new(const char* source, const size_t size)
{
    const size_t struct_size = sizeof(struct ostring_def);

    struct ostring_def* def = malloc(struct_size + size + 1);

    if (!def) return NULL;

    def->size = size;

    if (size && source)
    {
        const size_t source_length = strlen(source);
        const size_t copy_length = (source_length < size) ? source_length : size;
        memcpy(def->buffer, source, copy_length);
        memset(def->buffer + copy_length, 0, size - copy_length);
        def->length = copy_length;
    }
    else
    {
        memset(def->buffer, 0, size);
        def->length = 0;
    }

    def->buffer[size] = '\0';

    return def->buffer;
}

ostring ostring_new_empty(const size_t size)
{
    return ostring_new(NULL, size);
}

ostring ostring_new_from(const char* source)
{
    return ostring_new(source, strlen(source));
}

void ostring_delete(const ostring str)
{
    free(GET_DEF(str));
}

size_t ostring_length(const ostring str)
{
    return GET_DEF(str)->length;
}

size_t ostring_size(const ostring str)
{
    return GET_DEF(str)->size;
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

const char* ostring_ptr_of(const char* str, const char c)
{
    if (!str) return NULL;

    while (*str)
    {
        if (*str == c)
            return str;

        str++;
    }

    return NULL;
}

const char* ostring_ptr_of_last(const char* str, const char c)
{
    if (!str) return NULL;

    const char* last = NULL;

    while (*str)
    {
        if (*str == c)
            last = str;

        str++;
    }

    return last;
}