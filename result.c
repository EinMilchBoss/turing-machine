#include "result.h"

Result_String_Int Result_String_Int_createOk(const String ok)
{
    return (Result_String_Int){
        .ok = ok,
        .type = RESULT_TYPE_OK,
    };
}

Result_String_Int Result_String_Int_createError(const int error)
{
    return (Result_String_Int){
        .error = error,
        .type = RESULT_TYPE_ERROR,
    };
}

void Result_String_Int_delete(Result_String_Int *result)
{
    if (result->type == RESULT_TYPE_OK)
    {
        String_delete(&result->ok);
    }
}