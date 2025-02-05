#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "file.h"

// enum HeadMovement
// {
//     LEFT = -1,
//     NEUTRAL = 0,
//     RIGHT = 1,
// };
//
// struct Transition
// {
//     char srcChar;
//     char dstChar;
//     enum HeadMovement movement;
//     char *srcState;
//     char *dstState;
// };
//
// const char *skip(const char *string, const char *const skipping)
// {
//     assert(string != NULL);
//     assert(skipping != NULL);
//
//     size_t amountSkipped = strspn(string, skipping);
//     return string + amountSkipped;
// }
//
// char *readValidString(const char *cursor)
// {
//
// }
//
// struct Transition parseTransition(const char *line)
// {
//     assert(line != NULL);
//
//     const char *cursor = line;
//
//     cursor = skip(cursor, " ");
//     cursor = strchr(cursor, ',');
//
//
//     // Q,A>Q',B,L
//     // If A or B > 1, then return error.
//     // If L/N/R something else, return error.
//     // If argument amount wrong, return error.
//     // return 0;
// }
//
// #define LINE_BUFFER_SIZE 256

int main(void)
{
    const char *file = "../config.tm";

    const Result_String_Int contentResult = File_getContent(file);
    if (contentResult.type == RESULT_TYPE_ERROR)
    {
        switch (contentResult.error)
        {
        case FILE_ERROR_ERRNO:
            fprintf(stderr, "Reading file failed: %s.", strerror(errno));
            break;
        default:
            fprintf(stderr, "Reading file failed. Error code: %d.", contentResult.error);
            break;
        }

        return EXIT_FAILURE;
    }

    const String content = contentResult.ok;
    printf("Result: %s\n", content.value);

    return EXIT_SUCCESS;
}