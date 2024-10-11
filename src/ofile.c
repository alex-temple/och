#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "ofile.h"
#include "ostring.h"

bool is_dir(const char* source)
{
    struct stat s;
    return !stat(source, &s) && S_ISDIR(s.st_mode);
}

bool is_file(const char* source)
{
    struct stat s;
    return !stat(source, &s) && S_ISREG(s.st_mode);
}

bool file_exists(const char* source)
{
    struct stat s;
    return !stat(source, &s) && !s.st_mode;
}

bool file_copy(const char* source, const char* destination)
{
    i32 source_fd = 0;
    i32 destination_fd = 0;

    if ((source_fd = open(source, O_RDONLY)) < 0)
    {
        return false;
    }

    if ((destination_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
    {
        close(source_fd);
        return false;
    }

    char buffer[8192];

    i32 read_result;

    while ((read_result = read(source_fd, buffer, sizeof(buffer))) > 0)
    {
        i32 total_written = 0;

        while (total_written < read_result)
        {
            const i32 write_result = write(destination_fd, buffer + total_written, read_result - total_written);

            if (write_result < 0)
            {
                close(source_fd);
                close(destination_fd);

                return false;
            }

            total_written += write_result;
        }
    }

    close(source_fd);
    close(destination_fd);

    return true;
}

bool file_copy_to(const char* source, const char* directory)
{
    const char* file_name = string_ptr_of_last(source, '/');

    //create a copy of the given string to prevent surprise changes
    const ostring directory_copy = ostring_new_from(directory);
    const size_t directory_length = ostring_length(directory_copy);

    if (directory_length > 0 && directory[directory_length - 1] == '/')
    {
        directory_copy[directory_length - 1] = '\0';
    }

    const ostring destination = ostring_format("%s/%s", directory_copy, file_name ? file_name + 1 : source);

    const bool result = file_copy(source, destination);

    ostring_delete(directory_copy);
    ostring_delete(destination);

    return result;
}

size_t file_read_until(ostring* str, const char* delimiter, FILE* input)
{
    if (!str || !input) return OERROR;

    if (!*str) *str = ostring_new_empty(128);

    size_t written = 0;
    i32 c;

    while ((c = fgetc(input)) != EOF)
    {
        if (string_contains(delimiter, c)) break;

        *str = ostring_push(*str, (char)c);
        
        if (!*str) return OERROR;

        written++;
    }

    if (written == 0 || c == EOF) return OERROR;

    return written;
}