#ifndef LOGGER
#define LOGGER

#define INFO(message, ...) output(INFO, message, __VA_ARGS__);
#define WARNING(message, ...) output(WARNING, message, __VA_ARGS__);
#define ERROR(message, ...) output(ERROR, message, __VA_ARGS__);

enum log_level {
  INFO,
  WARNING,
  ERROR,
};

void output(const enum log_level level, const char* message, ...);

#endif
