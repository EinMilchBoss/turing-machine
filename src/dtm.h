#ifndef DTM_H
#define DTM_H

#include <stdlib.h>
#include <stdint.h>

#define TRANSITIONS_MAX 128

const extern int8_t MOVE_LEFT;
const extern int8_t MOVE_NEUTRAL;
const extern int8_t MOVE_RIGHT;

struct transition {
    uint8_t src_state;
    uint8_t dst_state;
    char src_symbol;
    char dst_symbol;
    int8_t move;
};

struct dtm {
    uint8_t states_amount;
    uint8_t start_state;
    uint8_t accept_state;
    uint8_t reject_state;

    char *alphabet;

    struct transition transitions[TRANSITIONS_MAX];
};

uint8_t string_to_uint8(const char *string);
int parse_transition(struct transition *transition, const char *line);

#endif //DTM_H
