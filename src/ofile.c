#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "ofile.h"
#include "ostring.h"

bool is_dir(const char* source)
{
    struct stat s;
    stat(source, &s);
    return S_ISDIR(s.st_mode);
}

bool is_file(const char* source)
{
    struct stat s;
    stat(source, &s);
    return S_ISREG(s.st_mode);
}

bool copy_file(const char* source, const char* destination)
{
    i32 source_file = 0;
    i32 destination_file = 0;

    if ((source_file = open(source, O_RDONLY)) < 0)
    {
        return false;
    }

    if ((destination_file = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
    {
        close(source_file);
        return false;
    }

    char buffer[8192];
    posix_fadvise(source_file, 0, 0, POSIX_FADV_SEQUENTIAL);

    i32 read_result;

    while ((read_result = read(source_file, buffer, sizeof(buffer))) > 0)
    {
        i32 total_written = 0;

        while (total_written < read_result)
        {
            const i32 write_result = write(destination_file, buffer + total_written, read_result - total_written);

            if (write_result < 0)
            {
                close(source_file);
                close(destination_file);

                return false;
            }

            total_written += write_result;
        }
    }

    close(source_file);
    close(destination_file);

    return true;
}

bool copy_file_to(const char* source, const char* directory)
{
    const char* file_name = ostring_ptr_of_last(source, '/');
    const ostring destination = ostring_format("%s/%s", directory, file_name ? file_name + 1 : file_name);
    const bool result = copy_file(source, destination);
    ostring_delete(destination);
    return result;
}