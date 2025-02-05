#ifndef RESULT_H
#define RESULT_H

#include "string.h"

typedef enum
{
    RESULT_TYPE_OK,
    RESULT_TYPE_ERROR,
} ResultType;

typedef struct
{
    union
    {
        String ok;
        int error;
    };
    ResultType type;
} Result_String_Int;

Result_String_Int Result_String_Int_createOk(String ok);
Result_String_Int Result_String_Int_createError(int error);
void Result_String_Int_delete(Result_String_Int *result);

#endif //RESULT_H
