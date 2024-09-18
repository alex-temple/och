#ifndef OFILE
#define OFILE

#include <stdio.h>

#include "defines.h"

#define FILE_READLINE(str, input) file_read_until(str, "\n", input)

bool is_dir(const char* source);
bool is_file(const char* source);

bool file_exists(const char* source);

bool file_copy(const char* source, const char* destination);
bool file_copy_to(const char* source, const char* directory);

size_t file_read_until(ostring* str, const char* delimiters, FILE* input_file);

#endif
