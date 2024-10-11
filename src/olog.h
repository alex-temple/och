#ifndef OLOGGER
#define OLOGGER

#include <stdarg.h>
#include <string.h>
#include <errno.h>

enum log_level {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
};

#define DEBUG(message, ...) output(DEBUG, message "\n", ##__VA_ARGS__);
#define INFO(message, ...) output(INFO, message "\n", ##__VA_ARGS__);
#define WARNING(message, ...) output(WARNING, message "\n", ##__VA_ARGS__);
#define ERROR(message, ...) output(ERROR, message "\n", ##__VA_ARGS__);

#define PERROR(message, ...) output(ERROR, message ": %s\n", ##__VA_ARGS__, strerror(errno));

void output(const enum log_level level, const char* format, ...);

#endif
