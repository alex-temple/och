#ifndef OFILE
#define OFILE

#include "defines.h"

bool is_dir(const char* source);
bool is_file(const char* source);

bool file_copy(const char* source, const char* destination);
bool file_copy_to(const char* source, const char* directory);

#endif
