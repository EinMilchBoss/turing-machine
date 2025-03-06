#ifndef DTM_H
#define DTM_H

#include <stdint.h>

const extern int8_t MOVE_LEFT;
const extern int8_t MOVE_NEUTRAL;
const extern int8_t MOVE_RIGHT;

typedef uint8_t state_t;

struct transition {
    state_t src_state;
    state_t dst_state;
    char src_symbol;
    char dst_symbol;
    int8_t move;
};

struct dtm {
    state_t states_amount;
    state_t start_state;
    state_t accept_state;
    state_t reject_state;

    char *alphabet;

    struct transition *transitions;
};

uint8_t string_to_uint8(const char *string);
int parse_transition(struct transition *transition, const char *line);

#endif //DTM_H
