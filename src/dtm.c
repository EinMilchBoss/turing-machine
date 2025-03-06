#include "dtm.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

const int8_t MOVE_LEFT = -1;
const int8_t MOVE_NEUTRAL = 0;
const int8_t MOVE_RIGHT = 1;

/**
 * Returns UINT8_MAX if the value could not be parsed.
 */
uint8_t string_to_uint8(const char *string) {
    if (!string)
        return UINT8_MAX;

    const size_t string_length = strlen(string);
    if (string_length == 0 || string_length > 3)
        return UINT8_MAX;

    uint8_t result = 0;
    uint8_t multiplier = 1;
    for (size_t i = 0; i < string_length; i++) {
        const size_t index_from_back = string_length - (i + 1);
        const char digit_char = string[index_from_back];
        if (digit_char < '0' || '9' < digit_char)
            return UINT8_MAX;

        const uint8_t digit = (uint8_t)digit_char - '0';
        const uint16_t new_result = result + multiplier * digit;
        if (new_result > UINT8_MAX)
            return UINT8_MAX;

        result = (uint8_t)new_result;
        multiplier *= 10;
    }

    return result;
}

int parse_transition(struct transition *transition, const char *line) {
    const char *value = line;
    const char *delimiter = NULL;
    size_t value_length = 0;
    char *value_string = NULL;

    delimiter = strchr(value, ',');
    value_length = (size_t)(delimiter - value);

    value_string = calloc(value_length + 1, sizeof(*value_string));
    strncpy(value_string, value, value_length);
    transition->src_state = string_to_uint8(value_string);
    free(value_string);

    if (transition->src_state == UINT8_MAX)
        return EXIT_FAILURE;

    value = delimiter + 1;

    delimiter = strchr(value, '=');
    value_length = (size_t)(delimiter - value);
    if (value_length != 1)
        return EXIT_FAILURE;

    transition->src_symbol = *value;
    // TODO: Check if symbol is in alphabet.

    value = delimiter + 1;

    delimiter = strchr(value, ',');
    value_length = (size_t)(delimiter - value);

    value_string = calloc(value_length + 1, sizeof(*value_string));
    strncpy(value_string, value, value_length);
    transition->dst_state = string_to_uint8(value_string);
    free(value_string);

    if (transition->dst_state == UINT8_MAX) {
        return EXIT_FAILURE;
    }

    value = delimiter + 1;

    delimiter = strchr(value, ',');
    value_length = (size_t)(delimiter - value);
    if (value_length != 1)
        return EXIT_FAILURE;

    transition->dst_symbol = *value;
    // TODO: Check if symbol is in alphabet.

    value = delimiter + 1;

    delimiter = strchr(value, '\0');
    value_length = (size_t)(delimiter - value);
    if (value_length != 1)
        return EXIT_FAILURE;

    switch (*value) {
    case '<':
        transition->move = MOVE_LEFT;
        break;
    case '-':
        transition->move = MOVE_NEUTRAL;
        break;
    case '>':
        transition->move = MOVE_RIGHT;
        break;
    default:
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}