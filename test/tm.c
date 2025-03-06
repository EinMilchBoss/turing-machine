#include <string.h>
#include <assert.h>

#include "../tm.h"

void test_dtm_transition_from_string(struct dtm_transition expected, const char *input_string) {
    struct dtm_transition transition = {0};

    enum tm_result result = dtm_transition_from_string(input_string, &transition);
    assert(result == TM_SUCCESS, "Result is not SUCCESS.");
    assert(memcmp(&transition, &expected, sizeof(struct dtm_transition)) == 0);
}

int main(void)
{
    assert(1);

    return 0;
}