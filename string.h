#ifndef STRING_H
#define STRING_H

#include "list.h"

struct _List_String;

typedef struct _String {
    char *cString;
    size_t length;
    size_t capacity;
} String;

String String_createEmpty(void);
String String_createWithLength(const char *cString, size_t length);
String String_create(const char *cString);
String String_copy(String string);
void String_delete(String *string);
int String_isEmpty(String string);
struct _List_String String_split(String string, char separator);

#endif //STRING_H
