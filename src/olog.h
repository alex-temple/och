#ifndef OLOGGER
#define OLOGGER

enum log_level {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
};

#define DEBUG(message, ...) output(INFO, message, ##__VA_ARGS__);
#define INFO(message, ...) output(INFO, message, ##__VA_ARGS__);
#define WARNING(message, ...) output(WARNING, message, ##__VA_ARGS__);
#define ERROR(message, ...) output(ERROR, message, ##__VA_ARGS__);

void output(const enum log_level level, const char* format, ...);

#endif
