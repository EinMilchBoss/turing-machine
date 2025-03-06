#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "string.h"

#include "transition.h"

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
    if (string->cString != NULL) {
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

/**
 * Checks if the string starts with a "//". Tabs and spaces are ignored.
 */
int String_isComment(const String string)
{
    if (String_isEmpty(string))
        return 0;

    for (const char* first = string.cString; *first != '\0'; first++) {
        if (*first != ' ' || *first != '\t')
            return strncmp(first, "//", 2) == 0;
    }

    return 0;
}

/**
 * Splits the `String` by the specified `char` as often as necessary.
 *
 * Multiple adjacent occurences of the separator do not create empty `String`s.
 * @return Returns an empty list if the `String` is empty.
 */
List_String String_split(const String string, const char separator)
{
    if (String_isEmpty(string))
        return List_String_create(NULL, 0);

    const char* current = string.cString;
    const char* next = strchr(string.cString, separator);

    if (next == NULL)
        return List_String_create(&string, 1);

    List_String splits = List_String_createEmpty();
    while (next != NULL) {
        const size_t length = next - current;

        if (length > 0) {
            String substring = String_createWithLength(current, length);
            List_String_push(&splits, substring);
            String_delete(&substring);
        }

        current = next + 1;
        next = strchr(current, separator);
    }

    const size_t processedLength = current - string.cString;
    if (processedLength < string.length) {
        String last = String_create(current);
        List_String_push(&splits, last);
        String_delete(&last);
    }

    return splits;
}

/**
 * Takes a line `String` and transforms it to a `Transition`.
 *
 * The line `String` itself will be deallocated.
 */
Transition String_toTransition(String line)
{
    // Q1,A>Q2,B,R
    List_String parts = String_split(line, '>');
    // TODO: Check if it only has 2 parts.

    // TODO: Check if
    String front = parts.values[0];
    List_String srcValues = String_split(front, ',');

    String srcState = srcValues.values[0];
    char srcChar = srcValues.values[1].cString[0];

    String back = parts.values[0];
    List_String dstValues = String_split(back, ',');

    String dstState = dstValues.values[0];
    char dstChar = dstValues.values[1].cString[0];
    TransitionDirection direction = TransitionDirection_fromChar(dstValues.values[2].cString[0]);

    List_String_delete(&parts);

    return (Transition){
        .srcState = srcState,
        .srcChar = srcChar,
        .dstState = dstState,
        .dstChar = dstChar,
        .direction = direction,
    };
}
