#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "file.h"
#include "result.h"

int main(void)
{
    const char *file = "../config.tm";

    const Result_String_Int contentResult = File_getContent(file);
    if (contentResult.type == RESULT_TYPE_ERROR)
    {
        switch (contentResult.error)
        {
        case FILE_ERROR_ERRNO:
            fprintf(stderr, "Reading file failed: %s.\n", strerror(errno));
            break;
        default:
            fprintf(stderr, "Reading file failed. Error code: %d.\n", contentResult.error);
            break;
        }

        return EXIT_FAILURE;
    }

    String content = contentResult.ok;
    printf("Result: %s\n", content.cString);

    List_String lines = String_split(content, '\n');
    for (size_t i = 0; i < lines.size; i++)
    {
        printf("Line: %s\n", lines.values[i].cString);
    }
    List_String_delete(&lines);

    String_delete(&content);

    return EXIT_SUCCESS;
}
