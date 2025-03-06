#ifndef TRANSITION_H
#define TRANSITION_H

#include "string.h"

typedef enum
{
    TRANSITION_DIRECTION_LEFT = -1,
    TRANSITION_DIRECTION_NEUTRAL = 0,
    TRANSITION_DIRECTION_RIGHT = 1,
} TransitionDirection;

TransitionDirection TransitionDirection_fromChar(char c);

typedef struct
{
    char srcChar;
    char dstChar;
    TransitionDirection direction;
    struct _String srcState;
    struct _String dstState;
} Transition;

#endif //TRANSITION_H
