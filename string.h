#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    char *value;
    size_t length;
    size_t capacity;
} String;

String String_createEmpty(void);
String String_create(const char *cString);
void String_delete(String *string);

#endif //STRING_H
