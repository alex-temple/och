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

ostring ostring_resize(ostring str, size_t new_size)
{
    const size_t struct_size = sizeof(struct ostring_def);

    struct ostring_def* old_def = GET_DEF(str);
    const size_t old_length = old_def->length;

    struct ostring_def* new_def = realloc(old_def, struct_size + new_size + 1);

    if (!new_def) return NULL;

    new_def->length = (old_length > new_size) ? new_size : old_length;
    new_def->size = new_size;

    return new_def->buffer;
}

void ostring_clear(ostring str)
{
    struct ostring_def* def = GET_DEF(str);

    def->length = 0;
    def->buffer[0] = '\0';
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

ostring ostring_push(ostring str, char c)
{
    const size_t length = ostring_length(str);
    const size_t size = ostring_size(str);

    if (length == size)
    {
        str = ostring_resize(str, size * 2);   
    }

    str[length] = c;
    str[length + 1] = '\0';

    GET_DEF(str)->length++;

    return str;
}

/*
i32 ostring_compare(const ostring left, const ostring right)
{
    if (!left || !right) return 

    size_t left_length = ostring_length(left);
    size_t right_length = ostring_length(right);

    size_t min_length = (left_length < right_length) ? left_length : right_length;

    i32 result = memcmp(left, right, min_length);

    if (result) return result;

    return (left_length > right_length) ? 1 : (left_length < right_length) ? -1 : 0;
}
*/

/*
ostring ostring_token(const char** ptr, const char* delimiters)
{
    const char* token_start = *ptr;

    if (!token_start || !*token_start) return NULL;

    while (string_contains(delimiters, *(++token_start)));

    const char* token_end = token_start;

    while (*token_end && !string_contains(delimiters, *(++token_end)));

    return ostring_new(token_start, (*ptr = token_end) - token_start);
}
*/

bool string_contains(const char* str, const char c)
{
    for (; *str; ++str) 
    {
        if (*str == c) return true;
    }
    
    return false;
}

const char* string_ptr_of(const char* str, const char c)
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

const char* string_ptr_of_last(const char* str, const char c)
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