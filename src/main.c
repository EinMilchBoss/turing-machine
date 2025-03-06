#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "dtm.h"

int parse_state(state_t *state, const char *line, const char *tag, const size_t tag_length) {
    // + 1 for the ':' at the end.
    const char *start_value = line + tag_length + 1;
    *state = string_to_uint8(start_value);

    if (*state == UINT8_MAX) {
        fprintf(stderr, "'%s' could not be parsed. Did you use a valid number from 0 to %hhu?\n", tag, UINT8_MAX - 1);
        return EXIT_FAILURE;
    }

    printf("Parsed '%s' successfully.\n", tag);
    return EXIT_SUCCESS;
}

int parse_states_amount(state_t *state, const char *line, const char *tag, const size_t tag_length) {
    if (parse_state(state, line, tag, tag_length))
        return EXIT_FAILURE;

    if (*state == 0) {
        fprintf(stderr, "'states' is set to illegal value 0.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

char* parse_alphabet(const char *line) {
    // There will be more logic than this in the future.
    return (char*)line;
}

char *string_slice_to_string(const char *string_slice, const size_t string_slice_length) {
    char *string = calloc(string_slice_length + 1, sizeof(*string));
    strncpy(string, string_slice, string_slice_length);
    return string;
}

int main(void) {
    const char *const states_tag = "states";
    const size_t states_tag_length = strlen(states_tag);

    const char *const start_tag = "start";
    const size_t start_tag_length = strlen(start_tag);

    const char *const accept_tag = "accept";
    const size_t accept_tag_length = strlen(accept_tag);

    const char *const reject_tag = "reject";
    const size_t reject_tag_length = strlen(reject_tag);

    const char *const alphabet_tag = "alphabet";
    const size_t alphabet_tag_length = strlen(alphabet_tag);

    char content[] =
        "states:5\n"
        "start:0\n"
        "accept:3\n"
        "be for real"
        "reject:4\n"
        "alphabet:01"
        "0,0=0,1,>";

    struct dtm dtm = {0};

    char *strtok_save = NULL;
    const char *line = strtok_r(content, "\n", &strtok_save);
    for (size_t line_number = 1; line; line_number++) {
        // Ignore empty lines.
        if (strlen(line) == 0)
            continue;

        if (strncmp(line, states_tag, states_tag_length) == 0) {
            if (parse_states_amount(&dtm.states_amount, line, states_tag, states_tag_length))
                return EXIT_FAILURE;
        } else if (strncmp(line, start_tag, start_tag_length) == 0) {
            if (parse_state(&dtm.start_state, line, start_tag, start_tag_length))
                return EXIT_FAILURE;
        } else if (strncmp(line, accept_tag, accept_tag_length) == 0) {
            if (parse_state(&dtm.accept_state, line, accept_tag, accept_tag_length))
                return EXIT_FAILURE;
        } else if (strncmp(line, reject_tag, reject_tag_length) == 0) {
            if (parse_state(&dtm.reject_state, line, reject_tag, reject_tag_length))
                return EXIT_FAILURE;
        } else if (strncmp(line, alphabet_tag, alphabet_tag_length) == 0) {
            // + 1 for the ':' at the end.
            dtm.alphabet = (char*)line + alphabet_tag_length + 1;
        } else {
            // if (parse_transition(dtm.transitions))
            //     return EXIT_FAILURE;
        }

        line = strtok_r(NULL, "\n", &strtok_save);
    }

    return EXIT_SUCCESS;
}
