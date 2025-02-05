#include "string.h"

String String_createEmpty(void)
{
    return (String){
        .value = nullptr,
        .length = 0,
        .capacity = 0,
    };
}

String String_create(const char *cString)
{
    const size_t length = strlen(cString);
    const size_t capacity = ((length / 32) + 1) * 32;

    char *value = calloc(capacity, sizeof(*value));
    if (value == nullptr)
    {
        return String_createEmpty();
    }
    memmove(value, cString, length);

    return (String){
        .value = value,
        .length = length,
        .capacity = capacity,
    };
}

void String_delete(String *string)
{
    if (string->value != nullptr)
    {
        free(string->value);
        string->value = nullptr;
    }
}