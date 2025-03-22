#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dtm.h"

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

int parse_state(uint8_t *state, const char *line, const char *tag, const size_t tag_length) {
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

int parse_states_amount(uint8_t *state, const char *line, const char *tag, const size_t tag_length) {
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

int main(void) {
    struct dtm dtm = {0};

    FILE *file = fopen("config.tm", "rb");
    if (!file)
        return EXIT_FAILURE;

    char *line = NULL;
    size_t line_capacity = 0;
    ssize_t line_length = 0;
    size_t line_number = 1;
    while ((line_length = getline(&line, &line_capacity, file)) != -1) {
        // Replace '\n' with '\0' because the parsing expects C strings (and also for better logging).
        if (!feof(file))
            line[line_length - 1] = 0;
        printf("Reading line %zu: \"%s\"\n", line_number, line);

        // Ignore empty lines.
        if (!*line) {
            printf("Skipped empty line %zu.\n", line_number);
            continue;
        }

        // TODO: Have a uint8_t for flags and flip them to 1 when already parsed.
        // TODO: Then include the check of those bits before the strncmp() call to avoid unnecessary calls.
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
            // TODO: Actually parse the alphabet.
            // + 1 for the ':' at the end.
            dtm.alphabet = (char*)line + alphabet_tag_length + 1;
            printf("Parsed 'alphabet' successfully.\n");
        } else {
            if (dtm.transition_size >= TRANSITIONS_MAX)
                return EXIT_FAILURE;

            if (parse_transition(&dtm.transitions[dtm.transition_size], line))
                return EXIT_FAILURE;

            printf("Parsed transition %zu.\n", dtm.transition_size + 1);
            dtm.transition_size++;
        }

        line_number++;
    }

    return EXIT_SUCCESS;
}
