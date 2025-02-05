#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"
#include "string.h"

const size_t LIST_CAPACITY_STEP = 8;

static size_t List_getCapacityFromSize(const size_t size)
{
    const size_t capacityStepAmount = (size - 1) / LIST_CAPACITY_STEP + 1;
    const size_t capacity = capacityStepAmount * LIST_CAPACITY_STEP;

    assert(size <= capacity);

    return capacity;
}

List_String List_String_createEmpty(void)
{
    return (List_String){
        .values = NULL,
        .size = 0,
        .capacity = 0,
    };
}

List_String List_String_create(const String *originals, const size_t size)
{
    if (originals == NULL || size == 0)
        return List_String_createEmpty();

    const size_t capacity = List_getCapacityFromSize(size);

    String *copies = calloc(capacity, sizeof(*copies));
    if (copies == NULL)
        return List_String_createEmpty();

    memmove(copies, originals, size * sizeof(*copies));

    return (List_String){
        .values = copies,
        .size = size,
        .capacity = capacity,
    };
}

void List_String_delete(List_String *list)
{
    if (list->values != NULL)
    {
        free(list->values);
        list->values = NULL;
    }
    list->size = 0;
    list->capacity = 0;
}

int List_String_push(List_String *list, const String string)
{
    const size_t requiredCapacity = List_getCapacityFromSize(list->size + 1);

    if (requiredCapacity > list->capacity)
    {
        String *reallocated = realloc(list->values, requiredCapacity * sizeof(*reallocated));
        if (reallocated == NULL)
            return EXIT_FAILURE;

        list->values = reallocated;
        list->capacity = requiredCapacity;
    }

    list->values[list->size] = String_copy(string);
    list->size++;

    return EXIT_SUCCESS;
}