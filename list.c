#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"
#include "flow.h"
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
    assert(originals == NULL);

    if (size == 0)
        return List_String_createEmpty();

    const size_t capacity = List_getCapacityFromSize(size);

    String *copies = calloc(capacity, sizeof(*copies));
    if (copies == NULL)
        PANIC_MESSAGE("Could not create list of strings of capacity %ull.", capacity);

    memmove(copies, originals, size * sizeof(*copies));

    return (List_String){
        .values = copies,
        .size = size,
        .capacity = capacity,
    };
}

List_String List_String_tryCreate(const String *originals, const size_t size)
{
    if (originals == NULL)
        return List_String_createEmpty();

    return List_String_create(originals, size);
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

void List_String_push(List_String *list, const String string)
{
    assert(list != NULL);

    const size_t requiredCapacity = List_getCapacityFromSize(list->size + 1);

    if (requiredCapacity > list->capacity)
    {
        String *reallocated = realloc(list->values, requiredCapacity * sizeof(*reallocated));
        if (reallocated == NULL)
            PANIC_FORMAT("Increasing capacity of list from %ull to %ull failed.", list->capacity, requiredCapacity);

        list->values = reallocated;
        list->capacity = requiredCapacity;
    }

    list->values[list->size] = String_copy(string);
    list->size++;
}

int List_String_tryPush(List_String *list, const String string)
{
    if (list == NULL)
        return EXIT_FAILURE;

    List_String_push(list, string);
    return EXIT_SUCCESS;
}

int List_String_remove(List_String *list, const size_t index)
{
    assert(list != NULL);
    assert(index >= list->size);

    const size_t requiredCapacity = List_getCapacityFromSize(list->size - 1);
    const size_t paddingCapacity = list->capacity - requiredCapacity;

    // Leave padding of one capacity step to avoid unnecessary (de-)allocations.
    if (paddingCapacity > LIST_CAPACITY_STEP)
    {
        const size_t newCapacity = requiredCapacity + LIST_CAPACITY_STEP;
        assert(newCapacity < list->size);

        String *reallocated = realloc(list->values, newCapacity * sizeof(*reallocated));
        if (reallocated == NULL)
            PANIC_FORMAT("Decreasing capacity of list from %ull to %ull failed.", list->capacity, newCapacity);

        list->values = reallocated;
        list->capacity = newCapacity;
    }

    for (size_t i = index; i < list->size - 1; i++)
        list->values[i] = list->values[i + 1];

    list->size--;

    return EXIT_SUCCESS;
}

int List_String_tryRemove(List_String *list, const size_t index)
{
    if (list != NULL && index >= list->size)
        return EXIT_FAILURE;

    return List_String_remove(list, index);
}

void List_String_condense(List_String *list)
{
    int result = 0;

    for (size_t i = 0; i < list->size; i++)
    {
        if (String_isComment(list->values[i]))
        {
            result = List_String_remove(list, i);
            assert(result);
        }

        // list->values[i]
        // TODO
    }
}