#ifndef FLOW_H
#define FLOW_H

#define PANIC_MESSAGE(message) Flow_panic(__FILE__, __LINE__, message, NULL)
#define PANIC_FORMAT(format, ...) Flow_panic(__FILE__, __LINE__, format, __VA_ARGS__)
void Flow_panic(const char *file, unsigned int line, const char* format, ...);

#endif //FLOW_H
