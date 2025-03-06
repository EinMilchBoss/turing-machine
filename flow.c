#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "flow.h"

void Flow_panic(const char* file, const unsigned int line, const char* format, ...)
{
    va_list arguments;

    fprintf(stderr, "[Error] File: \"%s\", Line: \"%u\", Message: ", file, line);

    va_start(arguments, format);
    vfprintf(stderr, format, arguments);
    va_end(arguments);

    fprintf(stderr, "\n");

    exit(EXIT_FAILURE);
}
