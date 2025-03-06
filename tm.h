#ifndef TM_H
#define TM_H

#include <stdlib.h>

enum tm_result {
    TM_SUCCESS,
};

enum dtm_move {
    LEFT    = -1,
    NEUTRAL = 0,
    RIGHT   = 1,
};

/**
 * Transition of a Deterministic Turing Machine.
 */
struct dtm_transition {
    char src_symbol;
    char dst_symbol;
    uint16_t src_state;
    uint16_t dst_state;
    enum dtm_move move;
};

/**
 * Deterministic Turing Machine.
 */
struct dtm {
    uint16_t states_amount;
    uint16_t start_state;
    uint16_t acc_state;
    uint16_t rej_state;

    char *alphabet;
    size_t alphabet_size;

    char *band_cells;
    size_t band_size;

    struct dtm_transition *transitions;
    size_t transitions_size;
};

enum tm_result dtm_transition_from_string(const char *string, struct dtm_transition *out);

#endif //TM_H
