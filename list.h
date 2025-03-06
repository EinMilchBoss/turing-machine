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
List_String List_String_tryCreate(const struct _String *originals, const size_t size);
void List_String_delete(List_String *list);
void List_String_push(List_String *list, struct _String string);
int List_String_tryPush(List_String *list, struct _String string);
void List_String_remove(List_String *list, size_t index);
int List_String_tryRemove(List_String *list, size_t index);
void List_String_condense(List_String *list);

#endif //LIST_H
