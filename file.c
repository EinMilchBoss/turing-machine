#include <stdio.h>

#include "file.h"

Result_String_Int File_getContent(const char *file)
{
    FILE *fileHandle = fopen(file, "rb");
    if (fileHandle == nullptr)
    {
        return Result_String_Int_createError(FILE_ERROR_ERRNO);
    }

    if (fseek(fileHandle, 0, SEEK_END) != 0)
    {
        if (ferror(fileHandle) != 0)
            return Result_String_Int_createError(FILE_ERROR_READ_DURING_WRITE);

        return Result_String_Int_createError(FILE_ERROR_ERRNO);
    }

    const long byteAmount = ftell(fileHandle);
    if (byteAmount == -1)
    {
        return Result_String_Int_createError(FILE_ERROR_ERRNO);
    }

    if (fseek(fileHandle, 0, SEEK_SET) != 0)
    {
        if (ferror(fileHandle) != 0)
            return Result_String_Int_createError(FILE_ERROR_READ_DURING_WRITE);

        return Result_String_Int_createError(FILE_ERROR_ERRNO);
    }

    char *buffer = calloc(byteAmount, sizeof(*buffer));
    if (buffer == nullptr)
    {
        return Result_String_Int_createError(FILE_ERROR_ALLOCATION);
    }

    size_t readByteAmount = fread(buffer, sizeof(char), byteAmount, fileHandle);
    if (readByteAmount != byteAmount)
    {
        if (feof(fileHandle))
            return Result_String_Int_createError(FILE_ERROR_UNEXPECTED_EOF);

        return Result_String_Int_createError(FILE_ERROR_READ_DURING_WRITE);
    }

    if (fclose(fileHandle) == EOF)
    {
        return Result_String_Int_createError(FILE_ERROR_CLOSE);
    }

    const String content = String_create(buffer);
    free(buffer);
    return Result_String_Int_createOk(content);
}