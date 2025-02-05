#ifndef FILE_H
#define FILE_H

#include "result.h"

typedef enum
{
    /**
     * Check `errno` for more information.
     */
    FILE_ERROR_ERRNO = 1,
    /**
     * Reading failed due to another program trying to write to that file.
     */
    FILE_ERROR_READ_DURING_WRITE,
    /**
     * Allocation failed.
     */
    FILE_ERROR_ALLOCATION,
    /**
     * Unexpected EOF.
     */
    FILE_ERROR_UNEXPECTED_EOF,
    /**
     * File could not be closed successfully.
     */
    FILE_ERROR_CLOSE,
} FileError;

Result_String_Int File_getContent(const char *file);

#endif //FILE_H
