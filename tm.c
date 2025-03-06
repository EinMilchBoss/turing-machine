#include "tm.h"

#include <stdbool.h>
#include <string.h>

#include "flow.h"

enum tm_result dtm_transition_from_string(char *string) {
    return TM_SUCCESS;
}

/**
 * Remove duplicate values from alphabet.
 */
static char* deduplicate_alphabet(const char *alphabet, const size_t alphabet_size) {
    char *deduplicated = calloc(alphabet_size, sizeof(*deduplicated));
    if (!deduplicated)
        PANIC_FORMAT("Could not allocate %ull bytes for deduplicated alphabet.", alphabet_size);

    size_t deduplicated_index = 0;

    for (size_t i = 0; i < alphabet_size; i++) {
        bool is_new = true;

        for (size_t j = 0; j < i; j++) {
            if (alphabet[i] == alphabet[j]) {
                is_new = false;
                break;
            }
        }

        if (is_new) {
            deduplicated[deduplicated_index] = alphabet[i];
            deduplicated_index++;
        }
    }

    return deduplicated;
}

/**
 * Alphabet mustn't contain the letter '#' as this is the reserved letter for empty cells.
 */
static bool is_alphabet_valid(const char *alphabet) {
    for (const char *symbol = alphabet; *symbol; symbol++) {
        if (*symbol == '#')
            return false;
    }

    return true;
}

/**
 * Transitions are valid, if there aren't any overlaps with the same source values.
 *
 * Acceptance and rejection states are not allowed to be on the source side.
 */
static bool are_transitions_valid(
    const struct dtm_transition *transitions,
    const size_t transitions_size,
    const uint16_t acc_state,
    const uint16_t rej_state
) {
    for (size_t i = 0; i < transitions_size; i++) {
        if (transitions[i].src_state == acc_state || transitions[i].src_state == rej_state) {
            // Illegal state.
            return false;
        }

        for (size_t j = 0; j < i; j++) {
            if (
                transitions[i].src_state == transitions[j].src_state &&
                transitions[i].src_symbol == transitions[j].src_symbol
            ) {
                // Non-deterministic.
                return false;
            }
        }
    }

    return true;
}

/**
 * The input must only contain characters from the alphabet and additionally '#'.
 */
static bool is_input_valid(
    const char *input,
    const size_t input_length,
    const char *alphabet,
    const size_t alphabet_size
) {
    for (size_t i = 0; i < input_length; i++) {
        if (input[i] == '#')
            continue;

        bool is_missing = true;

        for (size_t j = 0; j < alphabet_size; j++) {
            if (input[i] == alphabet[j]) {
                is_missing = false;
                break;
            }
        }

        if (is_missing)
            return false;
    }

    return false;
}

/**
 * Initializes the band's cells with the input.
 *
 * If the input is NULL, the band stays empty and true will be returned.
 *
 * If the input size is bigger than the band itself, the input will not be set and false will be returned.
 */
static bool initialize_band(char *band_cells, const size_t band_size, const char *input, const size_t input_length) {
    if (!input)
        return true;

    if (input_length > band_size)
        return false;

    memcpy(band_cells, input, input_length);
}

enum tm_result dtm_create(
    const size_t states_amount,
    uint16_t start_state,
    uint16_t acc_state,
    uint16_t rej_state,
    size_t band_size,
    const char *alphabet,
    const char *input,
    struct dtm *out
) {
    const size_t alphabet_size = strlen(alphabet);
    char *deduplicated_alphabet = deduplicate_alphabet(alphabet, alphabet_size);

    char *band_cells = malloc(band_size * sizeof(*band_cells));
    if (!band_cells)
        PANIC_FORMAT("Could not allocate %ull bytes for band.", band_size);
    memset(band_cells, '#', band_size);

    const size_t input_length = strlen(input);
    if (!initialize_band(band_cells, band_size, input, input_length)) {
        return 0; // TODO
    }

    *out = (struct dtm){
        .states_amount = states_amount,
        .start_state = start_state,
        .acc_state = acc_state,
        .rej_state = rej_state,

        .alphabet = deduplicated_alphabet,
        .alphabet_size = alphabet_size,

        .band_cells = band_cells,
        .band_size = band_size,
    };

    return TM_SUCCESS;
}
