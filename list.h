#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

struct _String;

typedef struct _List_String
{
    struct _String *values;
    size_t size;
    size_t capacity;
} List_String;

List_String List_String_createEmpty(void);
List_String List_String_create(const struct _String *originals, size_t size);
void List_String_delete(List_String *list);
int List_String_push(List_String *list, struct _String string);

#endif //LIST_H
