#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/dtm.h"

void test_string_to_uint8() {
    // Bad input.
    assert(string_to_uint8(NULL) == UINT8_MAX);
    assert(string_to_uint8("") == UINT8_MAX);
    assert(string_to_uint8("a") == UINT8_MAX);
    assert(string_to_uint8("-1") == UINT8_MAX);

    // Bounds.
    assert(string_to_uint8("0") == 0);
    assert(string_to_uint8("255") == 255);

    // Overflow.
    assert(string_to_uint8("256") == UINT8_MAX);
    assert(string_to_uint8("1024") == UINT8_MAX);
    assert(string_to_uint8("2048") == UINT8_MAX);
    assert(string_to_uint8("1000000") == UINT8_MAX);
}

void assert_parse_transition(const struct transition expected, const char *const input) {
    struct transition actual = {0};
    assert(!parse_transition(&actual, input));
    assert(actual.src_state == expected.src_state);
    assert(actual.src_symbol == expected.src_symbol);
    assert(actual.dst_state == expected.dst_state);
    assert(actual.dst_symbol == expected.dst_symbol);
    assert(actual.move == expected.move);
}

void test_parse_transition() {
    // Symbols.
    assert_parse_transition(
        (struct transition){
            .src_symbol = '1',
            .dst_symbol = '2'
        },
        "0,1=0,2,-"
    );

    // Moves.
    assert_parse_transition(
        (struct transition){
            .src_state = 0,
            .src_symbol = '0',
            .dst_state = 0,
            .dst_symbol = '0',
            .move = MOVE_LEFT
        },
        "0,0=0,0,<"
    );
    assert_parse_transition(
            (struct transition){
                .src_state = 0,
                .src_symbol = '0',
                .dst_state = 0,
                .dst_symbol = '0',
                .move = MOVE_NEUTRAL
            },
            "0,0=0,0,-"
        );
    assert_parse_transition(
        (struct transition){
            .src_state = 0,
            .src_symbol = '0',
            .dst_state = 0,
            .dst_symbol = '0',
            .move = MOVE_RIGHT
        },
        "0,0=0,0,>"
    );
}

int main(void) {
    test_string_to_uint8();
    test_parse_transition();

    return 0;
}
