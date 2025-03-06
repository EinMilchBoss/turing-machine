//
// Created by Simon Liebsch on 09.02.25.
//

#include "transition.h"

#include "flow.h"

TransitionDirection TransitionDirection_fromChar(const char c)
{
    switch (c)
    {
    case 'L':
        return TRANSITION_DIRECTION_LEFT;
    case 'N':
        return TRANSITION_DIRECTION_NEUTRAL;
    case 'R':
        return TRANSITION_DIRECTION_RIGHT;

    default:
        // TODO: Try to manage this with a return value instead.
        PANIC_MESSAGE("The input file contained a line with an invalid transition direction.");
        return 0;
    }
}
