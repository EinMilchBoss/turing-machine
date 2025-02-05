#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "string.h"

const size_t STRING_CAPACITY_STEP = 32;

static size_t String_getCapacityFromLength(const size_t length)
{
    const size_t capacityStepAmount = length / STRING_CAPACITY_STEP + 1;
    const size_t capacity = capacityStepAmount * STRING_CAPACITY_STEP;

    assert(length + 1 <= capacity);

    return capacity;
}

String String_createEmpty(void)
{
    return (String){
        .cString = NULL,
        .length = 0,
        .capacity = 0,
    };
}

String String_createWithLength(const char* cString, const size_t length)
{
    const size_t capacity = String_getCapacityFromLength(length);

    char* value = calloc(capacity, sizeof(*value));
    if (value == NULL)
        return String_createEmpty();
    memmove(value, cString, length * sizeof(*value));

    return (String){
        .cString = value,
        .length = length,
        .capacity = capacity,
    };
}

String String_create(const char* cString)
{
    const size_t length = strlen(cString);
    return String_createWithLength(cString, length);
}

String String_copy(const String string)
{
    return String_create(string.cString);
}

void String_delete(String* string)
{
    if (string->cString != NULL)
    {
        free(string->cString);
        string->cString = NULL;
    }
    string->length = 0;
    string->capacity = 0;
}

int String_isEmpty(const String string)
{
    return string.cString == NULL && string.length == 0 && string.capacity == 0;
}

List_String String_split(const String string, const char separator)
{
    if (String_isEmpty(string))
        return List_String_create(NULL, 0);

    const char* current = string.cString;
    const char* next = strchr(string.cString, separator);

    if (next == NULL)
        return List_String_create(&string, 1);

    List_String splits = List_String_createEmpty();
    while (next != NULL)
    {
        const size_t length = next - current;

        if (length > 0)
        {
            String substring = String_createWithLength(current, length);
            List_String_push(&splits, substring);
            String_delete(&substring);
        }

        current = next + 1;
        next = strchr(current, separator);
    }

    const size_t processedLength = current - string.cString;
    if (processedLength < string.length)
    {
        String last = String_create(current);
        List_String_push(&splits, last);
        String_delete(&last);
    }

    return splits;
}
